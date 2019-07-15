from matplotlib.patches import Ellipse,Rectangle
import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure()

def RGB(rgb):          
    #RGB（字符串形式的RBG值，记得加''），返回字符串形式的16进制颜色代码，直接放进函数里即可
    RGB = rgb.split(',')           
    color = '#'
    for i in RGB:
        num = int(i)
        color += str(hex(num))[-2:].replace('x', '0').upper()
    #print(color)
    st = ''
    st += color
    return st


def Draw_Rec_X(x,y,a,b,ang,color):
    #x整个图形最左侧的坐标（x），y整个图形最下侧的坐标（y），a宽度，b高度，ang为0即可，color颜色直接用RGB返回值即可
    ax = fig.add_subplot(111)
    re = Rectangle(xy=(x,y),width = a, height = b, angle = ang, facecolor =color)
    ax.add_patch(re)

G = RGB('55,48,46')  #绿色
W = RGB('254,254,254') #白色
Y = RGB('253,208,0')  #黄色
R = RGB('234,37,47')  #红色
B = RGB('171,227,240')  #蓝色
plt.axis([-20,20,-20,20])
plt.axis('off')


Draw_Rec_X(-6.5,7,13,3,0,G)         #脸轮廓
Draw_Rec_X(-5.5,7,1,3,0,R)
Draw_Rec_X(4.5,7,1,3,0,R)
Draw_Rec_X(-7.5,3,15,4,0,G)
Draw_Rec_X(-6.5,3,1,4,0,R)
Draw_Rec_X(-5.5,3,11,2,0,Y)
Draw_Rec_X(5.5,3,1,4,0,R)
Draw_Rec_X(4.5,4,1,1,0,R)
Draw_Rec_X(-6.5,0,13,3,0,G) 
Draw_Rec_X(-5.5,0,11,3,0,R) 
Draw_Rec_X(-5.5,-1,11,1,0,G)
Draw_Rec_X(-4.5,-1,9,1,0,R)
Draw_Rec_X(-4.5,-2,9,1,0,G)

Draw_Rec_X(-4.5,0,9,10,0,Y)
Draw_Rec_X(-3.5,-1,7,1,0,Y)  
Draw_Rec_X(-2.5,-2,5,1,0,Y)
Draw_Rec_X(-5.5,10,11,0,0,G)


Draw_Rec_X(-5.5,5,11,1,0,G)  #眉毛一带

Draw_Rec_X(-4.5,4,3,1,0,B)  #eyes
Draw_Rec_X(1.5,4,3,1,0,B)

Draw_Rec_X(-1.5,4.5,3,1,0,G)  
Draw_Rec_X(-2.5,-1,5,1,0,G)

Draw_Rec_X(-2.5,8,5,2,0,R)      
Draw_Rec_X(-1.5,7,3,1,0,R)

Draw_Rec_X(-4.5,10,9,1,0,R)   #额头
Draw_Rec_X(-4.5,11,9,1,0,G)
Draw_Rec_X(-1.5,11,3,1,0,R)
Draw_Rec_X(-1.5,12,3,1,0,G)

#如果只要头部的话去掉注释
Draw_Rec_X(-3.5,-3,7,1,0,G)
Draw_Rec_X(-2.5,-3,5,1,0,R)


#以上是头部
Draw_Rec_X(-2.5,-4,5,1,0,G)
Draw_Rec_X(-2.5,-5,1,1,0,G)
Draw_Rec_X(1.5,-5,1,1,0,G)
Draw_Rec_X(-1.5,-6,1,1,0,G)
Draw_Rec_X(0.5,-6,1,1,0,G)
Draw_Rec_X(-0.5,-7,1,1,0,G)
#以上是反应堆轮廓
Draw_Rec_X(-1.5,-5,3,1,0,B)
Draw_Rec_X(-0.5,-6,1,1,0,B)
#以上是反应堆颜色
Draw_Rec_X(-4.5,-3,1,1,0,R)
Draw_Rec_X(3.5,-3,1,1,0,R)
Draw_Rec_X(-5.5,-3,1,1,0,G)
Draw_Rec_X(4.5,-3,1,1,0,G)
<<<<<<< HEAD

Draw_Rec_X(-5.5,-4,1,1,0,R)
Draw_Rec_X(4.5,-4,1,1,0,R)
Draw_Rec_X(-6.5,-4,1,1,0,G)
Draw_Rec_X(5.5,-4,1,1,0,G)

Draw_Rec_X(-3.5,-4,1,1,0,R)
Draw_Rec_X(2.5,-4,1,1,0,R)
Draw_Rec_X(-4.5,-8,1,5,0,G)
Draw_Rec_X(3.5,-8,1,5,0,G)
#以上是肩部
Draw_Rec_X(-6.5,-5,1,1,0,Y)
Draw_Rec_X(5.5,-5,1,1,0,Y)
Draw_Rec_X(-7.5,-5,1,1,0,G)
Draw_Rec_X(6.5,-5,1,1,0,G)

Draw_Rec_X(-5.5,-6,1,2,0,Y)
Draw_Rec_X(4.5,-6,1,2,0,Y)

Draw_Rec_X(-7.5,-7,2,2,0,R)
Draw_Rec_X(5.5,-7,2,2,0,R)

Draw_Rec_X(-8.5,-7,1,2,0,G)
Draw_Rec_X(7.5,-7,1,2,0,G)

Draw_Rec_X(-7.5,-8,2,1,0,G)
Draw_Rec_X(5.5,-8,2,1,0,G)

Draw_Rec_X(-5.5,-7,1,1,0,G)
Draw_Rec_X(4.5,-7,1,1,0,G)
#以上是手部
Draw_Rec_X(-3.5,-8,1,5,0,R)
Draw_Rec_X(2.5,-8,1,5,0,R)

Draw_Rec_X(-2.5,-9,1,4,0,R)
Draw_Rec_X(1.5,-9,1,4,0,R)

Draw_Rec_X(-1.5,-9,1,3,0,R)
Draw_Rec_X(0.5,-9,1,3,0,R)

Draw_Rec_X(-0.5,-9,1,2,0,R)
#以上是躯干的红色部分
Draw_Rec_X(-1.5,-10,3,1,0,G)

Draw_Rec_X(-3.5,-10,2,1,0,Y)
Draw_Rec_X(1.5,-10,2,1,0,Y)

Draw_Rec_X(-4.5,-9,2,1,0,Y)
Draw_Rec_X(2.5,-9,2,1,0,Y)
#以上是胯部
Draw_Rec_X(-2.5,-13,1,3,0,G)
Draw_Rec_X(1.5,-13,1,3,0,G)

Draw_Rec_X(-5.5,-13,3,1,0,G)
Draw_Rec_X(2.5,-13,3,1,0,G)

Draw_Rec_X(-6.5,-13,1,3,0,G)
Draw_Rec_X(5.5,-13,1,3,0,G)

Draw_Rec_X(-5.5,-11,1,3,0,G)
Draw_Rec_X(4.5,-11,1,3,0,G)
#以上是腿部轮廓
Draw_Rec_X(-5.5,-12,3,1,0,R)
Draw_Rec_X(2.5,-12,3,1,0,R)

Draw_Rec_X(-4.5,-11,2,1,0,R)
Draw_Rec_X(2.5,-11,2,1,0,R)

Draw_Rec_X(-4.5,-10,1,1,0,R)
Draw_Rec_X(3.5,-10,1,1,0,R)
#以上是腿部颜色






=======
>>>>>>> b8190190a8f6d1a93fe9f6d6e3a556d50840fe8b

Draw_Rec_X(-5.5,-4,1,1,0,R)
Draw_Rec_X(4.5,-4,1,1,0,R)
Draw_Rec_X(-6.5,-4,1,1,0,G)
Draw_Rec_X(5.5,-4,1,1,0,G)

Draw_Rec_X(-3.5,-4,1,1,0,R)
Draw_Rec_X(2.5,-4,1,1,0,R)
Draw_Rec_X(-4.5,-8,1,5,0,G)
Draw_Rec_X(3.5,-8,1,5,0,G)
#以上是肩部
Draw_Rec_X(-6.5,-5,1,1,0,Y)
Draw_Rec_X(5.5,-5,1,1,0,Y)
Draw_Rec_X(-7.5,-5,1,1,0,G)
Draw_Rec_X(6.5,-5,1,1,0,G)

Draw_Rec_X(-5.5,-6,1,2,0,Y)
Draw_Rec_X(4.5,-6,1,2,0,Y)

Draw_Rec_X(-7.5,-7,2,2,0,R)
Draw_Rec_X(5.5,-7,2,2,0,R)

<<<<<<< HEAD
plt.show()
=======
Draw_Rec_X(-8.5,-7,1,2,0,G)
Draw_Rec_X(7.5,-7,1,2,0,G)

Draw_Rec_X(-7.5,-8,2,1,0,G)
Draw_Rec_X(5.5,-8,2,1,0,G)

Draw_Rec_X(-5.5,-7,1,1,0,G)
Draw_Rec_X(4.5,-7,1,1,0,G)
#以上是手部
Draw_Rec_X(-3.5,-8,1,5,0,R)
Draw_Rec_X(2.5,-8,1,5,0,R)

Draw_Rec_X(-2.5,-9,1,4,0,R)
Draw_Rec_X(1.5,-9,1,4,0,R)

Draw_Rec_X(-1.5,-9,1,3,0,R)
Draw_Rec_X(0.5,-9,1,3,0,R)

Draw_Rec_X(-0.5,-9,1,2,0,R)
#以上是躯干的红色部分
Draw_Rec_X(-1.5,-10,3,1,0,G)

Draw_Rec_X(-3.5,-10,2,1,0,Y)
Draw_Rec_X(1.5,-10,2,1,0,Y)

Draw_Rec_X(-4.5,-9,2,1,0,Y)
Draw_Rec_X(2.5,-9,2,1,0,Y)
#以上是胯部
Draw_Rec_X(-2.5,-13,1,3,0,G)
Draw_Rec_X(1.5,-13,1,3,0,G)

Draw_Rec_X(-5.5,-13,3,1,0,G)
Draw_Rec_X(2.5,-13,3,1,0,G)

Draw_Rec_X(-6.5,-13,1,3,0,G)
Draw_Rec_X(5.5,-13,1,3,0,G)

Draw_Rec_X(-5.5,-11,1,3,0,G)
Draw_Rec_X(4.5,-11,1,3,0,G)
#以上是腿部轮廓
Draw_Rec_X(-5.5,-12,3,1,0,R)
Draw_Rec_X(2.5,-12,3,1,0,R)

Draw_Rec_X(-4.5,-11,2,1,0,R)
Draw_Rec_X(2.5,-11,2,1,0,R)

Draw_Rec_X(-4.5,-10,1,1,0,R)
Draw_Rec_X(3.5,-10,1,1,0,R)
#以上是腿部颜色











plt.show()
>>>>>>> b8190190a8f6d1a93fe9f6d6e3a556d50840fe8b
