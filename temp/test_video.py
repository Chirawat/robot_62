from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import cv2
import RPi.GPIO as GPIO
import numpy as np

camera = PiCamera()
camera.resolution = (640, 480)
camera.framerate = 32
rawCapture = PiRGBArray(camera, size=(640, 480))

GPIO.setmode(GPIO.BCM)
GPIO.setup(27, GPIO.OUT)
GPIO.output(27, GPIO.LOW)
GPIO.setup(27, GPIO.OUT)

time.sleep(0.1)

for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
	image = frame.array
	gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
	ret, threshold = cv2.threshold(gray, 60, 255, cv2.THRESH_BINARY)

	ROI = threshold[399:400, 0:400]



	print( ROI.shape )

	

	



#	for x in ROI:
#		if(x==0):
#			seconds = time.time()
#			print(time.ctime(seconds), 'detected!')
#			GPIO.output(27, GPIO.HIGH)
#			break
#		else:
#			GPIO.output(27, GPIO.LOW)

	image = cv2.rectangle(image, (0, 250), (400,400), (0,255,0), 2)

#	cv2.imshow("img_mask", img_mask)
	cv2.imshow("ROI", ROI)
	cv2.imshow("image", image)
	cv2.imshow("threshold", threshold)

	key = cv2.waitKey(1) & 0xFF

	rawCapture.truncate(0)

	if key == ord("q"):
		break
