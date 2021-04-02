class WSClient {
	
	constructor(ip, endpoint) {
		this.address=ip;
		this.message = '0';
		const conditionalBar = endpoint.startsWith('/') ? '' : '/';
		console.log('connecting to ' + "ws://" + ip + conditionalBar + endpoint);
		this.socket = new WebSocket("ws://" + ip + ":81" + conditionalBar + endpoint);
		this.socket.onmessage = (ev) => {
			this.message = ev.data;
		}
		this.socket.onopen = (ev) => {
			console.log(ev)
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

class Input {
	constructor() {
		this.inputs = {};
		Object.keys(InputEnum).forEach((keyName) => {
			this.inputs[keyName] = false; 
		});

		document.addEventListener('keydown', (event) => {
			if(this.inputs[event.key] !== undefined) {
				this.inputs[event.key] = true;
			}
			event.preventDefault();
		});
		document.addEventListener('keyup', (event) => {
			if(this.inputs[event.key] !== undefined) {
				this.inputs[event.key] = false;
			}
			event.preventDefault();
		});
	}
}

class Core {

	constructor() {
		this.interval = 100;
		this.lastVal = 0;
		this.lastValB = 0;
		this.accelerationInput = document.querySelector('#acceleration-input');
		this.accelerationInput.setAttribute('max', 1);
		this.accelerationInput.setAttribute('min', -1);
		this.accelerationInput.setAttribute('step', '0.1');
		this.accelerationInput.value =0;

		this.steeringInput = document.querySelector('#steering-input');
		this.steeringInput.setAttribute('max', 1);
		this.steeringInput.setAttribute('min', -1);
		this.steeringInput.setAttribute('step', '0.1');
		this.steeringInput.value = 0;

		const clientIP = '192.168.0.37';
		this.client = new WSClient(clientIP, '');
		//this.accelerationClient = new WSClient(clientIP, '/acceleration');
		//this.extrasClient = new WSClient(clientIP, '/extras');
		//this.extrasClient = new WSClient(clientIP, '/configure');

		this.input = new Input();		

	}
	
	loop() {
		setInterval(() => {
			this.gamepad = navigator.getGamepads()[0];
			if(this.gamepad) {
				const val = this.gamepad.axes[1];
				const valB = this.gamepad.axes[2];
				// if(this.input.inputs.ArrowDown) {
				// 	this.accelerationInput.value = val;
				// }
				// if(this.input.inputs.ArrowUp) {
				// 	this.accelerationInput.value = val;
				// }
	
				if(val != this.lastVal) {
					this.lastVal = val;
					this.client.send("a:" + val.toPrecision(1));
				}
	
				if(valB != this.lastValB) {
					this.lastValB = valB;
					this.client.send("s:" + valB.toPrecision(1));
				}
			} else {
				const val = this.steeringInput.value;

	
				if(val != this.lastVal) {
					this.lastVal = val;
					this.client.send("s:" + val.toPrecision(1));
				}
			}

		}, this.interval);
	}
}

window.onload = function() {
	const core = new Core();
	core.loop();
}
