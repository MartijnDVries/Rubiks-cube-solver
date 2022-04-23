from ursina import *
import math
import datetime
import re

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
            # white edges
        self.white_edges_solved = False
        self.white_edge_left = False
        self.white_edge_front = False
        self.white_edge_right = False
        self.white_edge_back =  False
            #white corners
        self.white_corners_solved = False
        self.white_front_left_corner = False
        self.white_front_right_corner = False
        self.white_back_left_corner = False
        self.white_back_right_corner = False
            # middle edges
        self.middle_edges_solved = False
        self.green_orange_edge_solved = False
        self.green_red_edge_solved = False
        self.blue_red_edge_solved = False
        self.blue_orange_edge_solved = False
            # Upper cross
        self.upper_cross = False
            # Upper edges
        self.upper_edges_solved = False
            # Corners in the right spot
        self.upper_corner_placement = False
            # Solve yellow corners
        self.yellow_corners_solved = False
            # whole cube
        self.cube_solved = False

    def reset_solver(self):
        """reset all values to unsolved"""
        self.white_edge_left = False
        self.white_edge_front = False
        self.white_edge_right = False
        self.white_edge_back =  False
        self.white_edges_solved = False
        self.white_corners_solved = False
        self.white_front_left_corner = False
        self.white_front_right_corner = False
        self.white_back_left_corner = False
        self.white_back_right_corner = False
        self.middle_edges_solved = False
        self.green_orange_edge_solved = False
        self.green_red_edge_solved = False
        self.blue_red_edge_solved = False
        self.blue_orange_edge_solved = False
        self.upper_cross = False
        self.upper_edges_solved = False
        self.upper_corner_placement = False
        self.yellow_corners_solved = False
        self.cube_solved = False

    def solve_cube(self, cube_list, pos_list):
        if not self.white_edges_solved:
            self.solve_white_edges(cube_list, pos_list)
            return self.direction_list
        elif not self.white_corners_solved:
            self.solve_white_corners(cube_list, pos_list)
            return self.direction_list
        elif not self.middle_edges_solved:
            self.solve_middle_edges(cube_list, pos_list)
            return self.direction_list
        elif not self.upper_cross:
            self.solve_upper_cross(cube_list, pos_list)
            return self.direction_list
        elif not self.upper_edges_solved:
            self.solve_upper_edges(cube_list, pos_list)
            return self.direction_list
        elif not self.upper_corner_placement:
            self.set_upper_corners(cube_list, pos_list)
            return self.direction_list
        elif not self.yellow_corners_solved:
            self.solve_yellow_corners(cube_list, pos_list)
            return self.direction_list

        if self.yellow_corners_solved:
            self.cube_solved = True

    def solve_white_edges(self, cube_list, pos_list):
        # print("solving edges")
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
            print("white edges solved")

    def solve_white_corners(self, cube_list, pos_list):
        # print("solving corners")
        # start with an empty directions list again
        self.direction_list = list()
        # Then check all 8 corner positions for white pieces.
        for cube in cube_list:
            # Top left front corner
            if cube.position == pos_list[0,2,0]:
                if cube.top_color == color.white:
                    if cube.front_color == color.green:
                        self.white_front_left_corner = True
                    elif cube.front_color == color.orange \
                            or cube.front_color == color.blue \
                            or cube.front_color == color.red:
                        # get the corner to the bottom of the cube
                        directions = ["turn_front_left",
                                      "turn_bottom_right",
                                      "turn_front_right"]
                        self.direction_list.extend(directions)
                        break
                elif cube.left_color == color.white:
                    if cube.front_color == color.orange:
                        directions = ["turn_front_left",
                                      "turn_bottom_right",
                                      "turn_front_right",
                                      "turn_left_right",
                                      "turn_bottom_right",
                                      "turn_left_left"]
                        self.direction_list.extend(directions)
                        self.white_front_left_corner = True
                        break
                    elif cube.front_color == color.red \
                            or cube.front_color == color.blue \
                            or cube.front_color == color.green:
                        directions = ["turn_front_left",
                                      "turn_bottom_right",
                                      "turn_front_right"]
                        self.direction_list.extend(directions)
                        break
                elif cube.front_color == color.white:
                    if cube.top_color == color.orange:
                        directions = ["turn_front_left",
                                      "turn_bottom_left",
                                      "turn_front_right",
                                      "turn_bottom_right",
                                      "turn_front_left",
                                      "turn_bottom_left",
                                      "turn_front_right"]
                        self.direction_list.extend(directions)
                        self.white_front_left_corner = True
                        break
                    elif cube.top_color == color.blue \
                            or cube.top_color == color.green \
                            or cube.top_color == color.red:
                        directions = ["turn_front_left",
                                      "turn_bottom_right",
                                      "turn_front_right"]
                        self.direction_list.extend(directions)
                        break
            # Top right front corner
            if cube.position == pos_list[2,2,0]:
                if cube.top_color == color.white:
                    if cube.front_color == color.green:
                        self.white_front_right_corner = True
                    elif cube.front_color == color.red \
                            or cube.front_color == color.blue \
                            or cube.front_color == color.orange:
                        directions = ["turn_front_right",
                                      "turn_bottom_right",
                                      "turn_front_left"]
                        self.direction_list.extend(directions)
                        break
                elif cube.front_color == color.white:
                    if cube.top_color == color.red:
                        directions = ["turn_right_left",
                                      "turn_bottom_right",
                                      "turn_right_right",
                                      "turn_front_right",
                                      "turn_bottom_right",
                                      "turn_front_left"]
                        self.direction_list.extend(directions)
                        self.white_front_right_corner = True
                        break
                    elif cube.top_color == color.green \
                            or cube.top_color == color.orange \
                            or cube.top_color == color.blue:
                        directions = ["turn_right_left",
                                      "turn_bottom_right",
                                      "turn_right_right"]
                        self.direction_list.extend(directions)
                        break
                elif cube.right_color == color.white:
                    if cube.top_color == color.green:
                        directions = ["turn_right_left",
                                      "turn_bottom_left",
                                      "turn_right_right",
                                      "turn_bottom_right",
                                      "turn_right_left",
                                      "turn_bottom_left",
                                      "turn_right_right"]
                        self.direction_list.extend(directions)
                        self.white_front_right_corner = True
                        break
                    elif cube.top_color == color.red \
                            or cube.top_color == color.blue \
                            or cube.top_color == color.orange:
                        directions = ["turn_right_left",
                                      "turn_bottom_right",
                                      "turn_right_right"]
                        self.direction_list.extend(directions)
                        break
                # Top back left corner
            if cube.position == pos_list[0,2,2]:
                if cube.top_color == color.white:
                    if cube.left_color == color.orange:
                        self.white_back_left_corner = True
                    elif cube.left_color == color.red \
                            or cube.left_color == color.green \
                            or cube.left_color == color.blue:
                        directions = ["turn_left_left",
                                      "turn_bottom_right",
                                      "turn_left_right"]
                        self.direction_list.extend(directions)
                        break
                elif cube.left_color == color.white:
                    if cube.top_color == color.blue:
                        directions = ["turn_left_left",
                                      "turn_bottom_left",
                                      "turn_left_right",
                                      "turn_bottom_right",
                                      "turn_left_left",
                                      "turn_bottom_left",
                                      "turn_left_right"]
                        self.direction_list.extend(directions)
                        self.white_back_left_corner = True
                        break
                    elif cube.top_color == color.green \
                            or cube.top_color == color.red \
                            or cube.top_color == color.orange:
                        directions = ["turn_left_left",
                                      "turn_bottom_right",
                                      "turn_left_right"]
                        self.direction_list.extend(directions)
                        break
                elif cube.back_color == color.white:
                    if cube.top_color == color.orange:
                        directions = ["turn_left_left",
                                      "turn_bottom_right",
                                      "turn_left_right",
                                      "turn_back_right",
                                      "turn_bottom_right",
                                      "turn_back_left"]
                        self.direction_list.extend(directions)
                        self.white_back_left_corner = True
                        break
                    elif cube.top_color == color.red \
                            or cube.top_color == color.blue \
                            or cube.top_color == color.green:
                        directions = ["turn_left_left",
                                      "turn_bottom_right",
                                      "turn_left_right"]
                        self.direction_list.extend(directions)
                        break
            if cube.position == pos_list[2,2,2]:
                if cube.top_color == color.white:
                    if cube.back_color == color.blue:
                        self.white_back_right_corner = True
                    elif cube.back_color == color.green \
                            or cube.back_color == color.red \
                            or cube.back_color == color.orange:
                        directions = ["turn_right_right",
                                      "turn_bottom_right",
                                      "turn_right_left"]
                        self.direction_list.extend(directions)
                        break
                elif cube.right_color == color.white:
                    if cube.top_color == color.blue:
                        directions = ["turn_right_right",
                                      "turn_bottom_right",
                                      "turn_right_left",
                                      "turn_bottom_left",
                                      "turn_right_right",
                                      "turn_bottom_right",
                                      "turn_right_left"]
                        self.direction_list.extend(directions)
                        self.white_back_right_corner = True
                        break
                    elif cube.top_color == color.red \
                            or cube.top_color == color.green \
                            or cube.top_color == color.orange:
                        directions = ["turn_right_right",
                                      "turn_bottom_right",
                                      "turn_right_left"]
                        self.direction_list.extend(directions)
                        break
                elif cube.back_color == color.white:
                    if cube.top_color == color.red:
                        directions = ["turn_right_right",
                                      "turn_bottom_left",
                                      "turn_right_left",
                                      "turn_back_left",
                                      "turn_bottom_left",
                                      "turn_back_right"]
                        self.direction_list.extend(directions)
                        self.white_back_right_corner = True
                        break
                    elif cube.top_color == color.green \
                            or cube.top_color == color.blue \
                            or cube.top_color == color.orange:
                        directions = ["turn_right_right",
                                      "turn_bottom_right",
                                      "turn_right_left"]
                        self.direction_list.extend(directions)
                        break
                # Bottom front left corner
            if cube.position == pos_list[0,0,0]:
                if cube.bottom_color == color.white:
                    if cube.front_color == color.orange:
                        directions = ["turn_front_left",
                                      "turn_bottom_left",
                                      "turn_bottom_left",
                                      "turn_front_right",
                                      "turn_bottom_right",
                                      "turn_front_left",
                                      "turn_bottom_left",
                                      "turn_front_right"]
                        self.direction_list.extend(directions)
                        self.white_front_left_corner = True
                        break
                    else:
                        directions = ["turn_bottom_right"]
                        self.direction_list.extend(directions)
                        break
                elif cube.front_color == color.white:
                    if cube.bottom_color == color.green:
                        directions = ["turn_front_left",
                                      "turn_bottom_left",
                                      "turn_front_right"]
                        self.direction_list.extend(directions)
                        self.white_front_left_corner = True
                        break
                    else:
                        directions = ["turn_bottom_right"]
                        self.direction_list.extend(directions)
                        break
                elif cube.left_color == color.white:
                    if cube.front_color == color.green:
                        directions = ["turn_left_right",
                                      "turn_bottom_right",
                                      "turn_left_left"]
                        self.direction_list.extend(directions)
                        self.white_front_left_corner = True
                        break
                    else:
                        directions = ["turn_bottom_right"]
                        self.direction_list.extend(directions)
                        break
            if cube.position == pos_list[0,0,2]:
                if cube.bottom_color == color.white:
                    if cube.left_color == color.blue:
                        directions = ["turn_left_left",
                                      "turn_bottom_left",
                                      "turn_bottom_left",
                                      "turn_left_right",
                                      'turn_bottom_right',
                                      "turn_left_left",
                                      "turn_bottom_left",
                                      "turn_left_right"]
                        self.direction_list.extend(directions)
                        self.white_back_left_corner = True
                        break
                    else:
                        directions = ["turn_bottom_right"]
                        self.direction_list.extend(directions)
                        break
                elif cube.left_color == color.white:
                    if cube.bottom_color == color.orange:
                        directions = ["turn_left_left",
                                      "turn_bottom_left",
                                      "turn_left_right"]
                        self.direction_list.extend(directions)
                        self.white_back_left_corner = True
                        break
                    else:
                        directions = ["turn_bottom_right"]
                        self.direction_list.extend(directions)
                        break
                elif cube.back_color == color.white:
                    if cube.bottom_color == color.blue:
                        directions = ["turn_back_right",
                                      "turn_bottom_right",
                                      "turn_back_left"]
                        self.direction_list.extend(directions)
                        self.white_back_left_corner = True
                        break
                    else:
                        directions = ["turn_bottom_right"]
                        self.direction_list.extend(directions)
                        break
            if cube.position == pos_list[2,0,2]:
                if cube.bottom_color == color.white:
                    if cube.right_color == color.blue:
                        directions = ["turn_right_right",
                                      "turn_bottom_right",
                                      "turn_bottom_right",
                                      "turn_right_left",
                                      "turn_bottom_left",
                                      "turn_right_right",
                                      "turn_bottom_right",
                                      "turn_right_left"]
                        self.direction_list.extend(directions)
                        self.white_back_right_corner = True
                        break
                    else:
                        directions = ["turn_bottom_right"]
                        self.direction_list.extend(directions)
                        break
                elif cube.right_color == color.white:
                    if cube.bottom_color == color.red:
                        directions = ["turn_right_right",
                                      "turn_bottom_right",
                                      "turn_right_left"]
                        self.direction_list.extend(directions)
                        self.white_back_right_corner = True
                        break
                    else:
                        directions = ["turn_bottom_right"]
                        self.direction_list.extend(directions)
                        break
                elif cube.back_color == color.white:
                    if cube.bottom_color == color.blue:
                        directions = ["turn_back_left",
                                      "turn_bottom_left",
                                      "turn_back_right"]
                        self.direction_list.extend(directions)
                        self.white_back_right_corner = True
                        break
                    else:
                        directions = ["turn_bottom_right"]
                        self.direction_list.extend(directions)
                        break
            if cube.position == pos_list[2,0,0]:
                if cube.bottom_color == color.white:
                    if cube.front_color == color.red:
                        directions = ["turn_right_left",
                                      "turn_bottom_right",
                                      "turn_bottom_right",
                                      "turn_right_right",
                                      "turn_bottom_right",
                                      "turn_right_left",
                                      "turn_bottom_left",
                                      "turn_right_right"]
                        self.direction_list.extend(directions)
                        self.white_front_right_corner = True
                        break
                    else:
                        directions = ["turn_bottom_right"]
                        self.direction_list.extend(directions)
                        break
                elif cube.right_color == color.white:
                    if cube.bottom_color == color.red:
                        directions = ["turn_right_left",
                                      "turn_bottom_left",
                                      "turn_right_right"]
                        self.direction_list.extend(directions)
                        self.white_front_right_corner = True
                        break
                    else:
                        directions = ["turn_bottom_right"]
                        self.direction_list.extend(directions)
                        break
                elif cube.front_color == color.white:
                    if cube.bottom_color == color.green:
                        directions = ["turn_front_right",
                                      "turn_bottom_right",
                                      "turn_front_left"]
                        self.direction_list.extend(directions)
                        self.white_front_right_corner = True
                    else:
                        directions = ["turn_bottom_right"]
                        self.direction_list.extend(directions)
                        break


        if self.white_front_left_corner and self.white_front_right_corner and self.white_back_left_corner and self.white_back_right_corner:
            self.white_corners_solved = True
            print("white corners solved")

    def solve_middle_edges(self, cube_list, pos_list):
        no_solve_count = 0
        self.direction_list = list()
        for cube in cube_list:
            # First we check if there is not a possibility to line a corner piece up.
            if cube.position == pos_list[1,0,0]:
                if cube.bottom_color == color.yellow \
                        or cube.front_color == color.yellow:
                    no_solve_count += 1
                elif cube.front_color == color.green:
                    if cube.bottom_color == color.red:
                        directions = ["turn_bottom_left",
                                      "turn_right_left",
                                      "turn_bottom_right",
                                      "turn_right_right",
                                      "turn_bottom_right",
                                      "turn_front_right",
                                      "turn_bottom_left",
                                      "turn_front_left"]
                        self.direction_list.extend(directions)
                        self.green_red_edge_solved = True
                        break
                    elif cube.bottom_color == color.orange:
                        directions = ["turn_bottom_right",
                                      "turn_left_right",
                                      "turn_bottom_left",
                                      "turn_left_left",
                                      "turn_bottom_left",
                                      "turn_front_left",
                                      "turn_bottom_right",
                                      "turn_front_right"]
                        self.direction_list.extend(directions)
                        self.green_orange_edge_solved = True
                        break
                elif cube.front_color == color.blue:
                    directions = ["turn_bottom_right"]
                    self.direction_list.extend(directions)
                    break
                elif cube.front_color == color.red:
                    directions = ["turn_bottom_right"]
                    self.direction_list.extend(directions)
                    break
                elif cube.front_color == color.orange:
                    directions = ["turn_bottom_right"]
                    self.direction_list.extend(directions)
                    break
            if cube.position == pos_list[0,0,1]:
                if cube.bottom_color == color.yellow \
                        or cube.left_color == color.yellow:
                    no_solve_count += 1
                elif cube.left_color == color.orange:
                    if cube.bottom_color == color.green:
                        directions = ["turn_bottom_left",
                                      "turn_front_left",
                                      "turn_bottom_right",
                                      "turn_front_right",
                                      "turn_bottom_right",
                                      "turn_left_right",
                                      "turn_bottom_left",
                                      "turn_left_left"]
                        self.direction_list.extend(directions)
                        self.green_orange_edge_solved = True
                        break
                    elif cube.bottom_color == color.blue:
                        directions = ["turn_bottom_right",
                                      "turn_back_right",
                                      "turn_bottom_left",
                                      "turn_back_left",
                                      "turn_bottom_left",
                                      "turn_left_left",
                                      "turn_bottom_right",
                                      "turn_left_right"]
                        self.direction_list.extend(directions)
                        self.blue_orange_edge_solved = True
                        break
                elif cube.left_color == color.blue:
                    directions = ["turn_bottom_right"]
                    self.direction_list.extend(directions)
                    break
                elif cube.left_color == color.red:
                    directions = ["turn_bottom_right"]
                    self.direction_list.extend(directions)
                    break
                elif cube.left_color == color.green:
                    directions = ["turn_bottom_right"]
                    self.direction_list.extend(directions)
                    break
            if cube.position == pos_list[2,0,1]:
                if cube.bottom_color == color.yellow \
                        or cube.right_color == color.yellow:
                    no_solve_count += 1
                elif cube.right_color == color.red:
                    if cube.bottom_color == color.blue:
                        directions = ["turn_bottom_left",
                                      "turn_back_left",
                                      "turn_bottom_right",
                                      "turn_back_right",
                                      "turn_bottom_right",
                                      "turn_right_right",
                                      "turn_bottom_left",
                                      "turn_right_left"]
                        self.direction_list.extend(directions)
                        self.blue_red_edge_solved = True
                        break
                    elif cube.bottom_color == color.green:
                        directions = ["turn_bottom_right",
                                      "turn_front_right",
                                      "turn_bottom_left",
                                      "turn_front_left",
                                      "turn_bottom_left",
                                      "turn_right_left",
                                      "turn_bottom_right",
                                      "turn_right_right"]
                        self.direction_list.extend(directions)
                        self.green_red_edge_solved = True
                        break
                elif cube.right_color == color.blue:
                    directions = ["turn_bottom_right"]
                    self.direction_list.extend(directions)
                    break
                elif cube.right_color == color.green:
                    directions = ["turn_bottom_right"]
                    self.direction_list.extend(directions)
                    break
                elif cube.right_color == color.orange:
                    directions = ["turn_bottom_right"]
                    self.direction_list.extend(directions)
                    break
            if cube.position == pos_list[1,0,2]:
                if cube.bottom_color == color.yellow \
                        or cube.back_color == color.yellow:
                    no_solve_count += 1
                elif cube.back_color == color.blue:
                    if cube.bottom_color == color.red:
                        directions = ["turn_bottom_right",
                                      "turn_right_right",
                                      "turn_bottom_left",
                                      "turn_right_left",
                                      "turn_bottom_left",
                                      "turn_back_left",
                                      "turn_bottom_right",
                                      "turn_back_right"]
                        self.direction_list.extend(directions)
                        self.blue_red_edge_solved = True
                        break
                    elif cube.bottom_color == color.orange:
                        directions = ["turn_bottom_left",
                                      "turn_left_left",
                                      "turn_bottom_right",
                                      "turn_left_right",
                                      "turn_bottom_right",
                                      "turn_back_right",
                                      "turn_bottom_left",
                                      "turn_back_left"]
                        self.direction_list.extend(directions)
                        self.blue_orange_edge_solved = True
                        break
                elif cube.back_color == color.red:
                    directions = ["turn_bottom_right"]
                    self.direction_list.extend(directions)
                    break
                elif cube.back_color == color.orange:
                    directions = ["turn_bottom_right"]
                    self.direction_list.extend(directions)
                    break
                elif cube.back_color == color.green:
                    directions = ["turn_bottom_right"]
                    self.direction_list.extend(directions)
                    break

            # Middle edges
            if cube.position == pos_list[0,1,0]:
                if cube.front_color == color.green \
                        and cube.left_color == color.orange:
                    self.green_orange_edge_solved = True
                elif cube.front_color == color.orange \
                        and cube.left_color == color.green:
                    directions = ["turn_bottom_right",
                                  "turn_left_right",
                                  "turn_bottom_left",
                                  "turn_left_left",
                                  "turn_bottom_left",
                                  "turn_front_left",
                                  "turn_bottom_right",
                                  "turn_front_right",
                                  "turn_bottom_right",
                                  "turn_bottom_right",
                                  "turn_bottom_right",
                                  "turn_left_right",
                                  "turn_bottom_left",
                                  "turn_left_left",
                                  "turn_bottom_left",
                                  "turn_front_left",
                                  "turn_bottom_right",
                                  "turn_front_right"]
                    self.direction_list.extend(directions)
                    self.green_orange_edge_solved = True
                    break
                elif cube.left_color == color.red \
                        or cube.left_color == color.blue \
                        or cube.left_color == color.green \
                        or cube.left_color == color.orange:
                    directions = ["turn_bottom_right",
                                  "turn_left_right",
                                  "turn_bottom_left",
                                  "turn_left_left",
                                  "turn_bottom_left",
                                  "turn_front_left",
                                  "turn_bottom_right",
                                  "turn_front_right",
                                  "turn_bottom_right"]
                    self.direction_list.extend(directions)
                    break
            if cube.position == pos_list[2,1,0]:
                if cube.front_color == color.green \
                        and cube.right_color == color.red:
                    self.green_red_edge_solved = True
                elif cube.front_color == color.red \
                        and cube.right_color == color.green:
                    directions = ["turn_bottom_left",
                                  "turn_right_left",
                                  "turn_bottom_right",
                                  "turn_right_right",
                                  "turn_bottom_right",
                                  "turn_front_right",
                                  "turn_bottom_left",
                                  "turn_front_left",
                                  "turn_bottom_left",
                                  "turn_bottom_left",
                                  "turn_bottom_left",
                                  "turn_right_left",
                                  "turn_bottom_right",
                                  "turn_right_right",
                                  "turn_bottom_right",
                                  "turn_front_right",
                                  "turn_bottom_left",
                                  "turn_front_left"]
                    self.direction_list.extend(directions)
                    self.green_red_edge_solved = True
                    break
                elif cube.right_color == color.red \
                        or cube.right_color == color.green \
                        or cube.right_color == color.blue \
                        or cube.right_color == color.orange:
                    directions = ["turn_bottom_left",
                                  "turn_right_left",
                                  "turn_bottom_right",
                                  "turn_right_right",
                                  "turn_bottom_right",
                                  "turn_front_right",
                                  "turn_bottom_left",
                                  "turn_front_left"]
                    self.direction_list.extend(directions)
                    break
            if cube.position == pos_list[0,1,2]:
                if cube.back_color == color.blue \
                        and cube.left_color == color.orange:
                    self.blue_orange_edge_solved = True
                elif cube.back_color == color.orange \
                        and cube.left_color == color.blue:
                    directions = ["turn_bottom_left",
                                  "turn_left_left",
                                  "turn_bottom_right",
                                  "turn_left_right",
                                  "turn_bottom_right",
                                  "turn_back_right",
                                  "turn_bottom_left",
                                  "turn_back_left",
                                  "turn_bottom_left",
                                  "turn_bottom_left",
                                  "turn_bottom_left",
                                  "turn_left_left",
                                  "turn_bottom_right",
                                  "turn_left_right",
                                  "turn_bottom_right",
                                  "turn_back_right",
                                  "turn_bottom_left",
                                  "turn_back_left"]
                    self.direction_list.extend(directions)
                    self.blue_orange_edge_solved = True
                    break
                elif cube.back_color == color.orange \
                        or cube.back_color == color.green \
                        or cube.back_color == color.blue \
                        or cube.back_color == color.red:
                    directions = ["turn_bottom_left",
                                  "turn_left_left",
                                  "turn_bottom_right",
                                  "turn_left_right",
                                  "turn_bottom_right",
                                  "turn_back_right",
                                  "turn_bottom_left",
                                  "turn_back_left",
                                  "turn_bottom_right"]
                    self.direction_list.extend(directions)
                    break
            if cube.position == pos_list[2,1,2]:
                if cube.back_color == color.blue \
                        and cube.right_color == color.red:
                    self.blue_red_edge_solved = True
                elif cube.back_color == color.red \
                        and cube.right_color == color.blue:
                    directions = ["turn_bottom_right",
                                  "turn_right_right",
                                  "turn_bottom_left",
                                  "turn_right_left",
                                  "turn_bottom_left",
                                  "turn_back_left",
                                  "turn_bottom_right",
                                  "turn_back_right",
                                  "turn_bottom_right",
                                  "turn_bottom_right",
                                  "turn_bottom_right",
                                  "turn_right_right",
                                  "turn_bottom_left",
                                  "turn_right_left",
                                  "turn_bottom_left",
                                  "turn_back_left",
                                  "turn_bottom_right",
                                  "turn_back_right"]
                    self.direction_list.extend(directions)
                    self.blue_red_edge_solved = True
                    break
                elif cube.back_color == color.blue \
                        or cube.back_color == color.green \
                        or cube.back_color == color.red \
                        or cube.back_color == color.orange:
                    directions = ["turn_bottom_right",
                                  "turn_right_right",
                                  "turn_bottom_left",
                                  "turn_right_left",
                                  "turn_bottom_left",
                                  "turn_back_left",
                                  "turn_bottom_right",
                                  "turn_back_right"]
                    self.direction_list.extend(directions)
                    break


        if self.green_orange_edge_solved and self.green_red_edge_solved and self.blue_red_edge_solved and self.blue_orange_edge_solved:
            self.middle_edges_solved = True
            print("middle edges solved")

    def solve_upper_cross(self, cube_list, pos_list):
        """solve the upper cross"""
        # print("solving upper cross")
        self.direction_list = list()
        cross_list = list()
        for cube in cube_list:
            if cube.bottom_color == color.yellow:
                corner_1 = (0,0,0)
                corner_2 = (0,0,2)
                corner_3 = (2,0,0)
                corner_4 = (2,0,2)
                cross = [pos for pos,x in pos_list.items() if x == cube.position]
                if cross != [corner_1] and cross != [corner_2] and cross != [corner_3] and cross != [corner_4]:
                    cross_list.extend(cross)
        # Middle square
        a = [(1,0,1)]
        if set(a) == set(cross_list) \
                or len(cross_list) == 2:
            directions = ["turn_front_right",
                          "turn_left_right",
                          "turn_bottom_right",
                          "turn_left_left",
                          "turn_bottom_left",
                          "turn_front_left"]
            self.direction_list.extend(directions)

        # L - shape front is green
        a = [(1,0,2), (1,0,1), (2,0,1)]
        if set(a) == set(cross_list):
            directions = ["turn_front_right",
                          "turn_bottom_right",
                          "turn_left_right",
                          "turn_bottom_left",
                          "turn_left_left",
                          "turn_front_left"]
            self.direction_list.extend(directions)
            self.upper_cross = True

        # L-shape front is red
        a = [(1,0,2), (1,0,1), (0,0,1)]
        if set(a) == set(cross_list):
            directions = ["turn_right_right",
                          "turn_bottom_right",
                          "turn_front_right",
                          "turn_bottom_left",
                          "turn_front_left",
                          "turn_right_left"]
            self.direction_list.extend(directions)
            self.upper_cross = True

        # L-shape front is blue
        a = [(0,0,1), (1,0,1), (1,0,0)]
        if set(a) == set(cross_list):
            directions = ["turn_back_right",
                          "turn_bottom_right",
                          "turn_right_right",
                          "turn_bottom_left",
                          "turn_right_left",
                          "turn_back_left"]
            self.direction_list.extend(directions)
            self.upper_cross = True

        # L-shape front is orange
        a = [(1,0,0), (1,0,1), (2,0,1)]
        if set(a) == set(cross_list):
            directions = ["turn_left_right",
                          "turn_bottom_right",
                          "turn_back_right",
                          "turn_bottom_left",
                          "turn_back_left",
                          "turn_left_left"]
            self.direction_list.extend(directions)
            self.upper_cross = True

        # line red to orange
        a = [(1,0,1), (2,0,1), (0,0,1)]
        if set(a)  == set(cross_list):
            directions = ["turn_front_right",
                          "turn_left_right",
                          "turn_bottom_right",
                          "turn_left_left",
                          "turn_bottom_left",
                          "turn_front_left"]
            self.direction_list.extend(directions)
            self.upper_cross = True

        # line green to blue
        a = [(1,0,1), (1,0,0), (1,0,2)]
        if set(a) == set(cross_list):
            directions = ["turn_right_right",
                          "turn_front_right",
                          "turn_bottom_right",
                          "turn_front_left",
                          "turn_bottom_left",
                          "turn_right_left"]
            self.direction_list.extend(directions)
            self.upper_cross = True

        # cross is set
        a = [(1,0,0), (1,0,1), (0,0,1), (1,0,2), (2,0,1)]
        if set(a) == set(cross_list):
            self.upper_cross = True

    def solve_upper_edges(self, cube_list, pos_list):
        """Set the yellow edges on the right spot"""
        self.direction_list = list()
        configuration_list = [None, None, None]
        for cube in cube_list:
            if cube.position == pos_list[1,0,0]:
                if cube.front_color ==  color.green:
                    pass
                else:
                    directions = ["turn_bottom_left"]
                    self.direction_list.extend(directions)
                    return
            if cube.position == pos_list[2,0,1]:
                if cube.right_color == color.red:
                    configuration_list[0] = "red"
                elif cube.right_color == color.blue:
                    configuration_list[0] = "blue"
                elif cube.right_color == color.orange:
                    configuration_list[0] = "orange"
            if cube.position == pos_list[1,0,2]:
                if cube.back_color == color.blue:
                    configuration_list[1] = "blue"
                elif cube.back_color == color.red:
                    configuration_list[1] = "red"
                elif cube.back_color == color.orange:
                    configuration_list[1] = "orange"
            if cube.position == pos_list[0,0,1]:
                if cube.left_color == color.orange:
                    configuration_list[2] = "orange"
                elif cube.left_color == color.red:
                    configuration_list[2] = "red"
                elif cube.left_color == color.blue:
                    configuration_list[2] = "blue"
        if configuration_list[0] == "red":
            if configuration_list[1] == "blue":
                self.upper_edges_solved = True
                return
            elif configuration_list[1] == "orange":
                directions = ["turn_right_right",
                              "turn_bottom_right",
                              "turn_right_left",
                              "turn_bottom_right",
                              "turn_right_right",
                              "turn_bottom_right",
                              "turn_bottom_right",
                              "turn_right_left",
                              "turn_bottom_right"]
                self.direction_list.extend(directions)
                self.upper_edges_solved = True
                return
        elif configuration_list[0] == "orange":
            directions = ["turn_front_right",
                          "turn_bottom_right",
                          "turn_front_left",
                          "turn_bottom_right",
                          "turn_front_right",
                          "turn_bottom_right",
                          "turn_bottom_right",
                          "turn_front_left",
                          "turn_bottom_right",
                          "turn_right_right",
                          "turn_bottom_right",
                          "turn_right_left",
                          "turn_bottom_right",
                          "turn_right_right",
                          "turn_bottom_right",
                          "turn_bottom_right",
                          "turn_right_left",
                          "turn_bottom_right"]
            self.direction_list.extend(directions)
            if configuration_list[1] == "red":
                self.upper_edges_solved = True
                return
            elif configuration_list[1] == "blue":
                directions = ["turn_front_right",
                              "turn_bottom_right",
                              "turn_front_left",
                              "turn_bottom_right",
                              "turn_front_right",
                              "turn_bottom_right",
                              "turn_bottom_right",
                              "turn_front_left",
                              "turn_bottom_right"]
                self.direction_list.extend(directions)
                self.upper_edges_solved = True
                return
        elif configuration_list[0] == "blue":
            if configuration_list[1] == "orange":
                directions = ["turn_right_right",
                              "turn_bottom_right",
                              "turn_right_left",
                              "turn_bottom_right",
                              "turn_right_right",
                              "turn_bottom_right",
                              "turn_bottom_right",
                              "turn_right_left",
                              "turn_bottom_right",
                              "turn_front_right",
                              "turn_bottom_right",
                              "turn_front_left",
                              "turn_bottom_right",
                              "turn_front_right",
                              "turn_bottom_right",
                              "turn_bottom_right",
                              "turn_front_left",
                              "turn_bottom_right"]
                self.direction_list.extend(directions)
                self.upper_edges_solved = True
                return
            elif configuration_list[1] == "red":
                directions = ["turn_front_right",
                              "turn_bottom_right",
                              "turn_front_left",
                              "turn_bottom_right",
                              "turn_front_right",
                              "turn_bottom_right",
                              "turn_bottom_right",
                              "turn_front_left",
                              "turn_bottom_right"]
                self.direction_list.extend(directions)
                self.upper_edges_solved = True
                return

    def set_upper_corners(self, cube_list, pos_list):
        """set the corners in the right spot"""
        self.direction_list = list()
        # Make a list of the corners which are in the right position
        # First corner is (0,0,0) second is (0,0,2) third is (2,0,2) and last is (2,0,0)
        corner_list = [False, False, False, False]

        for cube in cube_list:
            if cube.position == pos_list[0,0,0]:
                if cube.bottom_color == color.yellow \
                        and cube.left_color == color.orange \
                        and cube.front_color == color.green \
                        or cube.bottom_color == color.green \
                        and cube.left_color == color.yellow \
                        and cube.front_color == color.orange \
                        or cube.bottom_color == color.orange \
                        and cube.front_color == color.yellow \
                        and cube.left_color == color.green:
                    corner_list[0] = True
            if cube.position == pos_list[0,0,2]:
                if cube.bottom_color == color.yellow \
                        and cube.left_color == color.orange \
                        and cube.back_color == color.blue \
                        or cube.bottom_color == color.blue \
                        and cube.left_color == color.yellow \
                        and cube.back_color == color.orange \
                        or cube.bottom_color == color.orange \
                        and cube.left_color == color.blue \
                        and cube.back_color == color.yellow:
                    corner_list[1] = True
            if cube.position == pos_list[2,0,2]:
                if cube.bottom_color == color.red \
                        and cube.back_color == color.yellow \
                        and cube.right_color == color.blue \
                        or cube.bottom_color == color.blue \
                        and cube.back_color == color.red \
                        and cube.right_color == color.yellow \
                        or cube.bottom_color == color.yellow \
                        and cube.right_color == color.red \
                        and cube.back_color == color.blue:
                    corner_list[2] = True
            if cube.position == pos_list[2,0,0]:
                if cube.bottom_color == color.green \
                        and cube.front_color == color.red \
                        and cube.right_color == color.yellow \
                        or cube.bottom_color == color.red \
                        and cube.front_color == color.yellow \
                        and cube.right_color == color.green \
                        or cube.bottom_color == color.yellow \
                        and cube.front_color == color.green \
                        and cube.right_color == color.red:
                    corner_list[3] = True
        print(f"corner_list is {corner_list}")
        if all(x is False for x in corner_list):
            # print("all corners false")
            directions = ["turn_bottom_right",
                          "turn_left_right",
                          "turn_bottom_left",
                          "turn_right_left",
                          "turn_bottom_right",
                          "turn_left_left",
                          "turn_bottom_left",
                          "turn_right_right"]
            self.direction_list.extend(directions)
            return
        elif all(x is True for x in corner_list):
            self.upper_corner_placement = True
            return
        else:
            if corner_list[0] is True:
                # print("corner 1")
                directions = ["turn_bottom_right",
                              "turn_left_right",
                              "turn_bottom_left",
                              "turn_right_left",
                              "turn_bottom_right",
                              "turn_left_left",
                              "turn_bottom_left",
                              "turn_right_right"]
                self.direction_list.extend(directions)
                return
            elif corner_list[1] is True:
                # print("corner 2")
                directions = ["turn_bottom_right",
                              "turn_back_right",
                              "turn_bottom_left",
                              "turn_front_left",
                              "turn_bottom_right",
                              "turn_back_left",
                              "turn_bottom_left",
                              "turn_front_right"]
                self.direction_list.extend(directions)
                return
            elif corner_list[2] is True:
                # print("corner 3")
                directions = ["turn_bottom_right",
                              "turn_right_right",
                              "turn_bottom_left",
                              "turn_left_left",
                              "turn_bottom_right",
                              "turn_right_left",
                              "turn_bottom_left",
                              "turn_left_right"]
                self.direction_list.extend(directions)
                return
            elif corner_list[3] is True:
                # print("corner 4")
                directions = ["turn_bottom_right",
                              "turn_front_right",
                              "turn_bottom_left",
                              "turn_back_left",
                              "turn_bottom_right",
                              "turn_front_left",
                              "turn_bottom_left",
                              "turn_back_right"]
                self.direction_list.extend(directions)
                return

    def solve_yellow_corners(self, cube_list, pos_list):
        """turn wrongly configurated yellow corners right"""
        self.direction_list = list()
        corner_list = [False, False, False, False]
        turn_list = [0,0,0,0]
        for cube in cube_list:
            if cube.position == pos_list[0,0,0]:
                if cube.bottom_color == color.yellow:
                    corner_list[0] = True
                elif cube.left_color == color.yellow:
                    turn_list[0] = 2
                elif cube.front_color == color.yellow:
                    turn_list[0] = 4
            if cube.position == pos_list[0,0,2]:
                if cube.bottom_color == color.yellow:
                    corner_list[1] = True
                elif cube.back_color == color.yellow:
                    turn_list[1] = 2
                elif cube.left_color == color.yellow:
                    turn_list[1] = 4
            if cube.position == pos_list[2,0,2]:
                if cube.bottom_color == color.yellow:
                    corner_list[2] = True
                elif cube.right_color == color.yellow:
                    turn_list[2] = 2
                elif cube.back_color == color.yellow:
                    turn_list[2] = 4
            if cube.position == pos_list[2,0,0]:
                if cube.bottom_color == color.yellow:
                    corner_list[3] = True
                elif cube.front_color == color.yellow:
                    turn_list[3] = 2
                elif cube.right_color == color.yellow:
                    turn_list[3] = 4
         # print(f"cornnerlist = {corner_list}, turn_list = {turn_list}")
        if all(x is True for x in corner_list):
            self.yellow_corners_solved = True
            return
        else:
            directions = ["turn_left_left",
                          "turn_top_left",
                          "turn_left_right",
                          "turn_top_right"]
            if corner_list[0] is True:
                self.direction_list.extend(["turn_bottom_right"])
            else:
                for i in range(int(turn_list[0])):
                    self.direction_list.extend(directions)
                self.direction_list.extend(["turn_bottom_right"])
            if corner_list[1] is True:
                self.direction_list.extend(["turn_bottom_right"])
            else:
                for i in range(int(turn_list[1])):
                    self.direction_list.extend(directions)
                self.direction_list.extend(["turn_bottom_right"])
            if corner_list[2] is True:
                self.direction_list.extend(["turn_bottom_right"])
            else:
                for i in range(int(turn_list[2])):
                    self.direction_list.extend(directions)
                self.direction_list.extend(["turn_bottom_right"])
            if  corner_list[3] is True:
                self.direction_list.extend(["turn_bottom_right"])
                self.yellow_corners_solved = True
            else:
                for i in range(int(turn_list[3])):
                    self.direction_list.extend(directions)
                self.direction_list.extend(["turn_bottom_right"])
                self.yellow_corners_solved = True

class RubiksCube:
    def __init__(self):
        self.pos_list = self.make_positions_list()
        self.cube_list = self.test_position()


    def make_positions_list(self):
        """set a 3d position list with the middle position in x y z dimension has coordinates (0,0,0)"""
        self.pos_list = dict()
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
        return self.pos_list

    def set_cube(self):
        self.cube_list = list()
        self.cube_list.append(Rubiks(front_color=color.green, left_color=color.orange, bottom_color=color.yellow, position=self.pos_list[0,0,0]))
        self.cube_list.append(Rubiks(front_color=color.green, bottom_color=color.yellow, position=self.pos_list[1, 0, 0]))
        self.cube_list.append(Rubiks(front_color=color.green, right_color=color.red, bottom_color=color.yellow, position=self.pos_list[2,0,0]))
        self.cube_list.append(Rubiks(front_color=color.green, left_color=color.orange, position=self.pos_list[0,1,0]))
        self.cube_list.append(Rubiks(front_color=color.green, position=self.pos_list[1,1,0]))
        self.cube_list.append(Rubiks(front_color=color.green, right_color=color.red, position=self.pos_list[2,1,0]))
        self.cube_list.append(Rubiks(front_color=color.green, left_color=color.orange, top_color=color.white, position=self.pos_list[0,2,0]))
        self.cube_list.append(Rubiks(front_color=color.green, top_color=color.white, position=self.pos_list[1,2,0]))
        self.cube_list.append(Rubiks(front_color=color.green, right_color=color.red, top_color=color.white, position=self.pos_list[2,2,0]))
        self.cube_list.append(Rubiks(left_color=color.orange, bottom_color=color.yellow, position=self.pos_list[0,0,1]))
        self.cube_list.append(Rubiks(bottom_color=color.yellow, position=self.pos_list[1,0,1]))
        self.cube_list.append(Rubiks(right_color=color.red, bottom_color=color.yellow, position=self.pos_list[2,0,1]))
        self.cube_list.append(Rubiks(left_color=color.orange , position=self.pos_list[0,1,1]))
        self.cube_list.append(Rubiks(position=self.pos_list[1,1,1]))
        self.cube_list.append(Rubiks(right_color=color.red, position=self.pos_list[2,1,1]))
        self.cube_list.append(Rubiks(left_color=color.orange, top_color=color.white, position=self.pos_list[0,2,1]))
        self.cube_list.append(Rubiks(top_color=color.white, position=self.pos_list[1,2,1]))
        self.cube_list.append(Rubiks(right_color=color.red, top_color=color.white, position=self.pos_list[2,2,1]))
        self.cube_list.append(Rubiks(left_color=color.orange, bottom_color=color.yellow, back_color=color.blue, position=self.pos_list[0,0,2]))
        self.cube_list.append(Rubiks(bottom_color=color.yellow, back_color=color.blue, position=self.pos_list[1,0,2]))
        self.cube_list.append(Rubiks(right_color=color.red, bottom_color=color.yellow, back_color=color.blue, position=self.pos_list[2,0,2]))
        self.cube_list.append(Rubiks(left_color=color.orange, back_color=color.blue, position=self.pos_list[0,1,2]))
        self.cube_list.append(Rubiks(back_color=color.blue, position=self.pos_list[1,1,2]))
        self.cube_list.append(Rubiks(right_color=color.red, back_color=color.blue, position=self.pos_list[2,1,2]))
        self.cube_list.append(Rubiks(left_color=color.orange, back_color=color.blue, top_color=color.white, position=self.pos_list[0,2,2]))
        self.cube_list.append(Rubiks(back_color=color.blue, top_color=color.white, position=self.pos_list[1,2,2]))
        self.cube_list.append(Rubiks(right_color=color.red, back_color=color.blue, top_color=color.white, position=self.pos_list[2,2,2]))
    
        return self.cube_list

    def test_position(self):
        self.cube_list = list()
        test_string = "go--y-g---y-b-r-w-go----b-r---go-w--g--w--b-ry---o--y---r-w--o-w----ry---o--yb----yb--r-wg-o---b--r--g-o-w-b---w-b--ry-g"
        re_list = re.findall('......', test_string)
        position_list = [(0,0,0),
                         (1,0,0),
                         (2,0,0),
                         (0,1,0),
                         (2,1,0),
                         (0,2,0),
                         (1,2,0),
                         (2,2,0),
                         (0,0,1),
                         (2,0,1),
                         (0,2,1),
                         (2,2,1),
                         (0,0,2),
                         (1,0,2),
                         (2,0,2),
                         (0,1,2),
                         (2,1,2),
                         (0,2,2),
                         (1,2,2),
                         (2,2,2)]
        i = 0
        for chunk in re_list:
            color_list  = list()
            for letter in chunk:
                if letter == 'g':
                    color_list.append(color.green)
                elif letter == 'w':
                    color_list.append(color.white)
                elif letter == 'b':
                    color_list.append(color.blue)
                elif letter == 'y':
                    color_list.append(color.yellow)
                elif letter == 'r':
                    color_list.append(color.red)
                elif letter == 'o':
                    color_list.append(color.orange)
                elif letter == '-':
                    color_list.append(color.black)
            print(len(color_list))
            self.cube_list.append(Rubiks(front_color=color_list[0], left_color=color_list[1], right_color=color_list[2],top_color=color_list[3], bottom_color=color_list[4], back_color= color_list[5], position=self.pos_list[position_list[i]]))
            i += 1

        self.cube_list.append(Rubiks(position=self.pos_list[1,1,1]))
        self.cube_list.append(Rubiks(front_color=color.green, position=self.pos_list[1,1,0]))
        self.cube_list.append(Rubiks(bottom_color=color.yellow, position=self.pos_list[1,0,1]))
        self.cube_list.append(Rubiks(left_color=color.orange , position=self.pos_list[0,1,1]))
        self.cube_list.append(Rubiks(right_color=color.red, position=self.pos_list[2,1,1]))
        self.cube_list.append(Rubiks(top_color=color.white, position=self.pos_list[1,2,1]))
        self.cube_list.append(Rubiks(back_color=color.blue, position=self.pos_list[1,1,2]))

        return self.cube_list


    def reset_cube(self):
        for cube in self.cube_list:
            destroy(cube)
        cube_list = self.set_cube()

    # Front side is the green side.
    def turn_front_right(self):
        for cube in self.cube_list:
            if cube.position == self.pos_list[0,0,0]:
                cube.position = self.pos_list[0,2,0]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.right_color
                cube.right_color = cube.top_color
                cube.top_color = cube.left_color
                cube.left_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[1,0,0]:
                cube.position = self.pos_list[0,1,0]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.right_color
                cube.right_color = cube.top_color
                cube.top_color = cube.left_color
                cube.left_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,0,0]:
                cube.position = self.pos_list[0,0,0]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.right_color
                cube.right_color = cube.top_color
                cube.top_color = cube.left_color
                cube.left_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[0,1,0]:
                cube.position = self.pos_list[1,2,0]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.right_color
                cube.right_color = cube.top_color
                cube.top_color = cube.left_color
                cube.left_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,1,0]:
                cube.position = self.pos_list[1,0,0]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.right_color
                cube.right_color = cube.top_color
                cube.top_color = cube.left_color
                cube.left_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[0,2,0]:
                cube.position = self.pos_list[2,2,0]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.right_color
                cube.right_color = cube.top_color
                cube.top_color = cube.left_color
                cube.left_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[1,2,0]:
                cube.position = self.pos_list[2,1,0]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.right_color
                cube.right_color = cube.top_color
                cube.top_color = cube.left_color
                cube.left_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,2,0]:
                cube.position = self.pos_list[2,0,0]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.right_color
                cube.right_color = cube.top_color
                cube.top_color = cube.left_color
                cube.left_color = org_bottom_color
                cube.model = cube.ColorCube()
    
    def turn_front_left(self):
        for cube in self.cube_list:
            if cube.position == self.pos_list[0,0,0]:
                cube.position = self.pos_list[2,0,0]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.left_color
                cube.left_color = cube.top_color
                cube.top_color = cube.right_color
                cube.right_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[1,0,0]:
                cube.position = self.pos_list[2,1,0]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.left_color
                cube.left_color = cube.top_color
                cube.top_color = cube.right_color
                cube.right_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,0,0]:
                cube.position = self.pos_list[2,2,0]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.left_color
                cube.left_color = cube.top_color
                cube.top_color = cube.right_color
                cube.right_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[0,1,0]:
                cube.position = self.pos_list[1,0,0]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.left_color
                cube.left_color = cube.top_color
                cube.top_color = cube.right_color
                cube.right_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,1,0]:
                cube.position = self.pos_list[1,2,0]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.left_color
                cube.left_color = cube.top_color
                cube.top_color = cube.right_color
                cube.right_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[0,2,0]:
                cube.position = self.pos_list[0,0,0]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.left_color
                cube.left_color = cube.top_color
                cube.top_color = cube.right_color
                cube.right_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[1,2,0]:
                cube.position = self.pos_list[0,1,0]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.left_color
                cube.left_color = cube.top_color
                cube.top_color = cube.right_color
                cube.right_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,2,0]:
                cube.position = self.pos_list[0,2,0]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.left_color
                cube.left_color = cube.top_color
                cube.top_color = cube.right_color
                cube.right_color = org_bottom_color
                cube.model = cube.ColorCube()
    
    # Red side is the right-hand side
    def turn_right_right(self):
        for cube in self.cube_list:
            if cube.position == self.pos_list[2,2,0]:
                cube.position = self.pos_list[2,2,2]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.back_color
                cube.back_color = cube.top_color
                cube.top_color = cube.front_color
                cube.front_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,2,1]:
                cube.position = self.pos_list[2,1,2]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.back_color
                cube.back_color = cube.top_color
                cube.top_color = cube.front_color
                cube.front_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,2,2]:
                cube.position = self.pos_list[2,0,2]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.back_color
                cube.back_color = cube.top_color
                cube.top_color = cube.front_color
                cube.front_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,1,0]:
                cube.position = self.pos_list[2,2,1]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.back_color
                cube.back_color = cube.top_color
                cube.top_color = cube.front_color
                cube.front_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,1,2]:
                cube.position = self.pos_list[2,0,1]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.back_color
                cube.back_color = cube.top_color
                cube.top_color = cube.front_color
                cube.front_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,0,0]:
                cube.position = self.pos_list[2,2,0]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.back_color
                cube.back_color = cube.top_color
                cube.top_color = cube.front_color
                cube.front_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,0,1]:
                cube.position = self.pos_list[2,1,0]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.back_color
                cube.back_color = cube.top_color
                cube.top_color = cube.front_color
                cube.front_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,0,2]:
                cube.position = self.pos_list[2,0,0]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.back_color
                cube.back_color = cube.top_color
                cube.top_color = cube.front_color
                cube.front_color = org_bottom_color
                cube.model = cube.ColorCube()
    
    def turn_right_left(self):
        for cube in self.cube_list:
            if cube.position == self.pos_list[2,0,0]:
                cube.position = self.pos_list[2,0,2]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.front_color
                cube.front_color = cube.top_color
                cube.top_color = cube.back_color
                cube.back_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,0,1]:
                cube.position = self.pos_list[2,1,2]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.front_color
                cube.front_color = cube.top_color
                cube.top_color = cube.back_color
                cube.back_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,0,2]:
                cube.position = self.pos_list[2,2,2]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.front_color
                cube.front_color = cube.top_color
                cube.top_color = cube.back_color
                cube.back_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,1,0]:
                cube.position = self.pos_list[2,0,1]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.front_color
                cube.front_color = cube.top_color
                cube.top_color = cube.back_color
                cube.back_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,1,2]:
                cube.position = self.pos_list[2,2,1]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.front_color
                cube.front_color = cube.top_color
                cube.top_color = cube.back_color
                cube.back_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,2,0]:
                cube.position = self.pos_list[2,0,0]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.front_color
                cube.front_color = cube.top_color
                cube.top_color = cube.back_color
                cube.back_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,2,1]:
                cube.position = self.pos_list[2,1,0]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.front_color
                cube.front_color = cube.top_color
                cube.top_color = cube.back_color
                cube.back_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,2,2]:
                cube.position = self.pos_list[2,2,0]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.front_color
                cube.front_color = cube.top_color
                cube.top_color = cube.back_color
                cube.back_color = org_bottom_color
                cube.model = cube.ColorCube()
    
    # Blue side is the back_side
    def turn_back_right(self):
        for cube in self.cube_list:
            if cube.position == self.pos_list[2,0,2]:
                cube.position = self.pos_list[2,2,2]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.left_color
                cube.left_color = cube.top_color
                cube.top_color = cube.right_color
                cube.right_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[1,0,2]:
                cube.position = self.pos_list[2,1,2]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.left_color
                cube.left_color = cube.top_color
                cube.top_color = cube.right_color
                cube.right_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[0,0,2]:
                cube.position = self.pos_list[2,0,2]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.left_color
                cube.left_color = cube.top_color
                cube.top_color = cube.right_color
                cube.right_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,1,2]:
                cube.position = self.pos_list[1,2,2]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.left_color
                cube.left_color = cube.top_color
                cube.top_color = cube.right_color
                cube.right_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[0,1,2]:
                cube.position = self.pos_list[1,0,2]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.left_color
                cube.left_color = cube.top_color
                cube.top_color = cube.right_color
                cube.right_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,2,2]:
                cube.position = self.pos_list[0,2,2]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.left_color
                cube.left_color = cube.top_color
                cube.top_color = cube.right_color
                cube.right_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[1,2,2]:
                cube.position = self.pos_list[0,1,2]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.left_color
                cube.left_color = cube.top_color
                cube.top_color = cube.right_color
                cube.right_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[0,2,2]:
                cube.position = self.pos_list[0,0,2]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.left_color
                cube.left_color = cube.top_color
                cube.top_color = cube.right_color
                cube.right_color = org_bottom_color
                cube.model = cube.ColorCube()
    
    def turn_back_left(self):
        for cube in self.cube_list:
            if cube.position == self.pos_list[2,0,2]:
                cube.position = self.pos_list[0,0,2]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.right_color
                cube.right_color = cube.top_color
                cube.top_color = cube.left_color
                cube.left_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[1,0,2]:
                cube.position = self.pos_list[0,1,2]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.right_color
                cube.right_color = cube.top_color
                cube.top_color = cube.left_color
                cube.left_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[0,0,2]:
                cube.position = self.pos_list[0,2,2]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.right_color
                cube.right_color = cube.top_color
                cube.top_color = cube.left_color
                cube.left_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,1,2]:
                cube.position = self.pos_list[1,0,2]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.right_color
                cube.right_color = cube.top_color
                cube.top_color = cube.left_color
                cube.left_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[0,1,2]:
                cube.position = self.pos_list[1,2,2]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.right_color
                cube.right_color = cube.top_color
                cube.top_color = cube.left_color
                cube.left_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,2,2]:
                cube.position = self.pos_list[2,0,2]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.right_color
                cube.right_color = cube.top_color
                cube.top_color = cube.left_color
                cube.left_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[1,2,2]:
                cube.position = self.pos_list[2,1,2]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.right_color
                cube.right_color = cube.top_color
                cube.top_color = cube.left_color
                cube.left_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[0,2,2]:
                cube.position = self.pos_list[2,2,2]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.right_color
                cube.right_color = cube.top_color
                cube.top_color = cube.left_color
                cube.left_color = org_bottom_color
                cube.model = cube.ColorCube()
    
    # Orange side is the left-hand side
    def turn_left_right(self):
        for cube in self.cube_list:
            if cube.position == self.pos_list[0,0,2]:
                cube.position = self.pos_list[0,2,2]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.front_color
                cube.front_color = cube.top_color
                cube.top_color = cube.back_color
                cube.back_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[0,0,1]:
                cube.position = self.pos_list[0,1,2]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.front_color
                cube.front_color = cube.top_color
                cube.top_color = cube.back_color
                cube.back_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[0,0,0]:
                cube.position = self.pos_list[0,0,2]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.front_color
                cube.front_color = cube.top_color
                cube.top_color = cube.back_color
                cube.back_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[0,1,2]:
                cube.position = self.pos_list[0,2,1]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.front_color
                cube.front_color = cube.top_color
                cube.top_color = cube.back_color
                cube.back_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[0,1,0]:
                cube.position = self.pos_list[0,0,1]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.front_color
                cube.front_color = cube.top_color
                cube.top_color = cube.back_color
                cube.back_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[0,2,2]:
                cube.position = self.pos_list[0,2,0]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.front_color
                cube.front_color = cube.top_color
                cube.top_color = cube.back_color
                cube.back_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[0,2,1]:
                cube.position = self.pos_list[0,1,0]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.front_color
                cube.front_color = cube.top_color
                cube.top_color = cube.back_color
                cube.back_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[0,2,0]:
                cube.position = self.pos_list[0,0,0]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.front_color
                cube.front_color = cube.top_color
                cube.top_color = cube.back_color
                cube.back_color = org_bottom_color
                cube.model = cube.ColorCube()
    
    def turn_left_left(self):
        for cube in self.cube_list:
            if cube.position == self.pos_list[0,0,2]:
                cube.position = self.pos_list[0,0,0]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.back_color
                cube.back_color = cube.top_color
                cube.top_color = cube.front_color
                cube.front_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[0,0,1]:
                cube.position = self.pos_list[0,1,0]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.back_color
                cube.back_color = cube.top_color
                cube.top_color = cube.front_color
                cube.front_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[0,0,0]:
                cube.position = self.pos_list[0,2,0]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.back_color
                cube.back_color = cube.top_color
                cube.top_color = cube.front_color
                cube.front_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[0,1,2]:
                cube.position = self.pos_list[0,0,1]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.back_color
                cube.back_color = cube.top_color
                cube.top_color = cube.front_color
                cube.front_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[0,1,0]:
                cube.position = self.pos_list[0,2,1]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.back_color
                cube.back_color = cube.top_color
                cube.top_color = cube.front_color
                cube.front_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[0,2,2]:
                cube.position = self.pos_list[0,0,2]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.back_color
                cube.back_color = cube.top_color
                cube.top_color = cube.front_color
                cube.front_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[0,2,1]:
                cube.position = self.pos_list[0,1,2]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.back_color
                cube.back_color = cube.top_color
                cube.top_color = cube.front_color
                cube.front_color = org_bottom_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[0,2,0]:
                cube.position = self.pos_list[0,2,2]
                org_bottom_color = cube.bottom_color
                cube.bottom_color = cube.back_color
                cube.back_color = cube.top_color
                cube.top_color = cube.front_color
                cube.front_color = org_bottom_color
                cube.model = cube.ColorCube()
    
    # White side is top side
    def turn_top_right(self):
        for cube in self.cube_list:
            if cube.position == self.pos_list[0,2,0]:
                cube.position = self.pos_list[0,2,2]
                org_front_color = cube.front_color
                cube.front_color = cube.right_color
                cube.right_color = cube.back_color
                cube.back_color = cube.left_color
                cube.left_color = org_front_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[0,2,1]:
                cube.position = self.pos_list[1,2,2]
                org_front_color = cube.front_color
                cube.front_color = cube.right_color
                cube.right_color = cube.back_color
                cube.back_color = cube.left_color
                cube.left_color = org_front_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[0,2,2]:
                cube.position = self.pos_list[2,2,2]
                org_front_color = cube.front_color
                cube.front_color = cube.right_color
                cube.right_color = cube.back_color
                cube.back_color = cube.left_color
                cube.left_color = org_front_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[1,2,0]:
                cube.position = self.pos_list[0,2,1]
                org_front_color = cube.front_color
                cube.front_color = cube.right_color
                cube.right_color = cube.back_color
                cube.back_color = cube.left_color
                cube.left_color = org_front_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[1,2,2]:
                cube.position = self.pos_list[2,2,1]
                org_front_color = cube.front_color
                cube.front_color = cube.right_color
                cube.right_color = cube.back_color
                cube.back_color = cube.left_color
                cube.left_color = org_front_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,2,0]:
                cube.position = self.pos_list[0,2,0]
                org_front_color = cube.front_color
                cube.front_color = cube.right_color
                cube.right_color = cube.back_color
                cube.back_color = cube.left_color
                cube.left_color = org_front_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,2,1]:
                cube.position = self.pos_list[1,2,0]
                org_front_color = cube.front_color
                cube.front_color = cube.right_color
                cube.right_color = cube.back_color
                cube.back_color = cube.left_color
                cube.left_color = org_front_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,2,2]:
                cube.position = self.pos_list[2,2,0]
                org_front_color = cube.front_color
                cube.front_color = cube.right_color
                cube.right_color = cube.back_color
                cube.back_color = cube.left_color
                cube.left_color = org_front_color
                cube.model = cube.ColorCube()
    
    def turn_top_left(self):
        for cube in self.cube_list:
            if cube.position == self.pos_list[0,2,0]:
                cube.position = self.pos_list[2,2,0]
                org_front_color = cube.front_color
                cube.front_color = cube.left_color
                cube.left_color = cube.back_color
                cube.back_color = cube.right_color
                cube.right_color = org_front_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[1,2,0]:
                cube.position = self.pos_list[2,2,1]
                org_front_color = cube.front_color
                cube.front_color = cube.left_color
                cube.left_color = cube.back_color
                cube.back_color = cube.right_color
                cube.right_color = org_front_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,2,0]:
                cube.position = self.pos_list[2,2,2]
                org_front_color = cube.front_color
                cube.front_color = cube.left_color
                cube.left_color = cube.back_color
                cube.back_color = cube.right_color
                cube.right_color = org_front_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[0,2,1]:
                cube.position = self.pos_list[1,2,0]
                org_front_color = cube.front_color
                cube.front_color = cube.left_color
                cube.left_color = cube.back_color
                cube.back_color = cube.right_color
                cube.right_color = org_front_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,2,1]:
                cube.position  = self.pos_list[1,2,2]
                org_front_color = cube.front_color
                cube.front_color = cube.left_color
                cube.left_color = cube.back_color
                cube.back_color = cube.right_color
                cube.right_color = org_front_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[0,2,2]:
                cube.position = self.pos_list[0,2,0]
                org_front_color = cube.front_color
                cube.front_color = cube.left_color
                cube.left_color = cube.back_color
                cube.back_color = cube.right_color
                cube.right_color = org_front_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[1,2,2]:
                cube.position = self.pos_list[0,2,1]
                org_front_color = cube.front_color
                cube.front_color = cube.left_color
                cube.left_color = cube.back_color
                cube.back_color = cube.right_color
                cube.right_color = org_front_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,2,2]:
                cube.position = self.pos_list[0,2,2]
                org_front_color = cube.front_color
                cube.front_color = cube.left_color
                cube.left_color = cube.back_color
                cube.back_color = cube.right_color
                cube.right_color = org_front_color
                cube.model = cube.ColorCube()
    
    # Yellow side is bottom side
    def turn_bottom_right(self):
        for cube in self.cube_list:
            if cube.position == self.pos_list[0,0,0]:
                cube.position = self.pos_list[2,0,0]
                org_front_color = cube.front_color
                cube.front_color = cube.left_color
                cube.left_color = cube.back_color
                cube.back_color = cube.right_color
                cube.right_color = org_front_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[1,0,0]:
                cube.position  = self.pos_list[2,0,1]
                org_front_color = cube.front_color
                cube.front_color = cube.left_color
                cube.left_color = cube.back_color
                cube.back_color = cube.right_color
                cube.right_color = org_front_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,0,0]:
                cube.position = self.pos_list[2,0,2]
                org_front_color = cube.front_color
                cube.front_color = cube.left_color
                cube.left_color = cube.back_color
                cube.back_color = cube.right_color
                cube.right_color = org_front_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[0,0,1]:
                cube.position = self.pos_list[1,0,0]
                org_front_color = cube.front_color
                cube.front_color = cube.left_color
                cube.left_color = cube.back_color
                cube.back_color = cube.right_color
                cube.right_color = org_front_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,0,1]:
                cube.position = self.pos_list[1,0,2]
                org_front_color = cube.front_color
                cube.front_color = cube.left_color
                cube.left_color = cube.back_color
                cube.back_color = cube.right_color
                cube.right_color = org_front_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[0,0,2]:
                cube.position = self.pos_list[0,0,0]
                org_front_color = cube.front_color
                cube.front_color = cube.left_color
                cube.left_color = cube.back_color
                cube.back_color = cube.right_color
                cube.right_color = org_front_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[1,0,2]:
                cube.position = self.pos_list[0,0,1]
                org_front_color = cube.front_color
                cube.front_color = cube.left_color
                cube.left_color = cube.back_color
                cube.back_color = cube.right_color
                cube.right_color = org_front_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,0,2]:
                cube.position = self.pos_list[0,0,2]
                org_front_color = cube.front_color
                cube.front_color = cube.left_color
                cube.left_color = cube.back_color
                cube.back_color = cube.right_color
                cube.right_color = org_front_color
                cube.model = cube.ColorCube()
    
    def turn_bottom_left(self):
        for cube in self.cube_list:
            if cube.position == self.pos_list[0,0,0]:
                cube.position = self.pos_list[0,0,2]
                org_front_color = cube.front_color
                cube.front_color = cube.right_color
                cube.right_color = cube.back_color
                cube.back_color = cube.left_color
                cube.left_color = org_front_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[1,0,0]:
                cube.position = self.pos_list[0,0,1]
                org_front_color = cube.front_color
                cube.front_color = cube.right_color
                cube.right_color = cube.back_color
                cube.back_color = cube.left_color
                cube.left_color = org_front_color
                cube.model = cube.ColorCube()
            elif cube.position  == self.pos_list[2,0,0]:
                cube.position = self.pos_list[0,0,0]
                org_front_color = cube.front_color
                cube.front_color = cube.right_color
                cube.right_color = cube.back_color
                cube.back_color = cube.left_color
                cube.left_color = org_front_color
                cube.model = cube.ColorCube()
            elif cube.position  == self.pos_list[0,0,1]:
                cube.position = self.pos_list[1,0,2]
                org_front_color = cube.front_color
                cube.front_color = cube.right_color
                cube.right_color = cube.back_color
                cube.back_color = cube.left_color
                cube.left_color = org_front_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,0,1]:
                cube.position = self.pos_list[1,0,0]
                org_front_color = cube.front_color
                cube.front_color = cube.right_color
                cube.right_color = cube.back_color
                cube.back_color = cube.left_color
                cube.left_color = org_front_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[0,0,2]:
                cube.position = self.pos_list[2,0,2]
                org_front_color = cube.front_color
                cube.front_color = cube.right_color
                cube.right_color = cube.back_color
                cube.back_color = cube.left_color
                cube.left_color = org_front_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[1,0,2]:
                cube.position = self.pos_list[2,0,1]
                org_front_color = cube.front_color
                cube.front_color = cube.right_color
                cube.right_color = cube.back_color
                cube.back_color = cube.left_color
                cube.left_color = org_front_color
                cube.model = cube.ColorCube()
            elif cube.position == self.pos_list[2,0,2]:
                cube.position = self.pos_list[2,0,0]
                org_front_color = cube.front_color
                cube.front_color = cube.right_color
                cube.right_color = cube.back_color
                cube.back_color = cube.left_color
                cube.left_color = org_front_color
                cube.model = cube.ColorCube()
    




app = Ursina()
f = Facing()
s = Solver()
r = RubiksCube()

def set_camera():
    camera.position = (0 , 0)
    camera.fov = 32

def update():
    f.get_facing_position(camera.world_position)


def input(key):
    if key == '6':
        s.reset_solver()
        if f.facing_side == "green":
            r.turn_front_right()
        elif f.facing_side == "red":
            r.turn_right_right()
        elif f.facing_side == "blue":
            r.turn_back_right()
        elif f.facing_side == "orange":
            r.turn_left_right()
        elif f.facing_side == "white":
            r.turn_top_right()
        elif f.facing_side == "yellow":
            r.turn_bottom_right()

    elif key == '4':
        s.reset_solver()
        if f.facing_side == "green":
            r.turn_front_left()
        elif f.facing_side == "red":
            r.turn_right_left()
        elif f.facing_side == "blue":
            r.turn_back_left()
        elif f.facing_side == "orange":
            r.turn_left_left()
        elif f.facing_side == "white":
            r.turn_top_left()
        elif f.facing_side == "yellow":
            r.turn_bottom_left()

    elif key == '9':
        s.reset_solver()
        if f.facing_side == "green" \
                or f.facing_side == "orange" \
                or f.facing_side == "blue" \
                or f.facing_side == "red":
            r.turn_top_right()

    elif key == "7":
        s.reset_solver()
        if f.facing_side == "green" \
                or f.facing_side == "orange" \
                or f.facing_side == "blue" \
                or f.facing_side == "red":
            r.turn_top_left()

    elif key == "3":
        s.reset_solver()
        if f.facing_side == "green" \
                or f.facing_side == "orange" \
                or f.facing_side == "blue" \
                or f.facing_side == "red":
            r.turn_bottom_right()

    elif key == "1":
        s.reset_solver()
        if f.facing_side == "green" \
                or f.facing_side == "orange" \
                or f.facing_side == "blue" \
                or f.facing_side == "red":
            r.turn_bottom_left()

    elif key == "n":
        r.reset_cube()

    elif key == "r":
        print("start randomizing")
        s.reset_solver()
        for i in range(random.randint(75, 100)):
            rando = random.randint(1, 12)
            if rando == 1:
                r.turn_front_left()
            elif rando == 2:
                r.turn_front_right()
            elif rando == 3:
                r.turn_left_right()
            elif rando == 4:
                r.turn_left_left()
            elif rando == 5:
                r.turn_right_right()
            elif rando == 6:
                r.turn_right_left()
            elif rando == 7:
                r.turn_back_left()
            elif rando == 8:
                r.turn_back_right()
            elif rando == 9:
                r.turn_top_right()
            elif rando == 10:
                r.turn_top_left()
            elif rando == 11:
                r.turn_bottom_left()
            elif rando == 12:
                r.turn_bottom_right()
        print("randomized")


    elif key == 'p':
        begin_time = datetime.datetime.now()
        while not s.cube_solved:
            dir_list = s.solve_cube(r.cube_list, r.pos_list)
            if dir_list != [] and dir_list is not None:
                print(dir_list)
                for dir in dir_list:
                    if dir == "turn_front_left":
                        r.turn_front_left()
                    elif dir == "turn_front_right":
                        r.turn_front_right()
                    elif dir == "turn_left_right":
                        r.turn_left_right()
                    elif dir == "turn_left_left":
                        r.turn_left_left()
                    elif dir == "turn_bottom_right":
                        r.turn_bottom_right()
                    elif dir == "turn_bottom_left":
                        r.turn_bottom_left()
                    elif dir == "turn_right_right":
                        r.turn_right_right()
                    elif dir == "turn_right_left":
                        r.turn_right_left()
                    elif dir == "turn_back_right":
                        r.turn_back_right()
                    elif dir == "turn_back_left":
                        r.turn_back_left()
                    elif dir == "turn_top_left":
                        r.turn_top_left()
                    elif dir == "turn_top_right":
                        r.turn_top_right()
            elif not dir_list or dir_list is None:
                continue
            elif s.cube_solved:
                break
        end_time = datetime.datetime.now()
        solve_time = end_time - begin_time
        print(f"solved in {str(solve_time)[-8:]}s.")
        
    elif key == 'm':
        dir_list = s.set_upper_corners(r.cube_list, r.pos_list)
        if dir_list != [] and dir_list is not None:
            print(s.direction_list)
            for dir in dir_list:
                if dir == "turn_front_left":
                    r.turn_front_left()
                elif dir == "turn_front_right":
                    r.turn_front_right()
                elif dir == "turn_left_right":
                    r.turn_left_right()
                elif dir == "turn_left_left":
                    r.turn_left_left()
                elif dir == "turn_bottom_right":
                    r.turn_bottom_right()
                elif dir == "turn_bottom_left":
                    r.turn_bottom_left()
                elif dir == "turn_right_right":
                    r.turn_right_right()
                elif dir == "turn_right_left":
                    r.turn_right_left()
                elif dir == "turn_back_right":
                    r.turn_back_right()
                elif dir == "turn_back_left":
                    r.turn_back_left()
                elif dir == "turn_top_left":
                    r.turn_top_left()
                elif dir == "turn_top_right":
                    r.turn_top_right()
        


set_camera()
EditorCamera()
app.run()