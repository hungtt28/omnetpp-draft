
import sys
import random
import math

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
		
def gen_network_testing(num, r):
	init_str = '[General]\nnetwork = Testing\n'
	init_str += '**.n = {}\n'.format(num)
	neighbor_str = ''
	graph = gen_coordinates(num, r)
	graph.updateNeighbor(r)
	for i in range(num):
		init_str += '*.node[{}].id = {}\n'.format(i, i)
		init_str += '*.node[{}].x = {}\n'.format(i, graph.nodes[i].x)
		init_str += '*.node[{}].y = {}\n'.format(i, graph.nodes[i].y)
		neighbor_str += '*.node[{}].neighbor_str = "{}"\n'.format(i, ' '.join(str(id) for id in graph.nodes[i].neighbor))
	init_str += '*.node[*].xD = {}\n'.format(graph.nodes[-1].x)
	init_str += '*.node[*].yD = {}\n'.format(graph.nodes[-1].y)
	# init_str += '**.xD = {}\n'.format(graph.nodes[-1].x)
	# init_str += '**.yD = {}\n'.format(graph.nodes[-1].y)
	init_str += '*.node[0].Source = true\n'
	init_str += '*.node[{}].Dest = true\n'.format(num-1)
	init_str += '**.range = {}\n'.format(r)
	return init_str + '\n' + neighbor_str

if __name__ == "__main__":
	if (len(sys.argv) < 3):
		print('python gen_network_testing.py <num> <t> <range>')
		sys.exit(0)
	num = int(sys.argv[1])
	r = int(sys.argv[2])
	init_str = gen_network_testing(num, r)
	open('omnetpp.ini', 'wb').write(init_str)