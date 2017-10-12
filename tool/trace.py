
import sys
import re

def parse_trace(log):
	log = log.split('\n')
	trace = []
	for line in log:
		m = re.match("\*\* Event \#\D*(\d+)  t\=0   Testing\.node\[\D*(\d+)\]", line)
		if (m):
			trace.append(m.group(2))
	return ', '.join(trace)

if __name__ == "__main__":
	log = open(sys.argv[1], 'rb').read()
	print(parse_trace(log))