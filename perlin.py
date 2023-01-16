import numpy as np
import matplotlib.pyplot as plt
import math
import time

def hashy(a):
    a = (a ^ 61) ^ (a >> 16)
    a = a + (a << 3)
    a = a ^ (a >> 4)
    a = a * 0x27d4eb2d
    a = a ^ (a >> 15)
    return a

def ivalue(y):
    return hashy(y<<16)&0xff

def smooth(x):
    return 6*x*x*x*x*x - 15*x*x*x*x + 10*x*x*x

def value(x):
    ix = math.floor(x)
    fx = smooth(x-ix)

    v00 = ivalue(ix+0)
    v01 = ivalue(ix+1)

    v0 = v00*(1-fx) + v01*fx
    return v0



n = 100000

a = np.zeros(n,dtype=np.uint8)
st = time.time()
for x in range(n): #every time i need a new rnd number i should do these operations
    v = 0
    for o in range(4):
        v = v + value(x/64.0*(1<<o))/(1<<o)
    r = round(v*0.5)
    a[x] = r

et = time.time()

print("elapsed time: ",et-st)
print(max(a))
print(min(a))

plt.plot(a)
plt.show()

print("salio todo bien")