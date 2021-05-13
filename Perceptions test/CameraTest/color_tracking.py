# import the necessary packages
from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import cv2
# initialize the camera and grab a reference to the raw camera capture
camera = PiCamera()
camera.resolution = (640, 480)
camera.framerate = 10
rawCapture = PiRGBArray(camera, size=(640, 480))
# allow the camera to warmup
time.sleep(0.1)

lower = (130, 100, 50)
upper = (180, 255, 255)

# capture frames from the camera
for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
    # grab the raw NumPy array representing the image, then initialize the timestamp
    # and occupied/unoccupied text
    image = frame.array

    blurred = cv2.GaussianBlur(image, (11, 11), 0)
    hsv = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)


    mask = cv2.inRange(hsv, lower, upper)
    mask = cv2.erode(mask, None, iterations = 2)
    mask = cv2.dilate(mask, None, iterations = 2)

    contours = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[0]
    center = None
    
    if len(contours) > 0:
        c = max(contours, key=cv2.contourArea)
        ((x, y), radius) = cv2.minEnclosingCircle(c)
        
        if radius > 10:
            print(x,y,radius)
            M = cv2.moments(c)
            center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))
            cv2.circle(image, (int(x), int(y)), int(radius), (0, 255, 255), 2)
            cv2.circle(image, center, 5, (0, 255, 255), 2)
            

    
	# show the frame
    cv2.imshow("Mask", mask)
    cv2.imshow("Original", image)

    key = cv2.waitKey(1) & 0xFF
	# clear the stream in preparation for the next frame
    rawCapture.truncate(0)
	# if the `q` key was pressed, break from the loop
    if key == ord("q"):
        break