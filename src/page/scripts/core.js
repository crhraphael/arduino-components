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
		this.accelerationInput = document.querySelector('#acceleration-input');
		this.accelerationInput.setAttribute('max', 1024);
		this.accelerationInput.setAttribute('min', 0);
		this.accelerationInput.setAttribute('value', 1024 / 2);

		const clientIP = '192.168.0.38';
		this.steeringClient = new WSClient(clientIP, '');
		//this.accelerationClient = new WSClient(clientIP, '/acceleration');
		//this.extrasClient = new WSClient(clientIP, '/extras');
		//this.extrasClient = new WSClient(clientIP, '/configure');

		this.input = new Input();		

	}
	
	loop() {
		setInterval(() => {
			const val = parseInt(this.accelerationInput.value);
			if(this.input.inputs.ArrowDown) {
				this.accelerationInput.value = val;
			}
			if(this.input.inputs.ArrowUp) {
				this.accelerationInput.value = val;
			}

			if(val != this.lastVal) {
				this.lastVal = val;
				this.steeringClient.send(val);
			}
		}, this.interval);
	}
}

window.onload = function() {
	const core = new Core();
	core.loop();
}
