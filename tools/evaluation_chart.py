#!/usr/bin/python3

import numpy as np
import scipy.misc as smp
import sys
import os

def to_color(win_rate):
    if win_rate < 0.5:
        return [255, 255 * 2 * win_rate, 0]
    else:
        return [255 * ((1 - win_rate) * 2), 255, 0]

if len(sys.argv) < 2:
    print("No filename given!")
    os.exit(1)

f = open(sys.argv[1], 'r')
generation_count = int(f.readline())

# Create a 1024x1024x3 array of 8 bit unsigned integers
data = np.zeros((generation_count, generation_count, 3), dtype=np.uint8)

line_count = 0
for line in f:
    r = generation_count - 1 - (line_count // generation_count)
    c = line_count % generation_count
    data[r, c] = to_color(float(line))
    line_count = line_count + 1

img = smp.toimage(data)         # Create a PIL image
img.show()                      # View in default viewer
smp.imsave("evaluation.png", img)
