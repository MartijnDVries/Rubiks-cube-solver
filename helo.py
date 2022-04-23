from textwrap import wrap
import re
from ursina import *

test_string = "go--y-g---y-g-r-y-go----g-r---go-w--g--w--g-rw---o--y---r-y--o-w----rw---o--yb----yb--r-yb-o---b--r--b-o-w-b---w-b--rw-b"
re_list = re.findall('......', test_string)
for chunk in re_list:
    color_list  = list()
    for letter in chunk:
        if letter == 'g':
            color_list.append("green")
        elif letter == 'w':
            color_list.append("white")
        elif letter == 'b':
            color_list.append("blue")
        elif letter == 'y':
            color_list.append("yellow")
        elif letter == 'r':
            color_list.append("red")
        elif letter == 'o':
            color_list.append("orange")
        elif letter == '-':
            color_list.append("black")
    print(color_list)
    print(len(color_list))