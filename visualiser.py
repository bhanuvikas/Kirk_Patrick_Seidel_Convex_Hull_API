import matplotlib.pyplot as plt
f = open('input.txt','r')
lines = f.readlines()
data_x=[]
data_y=[]
for line in lines:
	line= line[:-1]
	line = line.split(' ')
	x = line[0]
	y = line[1]
	data_x.append(float(x))
	data_y.append(float(y))
f.close()
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
print(len(path_x))
plt.scatter(data_x, data_y, label= "stars", color= "green",  
			marker= "*", s=30)
plt.xlabel('x - axis') 
# frequency label 
plt.ylabel('y - axis') 
# plot title 
plt.title('My scatter plot!') 
# showing legend 
plt.legend() 
  
# function to show the plot 
plt.plot(path_x, path_y, color='red', linestyle='dashed', linewidth = 3, 
         marker='o', markerfacecolor='blue', markersize=12)

plt.plot(lower_x, lower_y, color='orange', linestyle='dashed', linewidth = 3, 
         marker='o', markerfacecolor='blue', markersize=12) 
  
# setting x and y axis range 

# giving a title to my graph 
  
# function to show the plot 
plt.show() 
