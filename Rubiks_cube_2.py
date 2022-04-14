from ursina import *


class RubiksOneCube:
    def __init__(self, front_color=color.black, back_color= color.black, left_color=color.black, right_color=color.black, top_color=color.black, bottom_color=color.black):
        self.facing_side = "green"
        self.front_color = front_color
        self.back_color = back_color
        self.left_color = left_color
        self.right_color = right_color
        self.top_color = top_color
        self.bottom_color = bottom_color
        self.ColorCube()

    def ColorCube(self):
        e = Entity()

        # Entity(parent=e, model="quad",color=bottom_color, x=0, y=-0.5, z=0.5, rotation_x=-90)
        # Entity(parent=e, model="quad", color=top_color, x=0, y=0.5, z=0.5, rotation_x=90)
        # Entity(parent=e, model="quad",color=front_color, x=0, y=0, z=0)
        # Entity(parent=e, model="quad", color=back_color, x=0, y=0, z=1, rotation_x=180)
        # Entity(parent=e, model="quad", color=left_color, x=-0.5, y=0, z=0.5, rotation_y=90)
        # Entity(parent=e, model="quad", color=right_color, x=0.5, y=0, z=0.5, rotation_y=-90)

        Entity(parent=e, model="quad",color=self.bottom_color, x=0, y=-0.5, z=0, rotation_x=-90)
        Entity(parent=e, model="quad", color=self.top_color, x=0, y=0.5, z=0, rotation_x=90)
        Entity(parent=e, model="quad",color=self.front_color, x=0, y=0, z=-0.5)
        Entity(parent=e, model="quad", color=self.back_color, x=0, y=0, z=0.5, rotation_x=180)
        Entity(parent=e, model="quad", color=self.left_color, x=-0.5, y=0, z=0, rotation_y=90)
        Entity(parent=e, model="quad", color=self.right_color, x=0.5, y=0, z=0, rotation_y=-90)

        self.cube = e.combine()
        self.cube.generate()
        destroy(e)
        return self.cube



def display_cube(pos_list):
    """Display the cube with the rights colors in the start position. Also add to the cube list"""
    cube_list = list()

    cube_1 = RubiksOneCube(front_color=color.green, left_color=color.orange, bottom_color=color.yellow)
    cube_1.ColorCube()

    cube_list.append(Entity(parent=scene, model=cube_1, position=pos_list[0,0,0]))
    cube_list.append(Entity(parent=scene, model=RubiksOneCube(front_color=color.green, bottom_color=color.yellow), position=pos_list[1, 0, 0]))
    cube_list.append(Entity(parent=scene, model=RubiksOneCube(front_color=color.green, right_color=color.red, bottom_color=color.yellow), position=pos_list[2,0,0]))
    cube_list.append(Entity(parent=scene, model=RubiksOneCube(front_color=color.green, left_color=color.orange), position=pos_list[0,1,0]))
    cube_list.append(Entity(parent=scene, model=RubiksOneCube(front_color=color.green), position=pos_list[1,1,0]))
    cube_list.append(Entity(parent=scene, model=RubiksOneCube(front_color=color.green, right_color=color.red), position=pos_list[2,1,0]))
    cube_list.append(Entity(parent=scene, model=RubiksOneCube(front_color=color.green, left_color=color.orange, top_color=color.white), position=pos_list[0,2,0]))
    cube_list.append(Entity(parent=scene, model=RubiksOneCube(front_color=color.green, top_color=color.white), position=pos_list[1,2,0]))
    cube_list.append(Entity(parent=scene, model=RubiksOneCube(front_color=color.green, right_color=color.red, top_color=color.white), position=pos_list[2,2,0]))
    cube_list.append(Entity(parent=scene, model=RubiksOneCube(left_color=color.orange, bottom_color=color.yellow), position=pos_list[0,0,1]))
    cube_list.append(Entity(parent=scene, model=RubiksOneCube(bottom_color=color.yellow), position=pos_list[1,0,1]))
    cube_list.append(Entity(parent=scene, model=RubiksOneCube(right_color=color.red, bottom_color=color.yellow), position=pos_list[2,0,1]))
    cube_list.append(Entity(parent=scene, model=RubiksOneCube(left_color=color.orange ), position=pos_list[0,1,1]))
    cube_list.append(Entity(parent=scene, model=RubiksOneCube(), position=pos_list[1,1,1]))
    cube_list.append(Entity(parent=scene, model=RubiksOneCube(right_color=color.red), position=pos_list[2,1,1]))
    cube_list.append(Entity(parent=scene, model=RubiksOneCube(left_color=color.orange, top_color=color.white), position=pos_list[0,2,1]))
    cube_list.append(Entity(parent=scene, model=RubiksOneCube(top_color=color.white), position=pos_list[1,2,1]))
    cube_list.append(Entity(parent=scene, model=RubiksOneCube(right_color=color.red, top_color=color.white), position=pos_list[2,2,1]))
    cube_list.append(Entity(parent=scene, model=RubiksOneCube(left_color=color.orange, bottom_color=color.yellow, back_color=color.blue), position=pos_list[0,0,2]))
    cube_list.append(Entity(parent=scene, model=RubiksOneCube(bottom_color=color.yellow, back_color=color.blue), position=pos_list[1,0,2]))
    cube_list.append(Entity(parent=scene, model=RubiksOneCube(right_color=color.red, bottom_color=color.yellow, back_color=color.blue), position=pos_list[2,0,2]))
    cube_list.append(Entity(parent=scene, model=RubiksOneCube(left_color=color.orange, back_color=color.blue), position=pos_list[0,1,2]))
    cube_list.append(Entity(parent=scene, model=RubiksOneCube(back_color=color.blue), position=pos_list[1,1,2]))
    cube_list.append(Entity(parent=scene, model=RubiksOneCube(right_color=color.red, back_color=color.blue), position=pos_list[2,1,2]))
    cube_list.append(Entity(parent=scene, model=RubiksOneCube(left_color=color.orange, back_color=color.blue, top_color=color.white), position=pos_list[0,2,2]))
    cube_list.append(Entity(parent=scene, model=RubiksOneCube(back_color=color.blue, top_color=color.white), position=pos_list[1,2,2]))
    cube_list.append(Entity(parent=scene, model=RubiksOneCube(right_color=color.red, back_color=color.blue, top_color=color.white), position=pos_list[2,2,2]))

    return cube_list

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

def get_facing_position(camera_pos):
    if - 15 < camera_pos[0] < 15 \
            and -15 < camera_pos[1] < 15 \
            and -20 < camera_pos[2] < - 13.2:
        facing_side = "green"
        return facing_side
    elif 20 > camera_pos[0] > 15 \
            and -15 < camera_pos[1] < 15 \
            and -13.2 < camera_pos[2] < 13.2:
        facing_side = "red"
        return facing_side
    elif -15 < camera_pos[0] < 15 \
            and -15 < camera_pos[1] < 15 \
            and 13.2 < camera_pos[2] < 20:
        facing_side = "blue"
        return facing_side
    elif -20 < camera_pos[0] < - 15 \
            and -15 < camera_pos[1] < 15 \
            and -13.2 < camera_pos[2] < 13.2:
        facing_side = "orange"
        return facing_side
    elif -15 < camera_pos[0] < 15 \
            and -20 < camera_pos[1] < -15 \
            and -13.2 < camera_pos[2] < 13.2:
       facing_side = "yellow"
       return facing_side
    elif -15 < camera_pos[0] < 15 \
            and 15 < camera_pos[1] < 20 \
            and -13.2 < camera_pos[2] < 13.2:
        facing_side = "white"
        return facing_side

# Front side is the green side
def turn_front_right(cube_list, pos_list):
    for cube in cube_list:
        if cube.position == pos_list[0,0,0]:
            cube.position = pos_list[0,2,0]
            print(cube_list)

            # cube.bottom_color = cube.left_color
            # cube.right_color = cube.bottom_color
            # cube.top_color = cube.right_color
        # elif cube.position == pos_list[1,0,0]:
        #     cube.position = pos_list[0,1,0]
        #     # cube.rotation_z +=90
        #     cube.left_color = cube.top_color
        #     cube.bottom_color = cube.left_color
        #     cube.right_color = cube.bottom_color
        #     cube.top_color = cube.right_color
        # elif cube.position == pos_list[2,0,0]:
        #     cube.position = pos_list[0,0,0]
        #     # cube.rotation_z +=90
        #     cube.left_color = cube.top_color
        #     cube.bottom_color = cube.left_color
        #     cube.right_color = cube.bottom_color
        #     cube.top_color = cube.right_color
        # elif cube.position == pos_list[0,1,0]:
        #     cube.position = pos_list[1,2,0]
        #     # cube.rotation_z+=90
        #     cube.left_color = cube.top_color
        #     cube.bottom_color = cube.left_color
        #     cube.right_color = cube.bottom_color
        #     cube.top_color = cube.right_color
        # elif cube.position == pos_list[2,1,0]:
        #     cube.position = pos_list[1,0,0]
        #     # cube.rotation_z+=90
        #     cube.left_color = cube.top_color
        #     cube.bottom_color = cube.left_color
        #     cube.right_color = cube.bottom_color
        #     cube.top_color = cube.right_color
        # elif cube.position == pos_list[0,2,0]:
        #     cube.position = pos_list[2,2,0]
        #     # cube.rotation_z+=90
        #     cube.left_color = cube.top_color
        #     cube.bottom_color = cube.left_color
        #     cube.right_color = cube.bottom_color
        #     cube.top_color = cube.right_color
        # elif cube.position == pos_list[1,2,0]:
        #     cube.position = pos_list[2,1,0]
        #     # cube.rotation_z+=90
        #     cube.left_color = cube.top_color
        #     cube.bottom_color = cube.left_color
        #     cube.right_color = cube.bottom_color
        #     cube.top_color = cube.right_color
        # elif cube.position == pos_list[2,2,0]:
        #     cube.position = pos_list[2,0,0]
        #     # cube.rotation_z+=90
        #     cube.left_color = cube.top_color
        #     cube.bottom_color = cube.left_color
        #     cube.right_color = cube.bottom_color
        #     cube.top_color = cube.right_color

def turn_front_left(cube_list, pos_list):
    for cube in cube_list:
        if cube.position == pos_list[0,0,0]:
            cube.position = pos_list[2,0,0]
            cube.rotation_z -= 90
        elif cube.position == pos_list[1,0,0]:
            cube.position = pos_list[2,1,0]
            cube.rotation_z -= 90
        elif cube.position == pos_list[2,0,0]:
            cube.position = pos_list[2,2,0]
            cube.rotation_z -= 90
        elif cube.position == pos_list[0,1,0]:
            cube.position = pos_list[1,0,0]
            cube.rotation_z -= 90
        elif cube.position == pos_list[2,1,0]:
            cube.position = pos_list[1,2,0]
            cube.rotation_z -= 90
        elif cube.position == pos_list[0,2,0]:
            cube.position = pos_list[0,0,0]
            cube.rotation_z -= 90
        elif cube.position == pos_list[1,2,0]:
            cube.position = pos_list[0,1,0]
            cube.rotation_z -= 90
        elif cube.position == pos_list[2,2,0]:
            cube.position = pos_list[0,2,0]
            cube.rotation_z -= 90

def turn_right_right(cube_list, pos_list):
    for cube in cube_list:
        if cube.position == pos_list[2,2,0]:
            cube.position = pos_list[2,2,2]
            cube.rotation_z = 0
            cube.rotation_x += 90
        elif cube.position == pos_list[2,2,1]:
            cube.position = pos_list[2,1,2]
            cube.rotation_x += 90
            cube.rotation_z = 0
        elif cube.position == pos_list[2,2,2]:
            cube.position = pos_list[2,0,2]
            cube.rotation_x += 90
            cube.rotation_z = 0
        elif cube.position == pos_list[2,1,0]:
            cube.position = pos_list[2,2,1]
            cube.rotation_x += 90
            cube.rotation_z = 0
        elif cube.position == pos_list[2,1,2]:
            cube.position = pos_list[2,0,1]
            cube.rotation_x += 90
            cube.rotation_z = 0
        elif cube.position == pos_list[2,0,0]:
            cube.position = pos_list[2,2,0]
            cube.rotation_x += 90
            cube.rotation_z = 0
        elif cube.position == pos_list[2,0,1]:
            cube.position = pos_list[2,1,0]
            cube.rotation_x += 90
            cube.rotation_z = 0
        elif cube.position == pos_list[2,0,2]:
            cube.position = pos_list[2,0,0]
            cube.rotation_x += 90
            cube.rotation_z = 0




app = Ursina()
pos_list = make_positions_list()
cube_list = display_cube(pos_list)



# def input(key):
#     facing_side = get_facing_position(camera.world_position)
#     if facing_side == "green":
#         if key == '6':
#             turn_front_right()
#         elif key == '4':
#             turn_front_left()
#         elif key == '9':
#             turn_right_right()

def set_camera():
    camera.position = (0 , 0)
    camera.fov = 32

#
def update():
    for cube in cube_list:
        print(cube.position)



set_camera()
EditorCamera()

app.run()





