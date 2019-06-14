import numpy as np
import matplotlib.pyplot as plt
import imageio

print("Running GrahamScan Visualizer....")
fileName1 = "bridge_points.txt"
f = open('input.txt','r')
lines = f.readlines()
data_x=[]
data_y=[]
lines=lines[1:]
for line in lines:
	line= line[:-1]
	line = line.split(' ')
	x = line[0]
	y = line[1]
	data_x.append(float(x))
	data_y.append(float(y))
f.close()

gif = []
fig, ax = plt.subplots(figsize=(5,5))
ax.scatter(data_x, data_y, label= "stars", color= "green",  
			marker= "*", s=30)
fig.canvas.draw()
image = np.frombuffer(fig.canvas.tostring_rgb(), dtype='uint8')
gif.append(image.reshape(fig.canvas.get_width_height()[::-1] + (3,)))
with open(fileName1) as f:
    lines = f.readlines()
check = False
print(lines)
colop = 'red'
myiter = iter(range(0,len(lines)-1))
for i in myiter:
    #print(i)
    
    if lines[i]=='\n':
        colop='orange'
        check = True
        continue
    x1, y1 = list(map(float, lines[i].split()))[0:2]
    x2, y2 = list(map(float, lines[i+1].split()))[0:2]
    ax.scatter(data_x, data_y, label= "stars", color= "green",  
			marker= "*", s=30)
    ax.plot([x1,x2], [y1,y2], color=colop, linewidth = 3, 
         marker='o', markerfacecolor='blue', markersize=12)
    
    fig.canvas.draw()
    image = np.frombuffer(fig.canvas.tostring_rgb(), dtype='uint8')
    gif.append(image.reshape(fig.canvas.get_width_height()[::-1] + (3,)))

    print(i-1,x1, y1, x2, y2)
    next(myiter,None)

f2 = open('output.txt','r')
lines = f2.readlines()
f2.close
path_x=[]
path_y=[]
lower_x=[]
lower_y=[]
print(len(data_x))
check = False
for line in lines:
	if line=='\n':
		lower_x.append(path_x[len(path_x)-1])
		lower_y.append(path_y[len(path_y)-1])
		check = True
		continue
	line = line[:-1]
	x,y = line.split(' ')
	if check:
		lower_x.append(float(x))
		lower_y.append(float(y))		
	else:
		path_x.append(float(x))
		path_y.append(float(y))
ax.scatter(data_x, data_y, label= "stars", color= "green",  
			marker= "*", s=30)

  
# function to show the plot 
ax.plot(path_x, path_y, color='red', linewidth = 3, 
         marker='o', markerfacecolor='blue', markersize=12)

ax.plot(lower_x, lower_y, color='orange', linewidth = 3, 
         marker='o', markerfacecolor='blue', markersize=12) 

fig.canvas.draw()
image = np.frombuffer(fig.canvas.tostring_rgb(), dtype='uint8')
gif.append(image.reshape(fig.canvas.get_width_height()[::-1] + (3,)))
imageio.mimsave('./kirk.gif', gif, fps=2)
    
    