import numpy as np
import cv2
import matplotlib.pyplot as plt

def nothing(*arg):
    pass



def thresh_binary(img, lower, max):
    return cv2.threshold(img, lower, max,cv2.THRESH_BINARY)



def main():
    cv2.namedWindow('Thresholds')

    # Create tracker bars
    cv2.createTrackbar('lower_thresh', 'Thresholds', 0, 255, nothing)
    cv2.createTrackbar('upper_thresh', 'Thresholds', 0, 255, nothing)

    cv2.setTrackbarPos('lower_thresh', 'Thresholds', 120)
    cv2.setTrackbarPos('upper_thresh', 'Thresholds', 255)

    # Load image in grayscale
    path = r"C:\Python\Woordzoeker Solver\WS_images\WS_image_6.png"
    gray_image = cv2.imread(path, 0)

    while True:

        lower = cv2.getTrackbarPos('lower_thresh', 'Thresholds')
        max = cv2.getTrackbarPos('upper_thresh', 'Thresholds')

        ret, new_img = thresh_binary(gray_image, lower, max)

        # Display the resulting frame
        cv2.imshow('Thresholds', new_img)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break


main()