# import cv2
#
# import numpy
#
path = r"C:\Python\Woordzoeker Solver\WS_images\WS_image_4.png"
#
#
#
# img = cv2.imread(path)
#
# img_gray = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)
#
# while True:
#
#
#
#     cv2.imshow('Image', img)
#     cv2.imshow('Img2', img_gray)
#
#
#
#     if cv2.waitKey(10) & 0xFF == ord('q'):
#         break
#

#importing the required libraries
import numpy as np
import cv2
import matplotlib.pyplot as plt


#here 0 means that the image is loaded in gray scale format
gray_image = cv2.imread(path, 0)



ret,thresh_binary = cv2.threshold(gray_image,0,255,cv2.THRESH_BINARY)
ret,thresh_binary_inv = cv2.threshold(gray_image,127,255,cv2.THRESH_BINARY_INV)
ret,thresh_trunc = cv2.threshold(gray_image,127,255,cv2.THRESH_TRUNC)
ret,thresh_tozero = cv2.threshold(gray_image,127,255,cv2.THRESH_TOZERO)
ret,thresh_tozero_inv = cv2.threshold(gray_image,127,255,cv2.THRESH_TOZERO_INV)

#DISPLAYING THE DIFFERENT THRESHOLDING STYLES
names = ['Oiriginal Image','BINARY','THRESH_BINARY_INV','THRESH_TRUNC','THRESH_TOZERO','THRESH_TOZERO_INV']
images = gray_image,thresh_binary,thresh_binary_inv,thresh_trunc,thresh_tozero,thresh_tozero_inv

for i in range(6):
    plt.subplot(2,3,i+1),plt.imshow(images[i],'gray')
    plt.title(names[i])
    plt.xticks([]),plt.yticks([])

plt.show()




def thresh_binary(img, lower, max):
    return cv2.threshold(img, lower, max,cv2.THRESH_BINARY)














