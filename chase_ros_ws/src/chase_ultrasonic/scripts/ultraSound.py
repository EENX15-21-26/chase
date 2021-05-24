import RPi.GPIO as GPIO
import time
import rospy
from std_msgs.msg import Float64

GPIO.setmode(GPIO.BOARD)

TRIGGER_PIN = 18
ECHO_PIN = 10

#set GPIO direction (IN / OUT)
GPIO.setup(TRIGGER_PIN, GPIO.OUT)
GPIO.setup(ECHO_PIN, GPIO.IN)
 
class Distance():

    def __init__(self):
        

        self.start_node()

    def dist(self):
        # set Trigger to HIGH
        GPIO.output(TRIGGER_PIN, True)
    
        # set Trigger after 0.01ms to LOW
        time.sleep(0.00001)
        GPIO.output(TRIGGER_PIN, False)
    
        self.StartTime = time.time()
        self.StopTime = time.time()
    
        # save StartTime
        while GPIO.input(ECHO_PIN) == 0:
            self.StartTime = time.time()
    
        # save time of arrival
        while GPIO.input(ECHO_PIN) == 1:
            self.StopTime = time.time()
    
        # time difference between start and arrival
        self.TimeElapsed = self.StopTime - StartTime
        # multiply with the sonic speed (34300 cm/s)
        # and divide by 2, because there and back
        self.distance = (self.TimeElapsed * 34300) / 2

        return self.distance
    

    def start_node(self):
        pub = rospy.Publisher('sonic',
                            Float64, queue_size=1)
        rospy.init_node('sonic', anonymous=True)
        rate = rospy.Rate(10)  # 2hz
        while not rospy.is_shutdown():
            msg = self.dist()
            pub.publish(msg)
            rate.sleep()

 
if __name__ == '__main__':
    try:
        while True:
            dist = Distance()
    except rospy.ROSInterruptException:
        pass
 
        # Reset by pressing CTRL + C
    except KeyboardInterrupt:
        print("Measurement stopped by User")
        GPIO.cleanup()

