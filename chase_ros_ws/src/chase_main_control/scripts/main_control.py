#!/usr/bin/env python
import rospy
import copy
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
        self.params = copy.copy(params)

    def get_msg(self):
        msg = ChaseArduino()
        msg.mode = self.mode
        msg.params = self.params

        return msg

    def eval(self): 
        return self.mode, self.params



class Navigation:
    # Ett exempel på dum navigering

    DEFAULT_SPEED = 0.2
    DEFAULT_HEIGHT = 0.16
    DEFAULT_TURN = 0
    TURN_STANDING = 0.1
    TURN_TROTING = 0.3
    

    def __init__(self):
        self.in_view = False

        self.image_x = 640
        self.image_y = 480
        self.pos_x = -1
        self.pos_y = -1

        self.action_buffer = []
        self.last_seen = rospy.Time(0)
        self.last_turn = rospy.Time(0)
        self.last_action = Action(0,0,0)
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
        
        self.follow_object()
        

    def follow_object(self):
        current_time = rospy.get_rostime()

        # Om objektet inte sets på ett tag
        # Gå rakt i 3 sek, sedan sväng
        if ((not self.in_view) and (current_time - self.last_seen > rospy.Duration(3))):

            print("follow object first if")

            if (current_time - self.last_turn < rospy.Duration(3)):
                self.trot(0)
            else:
                duration = (float)(randint(10, 500)/100)  # Ger turn duration mellan 0.1 -> 5 sek
                self.turn_standing(duration,1)
        
        
        else:
            

            print("follow object else")
            turn = 0
            standing = False

            # Om objektet inte syns, backa och sväng
            if (not self.in_view):
                self.back()
                standing = True

             # Standing = 1 om objektet är nära
             # self.pos_y < 100 or 
            if(self.pos_x < 50 or self.pos_x > 590):
                standing = True
            
           
            if (self.pos_x < 250):
                turn = 1
                print("vänster")            # Svänger vänster
            elif (self.pos_x >= 250 and self.pos_x < 390):
                turn = 0
                print("mitt")              # Går rakt
                #if (standing==True):   # Objektet hittat om i mitten och nära
                    #self.lay()
            elif (self.pos_x >= 390):
                turn = -1
                print("höger")             # Svänger höger


            # Svänger på stället om objektet är nära
            # Svänger gåendes om objektet är långt bort
            if(standing==True):
                self.turn_standing(0.2,turn*self.TURN_STANDING) 
            else:
                self.trot(turn*self.TURN_TROTING)    




    # Alla olika rörelse kommandon

    def sleep(self):
        PARAMS = [0,0,0,0,0]
        self.action_buffer.append(Action(0.1, 0, PARAMS))

    def stand(self):
        PARAMS = [0.15,0,0,0,0]
        self.action_buffer.append(Action(0.1, 1, PARAMS))

    def walk(self):
        PARAMS = [0,0,0,0,0]
        PARAMS[0] = self.DEFAULT_SPEED
        PARAMS[1] = self.DEFAULT_TURN
        PARAMS[2] = self.DEFAULT_HEIGHT
        self.action_buffer.append(Action(0.1, 2, PARAMS))

    def trot(self, radius):
        PARAMS = [0,0,0,0,0]
        PARAMS[0] = self.DEFAULT_SPEED
        PARAMS[1] = radius
        PARAMS[2] = self.DEFAULT_HEIGHT
        self.action_buffer.append(Action(0.1, 3, PARAMS))

    # Backar i trot
    def back(self):
        PARAMS = [0,0,0,0,0]
        PARAMS[0] = -self.DEFAULT_SPEED
        PARAMS[1] = self.DEFAULT_TURN
        PARAMS[2] = self.DEFAULT_HEIGHT
        self.action_buffer.append(Action(2, 3, PARAMS))

    # Svänger i trot på plats
    def turn_standing(self, duration, left):
        PARAMS = [0,0,0,0,0]
        PARAMS[0] = self.DEFAULT_HEIGHT
        self.action_buffer.append(Action(0.5, 1, PARAMS))
        PARAMS2 = [0,0,0,0,0]
        PARAMS2[0] = self.DEFAULT_SPEED
        PARAMS2[1] = self.TURN_STANDING*left
        PARAMS2[2] = self.DEFAULT_HEIGHT
        self.action_buffer.append(Action(duration, 3, PARAMS2))

        current_time = rospy.get_rostime()
        self.last_turn = current_time

    # Objekt hittat, lägger sig ned.
    def lay(self):
        PARAMS[0] = 0.15
        self.action_buffer.append(Action(100, 1, PARAMS))
        self.control_mode = ControlMode.MANUAL_MOVE_MODE


    def clear_actions(self):
        self.action_buffer = []
        self.last_action = Action(0,0,0)
        self.next_action_time = rospy.Time(0)


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

        if (current_time >= self.next_action_time and len(self.action_buffer) != 0 ):
            action = self.action_buffer.pop()
            print("first action if")

            print(action.eval())
            print(self.last_action.eval())

            # Skickar inte samma meddelande flera gånger i rad
            if (action.eval() != self.last_action.eval()):
                self.next_action_time = current_time + action.duration
                self.last_action = copy.deepcopy(action)
                print("ny action skickas")
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
        self.start_node()

    def set_defaults(self):
        self.control_mode = ControlMode.FIND_OBJECT_MODE

    def object_detection_callback(self, msg):
        print("objekt callback")
        self.navigation.new_object_detection_msg(msg)

    def ultrasound_callback(self, msg):
        self.navigation.new_ultrasound_msg(msg)

    def control_mode_callback(self, data):
        self.control_mode = data.control_mode

    def pub_next_action(self):
        msg = self.navigation.new_action()
        if msg:
            self.pub_move.publish(msg)

    def start_node(self):
        rate = rospy.Rate(10)  # 10hz
        print("started")
        self.navigation.next_action_time = rospy.get_rostime()
        self.navigation.action_buffer.append(Action(10, 1, [0.16,0,0,0,0]))
        while not rospy.is_shutdown():

            if self.control_mode == ControlMode.MANUAL_MOVE_MODE:
                # TODO: Stop subscribing to object_detection
                # Do nothing send controll directly via move to arduino
                pass
            elif self.control_mode == ControlMode.FIND_OBJECT_MODE:
                self.pub_next_action() 

            rate.sleep()


if __name__ == '__main__':
    try:
        main_control = MainControl()
    except rospy.ROSInterruptException:
        pass
