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
class GamePad {
	constructor() {
		this.gamepad = navigator.getGamepads()[0]
		this.isEnabled = false;
		setInterval(() => {
			if(this.gamepad) return;
			this.gamepad = navigator.getGamepads()[0]
		}, 1000);
	}
	Enable() {
		this.isEnabled = true;

	}
	Disable() {
		this.isEnabled = false;
	}

	IsEnabled() {
		return this.isEnabled;
	}
	IsPlugged() {
		return this.gamepad
	}

	GetLeftAxleValue(precision) {
		return this.gamepad.axes[1].toPrecision(precision)
	}
	GetRightAxleValue(precision) {
		return this.gamepad.axes[2].toPrecision(precision)
	}
}

function bootstrap() {
	const consoleOutput = new ConsoleOutput();
	const gamepad = new GamePad();
	
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

		SetOldValue(val) {
			this.oldValue = val;
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

		GetGamePadValue() {
			return gamepad.GetLeftAxleValue(2);
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

		GetGamePadValue() {
			return gamepad.GetRightAxleValue(2);
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
	

	
	class Core {
	
		constructor() {
			this.interval = 10;

			this.accelerationInput = new AccelerationInput();	
			this.steeringInput = new SteeringInput();
	
			this.connection = false;
			this.input = new InputController();		
			this.gamepad = navigator.getGamepads()[0];

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
			if(!this.connection) return;
			// this.gamepad = navigator.getGamepads()[0];
			// if(this.gamepad) {
			// 	const val = this.gamepad.axes[1];
			// 	const valB = this.gamepad.axes[2];
			// 	// if(this.input.inputs.ArrowDown) {
			// 	// 	this.accelerationInput.value = val;
			// 	// }
			// 	// if(this.input.inputs.ArrowUp) {
			// 	// 	this.accelerationInput.value = val;
			// 	// }
	
			// 	if(val != this.lastVal) {
			// 		this.lastVal = val;
			// 		this.client.send("a:" + val.toPrecision(1));
			// 	}
	
			// 	if(valB != this.lastValB) {
			// 		this.lastValB = valB;
			// 		this.client.send("s:" + valB.toPrecision(1));
			// 	}
			// } else {
			const accelValue = this.accelerationInput.GetValue();	
			if(accelValue != this.accelerationInput.GetOldValue()) {
				this.accelerationInput.SetOldValue(accelValue);
				this.client.send("a:"+accelValue);
			}
			console.log(this.steeringInput.GetValue())
	
			const steerValue = this.steeringInput.GetValue();
			if(steerValue != this.steeringInput.GetOldValue()) {
				this.steeringInput.SetOldValue(steerValue);
				this.client.send("s:"+steerValue);
			}
			// }
	
		}
	}
	


	const core = new Core();
	//core.loop();

	setInterval(core.loop.bind(core), 10);
}

window.onload = bootstrap;
