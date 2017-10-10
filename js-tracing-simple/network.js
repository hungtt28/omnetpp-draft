class Application {

    constructor(canvas_id, pointer_id, target_id) {
        this.canvas_id = canvas_id;
        this.pointer_id = pointer_id;
        this.target_id = target_id;
        this.canvas = null;
        this.pointer = null;
		this.scale = 0;
		this.lineWidth = 0;
		this.node_size = 0;
		this.network = null;
    }
    
    load_app() {
        this.canvas = document.getElementById(this.canvas_id);
        this.pointer = document.getElementById(this.pointer_id);
        var ctx = this.canvas.getContext('2d');
        ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);
    }

    draw_networkMap(network) {
		this.network = network;
        var width = this.canvas.width;
        var height = this.canvas.height;
		
        var row_height = height / (network.maprect.top - network.maprect.bottom);
        var col_width = width / (network.maprect.right - network.maprect.left);
		this.scale = row_height < col_width ? row_height : col_width;
		this.node_size = this.scale / 10;
		this.lineWidth = this.scale / 30;
        var ctx = this.canvas.getContext('2d');
		ctx.translate(-network.maprect.left * this.scale, network.maprect.top * this.scale);
		// ctx.translate(0, height)
		ctx.scale(1, -1);
		// draw node
        for(var i = 0; i < network.nodes.length; i++) {
			var node = network.nodes[i];
			ctx.beginPath();
			ctx.arc(node.coord.x * this.scale, node.coord.y * this.scale, this.node_size, 0, 2*Math.PI);
			ctx.strokeStyle="green";
			ctx.fillStyle = "green";
			ctx.fill();
			ctx.stroke();
        }
		// draw connection
		for (var i = 0; i < network.connection.length; i++) {
			var connection = network.connection[i];
			var src = network.getNode(connection.src);
			var des = network.getNode(connection.des);
			ctx.beginPath();
			ctx.lineWidth = this.lineWidth;
			ctx.moveTo(src.coord.x * this.scale, src.coord.y * this.scale);
			ctx.lineTo(des.coord.x * this.scale, des.coord.y * this.scale);
			ctx.strokeStyle="#555";
			ctx.stroke();
		}
    }

	path_animation(x, y) {
		var ctx = this.canvas.getContext('2d');
		ctx.lineTo(x, y);
		ctx.stroke();
		this.pointer.style.transform = 'translate('+x+'px, '+(this.canvas.height - y)+'px)';
        return new Promise(resolve => {
            setTimeout(function() {
                resolve();
            }, 1000/60);
        });
	}
	
	async draw_path(curAddr, nextAddr) {
		var curNode = this.network.getNode(curAddr);
        var curX = (curNode.coord.x) * this.scale;
        var curY = (curNode.coord.y) * this.scale;
		
		var nextNode = this.network.getNode(nextAddr);
        var nextX = (nextNode.coord.x) * this.scale;
        var nextY = (nextNode.coord.y) * this.scale;
        
		var nIter = 40;
		var stepX = (nextX - curX) / nIter;
		var stepY = (nextY - curY) / nIter;
		
		var ctx = this.canvas.getContext('2d');
		ctx.beginPath();
		ctx.strokeStyle = '#ff0000';
		ctx.moveTo(curX, curY);
		for (var i = 0; i < nIter; i++)
			await this.path_animation(curX + i * stepX, curY + i * stepY);
		await this.path_animation(nextX, nextY);
        
        this.pointer.style.transform = 'translate('+nextX+'px, '+(this.canvas.height - nextY)+'px)';
        return new Promise(resolve => {
            setTimeout(function() {
                resolve();
            }, 1000/600);
        });
	}
	
	async draw_trace(path) {
		var srcNode = this.network.getNode(path[0]);
        var x = (srcNode.coord.x) * this.scale;
        var y = (srcNode.coord.y) * this.scale;
		
        var ctx = this.canvas.getContext('2d');
		ctx.beginPath();
		ctx.strokeStyle = '#ff0000';
		ctx.moveTo(x, y);
		ctx.stroke();
		for (var i = 0; i < path.length-1; i++)
			await this.draw_path(path[i], path[i+1]);
	}
	
    begin() {
        var ctx = this.canvas.getContext('2d');
        ctx.beginPath();
    }

    finish() {
        var ctx = this.canvas.getContext('2d');
        ctx.stroke();
    } 
}

class Coordinate {
	constructor(x, y) {
		this.x = x;
		this.y = y;
	}
}

class Node {
	constructor(node) {
		this.address = node.address;
		this.coord = node.coord;
		this.range = node.range;
		this.neighbor = node.neighbor;
	}
	
	addNeighbor(address) {
		this.neighbor.push(address);
	}
}

class Connection {
	constructor(src, des) {
		this.src = src;
		this.des = des;
	}
}

class NetworkMap {
	constructor(networkJson) {
		this.nodes = [];
		this.maprect = {};
		this.connection = [];
		this.buildNetwork(networkJson);
	}
	
	buildNetwork(networkJson) {
		var info = JSON.parse(networkJson);
		for (var i = 0; i < info.nodes.length; i++) {
			this.nodes.push(new Node(info.nodes[i]));
		}
		this.maprect = info.maprect;
		this.updateConnection();
	}
	
	updateConnection() {
		for (var i = 0; i < this.nodes.length; i++) {
			var node = this.nodes[i];
			for (var j = 0; j < node.neighbor.length; j++) {
				var neighborAddr = node.neighbor[j];
				this.connection.push(new Connection(node.address, neighborAddr));
			}
		}
	}
	
	isConnected(addr1, addr2) {
	}
	
	addNode(node) {
		this.nodes.push(node);
	}
	
	getNode(address) {
		for (var i = 0; i < this.nodes.length; i++) {
			if (this.nodes[i].address == address)
				return this.nodes[i];
		}
	}
}