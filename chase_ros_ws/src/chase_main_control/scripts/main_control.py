#!/usr/bin/env python
import rospy
from std_msgs.msg import String, Float32
from chase_msgs.msg import ObjectDetection, Move, ControlMode, ChaseArduino
from random import randint
from random import seed
#
# Main control skall
# Ta emot object detection signaler
# Skicka commando signaler till Arduinon
# Lyssna på IMU signalerna


class Action:
    
    def __init__(self, duration, mode, params):
        self.duration = rospy.Duration(duration)
        self.mode = mode
        self.params = params

    def get_msg(self):
        msg = ChaseArduino
        msg.mode = self.mode
        msg.params = self.params

        return msg



class Navigation:
    # Ett exempel på dum navigering

    DEFAULT_SPEED = 0.2
    DEFAULT_HEIGHT = 0.16
    DEFAULT_TURN = 0
    TURN_STANDING = 0.01
    TURN_TROTING = 0.3
    PARAMS = [0,0,0,0,0]

    def __init__(self):
        self.in_view = False

        self.image_x = 640
        self.image_y = 480
        self.pos_x = -1
        self.pos_y = -1

        self.action_buffer = []
        self.last_seen = 0
        self.last_turn = 0
        self.last_action = 0
        self.next_action_time = 0

        seed(1)


    def new_object_detection_msg(self, msg):
        self.in_view = msg.object_found

        if msg.object_found:

            self.image_y = msg.image_y
            self.image_y = msg.image_y

            self.pos_x = msg.pos_x
            self.pos_y = msg.pos_y
            self.last_seen = msg.time_stamp

        

    def follow_object(self):
        current_time = rospy.get_rostime()

        # Om objektet inte sets på ett tag
        # Gå rakt i 3 sek, sedan sväng
        if ((not self.in_view) and (current_time - self.last_seen > 3)):

            if (current_time - self.last_turn < 3):
                self.trot(0)
            else:
                duration = (float)(randint(10, 500)/100)  # Ger turn duration mellan 0.1 -> 5 sek
                self.turn_standing(duration,1)
        
        
        else:
            
            turn = 0
            standing = False

            # Om objektet inte syns, backa och sväng
            if (not self.in_view):
                self.back()
                standing = True

             # Standing = 1 om objektet är nära
             # self.pos_y < 100 or 
            if(self.pos_x < 120 or self.pos_x > 520):
                standing = True
            
           
            if (self.pos_x < 250):
                turn = 1            # Svänger vänster
            elif (self.pos_x >= 250 and self.pos_x < 390):
                turn = 0            # Går rakt
                #if (standing==True):   # Objektet hittat om i mitten och nära
                    #self.lay()
            elif (self.pos_x >= 390):
                turn = -1           # Svänger höger


            # Svänger på stället om objektet är nära
            # Svänger gåendes om objektet är långt bort
            if(standing==True):
                self.turn_standing(0.2,turn*self.TURN_STANDING) 
            else:
                self.trot(turn*self.TURN_TROTING)         




    # Alla olika rörelse kommandon

    def sleep(self):
        self.action_buffer.append(Action(0.1, 0, self.PARAMS))

    def stand(self):
        self.PARAMS[0] = self.DEFAULT_HEIGHT
        self.action_buffer.append(Action(0.1, 1, self.PARAMS))

    def walk(self):
        self.PARAMS[0] = self.DEFAULT_SPEED
        self.PARAMS[1] = self.DEFAULT_TURN
        self.PARAMS[2] = self.DEFAULT_HEIGHT
        self.action_buffer.append(Action(0.1, 2, self.PARAMS))

    def trot(self, radius):
        self.PARAMS[0] = self.DEFAULT_SPEED
        self.PARAMS[1] = radius
        self.PARAMS[2] = self.DEFAULT_HEIGHT
        self.action_buffer.append(Action(0.1, 3, self.PARAMS))

    # Backar i trot
    def back(self):
        self.PARAMS[0] = -self.DEFAULT_SPEED
        self.PARAMS[1] = self.DEFAULT_TURN
        self.PARAMS[2] = self.DEFAULT_HEIGHT
        self.action_buffer.append(Action(2, 3, self.PARAMS))

    # Svänger i trot på plats
    def turn_standing(self, duration, left):
        self.PARAMS[0] = self.DEFAULT_SPEED
        self.PARAMS[1] = self.TURN_STANDING*left
        self.PARAMS[2] = self.DEFAULT_HEIGHT
        self.action_buffer.append(Action(duration, 3, self.PARAMS))

        current_time = rospy.get_rostime()
        self.last_turn = current_time

    # Objekt hittat, lägger sig ned.
    def lay(self):
        self.PARAMS[0] = 0.15
        self.action_buffer.append(Action(100, 1, self.PARAMS))
        self.control_mode = ControlMode.MANUAL_MOVE_MODE


    def clear_actions(self):
        self.action_buffer = []
        self.last_action = 0
        self.next_action_time = 0


    def new_ultrasound_msg(self, msg):
        # if (distance < .....)
        # self.collision()

        pass  # TODO: implement

        # Force action funk, sätt tiden också

    def collision(self):
        self.clear_actions
        self.turn_standing(2,1) # Svänger alltid vänster i två sek

    def new_action(self):
        current_time = rospy.get_rostime()
        # TODO: Check if buffer is empty
        if current_time > self.next_action_time:
            action = self.action_buffer.pop()

                # Skickar inte samma meddelande flera gånger i rad
            if (action.get_msg() != self.last_action.get_msg()):
                self.next_action_time = current_time + action.duration
                self.last_action = action
                return action.get_msg()

        return None


class MainControl:
    def __init__(self):
        self.navigation = Navigation()

        rospy.init_node('main_control')

        self.pub_move = rospy.Publisher('arduinoMsgs', ChaseArduino, queue_size=10)
        #pub_move = rospy.Publisher('settings', Move, queue_size=10)

        self.object_detection_subscriber = rospy.Subscriber("object_detection", ObjectDetection,
                                                            self.object_detection_callback)
        # finns ett sensor_msgs
        self.ultrasound_subscriber = rospy.Subscriber("ultrasound", Float32,
                                                      self.ultrasound_callback)

        self.control_mode_subscriber = rospy.Subscriber("control_mode", ControlMode,
                                                        self.control_mode_callback)

        self.set_defaults()
        # self.run_node()()
        rospy.spin()

    def set_defaults(self):
        self.control_mode = ControlMode.MANUAL_MOVE_MODE

    def object_detection_callback(self, msg):
        self.navigation.new_object_detection_msg(msg)

    def ultrasound_callback(self, msg):
        self.navigation.new_ultrasound_msg(msg)

    def control_mode_callback(self, data):
        self.control_mode = data.control_mode

    def pub_next_action(self):
        msg = self.navigation.new_action()
        if msg:
            self.pub_move(msg)

    def start_node():
        rate = rospy.Rate(10)  # 10hz
        while not rospy.is_shutdown():
            if control_mode == ControlMode.MANUAL_MOVE_MODE:
                # TODO: Stop subscribing to object_detection
                # Do nothing send controll directly via move to arduino
                pass
            elif ControlMode == ControlMode.FIND_OBJECT_MODE:
                self.pub_next_action() 

            rate.sleep()


if __name__ == '__main__':
    try:
        main_control = MainControl()
    except rospy.ROSInterruptException:
        pass
