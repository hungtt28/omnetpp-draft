
const GPSR_GREEDY_ROUTING = 0;
const GPSR_PERIMETER_ROUTING = 1;
const GPSR_GG_PLANARIZATION = 0;
const GPSR_RNG_PLANARIZATION = 1;

class GPSRPacket {
	constructor() {
		this.mode = GPSR_GREEDY_ROUTING;
		this.destination = new Coord(0, 0);
		this.startPerimeter = new Coord(0, 0);
		this.forwardPerimeter = new Coord(0, 0);
		this.firstSenderAddress = -1;
		this.firstReceiveAddress = -1;
		this.senderAddress = -1;
	}
}

class GPSR {
	constructor(network) {
		this.network = network;
		this.planarizationMode = GPSR_GG_PLANARIZATION;
	}
	
	createPacket(des) {
		var packet = new GPSRPacket();
		var desNode = this.network.getNode(des);
		packet.mode = GPSR_GREEDY_ROUTING;
		packet.destination.set(desNode.coord);
		return packet;
	}
	
	findNextHop(node, packet) {
		var nextHop = -1;
		if (packet.mode == GPSR_GREEDY_ROUTING)
			nextHop = this.findGreedyRoutingNextHop(node, packet)
		else if (packet.mode == GPSR_PERIMETER_ROUTING) {
			if (packet.startPerimeter.x == node.coord.x && packet.startPerimeter.y == node.coord.y)
				nextHop = -1;
			else
				nextHop = this.findPerimeterRoutingNextHop(node, packet)
		}
		packet.senderAddress = node.address;
		return nextHop;
	}
	
	findGreedyRoutingNextHop(node, packet) {
		var minDistance = node.coord.distanceTo(packet.destination);
		var nextHop = -1;
		var flag = false;
		// greedy
		for (var i = 0; i < node.neighbor.length; i++) {
			var neighborAddress = node.neighbor[i];
			var neighbor = this.network.getNode(neighborAddress);
			if (neighbor == undefined)
				continue;
			var neighborDistance = neighbor.coord.distanceTo(packet.destination);
			if (neighborDistance < minDistance) {
				flag = true;
				minDistance = neighborDistance;
				nextHop = neighborAddress;
			}
		}
		if (flag == false) {
			packet.mode = GPSR_PERIMETER_ROUTING;
			packet.startPerimeter.set(node.coord);
			packet.firstSenderAddress = node.address;
			packet.firstReceiveAddress = -1;
			packet.senderAddress = -1;
			nextHop = this.findPerimeterRoutingNextHop(node, packet);
		}
		return nextHop;
	}
	
	findPerimeterRoutingNextHop(node, packet) {
		var nextHop = -1;
		var minDistance = packet.startPerimeter.distanceTo(packet.destination);
		var curDistance = node.coord.distanceTo(packet.destination);
		if (curDistance < minDistance) {
			packet.mode = GPSR_GREEDY_ROUTING;
			packet.startPerimeter = new Coord(0, 0);
			packet.forwardPerimeter = new Coord(0, 0);
			nextHop = this.findGreedyRoutingNextHop(node, packet);
		}
		else {
			var firstSenderAddress = packet.firstSenderAddress;
			var firstReceiverAddress = packet.firstReceiverAddress;
			nextHop = packet.senderAddress;
			var hasIntersection = true;
			while(hasIntersection) {
				if (nextHop == -1)
					nextHop = this.getNextPlanarNeighborCounterClockwise(node, nextHop, packet.destination);
				else 
					nextHop = this.getNextPlanarNeighborCounterClockwise(node, nextHop, this.network.getNode(nextHop).coord);
				if (nextHop == -1)
					break;
				var nextHopNode = this.network.getNode(nextHop);
				hasIntersection = this.intersection(packet.startPerimeter, packet.destination, node.coord, nextHopNode.coord);
				if (hasIntersection) {
					packet.firstSenderAddress = node.address;
					packet.firstReceiverAddress = -1;
				}
			}
			if (firstSenderAddress == node.address && firstReceiverAddress == nextHop)
				nextHop = 1;
			else {
				if (packet.firstReceiverAddress == -1)
					packet.firstReceiverAddress = nextHop;
			}
		}
		return nextHop;
	}
	
	getNextPlanarNeighborCounterClockwise(node, nextHop, centerPosition) {
		var minAngle = 2 * Math.PI;
		var startAngle = this.getNeighborAngle(node, centerPosition);
		var planarNeighbors = this.getPlanarNeighbors(node);
		for (var i = 0; i < planarNeighbors.length; i++) {
			var neighborNode = this.network.getNode(planarNeighbors[i]);
			var neighborAngle = this.getNeighborAngle(node, neighborNode.coord);
			var difAngle = neighborAngle - startAngle;
			if (difAngle < 0)
				difAngle = difAngle + 2 * Math.PI;
			if (difAngle != 0 && difAngle < minAngle) {
				minAngle = difAngle;
				nextHop = planarNeighbors[i];
			}
		}
		return nextHop;
	}
	
	getPlanarNeighbors(node) {
		var planarNeighbors = [];
		for (var i = 0; i < node.neighbor.length; i++) {
			var neighborNode = this.network.getNode(node.neighbor[i]);
			if (neighborNode == undefined)
				continue;
			var isCloseNeighbor = true;
			if (this.planarizationMode == GPSR_RNG_PLANARIZATION) {
				var neighborDistance = node.coord.distanceTo(neighborNode.coord);
				for (var j = 0; j < node.neighbor.length; j++) {
					if (i == j)
						continue;
					var witnessNode = this.network.getNode(node.neighbor[j]);
					if (neighborDistance > witnessNode.coord.distanceTo(node.coord) && neighborDistance > witnessNode.coord.distanceTo(neighborNode.coord)) {
						isCloseNeighbor = false;
						break;
					}
				}
			}
			else if (this.planarizationMode == GPSR_GG_PLANARIZATION) {
				var middlePosition = new Coord((node.coord.x + neighborNode.coord.x) / 2.0, (node.coord.y + neighborNode.coord.y) / 2.0);
				var neighborDistance = node.coord.distanceTo(middlePosition);
				for (var j = 0; j < node.neighbor.length; j++) {
					if (i == j)
						continue;
					var witnessNode = this.network.getNode(node.neighbor[j]);
					if (neighborDistance > witnessNode.coord.distanceTo(middlePosition)) {
						isCloseNeighbor = false;
						break;
					}
				}
			}
			if (isCloseNeighbor)
				planarNeighbors.push(node.neighbor[i]);
		}
		return planarNeighbors;
	}
	
	getNeighborAngle(node, neighborPosition) {
		var vector = new Coord(neighborPosition.x - node.coord.x, neighborPosition.y - node.coord.y);
		return this.getVectorAngle(vector);
	}
	
	getVectorAngle(vector) {
		var angle = Math.atan2(vector.y, vector.x);
		if (angle < 0)
			angle = angle + 2 * Math.PI;
		return angle;
	}
	
	intersection(begin1, end1, begin2, end2) {
		var x1 = begin1.x;
		var y1 = begin1.y;
		var x2 = end1.x;
		var y2 = end1.y;
		var x3 = begin2.x;
		var y3 = begin2.y;
		var x4 = end2.x;
		var y4 = end2.y;
		var a = this.determinant(x1, y1, x2, y2);
		var b = this.determinant(x3, y3, x4, y4);
		var c = this.determinant(x1 - x2, y1 - y2, x3 - x4, y3 - y4);
		var x = this.determinant(a, x1 - x2, b, x3 - x4) / c;
		var y = this.determinant(a, y1 - y2, b, y3 - y4) / c;
		if (x1 < x && x < x2 && x3 < x && x < x4 && y1 < y && y < y2 && y3 < y && y < y4)
			return true;
		else
			return false;
	}
	
	determinant(x1, y1, x2, y2) {
		return (x1 * y2) - (x2 * y1);
	}
}

