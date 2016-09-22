#!/usr/bin/env python

import rospy
from configure.msg._node_info import node_info

def notify(data):
	rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.data)

def callback(data):
	rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.nodeflag)

def listener():
	rospy.init_node('notify', anonymous=True)
	rospy.Subscriber("flushparam", node_info, callback)
	rospy.spin()


if __name__ == '__main__':
	try:
		listener()
	except rospy.ROSInterruptException:
		print('ROSInterruptException occur')
		pass
