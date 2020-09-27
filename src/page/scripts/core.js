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
		// if(this.socket.OPEN) this.socket.send(data); 
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
		this.velocityInput = document.querySelector('#velocity-input');
		this.velocityInput.setAttribute('max', 1024);
		this.velocityInput.setAttribute('min', 0);
		this.velocityInput.setAttribute('value', 1024 / 2);

		const clientIP = '192.168.0.37';
		this.steeringClient = new WSClient(clientIP, '');
		this.velocityClient = new WSClient(clientIP, '/velocity');
		this.extrasClient = new WSClient(clientIP, '/extras');
		this.extrasClient = new WSClient(clientIP, '/configure');

		this.input = new Input();		

	}
	
	loop() {
		setInterval(() => {
			const val = parseInt(this.velocityInput.value);
			if(this.input.inputs.ArrowDown) {
				this.velocityInput.value = val - 100;
			}
			if(this.input.inputs.ArrowUp) {
				this.velocityInput.value = val + 100;
			}
		}, this.interval);

		setInterval(() => {
			//this.steeringClient.send(this.steeringClient.value);
			console.log('velClient: ' + this.steeringClient.message);
		}, this.interval);
	}
}

window.onload = function() {
	const core = new Core();
	core.loop();
}
