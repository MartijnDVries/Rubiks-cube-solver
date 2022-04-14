from ursina import *


from ursina import Entity

def ColorCube(front_color=color.red, back_color= color.green, left_color=color.black, right_color=color.blue, top_color=color.yellow, bottom_color=color.orange):
    e = Entity()

    # Entity(parent=e, model="quad",color=bottom_color, x=0, y=-0.5, z=0.5, rotation_x=-90)
    # Entity(parent=e, model="quad", color=top_color, x=0, y=0.5, z=0.5, rotation_x=90)
    # Entity(parent=e, model="quad",color=front_color, x=0, y=0, z=0)
    # Entity(parent=e, model="quad", color=back_color, x=0, y=0, z=1, rotation_x=180)
    # Entity(parent=e, model="quad", color=left_color, x=-0.5, y=0, z=0.5, rotation_y=90)
    # Entity(parent=e, model="quad", color=right_color, x=0.5, y=0, z=0.5, rotation_y=-90)

    bottom = Entity(parent=e, model="quad",color=bottom_color, x=0, y=-0.5, z=0, rotation_x=-90)
    top = Entity(parent=e, model="quad", color=top_color, x=0, y=0.5, z=0, rotation_x=90)
    front = Entity(parent=e, model="quad",color=front_color, x=0, y=0, z=-0.5)
    back = Entity(parent=e, model="quad", color=back_color, x=0, y=0, z=0.5, rotation_x=180)
    left = Entity(parent=e, model="quad", color=left_color, x=-0.5, y=0, z=0, rotation_y=90)
    right = Entity(parent=e, model="quad", color=right_color, x=0.5, y=0, z=0, rotation_y=-90)

    cube = e.combine()
    cube.generate()
    destroy(e)

    return cube


app = Ursina()
cube = Entity(model=ColorCube(), position=(0,1,2))

centrum = Entity()

cube.parent = centrum



def input(key):


    if key == '6':
        cube.rotation_x +=90




    elif key == '8':
        cube.rotation_y += 90
        if cube.rotation_y == 360:
            cube.rotation_y = 0

    elif key == '9':
        cube.rotation_z += 90
        if cube.rotation_z == 360:
            cube.rotation_z = 0






def set_camera():
    camera.position = (1 , 1)
    camera.fov = 32


def update():
    print(f"cube origin:{cube.origin}")





set_camera()
EditorCamera()



app.run()

