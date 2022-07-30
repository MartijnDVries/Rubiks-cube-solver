
import cv2

import numpy

path = r"C:\Python\Woordzoeker Solver\WS_images\WS_image_4.png"



img = cv2.imread(path)

img_gray = cv2.cvtColor

while True:





    cv2.imshow('Image', img)



    if cv2.waitKey(10) & 0xFF == ord('q'):
        break