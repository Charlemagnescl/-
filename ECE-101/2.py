
import numpy as np
import numpy.matlib as npm
import random
import matplotlib.pyplot as plt

p1 = 100#100*random.random()
p2 = 10#100*random.random()



X = range(1,1001)
X = npm.asarray(X)

N = 200
Y = []
YY = []

for each in X:
    Y.append(each*p1+p2+N*random.uniform(-1.0,1.0))
    YY.append(each*p1 + p2)

Y = npm.asarray(Y)

#plt.scatter(X,Y)
#plt.show()

p = npm.ones((1,2)) * 50

y = npm.asarray(Y)
x1 = npm.asarray(X)
x2 = npm.ones((1,1000))

x = np.vstack([x1,x2])

#print(p.shape)
#print(y.shape)
p11 = []
p22 = []
loss = []
iters= 10700
for i in  range(iters):
    t1 = p * np.power(x,2)
    t1 = np.sum(t1,axis = 1)
    t2 = y * x.T
    #print(t1.shape)
    #print(t2.shape)
    #print(t2)
    dp = -2*(t1 - t2) / 1000
    #print(p)
    p += dp*1e-9
    loss.append(np.mean(p*x - y))
    p11.append(p[0,0])
    p22.append(p[0,1])

xx = range(0,iters)

print(str(p1) + " " + str(p2))
print(p)
plt.plot(xx,p11,color = "red")
plt.plot(xx,p22, color = "blue")
plt.plot(xx,loss, color = "yellow")
plt.show()
yy = []
for i in range(1000):
    yy.append(p[0,0] * X[i] + p[0,1])

plt.scatter(X,Y)
X.reshape((1,1000))
plt.plot(X,yy,color = 'red')
plt.plot(X,YY,color = 'green')
plt.show()
