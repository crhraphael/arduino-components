class ConsoleOutput {
	constructor() {
		this.consoleElement = document.querySelector('#console-output');
	}

	write(val) {
		this.consoleElement.innerHTML += val + "<br>";
	}

	clear() {
		this.consoleElement.innerHTML = "";
	}
}

function bootstrap() {
	const consoleOutput = new ConsoleOutput();
	
	class WSClient {
	
		constructor(ip, endpoint) {
			this.address = ip;
			this.message = '';

			const conditionalBar = endpoint.startsWith('/') ? '' : '/';
			const fullAddress = "ws://" + ip + ":81" + conditionalBar + endpoint;
			
			const connectingMsg = 'connecting to ' + fullAddress + '...';
			const connectionFailedMsg = 'can’t establish a connection to the server at ' + fullAddress + '...';

			console.log(connectingMsg);
			consoleOutput.write(connectingMsg);

			this.socket = new WebSocket(fullAddress);
			this.socket.onmessage = (ev) => {
				this.message = ev.data;

			}
			this.socket.onerror = (ev) => {
				consoleOutput.write(connectionFailedMsg);
			}
			this.socket.onopen = (ev) => {
				console.log(ev);
				consoleOutput.write('oppened connection with ' + ev.originalTarget.url);
			}
		}
		
		send(data) {
			if(this.socket.readyState == WebSocket.OPEN) this.socket.send(data); 
		}
	
		listen() {
			return this.message;
		}
	}
	
	const InputEnum = {
		ArrowDown: 'ArrowDown',
		ArrowUp: 'ArrowUp'
	}



	class AInput {
		constructor() {
			this.input = undefined;
			this.oldValue = undefined;
		}
		GetValue() {
			return this.input.value;
		}

		SetValue(val) {
			this.input.value = val;
		}

		SetOldValue(val) {
			this.oldValue = val;
		}

		HasChanged() {
			return this.input.value != this.oldValue
		}
		GetOldValue() {
			return this.oldValue;
		}
	}
	class AccelerationInput extends AInput {
		constructor() {
			super();
			this.input = document.querySelector('#acceleration-input');
			this.input.setAttribute('max', 1);
			this.input.setAttribute('min', -1);
			this.input.setAttribute('step', '0.1');
			this.input.value = 0;
			this.oldValue = this.input.value;
		}
	}
	class SteeringInput extends AInput {
		constructor() {
			super();
			this.input = document.querySelector('#steering-input');
			this.input.setAttribute('max', 1);
			this.input.setAttribute('min', -1);
			this.input.setAttribute('step', '0.1');
			this.input.value = 0;
			this.oldValue = this.input.value;
		}
	}

	class InputController {
		constructor() {
			this.inputs = {};
			Object.keys(InputEnum).forEach((keyName) => {
				this.inputs[keyName] = false; 
			});
	
			document.addEventListener('keydown', (event) => {
				if(this.inputs[event.key] !== undefined) {
					this.inputs[event.key] = true;
					event.preventDefault();
				}
			});
			document.addEventListener('keyup', (event) => {
				if(this.inputs[event.key] !== undefined) {
					this.inputs[event.key] = false;
					event.preventDefault();
				}
			});
		}
	}

	class GamepadController {
		constructor(inputs = {
			acceleration: null,
			steering: null
		}) {
			this.stateEnum = {
				ENABLED: 'enabled',
				DISABLED: 'disabled'
			};

			this.inputs = inputs;
			
			this.input = document.querySelector('#gamepad-enable-btn');
			this.label = document.querySelector('#gamepad-enable-status-lbl');

			this.isEnabled = this.gamepad && this.input.getAttribute('data-value') == this.stateEnum.ENABLED;

			this.input.addEventListener('click', this.onClick.bind(this));
			window.addEventListener('gamepadconnected', this.onConnect.bind(this));
			this.axleL = 0;
			this.axleR = 0;
		}

		onConnect(ev) {
				console.log("Gamepad connected at index %d: %s. %d buttons, %d axes.",
					ev.gamepad.index, ev.gamepad.id,
					ev.gamepad.buttons.length, ev.gamepad.axes.length);

				this.gamepad = ev.gamepad
		}

		onClick(ev) {
			this.isEnabled = this.gamepad && !this.isEnabled;

			const msg = this.isEnabled 
				? this.stateEnum.ENABLED
				: this.stateEnum.DISABLED

			this.label.innerHTML = msg;
		}

		update() {
			if(!this.isEnabled) return;

			this.axleL = this.gamepad.axes[0].toPrecision(2);
			this.axleR = this.gamepad.axes[4].toPrecision(2) * -1;

			this.inputs.steering.SetValue(this.axleL);			
			this.inputs.acceleration.SetValue(this.axleR);
		}


	}
	

	
	class Core {
	
		constructor() {
			this.interval = 10;

			this.accelerationInput = new AccelerationInput();	
			this.steeringInput = new SteeringInput();
	
			this.connection = false;
			this.gamepadController = new GamepadController({
				acceleration: this.accelerationInput,
				steering: this.steeringInput,
			});

			this.connectBtn = document.querySelector("#connect-to-btn");
			this.connectBtn.addEventListener('click', this.connect.bind(this));
		}
		
		connect() {
			const clientIP = document.querySelector("#car-ip").value;
			const endpoint = '';

			this.connection = true;

			this.client = new WSClient(clientIP, endpoint);
		}

		loop() {
			this.gamepadController.update();
			if(!this.connection) return;

			if(this.accelerationInput.HasChanged()) {
				const accelValue = this.accelerationInput.GetValue();	
				this.accelerationInput.SetOldValue(accelValue);
				this.client.send("a:"+accelValue);
			}
	
			if(this.steeringInput.HasChanged()) {
				const steerValue = this.steeringInput.GetValue();
				this.steeringInput.SetOldValue(steerValue);
				this.client.send("s:"+steerValue);
			}	
		}
	}
	


	const core = new Core();
	//core.loop();

	setInterval(core.loop.bind(core), 10);
}

window.onload = bootstrap;
