from ursina import *


class Rubiks:
    def __init__(self, front_color=color.black, back_color= color.black, left_color=color.black, right_color=color.black, top_color=color.black, bottom_color=color.black):
        super().__init__()
        self.pos_list = dict()
        self.cube_list = list()
        self.cube = None
        self.make_positions_list()
        self.facing_side = "green"
        self.front_color = front_color
        self.back_color = back_color
        self.left_color = left_color
        self.right_color = right_color
        self.top_color = top_color
        self.bottom_color = bottom_color
        self.cubic = self.ColorCube()


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

        cube = e.combine()
        cube.generate()
        destroy(e)

        return cube

    def display_cube(self):
        """Display the cube with the rights colors in the start position. Also add to the cube list"""

        self.cube_list.append(Entity(parent=scene, model=Rubkis(front_color=color.green, left_color=color.orange, bottom_color=color.yellow), position=self.pos_list[0,0,0]))
        self.cube_list.append(Entity(parent=scene, model=Rubiks(front_color=color.green, bottom_color=color.yellow), position=self.pos_list[1, 0, 0]))
        self.cube_list.append(Entity(parent=scene, model=Rubiks(front_color=color.green, right_color=color.red, bottom_color=color.yellow), position=self.pos_list[2,0,0]))
        self.cube_list.append(Entity(parent=scene, model=Rubiks(front_color=color.green, left_color=color.orange), position=self.pos_list[0,1,0]))
        self.cube_list.append(Entity(parent=scene, model=Rubiks(front_color=color.green), position=self.pos_list[1,1,0]))
        self.cube_list.append(Entity(parent=scene, model=Rubiks(front_color=color.green, right_color=color.red), position=self.pos_list[2,1,0]))
        self.cube_list.append(Entity(parent=scene, model=Rubiks(front_color=color.green, left_color=color.orange, top_color=color.white), position=self.pos_list[0,2,0]))
        self.cube_list.append(Entity(parent=scene, model=Rubiks(front_color=color.green, top_color=color.white), position=self.pos_list[1,2,0]))
        self.cube_list.append(Entity(parent=scene, model=Rubiks(front_color=color.green, right_color=color.red, top_color=color.white), position=self.pos_list[2,2,0]))
        self.cube_list.append(Entity(parent=scene, model=Rubiks(left_color=color.orange, bottom_color=color.yellow), position=self.pos_list[0,0,1]))
        self.cube_list.append(Entity(parent=scene, model=Rubiks(bottom_color=color.yellow), position=self.pos_list[1,0,1]))
        self.cube_list.append(Entity(parent=scene, model=Rubiks(right_color=color.red, bottom_color=color.yellow), position=self.pos_list[2,0,1]))
        self.cube_list.append(Entity(parent=scene, model=Rubiks(left_color=color.orange ), position=self.pos_list[0,1,1]))
        self.cube_list.append(Entity(parent=scene, model=Rubiks(), position=self.pos_list[1,1,1]))
        self.cube_list.append(Entity(parent=scene, model=Rubiks(right_color=color.red), position=self.pos_list[2,1,1]))
        self.cube_list.append(Entity(parent=scene, model=Rubiks(left_color=color.orange, top_color=color.white), position=self.pos_list[0,2,1]))
        self.cube_list.append(Entity(parent=scene, model=Rubiks(top_color=color.white), position=self.pos_list[1,2,1]))
        self.cube_list.append(Entity(parent=scene, model=Rubiks(right_color=color.red, top_color=color.white), position=self.pos_list[2,2,1]))
        self.cube_list.append(Entity(parent=scene, model=Rubiks(left_color=color.orange, bottom_color=color.yellow, back_color=color.blue), position=self.pos_list[0,0,2]))
        self.cube_list.append(Entity(parent=scene, model=Rubiks(bottom_color=color.yellow, back_color=color.blue), position=self.pos_list[1,0,2]))
        self.cube_list.append(Entity(parent=scene, model=Rubiks(right_color=color.red, bottom_color=color.yellow, back_color=color.blue), position=self.pos_list[2,0,2]))
        self.cube_list.append(Entity(parent=scene, model=Rubiks(left_color=color.orange, back_color=color.blue), position=self.pos_list[0,1,2]))
        self.cube_list.append(Entity(parent=scene, model=Rubiks(back_color=color.blue), position=self.pos_list[1,1,2]))
        self.cube_list.append(Entity(parent=scene, model=Rubiks(right_color=color.red, back_color=color.blue), position=self.pos_list[2,1,2]))
        self.cube_list.append(Entity(parent=scene, model=Rubiks(left_color=color.orange, back_color=color.blue, top_color=color.white), position=self.pos_list[0,2,2]))
        self.cube_list.append(Entity(parent=scene, model=Rubiks(back_color=color.blue, top_color=color.white), position=self.pos_list[1,2,2]))
        self.cube_list.append(Entity(parent=scene, model=Rubiks(right_color=color.red, back_color=color.blue, top_color=color.white), position=self.pos_list[2,2,2]))

    def make_positions_list(self):
        """set a 3d position list with the middle position in x y z dimension has coordinates (0,0,0)"""
        x = -2.2
        for i in range(3):
            x += 1.1
            y = -2.2
            for j in range(3):
                y += 1.1
                z = -2.2
                for k in range(3):
                    z += 1.1
                    self.pos_list[i, j, k] = tuple((x, y , z))

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

    # Front side is the green side
    def turn_front_right(self):
        for cube in self.cube_list:
            if cube.position == self.pos_list[0,0,0]:
                cube.position = self.pos_list[0,2,0]
                cube.bottom_color = cube.left_color
                cube.right_color = cube.bottom_color
                cube.top_color = cube.right_color
            elif cube.position == self.pos_list[1,0,0]:
                cube.position = self.pos_list[0,1,0]
                cube.left_color = cube.top_color
                cube.bottom_color = cube.left_color
                cube.right_color = cube.bottom_color
                cube.top_color = cube.right_color
            elif cube.position == self.pos_list[2,0,0]:
                cube.position = self.pos_list[0,0,0]
                cube.left_color = cube.top_color
                cube.bottom_color = cube.left_color
                cube.right_color = cube.bottom_color
                cube.top_color = cube.right_color
            elif cube.position == self.pos_list[0,1,0]:
                cube.position = self.pos_list[1,2,0]
                cube.left_color = cube.top_color
                cube.bottom_color = cube.left_color
                cube.right_color = cube.bottom_color
                cube.top_color = cube.right_color
            elif cube.position == self.pos_list[2,1,0]:
                cube.position = self.pos_list[1,0,0]
                cube.left_color = cube.top_color
                cube.bottom_color = cube.left_color
                cube.right_color = cube.bottom_color
                cube.top_color = cube.right_color
            elif cube.position == self.pos_list[0,2,0]:
                cube.position = self.pos_list[2,2,0]
                cube.left_color = cube.top_color
                cube.bottom_color = cube.left_color
                cube.right_color = cube.bottom_color
                cube.top_color = cube.right_color
            elif cube.position == self.pos_list[1,2,0]:
                cube.position = self.pos_list[2,1,0]
                cube.left_color = cube.top_color
                cube.bottom_color = cube.left_color
                cube.right_color = cube.bottom_color
                cube.top_color = cube.right_color
            elif cube.position == self.pos_list[2,2,0]:
                cube.position = self.pos_list[2,0,0]
                cube.left_color = cube.top_color
                cube.bottom_color = cube.left_color
                cube.right_color = cube.bottom_color
                cube.top_color = cube.right_color

    def turn_front_left(self):
        for cube in self.cube_list:
            if cube.position == self.pos_list[0,0,0]:
                cube.position = self.pos_list[2,0,0]
                cube.rotation_z -= 90
            elif cube.position == self.pos_list[1,0,0]:
                cube.position = self.pos_list[2,1,0]
                cube.rotation_z -= 90
            elif cube.position == self.pos_list[2,0,0]:
                cube.position = self.pos_list[2,2,0]
                cube.rotation_z -= 90
            elif cube.position == self.pos_list[0,1,0]:
                cube.position = self.pos_list[1,0,0]
                cube.rotation_z -= 90
            elif cube.position == self.pos_list[2,1,0]:
                cube.position = self.pos_list[1,2,0]
                cube.rotation_z -= 90
            elif cube.position == self.pos_list[0,2,0]:
                cube.position = self.pos_list[0,0,0]
                cube.rotation_z -= 90
            elif cube.position == self.pos_list[1,2,0]:
                cube.position = self.pos_list[0,1,0]
                cube.rotation_z -= 90
            elif cube.position == self.pos_list[2,2,0]:
                cube.position = self.pos_list[0,2,0]
                cube.rotation_z -= 90






app = Ursina()
R = Rubiks()
R.display_cube()

def input(key):
    if R.facing_side == "green":
        if key == '6':
            R.turn_front_right()
        elif key == '4':
            R.turn_front_left()
        elif key == '9':
            R.turn_right_right()

def set_camera():
    camera.position = (0 , 0)
    camera.fov = 32


def update():
    R.get_facing_position(camera.world_position)
    print(R.facing_side)
    print(camera.world_position)



set_camera()
EditorCamera()



app.run()





