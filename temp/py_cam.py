import cv2
import numpy as np

cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    ret, threshold = cv2.threshold(gray, 60, 255,cv2.THRESH_BINARY)
    ROI = threshold[250:400, 0:400]
    cv2.rectangle(frame, (0, 250), (400,400), (0,255,0), 2)
    
    rows, cols = ROI.shape

    for i in range(rows):
        for j in range(cols):
            if(ROI[i, j] == 0):
                print(i, j)
                print('detected!')
                break

    cv2.imshow('frame', frame)
    cv2.imshow("ROI", ROI)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break;

cap.release()
cv2.destroyAllWindows()
