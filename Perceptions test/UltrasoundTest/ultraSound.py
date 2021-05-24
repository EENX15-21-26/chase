import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)

TRIGGER_PIN = 18
ECHO_PIN = 16
print("uppe")
#set GPIO direction (IN / OUT)
GPIO.setup(TRIGGER_PIN, GPIO.OUT)
GPIO.setup(ECHO_PIN, GPIO.IN)
 
def distance():
    print("start")

    # set Trigger to HIGH
    GPIO.output(TRIGGER_PIN, True)

    # set Trigger after 0.01ms to LOW
    time.sleep(0.00001)
    GPIO.output(TRIGGER_PIN, False)

    StartTime = time.time()
    StopTime = time.time()

    # save StartTime
    while GPIO.input(ECHO_PIN) == 0:
        StartTime = time.time()

    # save time of arrival
    while GPIO.input(ECHO_PIN) == 1:
        StopTime = time.time()

    # time difference between start and arrival
    TimeElapsed = StopTime - StartTime
    # multiply with thesonic speed (34300 cm/s)
    # and divide by 2, because there and back

    distance = (TimeElapsed * 34300) / 2

    return distance
    

 
if __name__ == '__main__':
    try:
        while True:
            dist = distance()
            print("Measured Distance = %.1f cm" % dis)
            time.sleep(1)
    except KeyboardInterrupt:
        print("Measurement stopped by User")
        GPIO.cleanup()
 

