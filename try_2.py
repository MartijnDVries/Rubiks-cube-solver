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

class Solver:
    def __init__(self):
        self.solved = False
        self.direction_list = list()
        self.white_edge_left = False
        self.white_edge_front = False
        self.white_edge_right = False
        self.white_edge_back =  False
        self.white_edges_solved = False
        self.cube_solved = False

    def reset_solver(self):
        self.white_edge_left = False
        self.white_edge_front = False
        self.white_edge_right = False
        self.white_edge_back =  False
        self.white_edges_solved = False
        self.cube_solved = False

    def solve_cube(self, cube_list, pos_list):
        if not self.white_edges_solved:
            self.solve_white_edges(cube_list, pos_list)
            return self.direction_list
        if self.white_edges_solved:
            self.solve_white_corners(cube_list, pos_list)

        #
        # if not self.cube_solved:
        #     return self.direction_list

    def solve_white_edges(self, cube_list, pos_list):
        self.direction_list = list()
        for cube in cube_list:
            # First we check the left side of the cube
                # left top
            if cube.position == pos_list[0,2,1]:
                if cube.top_color == color.white:
                    if cube.left_color == color.orange:
                        self.white_edge_left = True
                    elif cube.left_color == color.red \
                        or cube.left_color == color.blue \
                        or cube.left_color == color.green:
                        directions = ["turn_left_left",
                                      "turn_left_left",
                                      "turn_bottom_right"]
                        self.direction_list.extend(directions)
                        break
                elif cube.left_color == color.white:
                    if cube.top_color == color.orange:
                        directions = ["turn_left_right",
                                      "turn_front_left",
                                      "turn_bottom_left",
                                      "turn_front_right",
                                      "turn_left_right",
                                      "turn_left_right"]
                        self.direction_list.extend(directions)
                        self.white_edge_left = True
                        break
                    elif cube.top_color == color.red \
                            or cube.top_color == color.blue \
                            or cube.top_color == color.green:
                        directions = ["turn_left_right",
                                      "turn_left_right",
                                      "turn_bottom_right"]
                        self.direction_list.extend(directions)
                        break
                # left back
            if cube.position == pos_list[0,1,2]:
                if cube.back_color == color.white:
                    if cube.left_color == color.orange:
                        directions = ["turn_left_right"]
                        self.direction_list.extend(directions)
                        self.white_edge_left = True
                        break
                    elif cube.left_color == color.red \
                            or cube.left_color == color.green:
                        directions = ["turn_back_right",
                                      "turn_bottom_right",
                                      "turn_back_left"]
                        self.direction_list.extend(directions)
                        break
                    elif cube.left_color == color.blue:
                        directions = ["turn_left_left",
                                      "turn_bottom_left",
                                      "turn_left_right",
                                      "turn_back_right",
                                      "turn_back_right"]
                        self.direction_list.extend(directions)
                        self.white_edge_back = True
                        break
                elif cube.left_color == color.white:
                    if cube.back_color == color.orange:
                        directions = ["turn_back_right",
                                      "turn_bottom_right",
                                      "turn_back_left",
                                      "turn_left_right",
                                      "turn_left_right"]
                        self.direction_list.extend(directions)
                        self.white_edge_left = True
                        break
                    elif cube.back_color == color.red \
                            or cube.back_color == color.green:
                        directions = ["turn_back_right",
                                      "turn_bottom_right",
                                      "turn_back_left"]
                        self.direction_list.extend(directions)
                        break
                    elif cube.back_color == color.blue:
                        directions = ["turn_back_left"]
                        self.direction_list.extend(directions)
                        self.white_edge_back = True
                        break
                # left front
            if cube.position == pos_list[0,1,0]:
                if cube.front_color == color.white:
                    if cube.left_color == color.orange:
                        directions = ["turn_left_left"]
                        self.direction_list.extend(directions)
                        self.white_edge_left = True
                        break
                    elif cube.left_color == color.red \
                            or cube.left_color == color.blue:
                        directions = ["turn_front_left",
                                      "turn_bottom_right",
                                      "turn_front_right"]
                        self.direction_list.extend(directions)
                        break
                    elif cube.left_color == color.green:
                        directions = ["turn_left_right",
                                      "turn_bottom_right",
                                      "turn_left_left",
                                      "turn_front_left",
                                      "turn_front_left"]
                        self.direction_list.extend(directions)
                        self.white_edge_front = True
                        break
                elif cube.left_color == color.white:
                    if cube.front_color == color.orange:
                        directions = ["turn_front_left",
                                      "turn_bottom_left",
                                      "turn_front_right",
                                      "turn_left_right",
                                      "turn_left_right"]
                        self.direction_list.extend(directions)
                        self.white_edge_left = True
                        break
                    elif cube.front_color == color.red \
                            or cube.front_color == color.blue:
                        directions = ["turn_front_left",
                                      "turn_bottom_right",
                                      "turn_front_right"]
                        self.direction_list.extend(directions)
                        break
                    elif cube.front_color == color.green:
                        directions = ["turn_front_right"]
                        self.direction_list.extend(directions)
                        self.white_edge_front = True
                        break
                # front top
            if cube.position == pos_list[1,2,0]:
                if cube.top_color == color.white:
                    if cube.front_color == color.green:
                        self.white_edge_front = True
                    elif cube.front_color == color.red \
                            or cube.front_color == color.blue \
                            or cube.front_color == color.orange:
                        directions = ["turn_front_right",
                                      "turn_front_right",
                                      "turn_bottom_right"]
                        self.direction_list.extend(directions)
                        break
                elif cube.front_color == color.white:
                    if cube.top_color == color.green:
                        directions = ["turn_front_right",
                                      "turn_right_left",
                                      "turn_bottom_right",
                                      "turn_right_right",
                                      "turn_front_right",
                                      "turn_front_right"]
                        self.direction_list.extend(directions)
                        self.white_edge_front = True
                        break
                    elif cube.top_color == color.red \
                            or cube.top_color == color.blue \
                            or cube.top_color == color.orange:
                        directions = ["turn_front_right",
                                      "turn_front_right",
                                      "turn_bottom_right"]
                        self.direction_list.extend(directions)
                        break
                # Front right edge
            if cube.position == pos_list[2,1,0]:
                if cube.right_color == color.white:
                    if cube.front_color == color.green:
                        directions = ["turn_front_left"]
                        self.direction_list.extend(directions)
                        self.white_edge_front = True
                        break
                    elif cube.front_color == color.orange \
                            or cube.front_color == color.blue:
                        directions = ["turn_front_right",
                                      "turn_bottom_right",
                                      "turn_front_left"]
                        self.direction_list.extend(directions)
                        break
                    elif cube.front_color == color.red:
                        directions = ["turn_front_right",
                                      "turn_bottom_right",
                                      "turn_front_left",
                                      "turn_right_right",
                                      "turn_right_right"]
                        self.direction_list.extend(directions)
                        self.white_edge_right = True
                        break
                elif cube.front_color == color.white:
                    if cube.right_color == color.green:
                        directions = ["turn_right_left",
                                      "turn_bottom_left",
                                      "turn_right_right",
                                      "turn_front_left",
                                      "turn_front_left"]
                        self.direction_list.extend(directions)
                        self.white_edge_front = True
                        break
                    elif cube.right_color == color.red:
                        directions = ["turn_right_right"]
                        self.direction_list.extend(directions)
                        self.white_edge_right = True
                        break
                    elif cube.right_color == color.blue \
                            or cube.right_color == color.orange:
                        directions = ["turn_right_left",
                                      "turn_bottom_right",
                                      "turn_right_right"]
                        self.direction_list.extend(directions)
                        break
                # Top right edge
            if cube.position == pos_list[2,2,1]:
                if cube.top_color == color.white:
                    if cube.right_color == color.red:
                        self.white_edge_right = True
                    elif cube.right_color == color.green \
                            or cube.right_color == color.orange \
                            or cube.right_color == color.blue:
                        directions = ["turn_right_right",
                                      "turn_right_right",
                                      "turn_bottom_right"]
                        self.direction_list.extend(directions)
                        break
                elif cube.right_color == color.white:
                    if cube.top_color == color.red:
                        directions = ["turn_right_left",
                                      "turn_front_right",
                                      "turn_bottom_right",
                                      "turn_front_left",
                                      "turn_right_right",
                                      "turn_right_right"]
                        self.direction_list.extend(directions)
                        self.white_edge_right = True
                        break
                    elif cube.top_color == color.green \
                            or cube.top_color == color.blue \
                            or cube.top_color == color.orange:
                        directions = ["turn_right_left",
                                      "turn_right_left",
                                      "turn_bottom_right"]
                        self.direction_list.extend(directions)
                        break
                # Back right
            if cube.position == pos_list[2,1,2]:
                if cube.back_color == color.white:
                    if cube.right_color == color.red:
                        directions = ["turn_right_left"]
                        self.direction_list.extend(directions)
                        self.white_edge_right = True
                        break
                    elif cube.right_color == color.green \
                            or cube.right_color == color.orange:
                        directions = ["turn_right_right",
                                      "turn_bottom_right",
                                      "turn_right_left"]
                        self.direction_list.extend(directions)
                        break
                    elif cube.right_color == color.blue:
                        directions = ["turn_right_right",
                                      "turn_bottom_right",
                                      "turn_right_left",
                                      "turn_back_right",
                                      "turn_back_right"]
                        self.direction_list.extend(directions)
                        self.white_edge_back = True
                        break
                elif cube.right_color == color.white:
                    if cube.back_color == color.red:
                        directions = ["turn_back_left",
                                      "turn_bottom_left",
                                      "turn_back_right",
                                      "turn_right_right",
                                      "turn_right_right"]
                        self.direction_list.extend(directions)
                        self.white_edge_right = True
                        break
                    elif cube.back_color == color.green \
                            or cube.back_color == color.orange:
                        directions = ["turn_back_left",
                                      "turn_bottom_right",
                                      "turn_back_right"]
                        self.direction_list.extend(directions)
                        break
                    elif cube.back_color == color.blue:
                        directions = ["turn_back_right"]
                        self.direction_list.extend(directions)
                        self.white_edge_back = True
                        break
                # Top back edge
            if cube.position == pos_list[1,2,2]:
                if cube.top_color == color.white:
                    if cube.back_color == color.blue:
                        self.white_edge_back = True
                    elif cube.back_color == color.green \
                            or cube.back_color == color.red \
                            or cube.back_color == color.orange:
                        directions = ["turn_back_left",
                                      "turn_back_left",
                                      "turn_bottom_right"]
                        self.direction_list.extend(directions)
                        break
                elif cube.back_color == color.white:
                    if cube.top_color == color.blue:
                        directions = ["turn_back_right",
                                      "turn_left_left",
                                      "turn_bottom_left",
                                      "turn_left_right",
                                      "turn_back_left",
                                      "turn_back_left"]
                        self.direction_list.extend(directions)
                        self.white_edge_back = True
                        break
                    elif cube.top_color == color.green \
                            or cube.top_color == color.orange \
                            or cube.top_color == color.red:
                        directions = ["turn_back_left",
                                      "turn_back_left",
                                      "turn_bottom_right"]
                        self.direction_list.extend(directions)
                        break
                # Front bottom edge
            if cube.position == pos_list[1,0,0]:
                if cube.bottom_color == color.white:
                    if cube.front_color == color.green:
                        directions = ["turn_front_right",
                                      "turn_front_right"]
                        self.direction_list.extend(directions)
                        self.white_edge_front = True
                        break
                    elif cube.front_color == color.orange:
                        directions = ["turn_bottom_left",
                                      "turn_left_left",
                                      "turn_left_left",]
                        self.direction_list.extend(directions)
                        self.white_edge_left = True
                        break
                    elif cube.front_color == color.blue:
                        directions = ["turn_bottom_left",
                                      "turn_bottom_left",
                                      "turn_back_left",
                                      "turn_back_left"]
                        self.direction_list.extend(directions)
                        self.white_edge_back = True
                        break
                    elif cube.front_color == color.red:
                        directions = ["turn_bottom_right",
                                      "turn_right_left",
                                      "turn_right_left"]
                        self.direction_list.extend(directions)
                        self.white_edge_right = True
                        break
                elif cube.front_color == color.white:
                    if cube.bottom_color == color.green:
                        directions = ["turn_front_left",
                                      "turn_right_left",
                                      "turn_bottom_left",
                                      "turn_right_right",
                                      "turn_front_left",
                                      "turn_front_left"]
                        self.direction_list.extend(directions)
                        self.white_edge_front = True
                        break
                    elif cube.bottom_color == color.orange:
                        directions = ["turn_bottom_left",
                                      "turn_left_left",
                                      "turn_front_left",
                                      "turn_bottom_left",
                                      "turn_front_right",
                                      "turn_left_left",
                                      "turn_left_left"]
                        self.direction_list.extend(directions)
                        self.white_edge_left = True
                        break
                    elif cube.bottom_color == color.blue:
                        directions = ["turn_bottom_left",
                                      "turn_bottom_left",
                                      "turn_back_left",
                                      "turn_left_left",
                                      "turn_bottom_left",
                                      "turn_left_right",
                                      "turn_back_left",
                                      "turn_back_left"]
                        self.direction_list.extend(directions)
                        self.white_edge_back = True
                        break
                    elif cube.bottom_color == color.red:
                        directions = ["turn_bottom_right",
                                      "turn_right_right",
                                      "turn_front_right",
                                      "turn_bottom_right",
                                      "turn_front_left",
                                      "turn_right_right",
                                      "turn_right_right"]
                        self.direction_list.extend(directions)
                        self.white_edge_right = True
                        break
                # Bottom right
            if cube.position  == pos_list[2,0,1]:
                if cube.bottom_color == color.white:
                    if cube.right_color == color.red:
                        directions = ["turn_right_right",
                                      "turn_right_right"]
                        self.direction_list.extend(directions)
                        self.white_edge_right = True
                        break
                    elif cube.right_color == color.green:
                        directions = ["turn_bottom_left",
                                      "turn_front_left",
                                      "turn_front_left"]
                        self.direction_list.extend(directions)
                        self.white_edge_front = True
                        break
                    elif cube.right_color == color.blue:
                        directions = ["turn_bottom_right",
                                      "turn_back_right",
                                      "turn_back_right"]
                        self.direction_list.extend(directions)
                        self.white_edge_back = True
                        break
                    elif cube.right_color == color.orange:
                        directions = ["turn_bottom_right",
                                      "turn_bottom_right",
                                      "turn_left_left",
                                      "turn_left_left"]
                        self.direction_list.extend(directions)
                        self.white_edge_left = True
                        break
                elif cube.right_color == color.white:
                    if cube.bottom_color == color.red:
                        directions = ["turn_right_right",
                                      "turn_front_right",
                                      "turn_bottom_right",
                                      "turn_front_left",
                                      "turn_right_right",
                                      "turn_right_right"]
                        self.direction_list.extend(directions)
                        self.white_edge_right = True
                        break
                    elif cube.bottom_color ==  color.blue:
                        directions = ["turn_bottom_right",
                                      "turn_back_right",
                                      "turn_right_right",
                                      "turn_bottom_right",
                                      "turn_right_left",
                                      "turn_back_right",
                                      "turn_back_right"]
                        self.direction_list.extend(directions)
                        self.white_edge_back = True
                        break
                    elif cube.bottom_color == color.orange:
                        directions = ["turn_bottom_right",
                                      "turn_bottom_right",
                                      "turn_left_left",
                                      "turn_front_left",
                                      "turn_bottom_left",
                                      "turn_front_right",
                                      "turn_left_left",
                                      "turn_left_left"]
                        self.direction_list.extend(directions)
                        self.white_edge_left = True
                        break
                    elif cube.bottom_color == color.green:
                        directions = ["turn_bottom_left",
                                      "turn_front_left",
                                      "turn_right_left",
                                      "turn_bottom_left",
                                      "turn_right_right",
                                      "turn_front_left",
                                      "turn_front_left"]
                        self.direction_list.extend(directions)
                        self.white_edge_front = True
                        break
                # Bottom back
            if cube.position == pos_list[1,0,2]:
                if cube.bottom_color == color.white:
                    if cube.back_color == color.blue:
                        directions = ["turn_back_left",
                                      "turn_back_left"]
                        self.direction_list.extend(directions)
                        self.white_edge_back = True
                        break
                    elif cube.back_color == color.green:
                        directions = ["turn_bottom_left",
                                      "turn_bottom_left",
                                      "turn_front_left",
                                      "turn_front_left"]
                        self.direction_list.extend(directions)
                        self.white_edge_front = True
                        break
                    elif cube.back_color == color.red:
                        directions = ["turn_bottom_left",
                                      "turn_right_right",
                                      "turn_right_right"]
                        self.direction_list.extend(directions)
                        self.white_edge_right = True
                        break
                    elif cube.back_color == color.orange:
                        directions = ["turn_bottom_right",
                                      "turn_left_left",
                                      "turn_left_left"]
                        self.direction_list.extend(directions)
                        self.white_edge_left = True
                        break
                elif cube.back_color == color.white:
                    if cube.bottom_color == color.blue:
                        directions = ["turn_back_left",
                                      "turn_left_left",
                                      "turn_bottom_left",
                                      "turn_left_right",
                                      "turn_back_left",
                                      "turn_back_left"]
                        self.direction_list.extend(directions)
                        self.white_edge_back = True
                        break
                    elif cube.bottom_color == color.orange:
                        directions = ["turn_bottom_right",
                                      "turn_left_left",
                                      "turn_front_left",
                                      "turn_bottom_left",
                                      "turn_front_right",
                                      "turn_left_left",
                                      "turn_left_left"]
                        self.direction_list.extend(directions)
                        self.white_edge_left = True
                        break
                    elif cube.bottom_color == color.red:
                        directions = ["turn_bottom_left",
                                      "turn_right_right",
                                      "turn_front_right",
                                      "turn_bottom_right",
                                      "turn_front_left",
                                      "turn_right_right",
                                      "turn_right_right"]
                        self.direction_list.extend(directions)
                        self.white_edge_right = True
                        break
                    elif cube.bottom_color == color.green:
                        directions = ["turn_bottom_left",
                                      "turn_bottom_left",
                                      "turn_front_left",
                                      "turn_right_left",
                                      "turn_bottom_left",
                                      "turn_right_right",
                                      "turn_front_right",
                                      "turn_front_right"]
                        self.direction_list.extend(directions)
                        self.white_edge_front = True
                        break
                # Bottom left
            if cube.position == pos_list[0,0,1]:
                if cube.bottom_color == color.white:
                    if cube.left_color == color.orange:
                        directions = ["turn_left_left",
                                      "turn_left_left"]
                        self.direction_list.extend(directions)
                        self.white_edge_left = True
                        break
                    elif cube.left_color == color.blue:
                        directions = ["turn_bottom_left",
                                      "turn_back_left",
                                      "turn_back_left"]
                        self.direction_list.extend(directions)
                        self.white_edge_back = True
                        break
                    elif cube.left_color == color.red:
                        directions = ["turn_bottom_left",
                                      "turn_bottom_left",
                                      "turn_right_right",
                                      "turn_right_right"]
                        self.direction_list.extend(directions)
                        self.white_edge_right = True
                        break
                    elif cube.left_color == color.green:
                        directions = ["turn_bottom_right",
                                      "turn_front_right",
                                      "turn_front_right"]
                        self.direction_list.extend(directions)
                        self.white_edge_front = True
                        break
                elif cube.left_color == color.white:
                    if cube.bottom_color == color.orange:
                        directions = ["turn_left_left",
                                      "turn_front_left",
                                      "turn_bottom_left",
                                      "turn_front_right",
                                      "turn_left_left",
                                      "turn_left_left"]
                        self.direction_list.extend(directions)
                        self.white_edge_left = True
                        break
                    elif cube.bottom_color == color.green:
                        directions = ["turn_bottom_right",
                                      "turn_front_right",
                                      "turn_left_right",
                                      "turn_bottom_right",
                                      "turn_left_left",
                                      "turn_front_left",
                                      "turn_front_left"]
                        self.direction_list.extend(directions)
                        self.white_edge_front = True
                        break
                    elif cube.bottom_color == color.red:
                        directions = ["turn_bottom_right",
                                      "turn_bottom_right",
                                      "turn_right_right",
                                      "turn_front_right",
                                      "turn_bottom_right",
                                      "turn_front_left",
                                      "turn_right_left",
                                      "turn_right_left"]
                        self.direction_list.extend(directions)
                        self.white_edge_right = True
                        break
                    elif cube.bottom_color == color.blue:
                        directions = ["turn_bottom_left",
                                      "turn_back_left",
                                      "turn_left_left",
                                      "turn_bottom_left",
                                      "turn_left_right",
                                      "turn_back_left",
                                      "turn_back_left"]
                        self.direction_list.extend(directions)
                        self.white_edge_back = True
                        break


        if self.white_edge_left and self.white_edge_front and self.white_edge_back and self.white_edge_right:
            self.white_edges_solved = True

    def solve_white_corners(self, cube_list, pos_list):
        print("solving_white_corners")




    def move(self):
        return self.direction_list







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
s = Solver()
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
        print("start randomizing")
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
        print("randomized")
        s.reset_solver()


    elif key == 'p':
        while not s.cube_solved:
            dir_list = s.solve_cube(cube_list, pos_list)
            if dir_list != [] and dir_list is not None:
                print(dir_list)
                for dir in dir_list:
                    if dir == "turn_front_left":
                        turn_front_left(cube_list, pos_list)
                    elif dir == "turn_front_right":
                        turn_front_right(cube_list, pos_list)
                    elif dir == "turn_left_right":
                        turn_left_right(cube_list, pos_list)
                    elif dir == "turn_left_left":
                        turn_left_left(cube_list, pos_list)
                    elif dir == "turn_bottom_right":
                        turn_bottom_right(cube_list, pos_list)
                    elif dir == "turn_bottom_left":
                        turn_bottom_left(cube_list, pos_list)
                    elif dir == "turn_right_right":
                        turn_right_right(cube_list, pos_list)
                    elif dir == "turn_right_left":
                        turn_right_left(cube_list, pos_list)
                    elif dir == "turn_back_right":
                        turn_back_right(cube_list, pos_list)
                    elif dir == "turn_back_left":
                        turn_back_left(cube_list, pos_list)
                    elif dir == "turn_top_left":
                        turn_top_left(cube_list, pos_list)
                    elif dir == "turn_top_right":
                        turn_top_right(cube_list, pos_list)
            elif not dir_list or dir_list is None:
                print("no solutions found")
                break



set_camera()
EditorCamera()
app.run()