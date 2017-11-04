
import sys
import random
import math
import json

class Coord():
	def __init__(self, x, y):
		self.x = x
		self.y = y
		self.neighbor = []

class Graph():
	def __init__(self):
		self.nodes = []
		
	def updateNeighbor(self, r):
		for i in range(len(self.nodes)):
			curNode = self.nodes[i]
			for j in range(len(self.nodes)):
				if (i == j):
					continue
				else:
					neibNode = self.nodes[j]
					if (((curNode.x - neibNode.x)**2 + (curNode.y - neibNode.y)**2) <= r*r):
						self.nodes[i].neighbor.append(j)
		return
		
	def hasNode(self, cNode):
		for node in self.nodes:
			if (node.x == cNode.x & node.y == cNode.y):
				return True
		return False
		
def gen_neighbor(curNode, r, b):
	x = random.randrange(r)
	y = random.randint(0, int(math.sqrt(r*r - x * x)))
	if (curNode.x + x > b.x):
		dx = -1
	elif (curNode.x - x < 0):
		dx = 1
	else:
		dx = random.choice([1, -1])
	if (curNode.y + y > b.y):
		dy = -1
	elif (curNode.y - y < 0):
		dy = 1
	else:
		dy = random.choice([1, -1])
	return Coord(curNode.x + dx * x, curNode.y + dy * y)
		
def gen_coordinates(num, r):
	graph = Graph()
	# creat minimum graph connected
	curNode = Coord(random.randrange(num), random.randrange(num))
	graph.nodes.append(curNode)
	b = 2 * r * int(math.sqrt(num))
	num -= 1
	while(num):
		newNode = gen_neighbor(curNode, r, Coord(b, b))
		if (graph.hasNode(newNode)):
			continue
		graph.nodes.append(newNode)
		curNode = newNode
		num -= 1
	return graph
		
def to_omnetpp_ini(graph, num, r):
	init_str = '[General]\nnetwork = Network\n'
	init_str += '*.numHosts = {}\n'.format(num)
	init_str += '*.range = {}\n'.format(r)
	neighbor_str = ''
	# graph = gen_coordinates(num, r)
	# graph.updateNeighbor(r)
	for i in range(num):
		init_str += '*.host[{}].ID = {}\n'.format(i, i)
		init_str += '*.host[{}].X = {}\n'.format(i, graph.nodes[i].x)
		init_str += '*.host[{}].Y = {}\n'.format(i, graph.nodes[i].y)
		neighbor_str += '*.host[{}].neighbor_str = "{}"\n'.format(i, ' '.join(str(id) for id in graph.nodes[i].neighbor))
	init_str += '# data\n'
	init_str += '*.host[0].isSource = true\n'
	init_str += '*.host[0].destID = {}\n'.format(num-1)
	init_str += '*.host[0].destX = {}\n'.format(graph.nodes[-1].x)
	init_str += '*.host[0].destY = {}\n'.format(graph.nodes[-1].y)
	init_str += '\n' + neighbor_str
	open('omnetpp.ini', 'wb').write(init_str)
	return 

def to_js_json(graph, num, r):
	node_str = '\tnodes: [\n'
	maxX, minX, maxY, minY = -1, -1, -1, -1
	for i in range(num):
		if (maxX < graph.nodes[i].x) | (maxX == -1):
			maxX = graph.nodes[i].x
		if (minX > graph.nodes[i].x) | (minX == -1):
			minX = graph.nodes[i].x
		if (maxY < graph.nodes[i].y) | (maxY == -1):
			maxY = graph.nodes[i].y
		if (minY > graph.nodes[i].y) | (minY == -1):
			minY = graph.nodes[i].y
		node_str += '\t\t{' + 'address: {}, '.format(i)
		node_str += 'coord: {'+ 'x: {}, y: {}'.format(graph.nodes[i].x, graph.nodes[i].y) + '}, '
		node_str += 'range: {}, '.format(r)
		node_str += 'neighbor: {}'.format(graph.nodes[i].neighbor) + '},\n'
	node_str += '\t],\n'
	js_str = 'networkInfo = {\n'
	js_str += '\tmaprect: {\n'
	js_str += '\t\ttop: {},\n'.format(maxY+1)
	js_str += '\t\tleft: {},\n'.format(minX-1)
	js_str += '\t\tbottom: {},\n'.format(minY-1)
	js_str += '\t\tright: {},\n'.format(maxX+1)
	js_str += '\t},\n'
	js_str += node_str + '}'
	open('omnetpp.js', 'wb').write(js_str)
	return
	
def to_castalia_format(graph, num, r):
	node_str = '\n'
	maxX, minX, maxY, minY = -1, -1, -1, -1
	for i in range(num):
		if (maxX < graph.nodes[i].x) | (maxX == -1):
			maxX = graph.nodes[i].x
		if (minX > graph.nodes[i].x) | (minX == -1):
			minX = graph.nodes[i].x
		if (maxY < graph.nodes[i].y) | (maxY == -1):
			maxY = graph.nodes[i].y
		if (minY > graph.nodes[i].y) | (minY == -1):
			minY = graph.nodes[i].y
		node_str += 'SN.node[{}].xCoor = {}\n'.format(i, graph.nodes[i].x)
		node_str += 'SN.node[{}].yCoor = {}\n'.format(i, graph.nodes[i].y)
		node_str += 'SN.node[{}].zCoor = {}\n\n'.format(i, 0)
	node_str += '\n'
	print('[+] maxX: {}'.format(maxX))
	print('[+] maxY: {}'.format(maxY))
	open('node_location.ini', 'wb').write(node_str)
	return
	
def gen_network_testing(num, r):
	graph = gen_coordinates(num, r)
	graph.updateNeighbor(r)
	to_omnetpp_ini(graph, num, r)
	to_js_json(graph, num, r)
	to_castalia_format(graph, num, r)
	return
	
if __name__ == "__main__":
	if (len(sys.argv) < 3):
		print('python gen_network_testing.py <num> <range>')
		sys.exit(0)
	num = int(sys.argv[1])
	r = int(sys.argv[2])
	gen_network_testing(num, r)



