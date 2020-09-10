import matplotlib.pyplot as plt
import sys

if len(sys.argv) < 1:
    print("Please write the name of the file you wish to plot")
else:
    filename = str(sys.argv[1])
    myfile = open(filename, "r")
    e = []
    x = []
    n = []
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
