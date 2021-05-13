#!/usr/bin/env python
import rospy
from std_msgs.msg import String, Float32
from chase_msgs.msg import ObjectDetection, Move, ControlMode
from random import randint
#
# Main control skall
# Ta emot object detection signaler
# Skicka commando signaler till Arduinon
# Lyssna på IMU signalerna


class Action:
    # Jadu
    def __init__(self, duration, speed=0, turn_radius=0):
        self.duration = rospy.Duration(duration)
        self.speed = speed
        self.turn_radius = turn_radius

    def get_msg(self):
        msg = Move()
        msg.velocity_forward = self.speed
        msg.turn_radius = self.turn_radius

        return msg


class Navigation:
    # Ett exempel på dum navigering
    DEFAULT_SPEED = 0.3

    def __init__(self):
        self.in_view = False

        self.image_x = -1
        self.image_y = -1
        self.pos_x = -1
        self.pos_y = -1

        self.action_buffer = []
        self.last_seen = 0
        self.last_action = 0
        self.next_action_time = 0

    def new_object_detection_msg(self, msg):
        self.in_view = msg.object_found

        if msg.object_found:
            # TODO: Kanske borde vara en setting som skickas, eller hämtas
            self.image_y = msg.image_y
            self.image_y = msg.image_y

            self.pos_x = msg.pos_x
            self.pos_y = msg.pos_y
            self.last_seen = msg.time_stamp

    def follow_object(self):
        pass  # TODO

    def new_ultrasound_msg(self, msg):
        # if (distance < .....)
        # self.collision()

        pass  # TODO: implement

    def collision(self):
        action_buffer = []
        action_buffer.append(Action(0.3, -DEFAULT_SPEED, 0))
        action_buffer.append(Action(0.3, 0, 0.1))  # Svänger alltid höger
        action_buffer.append(Action(100, 0, 0.1))  # Svänger alltid höger

    def new_action(self):
        current_time = rospy.get_rostime()
        # TODO: Check if buffer is empty
        if current_time < self.next_action_time:
            action = self.action_buffer.pop()
            self.next_action_time = current_time + action.duration
            return action.get_msg()

        return None


class MainControl:
    def __init__(self):
        self.navigation = Navigation()

        rospy.init_node('main_control')

        self.pub_move = rospy.Publisher('move', Move, queue_size=10)
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
        msg = self.navigation.get_action()
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
