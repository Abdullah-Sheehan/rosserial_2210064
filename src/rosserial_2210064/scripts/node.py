#!/usr/bin/env python3

import rospy 
from std_msgs import Float32MultiArray
from geometry_msgs import Twist

def cb_sensor(data):
    signal = data.data[0]
    echo = data.data[1]

    cmd_vel = Twist()

    if(echo > 20):
        cmd_vel.linear.x = signal
        cmd_vel.angular.z = 0
    
    else:
        cmd_vel.linear.x = 0
        cmd_vel.angular.z = signal
    
    pub.publish(cmd_vel)

rospy.init_node('avoid_obstacle')

pub = rospy.Publisher('/cmd_vel', Twist, queue_size=10)
rospy.Subscriber('/sensor_data', Float32MultiArray, cb_sensor)

rospy.spin()