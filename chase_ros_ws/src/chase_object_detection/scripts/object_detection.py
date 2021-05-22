#!/usr/bin/env python
import rospy
from std_msgs.msg import String
from chase_msgs.msg import ObjectDetection
import cv2
import time
import numpy as np

from picamera import PiCamera


# allow the camera to warmup


#lower = (130, 100, 50)
#upper = (180, 255, 255)
#last_time = time.time()

class TheCamera:
    lower = (130, 100, 50)
    upper = (180, 255, 255)


    def __init__(self):
        
        self.camera = PiCamera()
        self.camera.resolution = (640, 480)
        self.camera.framerate = 30
        self.image = np.empty((480, 640, 3), dtype=np.uint8)
        #self.rawCapture = PiRGBArray(self.camera, size=(640, 480))

        time.sleep(2)

        self.start_node()

    def find_object(self):
        self.camera.capture(self.image, format="bgr")

    # capture frames from the camera
        # grab the raw NumPy array representing the image, then initialize the timestamp
        # and occupied/unoccupied text
        #image = frame.array

        blurred = cv2.GaussianBlur(self.image, (11, 11), 0)
        hsv = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)

        mask = cv2.inRange(hsv, self.lower, self.upper)
        mask = cv2.erode(mask, None, iterations = 2)
        mask = cv2.dilate(mask, None, iterations = 2)

        contours = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[0]
        center = None
        
        if len(contours) > 0:
            c = max(contours, key=cv2.contourArea)
            ((x, y), radius) = cv2.minEnclosingCircle(c)
            
            if radius > 10:
                print(x,y,radius)
                #M = cv2.moments(c)
                #center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))
                #cv2.circle(image, (int(x), int(y)), int(radius), (0, 255, 255), 2)
                #cv2.circle(image, center, 5, (0, 255, 255), 2)
                return True, int(x) #, int(y)
                
        return False, 0 #, 0
    
        # show the frame
        #cv2.imshow("Mask", mask)
        #cv2.imshow("Original", image)

        #key = cv2.waitKey(1) & 0xFF
        # clear the stream in preparation for the next frame
        #self.rawCapture.truncate(0)
        # if the `q` key was pressed, break from the loop
        #if key == ord("q"):
        #   break

        #print(time.time() - last_time)
        #last_time = time.time()


    def object_detection(self):
        # Todo lägg till kod här
        found, x  = self.find_object()
        rospy.loginfo(x)
        print(found)
        print(x)
        obj_det_msg = ObjectDetection()
        obj_det_msg.time_stamp = rospy.get_rostime()
        obj_det_msg.pos_x = x
        # obj_det_msg.pos_y = y
        obj_det_msg.object_found = found

        return obj_det_msg


    def start_node(self):
        pub = rospy.Publisher('object_detection',
                            ObjectDetection, queue_size=10)
        rospy.init_node('object_detection', anonymous=True)
        rate = rospy.Rate(2)  # 2hz
        while not rospy.is_shutdown():
            msg = self.object_detection()
            pub.publish(msg)
            rate.sleep()


if __name__ == '__main__':
    try:
        the_camera = TheCamera()
    except rospy.ROSInterruptException:
        pass
