#!/usr/bin/python3

import sys

if len(sys.argv) != 3:
    print("Need two arguments! Filename and target size.")

lines = []

with open(sys.argv[1]) as f:
    lines = f.read().splitlines()
    
target_length = int(sys.argv[2])
splitters = [int(x / target_length * len(lines)) for x in range(target_length)] + [len(lines)]

offset = splitters[0]
result = []

for limit in splitters[1:]:
    result.append(sum([int(lines[i]) for i in range(offset, limit)]) / (limit - offset))
    offset = limit
    
with open(sys.argv[1][:-4] + '_compressed.csv', 'w') as f:
    f.writelines([str(r) + '\n' for r in result])
