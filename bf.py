import brainfuck
import sys

bf = open('{0}'.format(sys.argv[0]), "r")
print(brainfuck.evaluate(bf.read()))
bf.close()