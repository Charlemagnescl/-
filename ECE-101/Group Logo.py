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


def Draw_Rec_X(x,y,a,b,ang=0,color):
    #x整个图形最左侧的坐标（x），y整个图形最下侧的坐标（y），a宽度，b高度，ang为0即可，color颜色直接用RGB返回值即可
    ax = fig.add_subplot(111)
    re = Rectangle(xy=(x,y),width = a, height = b, angle = ang, facecolor =color)
    ax.add_patch(re)

G = RGB('55,48,46')  #绿色
W = RGB('254,254,254') #白色
Y = RGB('253,208,0')  #黄色
R = RGB('234,37,47')  #红色
B = RGB('171,227,240')  #蓝色
Draw_Rec_X(-4.5,-1.0,9,11,0,Y)  #脸轮廓
Draw_Rec_X(-2.5,-2,5,1,1,Y)

Draw_Rec_X(-5.5,5.5,11,1,0,G)  #眉毛一带

Draw_Rec_X(-4.5,4.5,3,1,0,B)
Draw_Rec_X(1.5,4.5,3,1,0,B)

Draw_Rec_X(-1.5,4.5,3,1,0,G)  
Draw_Rec_X(-2.5,-1,5,1,1,G)

Draw_Rec_X(-2.5,8,5,2,0,R)
Draw_Rec_X(-1.5,7,3,1,0,R)

Draw_Rec_X(-4.5,10,9,1,0,R)
Draw_Rec_X(-4.5,11,9,1,0,G)
Draw_Rec_X(-1.5,11,3,1,0,R)
Draw_Rec_X(-1.5,12,3,1,0,G)


plt.axis([-20,20,-20,20])
plt.show()


