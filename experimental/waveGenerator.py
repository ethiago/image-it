import numpy
import math

coss = [ str(math.cos(x)) for x in numpy.arange(-100, 100, 0.1)]

print( ",".join(coss) )
print( ",".join(coss) ),