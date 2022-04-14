from ursina import *
import math

class Rubiks(Entity):
    def __init__(self, front_color=color.black, back_color= color.black, left_color=color.black, right_color=color.black, top_color=color.black, bottom_color=color.black, position=None):
        super().__init__()
        self.pos_list = dict()
        self.cube_list = list()
        self.position = position
        self.facing_side = "green"
        self.front_color = front_color
        self.back_color = back_color
        self.left_color = left_color
        self.right_color = right_color
        self.top_color = top_color
        self.bottom_color = bottom_color
        self.model = self.ColorCube()

    def ColorCube(self):
        e = Entity()

        Entity(parent=e, model="quad",color=self.bottom_color, x=0, y=-0.5, z=0, rotation_x=-90)
        Entity(parent=e, model="quad", color=self.top_color, x=0, y=0.5, z=0, rotation_x=90)
        Entity(parent=e, model="quad",color=self.front_color, x=0, y=0, z=-0.5)
        Entity(parent=e, model="quad", color=self.back_color, x=0, y=0, z=0.5, rotation_x=180)
        Entity(parent=e, model="quad", color=self.left_color, x=-0.5, y=0, z=0, rotation_y=90)
        Entity(parent=e, model="quad", color=self.right_color, x=0.5, y=0, z=0, rotation_y=-90)

        cube = e.combine()
        cube.generate()
        destroy(e)

        return cube

class Facing:
    def __init__(self):
        self.facing_side = "green"

    def get_facing_position(self, camera_pos):
        if - 15 < camera_pos[0] < 15 \
                and -15 < camera_pos[1] < 15 \
                and -20 < camera_pos[2] < - 13.2:
            self.facing_side = "green"
        elif 20 > camera_pos[0] > 15 \
                and -15 < camera_pos[1] < 15 \
                and -13.2 < camera_pos[2] < 13.2:
            self.facing_side = "red"
        elif -15 < camera_pos[0] < 15 \
                and -15 < camera_pos[1] < 15 \
                and 13.2 < camera_pos[2] < 20:
            self.facing_side = "blue"
        elif -20 < camera_pos[0] < - 15 \
                and -15 < camera_pos[1] < 15 \
                and -13.2 < camera_pos[2] < 13.2:
            self.facing_side = "orange"
        elif -15 < camera_pos[0] < 15 \
                and -20 < camera_pos[1] < -15 \
                and -13.2 < camera_pos[2] < 13.2:
           self.facing_side = "yellow"
        elif -15 < camera_pos[0] < 15 \
                and 15 < camera_pos[1] < 20 \
                and -13.2 < camera_pos[2] < 13.2:
            self.facing_side = "white"

        # print(self.facing_side)


def make_positions_list():
    """set a 3d position list with the middle position in x y z dimension has coordinates (0,0,0)"""
    pos_list = dict()
    x = -2.2
    for i in range(3):
        x += 1.1
        y = -2.2
        for j in range(3):
            y += 1.1
            z = -2.2
            for k in range(3):
                z += 1.1
                pos_list[i, j, k] = tuple((x, y , z))
    return pos_list

def set_cube(pos_list):
    cube_list = list()
    cube_list.append(Rubiks(front_color=color.green, left_color=color.orange, bottom_color=color.yellow, position=pos_list[0,0,0]))
    cube_list.append(Rubiks(front_color=color.green, bottom_color=color.yellow, position=pos_list[1, 0, 0]))
    cube_list.append(Rubiks(front_color=color.green, right_color=color.red, bottom_color=color.yellow, position=pos_list[2,0,0]))
    cube_list.append(Rubiks(front_color=color.green, left_color=color.orange, position=pos_list[0,1,0]))
    cube_list.append(Rubiks(front_color=color.green, position=pos_list[1,1,0]))
    cube_list.append(Rubiks(front_color=color.green, right_color=color.red, position=pos_list[2,1,0]))
    cube_list.append(Rubiks(front_color=color.green, left_color=color.orange, top_color=color.white, position=pos_list[0,2,0]))
    cube_list.append(Rubiks(front_color=color.green, top_color=color.white, position=pos_list[1,2,0]))
    cube_list.append(Rubiks(front_color=color.green, right_color=color.red, top_color=color.white, position=pos_list[2,2,0]))
    cube_list.append(Rubiks(left_color=color.orange, bottom_color=color.yellow, position=pos_list[0,0,1]))
    cube_list.append(Rubiks(bottom_color=color.yellow, position=pos_list[1,0,1]))
    cube_list.append(Rubiks(right_color=color.red, bottom_color=color.yellow, position=pos_list[2,0,1]))
    cube_list.append(Rubiks(left_color=color.orange , position=pos_list[0,1,1]))
    cube_list.append(Rubiks(position=pos_list[1,1,1]))
    cube_list.append(Rubiks(right_color=color.red, position=pos_list[2,1,1]))
    cube_list.append(Rubiks(left_color=color.orange, top_color=color.white, position=pos_list[0,2,1]))
    cube_list.append(Rubiks(top_color=color.white, position=pos_list[1,2,1]))
    cube_list.append(Rubiks(right_color=color.red, top_color=color.white, position=pos_list[2,2,1]))
    cube_list.append(Rubiks(left_color=color.orange, bottom_color=color.yellow, back_color=color.blue, position=pos_list[0,0,2]))
    cube_list.append(Rubiks(bottom_color=color.yellow, back_color=color.blue, position=pos_list[1,0,2]))
    cube_list.append(Rubiks(right_color=color.red, bottom_color=color.yellow, back_color=color.blue, position=pos_list[2,0,2]))
    cube_list.append(Rubiks(left_color=color.orange, back_color=color.blue, position=pos_list[0,1,2]))
    cube_list.append(Rubiks(back_color=color.blue, position=pos_list[1,1,2]))
    cube_list.append(Rubiks(right_color=color.red, back_color=color.blue, position=pos_list[2,1,2]))
    cube_list.append(Rubiks(left_color=color.orange, back_color=color.blue, top_color=color.white, position=pos_list[0,2,2]))
    cube_list.append(Rubiks(back_color=color.blue, top_color=color.white, position=pos_list[1,2,2]))
    cube_list.append(Rubiks(right_color=color.red, back_color=color.blue, top_color=color.white, position=pos_list[2,2,2]))

    return cube_list
    
# Front side is the green side.
def turn_front_right(cube_list, pos_list):
    for cube in cube_list:
        if cube.position == pos_list[0,0,0]:
            cube.position = pos_list[0,2,0]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.right_color
            cube.right_color = cube.top_color
            cube.top_color = cube.left_color
            cube.left_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[1,0,0]:
            cube.position = pos_list[0,1,0]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.right_color
            cube.right_color = cube.top_color
            cube.top_color = cube.left_color
            cube.left_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,0,0]:
            cube.position = pos_list[0,0,0]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.right_color
            cube.right_color = cube.top_color
            cube.top_color = cube.left_color
            cube.left_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[0,1,0]:
            cube.position = pos_list[1,2,0]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.right_color
            cube.right_color = cube.top_color
            cube.top_color = cube.left_color
            cube.left_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,1,0]:
            cube.position = pos_list[1,0,0]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.right_color
            cube.right_color = cube.top_color
            cube.top_color = cube.left_color
            cube.left_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[0,2,0]:
            cube.position = pos_list[2,2,0]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.right_color
            cube.right_color = cube.top_color
            cube.top_color = cube.left_color
            cube.left_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[1,2,0]:
            cube.position = pos_list[2,1,0]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.right_color
            cube.right_color = cube.top_color
            cube.top_color = cube.left_color
            cube.left_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,2,0]:
            cube.position = pos_list[2,0,0]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.right_color
            cube.right_color = cube.top_color
            cube.top_color = cube.left_color
            cube.left_color = org_bottom_color
            cube.model = cube.ColorCube()

def turn_front_left(cube_list, pos_list):
    for cube in cube_list:
        if cube.position == pos_list[0,0,0]:
            cube.position = pos_list[2,0,0]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.left_color
            cube.left_color = cube.top_color
            cube.top_color = cube.right_color
            cube.right_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[1,0,0]:
            cube.position = pos_list[2,1,0]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.left_color
            cube.left_color = cube.top_color
            cube.top_color = cube.right_color
            cube.right_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,0,0]:
            cube.position = pos_list[2,2,0]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.left_color
            cube.left_color = cube.top_color
            cube.top_color = cube.right_color
            cube.right_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[0,1,0]:
            cube.position = pos_list[1,0,0]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.left_color
            cube.left_color = cube.top_color
            cube.top_color = cube.right_color
            cube.right_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,1,0]:
            cube.position = pos_list[1,2,0]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.left_color
            cube.left_color = cube.top_color
            cube.top_color = cube.right_color
            cube.right_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[0,2,0]:
            cube.position = pos_list[0,0,0]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.left_color
            cube.left_color = cube.top_color
            cube.top_color = cube.right_color
            cube.right_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[1,2,0]:
            cube.position = pos_list[0,1,0]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.left_color
            cube.left_color = cube.top_color
            cube.top_color = cube.right_color
            cube.right_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,2,0]:
            cube.position = pos_list[0,2,0]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.left_color
            cube.left_color = cube.top_color
            cube.top_color = cube.right_color
            cube.right_color = org_bottom_color
            cube.model = cube.ColorCube()

# Red side is the right-hand side
def turn_right_right(cube_list, pos_list):
    for cube in cube_list:
        if cube.position == pos_list[2,2,0]:
            cube.position = pos_list[2,2,2]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.back_color
            cube.back_color = cube.top_color
            cube.top_color = cube.front_color
            cube.front_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,2,1]:
            cube.position = pos_list[2,1,2]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.back_color
            cube.back_color = cube.top_color
            cube.top_color = cube.front_color
            cube.front_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,2,2]:
            cube.position = pos_list[2,0,2]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.back_color
            cube.back_color = cube.top_color
            cube.top_color = cube.front_color
            cube.front_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,1,0]:
            cube.position = pos_list[2,2,1]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.back_color
            cube.back_color = cube.top_color
            cube.top_color = cube.front_color
            cube.front_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,1,2]:
            cube.position = pos_list[2,0,1]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.back_color
            cube.back_color = cube.top_color
            cube.top_color = cube.front_color
            cube.front_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,0,0]:
            cube.position = pos_list[2,2,0]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.back_color
            cube.back_color = cube.top_color
            cube.top_color = cube.front_color
            cube.front_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,0,1]:
            cube.position = pos_list[2,1,0]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.back_color
            cube.back_color = cube.top_color
            cube.top_color = cube.front_color
            cube.front_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,0,2]:
            cube.position = pos_list[2,0,0]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.back_color
            cube.back_color = cube.top_color
            cube.top_color = cube.front_color
            cube.front_color = org_bottom_color
            cube.model = cube.ColorCube()

def turn_right_left(cube_list, pos_list):
    for cube in cube_list:
        if cube.position == pos_list[2,0,0]:
            cube.position = pos_list[2,0,2]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.front_color
            cube.front_color = cube.top_color
            cube.top_color = cube.back_color
            cube.back_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,0,1]:
            cube.position = pos_list[2,1,2]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.front_color
            cube.front_color = cube.top_color
            cube.top_color = cube.back_color
            cube.back_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,0,2]:
            cube.position = pos_list[2,2,2]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.front_color
            cube.front_color = cube.top_color
            cube.top_color = cube.back_color
            cube.back_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,1,0]:
            cube.position = pos_list[2,0,1]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.front_color
            cube.front_color = cube.top_color
            cube.top_color = cube.back_color
            cube.back_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,1,2]:
            cube.position = pos_list[2,2,1]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.front_color
            cube.front_color = cube.top_color
            cube.top_color = cube.back_color
            cube.back_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,2,0]:
            cube.position = pos_list[2,0,0]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.front_color
            cube.front_color = cube.top_color
            cube.top_color = cube.back_color
            cube.back_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,2,1]:
            cube.position = pos_list[2,1,0]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.front_color
            cube.front_color = cube.top_color
            cube.top_color = cube.back_color
            cube.back_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,2,2]:
            cube.position = pos_list[2,2,0]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.front_color
            cube.front_color = cube.top_color
            cube.top_color = cube.back_color
            cube.back_color = org_bottom_color
            cube.model = cube.ColorCube()

# Blue side is the back_side
def turn_back_right(cube_list, pos_list):
    for cube in cube_list:
        if cube.position == pos_list[2,0,2]:
            cube.position = pos_list[2,2,2]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.left_color
            cube.left_color = cube.top_color
            cube.top_color = cube.right_color
            cube.right_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[1,0,2]:
            cube.position = pos_list[2,1,2]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.left_color
            cube.left_color = cube.top_color
            cube.top_color = cube.right_color
            cube.right_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[0,0,2]:
            cube.position = pos_list[2,0,2]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.left_color
            cube.left_color = cube.top_color
            cube.top_color = cube.right_color
            cube.right_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,1,2]:
            cube.position = pos_list[1,2,2]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.left_color
            cube.left_color = cube.top_color
            cube.top_color = cube.right_color
            cube.right_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[0,1,2]:
            cube.position = pos_list[1,0,2]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.left_color
            cube.left_color = cube.top_color
            cube.top_color = cube.right_color
            cube.right_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,2,2]:
            cube.position = pos_list[0,2,2]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.left_color
            cube.left_color = cube.top_color
            cube.top_color = cube.right_color
            cube.right_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[1,2,2]:
            cube.position = pos_list[0,1,2]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.left_color
            cube.left_color = cube.top_color
            cube.top_color = cube.right_color
            cube.right_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[0,2,2]:
            cube.position = pos_list[0,0,2]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.left_color
            cube.left_color = cube.top_color
            cube.top_color = cube.right_color
            cube.right_color = org_bottom_color
            cube.model = cube.ColorCube()

def turn_back_left(cube_list, pos_list):
    for cube in cube_list:
        if cube.position == pos_list[2,0,2]:
            cube.position = pos_list[0,0,2]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.right_color
            cube.right_color = cube.top_color
            cube.top_color = cube.left_color
            cube.left_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[1,0,2]:
            cube.position = pos_list[0,1,2]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.right_color
            cube.right_color = cube.top_color
            cube.top_color = cube.left_color
            cube.left_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[0,0,2]:
            cube.position = pos_list[0,2,2]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.right_color
            cube.right_color = cube.top_color
            cube.top_color = cube.left_color
            cube.left_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,1,2]:
            cube.position = pos_list[1,0,2]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.right_color
            cube.right_color = cube.top_color
            cube.top_color = cube.left_color
            cube.left_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[0,1,2]:
            cube.position = pos_list[1,2,2]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.right_color
            cube.right_color = cube.top_color
            cube.top_color = cube.left_color
            cube.left_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,2,2]:
            cube.position = pos_list[2,0,2]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.right_color
            cube.right_color = cube.top_color
            cube.top_color = cube.left_color
            cube.left_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[1,2,2]:
            cube.position = pos_list[2,1,2]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.right_color
            cube.right_color = cube.top_color
            cube.top_color = cube.left_color
            cube.left_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[0,2,2]:
            cube.position = pos_list[2,2,2]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.right_color
            cube.right_color = cube.top_color
            cube.top_color = cube.left_color
            cube.left_color = org_bottom_color
            cube.model = cube.ColorCube()

# Orange side is the left-hand side
def turn_left_right(cube_list, pos_list):
    for cube in cube_list:
        if cube.position == pos_list[0,0,2]:
            cube.position = pos_list[0,2,2]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.front_color
            cube.front_color = cube.top_color
            cube.top_color = cube.back_color
            cube.back_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[0,0,1]:
            cube.position = pos_list[0,1,2]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.front_color
            cube.front_color = cube.top_color
            cube.top_color = cube.back_color
            cube.back_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[0,0,0]:
            cube.position = pos_list[0,0,2]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.front_color
            cube.front_color = cube.top_color
            cube.top_color = cube.back_color
            cube.back_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[0,1,2]:
            cube.position = pos_list[0,2,1]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.front_color
            cube.front_color = cube.top_color
            cube.top_color = cube.back_color
            cube.back_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[0,1,0]:
            cube.position = pos_list[0,0,1]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.front_color
            cube.front_color = cube.top_color
            cube.top_color = cube.back_color
            cube.back_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[0,2,2]:
            cube.position = pos_list[0,2,0]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.front_color
            cube.front_color = cube.top_color
            cube.top_color = cube.back_color
            cube.back_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[0,2,1]:
            cube.position = pos_list[0,1,0]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.front_color
            cube.front_color = cube.top_color
            cube.top_color = cube.back_color
            cube.back_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[0,2,0]:
            cube.position = pos_list[0,0,0]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.front_color
            cube.front_color = cube.top_color
            cube.top_color = cube.back_color
            cube.back_color = org_bottom_color
            cube.model = cube.ColorCube()

def turn_left_left(cube_list, pos_list):
    for cube in cube_list:
        if cube.position == pos_list[0,0,2]:
            cube.position = pos_list[0,0,0]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.back_color
            cube.back_color = cube.top_color
            cube.top_color = cube.front_color
            cube.front_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[0,0,1]:
            cube.position = pos_list[0,1,0]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.back_color
            cube.back_color = cube.top_color
            cube.top_color = cube.front_color
            cube.front_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[0,0,0]:
            cube.position = pos_list[0,2,0]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.back_color
            cube.back_color = cube.top_color
            cube.top_color = cube.front_color
            cube.front_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[0,1,2]:
            cube.position = pos_list[0,0,1]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.back_color
            cube.back_color = cube.top_color
            cube.top_color = cube.front_color
            cube.front_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[0,1,0]:
            cube.position = pos_list[0,2,1]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.back_color
            cube.back_color = cube.top_color
            cube.top_color = cube.front_color
            cube.front_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[0,2,2]:
            cube.position = pos_list[0,0,2]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.back_color
            cube.back_color = cube.top_color
            cube.top_color = cube.front_color
            cube.front_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[0,2,1]:
            cube.position = pos_list[0,1,2]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.back_color
            cube.back_color = cube.top_color
            cube.top_color = cube.front_color
            cube.front_color = org_bottom_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[0,2,0]:
            cube.position = pos_list[0,2,2]
            org_bottom_color = cube.bottom_color
            cube.bottom_color = cube.back_color
            cube.back_color = cube.top_color
            cube.top_color = cube.front_color
            cube.front_color = org_bottom_color
            cube.model = cube.ColorCube()

# White side is top side

def turn_top_right(cube_list, pos_list):
    for cube in cube_list:
        if cube.position == pos_list[0,2,0]:
            cube.position = pos_list[0,2,2]
            org_front_color = cube.front_color
            cube.front_color = cube.right_color
            cube.right_color = cube.back_color
            cube.back_color = cube.left_color
            cube.left_color = org_front_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[0,2,1]:
            cube.position = pos_list[1,2,2]
            org_front_color = cube.front_color
            cube.front_color = cube.right_color
            cube.right_color = cube.back_color
            cube.back_color = cube.left_color
            cube.left_color = org_front_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[0,2,2]:
            cube.position = pos_list[2,2,2]
            org_front_color = cube.front_color
            cube.front_color = cube.right_color
            cube.right_color = cube.back_color
            cube.back_color = cube.left_color
            cube.left_color = org_front_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[1,2,0]:
            cube.position = pos_list[0,2,1]
            org_front_color = cube.front_color
            cube.front_color = cube.right_color
            cube.right_color = cube.back_color
            cube.back_color = cube.left_color
            cube.left_color = org_front_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[1,2,2]:
            cube.position = pos_list[2,2,1]
            org_front_color = cube.front_color
            cube.front_color = cube.right_color
            cube.right_color = cube.back_color
            cube.back_color = cube.left_color
            cube.left_color = org_front_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,2,0]:
            cube.position = pos_list[0,2,0]
            org_front_color = cube.front_color
            cube.front_color = cube.right_color
            cube.right_color = cube.back_color
            cube.back_color = cube.left_color
            cube.left_color = org_front_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,2,1]:
            cube.position = pos_list[1,2,0]
            org_front_color = cube.front_color
            cube.front_color = cube.right_color
            cube.right_color = cube.back_color
            cube.back_color = cube.left_color
            cube.left_color = org_front_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,2,2]:
            cube.position = pos_list[2,2,0]
            org_front_color = cube.front_color
            cube.front_color = cube.right_color
            cube.right_color = cube.back_color
            cube.back_color = cube.left_color
            cube.left_color = org_front_color
            cube.model = cube.ColorCube()

def turn_top_left(cube_list, pos_list):
    for cube in cube_list:
        if cube.position == pos_list[0,2,0]:
            cube.position = pos_list[2,2,0]
            org_front_color = cube.front_color
            cube.front_color = cube.left_color
            cube.left_color = cube.back_color
            cube.back_color = cube.right_color
            cube.right_color = org_front_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[1,2,0]:
            cube.position = pos_list[2,2,1]
            org_front_color = cube.front_color
            cube.front_color = cube.left_color
            cube.left_color = cube.back_color
            cube.back_color = cube.right_color
            cube.right_color = org_front_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,2,0]:
            cube.position = pos_list[2,2,2]
            org_front_color = cube.front_color
            cube.front_color = cube.left_color
            cube.left_color = cube.back_color
            cube.back_color = cube.right_color
            cube.right_color = org_front_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[0,2,1]:
            cube.position = pos_list[1,2,0]
            org_front_color = cube.front_color
            cube.front_color = cube.left_color
            cube.left_color = cube.back_color
            cube.back_color = cube.right_color
            cube.right_color = org_front_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,2,1]:
            cube.position  = pos_list[1,2,2]
            org_front_color = cube.front_color
            cube.front_color = cube.left_color
            cube.left_color = cube.back_color
            cube.back_color = cube.right_color
            cube.right_color = org_front_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[0,2,2]:
            cube.position = pos_list[0,2,0]
            org_front_color = cube.front_color
            cube.front_color = cube.left_color
            cube.left_color = cube.back_color
            cube.back_color = cube.right_color
            cube.right_color = org_front_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[1,2,2]:
            cube.position = pos_list[0,2,1]
            org_front_color = cube.front_color
            cube.front_color = cube.left_color
            cube.left_color = cube.back_color
            cube.back_color = cube.right_color
            cube.right_color = org_front_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,2,2]:
            cube.position = pos_list[0,2,2]
            org_front_color = cube.front_color
            cube.front_color = cube.left_color
            cube.left_color = cube.back_color
            cube.back_color = cube.right_color
            cube.right_color = org_front_color
            cube.model = cube.ColorCube()

# Yellow side is bottom side

def turn_bottom_right(cube_list, pos_list):
    for cube in cube_list:
        if cube.position == pos_list[0,0,0]:
            cube.position = pos_list[2,0,0]
            org_front_color = cube.front_color
            cube.front_color = cube.left_color
            cube.left_color = cube.back_color
            cube.back_color = cube.right_color
            cube.right_color = org_front_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[1,0,0]:
            cube.position  = pos_list[2,0,1]
            org_front_color = cube.front_color
            cube.front_color = cube.left_color
            cube.left_color = cube.back_color
            cube.back_color = cube.right_color
            cube.right_color = org_front_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,0,0]:
            cube.position = pos_list[2,0,2]
            org_front_color = cube.front_color
            cube.front_color = cube.left_color
            cube.left_color = cube.back_color
            cube.back_color = cube.right_color
            cube.right_color = org_front_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[0,0,1]:
            cube.position = pos_list[1,0,0]
            org_front_color = cube.front_color
            cube.front_color = cube.left_color
            cube.left_color = cube.back_color
            cube.back_color = cube.right_color
            cube.right_color = org_front_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,0,1]:
            cube.position = pos_list[1,0,2]
            org_front_color = cube.front_color
            cube.front_color = cube.left_color
            cube.left_color = cube.back_color
            cube.back_color = cube.right_color
            cube.right_color = org_front_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[0,0,2]:
            cube.position = pos_list[0,0,0]
            org_front_color = cube.front_color
            cube.front_color = cube.left_color
            cube.left_color = cube.back_color
            cube.back_color = cube.right_color
            cube.right_color = org_front_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[1,0,2]:
            cube.position = pos_list[0,0,1]
            org_front_color = cube.front_color
            cube.front_color = cube.left_color
            cube.left_color = cube.back_color
            cube.back_color = cube.right_color
            cube.right_color = org_front_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,0,2]:
            cube.position = pos_list[0,0,2]
            org_front_color = cube.front_color
            cube.front_color = cube.left_color
            cube.left_color = cube.back_color
            cube.back_color = cube.right_color
            cube.right_color = org_front_color
            cube.model = cube.ColorCube()

def turn_bottom_left(cube_list, pos_list):
    for cube in cube_list:
        if cube.position == pos_list[0,0,0]:
            cube.position = pos_list[0,0,2]
            org_front_color = cube.front_color
            cube.front_color = cube.right_color
            cube.right_color = cube.back_color
            cube.back_color = cube.left_color
            cube.left_color = org_front_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[1,0,0]:
            cube.position = pos_list[0,0,1]
            org_front_color = cube.front_color
            cube.front_color = cube.right_color
            cube.right_color = cube.back_color
            cube.back_color = cube.left_color
            cube.left_color = org_front_color
            cube.model = cube.ColorCube()
        elif cube.position  == pos_list[2,0,0]:
            cube.position = pos_list[0,0,0]
            org_front_color = cube.front_color
            cube.front_color = cube.right_color
            cube.right_color = cube.back_color
            cube.back_color = cube.left_color
            cube.left_color = org_front_color
            cube.model = cube.ColorCube()
        elif cube.position  == pos_list[0,0,1]:
            cube.position = pos_list[1,0,2]
            org_front_color = cube.front_color
            cube.front_color = cube.right_color
            cube.right_color = cube.back_color
            cube.back_color = cube.left_color
            cube.left_color = org_front_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,0,1]:
            cube.position = pos_list[1,0,0]
            org_front_color = cube.front_color
            cube.front_color = cube.right_color
            cube.right_color = cube.back_color
            cube.back_color = cube.left_color
            cube.left_color = org_front_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[0,0,2]:
            cube.position = pos_list[2,0,2]
            org_front_color = cube.front_color
            cube.front_color = cube.right_color
            cube.right_color = cube.back_color
            cube.back_color = cube.left_color
            cube.left_color = org_front_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[1,0,2]:
            cube.position = pos_list[2,0,1]
            org_front_color = cube.front_color
            cube.front_color = cube.right_color
            cube.right_color = cube.back_color
            cube.back_color = cube.left_color
            cube.left_color = org_front_color
            cube.model = cube.ColorCube()
        elif cube.position == pos_list[2,0,2]:
            cube.position = pos_list[2,0,0]
            org_front_color = cube.front_color
            cube.front_color = cube.right_color
            cube.right_color = cube.back_color
            cube.back_color = cube.left_color
            cube.left_color = org_front_color
            cube.model = cube.ColorCube()





app = Ursina()
f = Facing()
pos_list = make_positions_list()
cube_list = set_cube(pos_list)

def set_camera():
    camera.position = (0 , 0)
    camera.fov = 32

def update():
    f.get_facing_position(camera.world_position)

def input(key):
    if key == '6':
        if f.facing_side == "green":
            turn_front_right(cube_list, pos_list)
        elif f.facing_side == "red":
            turn_right_right(cube_list, pos_list)
        elif f.facing_side == "blue":
            turn_back_right(cube_list, pos_list)
        elif f.facing_side == "orange":
            turn_left_right(cube_list, pos_list)
        elif f.facing_side == "white":
            turn_top_right(cube_list, pos_list)
        elif f.facing_side == "yellow":
            turn_bottom_right(cube_list, pos_list)

    elif key == '4':
        if f.facing_side == "green":
            turn_front_left(cube_list, pos_list)
        elif f.facing_side == "red":
            turn_right_left(cube_list, pos_list)
        elif f.facing_side == "blue":
            turn_back_left(cube_list, pos_list)
        elif f.facing_side == "orange":
            turn_left_left(cube_list, pos_list)
        elif f.facing_side == "white":
            turn_top_left(cube_list, pos_list)
        elif f.facing_side == "yellow":
            turn_bottom_left(cube_list, pos_list)

    elif key == '9':
        if f.facing_side == "green" \
                or f.facing_side == "orange" \
                or f.facing_side == "blue" \
                or f.facing_side == "red":
            turn_top_right(cube_list, pos_list)

    elif key == "7":
        if f.facing_side == "green" \
                or f.facing_side == "orange" \
                or f.facing_side == "blue" \
                or f.facing_side == "red":
            turn_top_left(cube_list, pos_list)

    elif key == "3":
        if f.facing_side == "green" \
                or f.facing_side == "orange" \
                or f.facing_side == "blue" \
                or f.facing_side == "red":
            turn_bottom_right(cube_list, pos_list)

    elif key == "1":
        if f.facing_side == "green" \
                or f.facing_side == "orange" \
                or f.facing_side == "blue" \
                or f.facing_side == "red":
            turn_bottom_left(cube_list, pos_list)

    elif key == "r":
        for i in range(random.randint(75, 100)):
            rando = random.randint(1, 12)
            if rando == 1:
                turn_front_left(cube_list, pos_list)
            elif rando == 2:
                turn_front_right(cube_list, pos_list)
            elif rando == 3:
                turn_left_right(cube_list, pos_list)
            elif rando == 4:
                turn_left_left(cube_list, pos_list)
            elif rando == 5:
                turn_right_right(cube_list, pos_list)
            elif rando == 6:
                turn_right_left(cube_list, pos_list)
            elif rando == 7:
                turn_back_left(cube_list, pos_list)
            elif rando == 8:
                turn_back_right(cube_list, pos_list)
            elif rando == 9:
                turn_top_right(cube_list, pos_list)
            elif rando == 10:
                turn_top_left(cube_list, pos_list)
            elif rando == 11:
                turn_bottom_left(cube_list, pos_list)
            elif rando == 12:
                turn_bottom_right(cube_list, pos_list)

set_camera()
EditorCamera()
app.run()