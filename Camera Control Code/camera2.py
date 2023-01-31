import cv2
import numpy
import numpy as np
import statistics


cap = cv2.VideoCapture(1)
ret, frame = cap.read()

# cv2.rectangle(frame,(115,125), (165,175), (0,0,0), 1)
cv2.rectangle(frame,(225,125), (275,175), (0,0,0), 1)
cv2.rectangle(frame,(335,125), (385,175), (0,0,0), 1)

# convert to hsv colorspace
hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
# lower bound and upper bound for Green color
lower_bound_white = np.array([0, 13, 195])
upper_bound_white = np.array([16, 64, 255])
# find the colors within the boundaries
mask_white = cv2.inRange(hsv, lower_bound_white, upper_bound_white)

    #define kernel size
kernel = np.ones((7,7),np.uint8)
# Remove unnecessary noise from mask_white
mask_white = cv2.morphologyEx(mask_white, cv2.MORPH_CLOSE, kernel)
mask_white = cv2.morphologyEx(mask_white, cv2.MORPH_OPEN, kernel)

segmented_img_white = cv2.bitwise_and(frame, frame, mask=mask_white)


frame_color_1_1 = segmented_img_white[130:170,340:380]

frame_color_2 = frame[125:175,115:165]
hsv2 = cv2.cvtColor(frame_color_2, cv2.COLOR_BGR2HSV)

print(hsv2)


red_list = list()
blue_list = list()
green_list = list()

# for i in frame[125:175, 115:165]:
#     for j in i:
#         print(f"frame color ij = {j}")
#         red = j[0]
#         red_list.append(red)
#         green = j[1]
#         green_list.append(green)
#         blue = j[2]
#         blue_list.append(blue)
#     # print(f"frame color i = {i}")
#
# print(f"red list {red_list}, red mean {statistics.mean(red_list)}")

while True:
    ret, frame = cap.read()

    cv2.rectangle(frame,(115,125), (165,175), (0,0,0), 1)
    cv2.rectangle(frame,(225,125), (275,175), (0,0,0), 1)
    cv2.rectangle(frame,(335,125), (385,175), (0,0,0), 1)



    if cv2.waitKey(1) == ord('q'):
        break

    cv2.imshow("frame", frame)
    cv2.imshow("hsv", hsv2)

cap.release()
cv2.destroyAllWindows()

