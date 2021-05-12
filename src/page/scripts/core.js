/**
 * Panel used to write and clear relevant debuggable data. 
 */
class ConsolePanel {
	constructor(elementId) {
		this.consoleElement = document.querySelector(elementId + ' #console-output');
		this.outputWindow = document.querySelector(elementId + ' #output');
		this.clearBtn = document.querySelector(elementId + ' #clear-console-btn');
		this.clearBtn.addEventListener('click', this.clear.bind(this));
	}

	/**
	 * Writes the value and adds a line-break (<br>) at the end.
	 * 
	 * @param {string} val Value to write into the element.
	 */
	write(val) {
		console.log(val);
		this.outputWindow.innerHTML += val + "<br>";
	}

	/**
	 * Clears the inner HTML.
	 */
	clear() {
		this.outputWindow.innerHTML = "";
	}
}

/**
 * Keeps a reference of every console to easily get them when needed.
 */
class ConsoleManager {
	static consoles = [];
	constructor() {
	}

	/**
	 * Stores a given console within the `ownerId` key.
	 * 
	 * @param {ConsolePanel} aConsole  console to be stored
	 * @param {string} ownerId index key representing it's owner.
	 */
	static register(aConsole, ownerId) {
		this.consoles[ownerId] = aConsole;
	}

	/**
	 * 
	 * @param {string} ownerId 
	 * @returns {ConsolePanel} ConsolePanel
	 */
	static get(ownerId) {
		return this.consoles[ownerId];
	}

	static search(aConsole) {
		return this.consoles.indexOf(aConsole);
	}

	static remove(aConsole) {
		const index = aConsole;
		this.consoles[index] = null; 
	}

	static removeAt(ownerId) {
		this.consoles[ownerId] = null;
	}
}


function bootstrap() {
	const mainConsole = new ConsolePanel('#main-console');
	ConsoleManager.register(mainConsole, '#main-console');
	

	/**
	 * Websocket logic code.
	 */
	class WSClient {	
		constructor(ip, endpoint, ownerId = null) {
			this.address = ip;
			this.message = '';
			this.endpoint = endpoint;
			this.elementId = ownerId;
			this.console = ownerId ? ConsoleManager.get(this.elementId) : mainConsole;

			const conditionalBar = endpoint.startsWith('/') ? '' : '/';
			this.fullAddress = "ws://" + this.address + ":81" + conditionalBar + this.endpoint;
		}

		connect() {
			const connectingMsg = 'connecting to ' + this.fullAddress + '...';

			this.console.write(connectingMsg);

			this.socket = new WebSocket(this.fullAddress);
			this.socket.addEventListener('message', this.onMessage.bind(this));
			this.socket.addEventListener('error', this.onError.bind(this));
			this.socket.addEventListener('open', this.onOpen.bind(this));
		}

		onMessage(ev) {
			this.message = ev.data;
		}
		onError(ev) {
			const connectionFailedMsg = 'can’t establish a connection to the server at ' + fullAddress + '...';
			this.console.write(connectionFailedMsg);
		}
		onOpen(ev) {
			const connectionOppenedMsg = 'oppened connection with ' + ev.originalTarget.url;
			this.console.write(connectionOppenedMsg);
		}
		
		send(data) {
			if(this.socket.readyState == WebSocket.OPEN) this.socket.send(data); 
		}
	}

	/**
	 * Input base abstract class, contains features that 'defines' a user input.
	 */
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

	/**
	 * Specific Acceleration Input class.
	 */
	class AccelerationInput extends AInput {
		constructor(elementId) {
			super();
			this.input = document.querySelector(elementId + ' #acceleration-input');
			this.input.setAttribute('max', 1);
			this.input.setAttribute('min', -1);
			this.input.setAttribute('step', '0.1');
			this.input.value = 0;
			this.oldValue = this.input.value;
		}
	}

	/**
	 * Specific Steering Input class.
	 */
	class SteeringInput extends AInput {
		constructor(elementId) {
			super();
			this.input = document.querySelector(elementId + ' #steering-input');
			this.input.setAttribute('max', 1);
			this.input.setAttribute('min', -1);
			this.input.setAttribute('step', '0.1');
			this.input.value = 0;
			this.oldValue = this.input.value;
		}
	}

	/**
	 * A GamepadController listens to connected gamepads and assigns 
	 * the inputs to the specified DOM input field through the `update` method.
	 */
	class GamepadController {
		constructor(
			elementId,
			inputs = {
				acceleration: null,
				steering: null
			}
		) {
			this.stateEnum = {
				ENABLED: 'enabled',
				DISABLED: 'disabled'
			};

			this.inputs = inputs;
			
			this.input = document.querySelector(elementId + ' #gamepad-enable-btn');
			this.label = document.querySelector(elementId + ' #gamepad-enable-status-lbl');

			this.console = ConsoleManager.get(elementId);
			this.isEnabled = this.gamepad && this.input.getAttribute('data-value') == this.stateEnum.ENABLED;

			this.input.addEventListener('click', this.onClick.bind(this));
			window.addEventListener('gamepadconnected', this.onConnect.bind(this));
			this.axleL = 0;
			this.axleR = 0;
		}

		onConnect(ev) {
			const msg = "Gamepad connected at index " 
				+ ev.gamepad.index 
				+ ": " 
				+ ev.gamepad.id 
				+ ". "
				+ ev.gamepad.buttons.length 
				+ " buttons, " 
				+ ev.gamepad.axes.length 
				+ " axes." 
			
				this.console.write(msg);

				this.gamepad = ev.gamepad
		}

		onClick(ev) {
			this.isEnabled = this.gamepad && !this.isEnabled;

			const status = this.isEnabled 
				? this.stateEnum.ENABLED
				: this.stateEnum.DISABLED
			
			const msg = "Gamepad is " + status;

			this.console.write(msg);

			this.label.innerHTML = status;
		}

		update() {
			if(!this.isEnabled) return;

			this.axleL = this.gamepad.axes[0].toPrecision(2);
			this.axleR = this.gamepad.axes[4].toPrecision(2) * -1;

			this.inputs.steering.SetValue(this.axleL);			
			this.inputs.acceleration.SetValue(this.axleR);
		}


	}
	

	/**
	 * This class represents one controller component.
	 * TODO: This is not a `Core`, name must change.
	 */
	class Core {
	
		constructor(controllerId) {
			this.interval = 10;

			this.elementId = '#vehicle-controller-' + controllerId;

			this.accelerationInput = new AccelerationInput(this.elementId);	
			this.steeringInput = new SteeringInput(this.elementId);

			this.consoleElement = new ConsolePanel(this.elementId);
			ConsoleManager.register(this.consoleElement, this.elementId);
	
			this.connection = false;
			this.gamepadController = new GamepadController(
				this.elementId,
				{
					acceleration: this.accelerationInput,
					steering: this.steeringInput,
				}
			);

			this.connectBtn = document.querySelector(this.elementId + " #connect-to-btn");
			this.connectBtn.addEventListener('click', this.onConnect.bind(this));
		}
		
		onConnect() {
			const clientIP = document.querySelector(this.elementId + " #car-ip").value;
			const endpoint = '';

			this.connection = true;

			this.client = new WSClient(clientIP, endpoint, this.elementId);
			this.client.connect();
		}

		/**
		 * Loop method that goes inside a `setInterval` call.
		 */
		loop() {
			this.gamepadController.update();
			if(!this.connection) return;

			if(this.accelerationInput.HasChanged()) {
				const accelValue = this.accelerationInput.GetValue();	
				this.accelerationInput.SetOldValue(accelValue);
				this.client.send("a:" + accelValue);
			}
	
			if(this.steeringInput.HasChanged()) {
				const steerValue = this.steeringInput.GetValue();
				this.steeringInput.SetOldValue(steerValue);
				this.client.send("s:" + steerValue);
			}	
		}
	}
	


	const core = new Core(0);

	setInterval(core.loop.bind(core), core.interval);
}

window.onload = bootstrap;
