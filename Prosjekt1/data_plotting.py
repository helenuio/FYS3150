import matplotlib.pyplot as plt

myfile = open("b-fil3", "r")

n = []
e = []
x = []
for i in myfile:
    i = i.split()
    x.append(i[0])
    n.append(i[1])
    e.append(i[2])

plt.plot(x,n, label="numerisk")
plt.plot(x,e, label="eksakt")
plt.legend()
plt.show()
myfile.close()
