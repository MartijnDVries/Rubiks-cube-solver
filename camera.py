import cv2
import numpy as np


cap = cv2.VideoCapture(1)

while True:
    ret, frame = cap.read()

    imgblur = cv2.GaussianBlur(frame, (15, 15), 1)
    gray = cv2.cvtColor(imgblur, cv2.COLOR_BGR2GRAY)
    # gray = cv2.bitwise_not(gray)
    hsv = cv2.cvtColor(imgblur, cv2.COLOR_BGR2HSV)
    thresh = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU)[1]
    thresh_2 = cv2.adaptiveThreshold(gray, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY, 11,2)

    imgCanny = cv2.Canny(gray, 55, 100)

    kernel = np.ones((3,3))

    imgDil = cv2.dilate(imgCanny, kernel, iterations=2)



    cnts, h  = cv2.findContours(imgDil, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    # cnts = cnts[0] if len(cnts) == 2 else cnts[1]

    i = 0
    for cnt in cnts:
        if i == 0:
            i = 1
            continue
        approx = cv2.approxPolyDP(cnt,0.02*cv2.arcLength(cnt,True),True)
        area = cv2.contourArea(cnt)
        if area > 1000:
            M = cv2.moments(cnt)
            if M['m00'] != 0.0:
                x = int(M['m10']/M['m00'])
                y = int(M['m01']/M['m00'])



            if len(approx) == 4:
                # cv2.putText(imgDil, 'Quadrilateral', (x, y),
                # cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255, 255, 255), 2)
                cv2.drawContours(frame, [cnt], 0, (255, 0, 0), 5)


            n = approx.ravel()
            i = 0

            for j in n :
                if(i % 2 == 0):
                    x = n[i]
                    y = n[i + 1]
                    font = cv2.FONT_HERSHEY_COMPLEX
                    # String containing the co-ordinates.
                    string = str(x) + " " + str(y)

                    if(i == 0):
                        # text on topmost co-ordinate.
                        cv2.putText(frame, "Arrow tip", (x, y),
                                        font, 0.5, (255, 0, 0))
                    else:
                        # text on remaining co-ordinates.
                        cv2.putText(frame, string, (x, y),
                                  font, 0.5, (0, 255, 0))
                i = i + 1
    b,g,r = (frame[160,49])
    print(f"bgr = {b,g,r}")
    cv2.imshow("frame", frame)
    cv2.imshow("frame2", imgDil)
    cv2.imshow("frame3", imgblur)


    if cv2.waitKey(1) == ord('q'):
        break


cap.release()
cv2.destroyAllWindows()

