class Emulator {

    constructor(canvas_id, pointer_id, target_id) {
        this.canvas_id = canvas_id;
        this.pointer_id = pointer_id;
        this.target_id = target_id;
        this.canvas = null;
        this.pointer = null;
		this.target = null;
		this.scale = 0;
		this.lineWidth = 0;
		this.node_size = 0;
		this.network = null;
		this.pointer_size = 10;
		this.corner = {x: 0, y: 0};
		this.load_app();
    }
    
    load_app() {
        this.canvas = document.getElementById(this.canvas_id);
        this.pointer = document.getElementById(this.pointer_id);
		this.target = document.getElementById(this.target_id);
        var ctx = this.canvas.getContext('2d');
        ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);
    }

	init(network) {
		this.network = network;
	}
	
    draw_networkMap() {
        var width = this.canvas.width;
        var height = this.canvas.height;
		
        var row_height = height / (this.network.maprect.top - this.network.maprect.bottom);
        var col_width = width / (this.network.maprect.right - this.network.maprect.left);
		this.scale = row_height < col_width ? row_height : col_width;
		this.node_size = this.scale / 10;
		this.lineWidth = this.scale / 30;
		// this.pointer_size = this.scale / 15;
		// this.pointer.style.width = (this.pointer_size).toString()+"px";
		// this.pointer.style.height = (this.pointer_size).toString()+"px";
		
        var ctx = this.canvas.getContext('2d');
		this.corner.x = this.network.maprect.left * this.scale;
		this.corner.y = this.network.maprect.top * this.scale
		ctx.translate(-this.corner.x, this.corner.y);
		// ctx.translate(0, height)
		ctx.scale(1, -1);
		// draw node
        for(var i = 0; i < this.network.nodes.length; i++) {
			var node = this.network.nodes[i];
			ctx.beginPath();
			ctx.arc(node.coord.x * this.scale, node.coord.y * this.scale, this.node_size, 0, 2*Math.PI);
			ctx.strokeStyle="green";
			ctx.fillStyle = "green";
			ctx.fill();
			ctx.stroke();
        }
		// draw connection
		for (var i = 0; i < this.network.connection.length; i++) {
			var connection = this.network.connection[i];
			var src = this.network.getNode(connection.src);
			var des = this.network.getNode(connection.des);
			ctx.beginPath();
			ctx.lineWidth = this.lineWidth;
			ctx.moveTo(src.coord.x * this.scale, src.coord.y * this.scale);
			ctx.lineTo(des.coord.x * this.scale, des.coord.y * this.scale);
			ctx.strokeStyle="#555";
			ctx.stroke();
		}
        for(var i = 0; i < this.network.nodes.length; i++) {
			var node = this.network.nodes[i];
			ctx.save();
			ctx.translate(node.coord.x * this.scale, node.coord.y * this.scale - this.node_size - 1);
			ctx.rotate(Math.PI);
			ctx.scale(-1, 1);
			ctx.fillStyle = "black";
			ctx.font = "20px Arial";
			ctx.fillText(node.address.toString(), 0, 0);
			ctx.stroke();
			ctx.restore();
		}
    }

	path_animation(x, y) {
		var ctx = this.canvas.getContext('2d');
		ctx.lineTo(x, y);
		ctx.stroke();
		this.pointer.style.transform = 'translate('+(x - this.corner.x)+'px, '+(this.corner.y - y)+'px)';
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
        
        this.pointer.style.transform = 'translate('+(nextX - this.corner.x)+'px, '+(this.corner.y - nextY)+'px)';
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
	
	route(node, packet) {
		var curNode = this.network.getNode(node);
		return this.network.routing.findNextHop(curNode, packet);
	}
	
    async routing_trace(src, des) {
		var curHop = src;
		var nextHop = -1;
		var srcNode = this.network.getNode(src);
		
        var x = (srcNode.coord.x) * this.scale;
        var y = (srcNode.coord.y) * this.scale;
        var ctx = this.canvas.getContext('2d');
		ctx.beginPath();
		ctx.strokeStyle = '#ff0000';
		ctx.moveTo(x, y);
		ctx.stroke();
		
		var desNode = this.network.getNode(des);
		this.target.style.transform = 'translate('+(desNode.coord.x * this.scale - this.corner.x)+'px, '+(this.corner.y - desNode.coord.y * this.scale)+'px)';
		
		var packet = this.network.routing.createPacket(des);
		while(1) {
			if (curHop == des)
				break;
			nextHop = this.route(curHop, packet)
			if (nextHop == -1)
				break;
			await this.draw_path(curHop, nextHop);
			curHop = nextHop;
		}
	}
}

class Coord {
	constructor(x, y) {
		this.x = x;
		this.y = y;
	}
	
	distanceTo(coord) {
		return Math.sqrt(Math.pow(this.x - coord.x, 2) + Math.pow(this.y - coord.y, 2))
	}
	
	set(coord) {
		this.x = coord.x;
		this.y = coord.y;
	}
}

class Node {
	constructor(node) {
		this.address = node.address;
		this.coord = new Coord(node.coord.x, node.coord.y);
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
	constructor(networkInfo) {
		this.nodes = [];
		this.maprect = {};
		this.connection = [];
		this.routing;
		this.buildNetwork(networkInfo);
	}
	
	buildNetwork(networkInfo) {
		for (var i = 0; i < networkInfo.nodes.length; i++) {
			this.nodes.push(new Node(networkInfo.nodes[i]));
		}
		this.maprect = networkInfo.maprect;
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
	
	setRouting(routing) {
		this.routing = routing;
	}
}

function ra(n) {
	return Math.round(n * Math.random());
}

function getIndexOfMatrix(n, i, j) {
	return i * n - ((i + 2) * (i + 1) / 2) + j;
}

function distance(curNode, targetNode) {
	var dist = Math.sqrt(Math.pow(curNode.coord.x - targetNode.coord.x, 2) + Math.pow(curNode.coord.y - targetNode.coord.y, 2));
	return dist;
}

function genNetworkInfo(numNode, r) {
	var networkInfo = {};
	var maxWidth = 4 * r * Math.sqrt(numNode / 24);
	var maxHeight = 3 * r * Math.sqrt(numNode / 24);
	networkInfo['maprect'] = {'top': maxHeight, 'left': 0, 'bottom': 0, 'right': maxWidth};
	var nodes = [];
	for (var i = 0; i < numNode; i++) {
		var newNode = {};
		newNode['address'] = i;
		newNode['coord'] = {'x': ra(maxWidth), 'y': ra(maxHeight)};
		newNode['range'] = 0;
		newNode['neighbor'] = [];
		nodes.push(newNode);
	}
	// update neighbor
	var iCol = 0;
	var iRow = 0;
	var distanceMatrix = [];
	while(iRow < numNode) {
		var curNode = nodes[iRow];
		iCol = iRow + 1
		while(iCol < numNode) {
			var targetNode = nodes[iCol];
			distanceMatrix.push(distance(curNode, targetNode));
			iCol++;
		}
		iRow++;
	}
	for (var i = 0; i < nodes.length; i++) {
		for (var j = 0; j < nodes.length; j++) {
			if (i == j)
				continue;
			else if (i < j)
				var index = getIndexOfMatrix(numNode, i, j);
			else if (i > j)
				var index = getIndexOfMatrix(numNode, j, i);
			if (distanceMatrix[index] <= r)
				nodes[i].neighbor.push(j);
		}
	}
	networkInfo['nodes'] = nodes;
	return networkInfo;
}

function updateNeighborTable(networkInfo) {
	// update neighbor
	var iCol = 0;
	var iRow = 0;
	var distanceMatrix = [];
	var numNode = networkInfo['nodes'].length;
	while(iRow < numNode) {
		var curNode = networkInfo['nodes'][iRow];
		iCol = iRow + 1
		while(iCol < numNode) {
			var targetNode = networkInfo['nodes'][iCol];
			distanceMatrix.push(distance(curNode, targetNode));
			iCol++;
		}
		iRow++;
	}
	for (var i = 0; i < numNode; i++) {
		var r = networkInfo['nodes'][i]['range'];
		for (var j = 0; j < numNode; j++) {
			if (i == j)
				continue;
			else if (i < j)
				var index = getIndexOfMatrix(numNode, i, j);
			else if (i > j)
				var index = getIndexOfMatrix(numNode, j, i);
			if (distanceMatrix[index] <= r)
				networkInfo['nodes'][i].neighbor.push(j);
		}
	}
}