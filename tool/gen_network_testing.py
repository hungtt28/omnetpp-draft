
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
					if (((curNode.x - neibNode.x)**2 + (curNode.y - neibNode.y)**2) < r*r):
						self.nodes[i].neighbor.append(j)
		return
		
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
	for i in xrange(1, num):
		newNode = gen_neighbor(curNode, r, Coord(b, b))
		graph.nodes.append(newNode)
		curNode = newNode
	return graph
		
def to_omnetpp_ini(graph, num, r):
	init_str = '[General]\nnetwork = Testing\n'
	init_str += '**.n = {}\n'.format(num)
	neighbor_str = ''
	# graph = gen_coordinates(num, r)
	# graph.updateNeighbor(r)
	for i in range(num):
		init_str += '*.node[{}].id = {}\n'.format(i, i)
		init_str += '*.node[{}].x = {}\n'.format(i, graph.nodes[i].x)
		init_str += '*.node[{}].y = {}\n'.format(i, graph.nodes[i].y)
		neighbor_str += '*.node[{}].neighbor_str = "{}"\n'.format(i, ' '.join(str(id) for id in graph.nodes[i].neighbor))
	# init_str += '*.node[*].xD = {}\n'.format(graph.nodes[-1].x)
	# init_str += '*.node[*].yD = {}\n'.format(graph.nodes[-1].y)
	init_str += '**.xD = {}\n'.format(graph.nodes[-1].x)
	init_str += '**.yD = {}\n'.format(graph.nodes[-1].y)
	init_str += '*.node[0].Source = true\n'
	init_str += '*.node[{}].Dest = true\n'.format(num-1)
	init_str += '**.range = {}\n'.format(r)
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
	js_str += '\t\ttop: {},\n'.format(maxY)
	js_str += '\t\tleft: {},\n'.format(minX)
	js_str += '\t\tbottom: {},\n'.format(minY)
	js_str += '\t\tright: {},\n'.format(maxX)
	js_str += '\t},\n'
	js_str += node_str + '}'
	open('omnetpp.js', 'wb').write(js_str)
	return
	
def gen_network_testing(num, r):
	graph = gen_coordinates(num, r)
	graph.updateNeighbor(r)
	to_omnetpp_ini(graph, num, r)
	to_js_json(graph, num, r)
	return
	
if __name__ == "__main__":
	if (len(sys.argv) < 3):
		print('python gen_network_testing.py <num> <t> <range>')
		sys.exit(0)
	num = int(sys.argv[1])
	r = int(sys.argv[2])
	gen_network_testing(num, r)



