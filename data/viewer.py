import os
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm

data_path = os.path.dirname(os.path.realpath(__file__))
in_file = os.path.join(data_path, "target.csv")
out_file = os.path.join(data_path, "out.csv")


def parse_2d(file=in_file):

    with open(file) as f:

        lines = f.readlines()
        x1s = []
        x2s = []
        colors = []

        for line in lines:
            x1, x2, color = [float(x) for x in line.split(",")]
            x1s += [x1]
            x2s += [x2]
            colors += [color]

    return x1s, x2s, colors


def plot2d(x1s, x2s, colors):
    plt.scatter(x1s, x2s, c=colors, marker=".")
    plt.show()


#x1s, x2s, xcolors = parse_2d(file=in_file)
y1s, y2s, ycolors = parse_2d(file=out_file)
#plot2d(x1s, x2s, xcolors)
plot2d(y1s, y2s, ycolors)