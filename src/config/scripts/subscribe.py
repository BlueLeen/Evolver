#!/usr/bin/env python

import sys
import rospy
from config.srv._node_infos import node_infos
from config.msg._node_info import node_info

def listener():
	rospy.init_node('notify', anonymous=True)
	rospy.Subscriber("flushparam", node_info, callback)
	display()
	rospy.spin()

def callback(data):
	rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.nodeflag)

def display():
	rospy.wait_for_service('requestparam')
	try:
		node_infos.nodeflag = 2
		getnodeflag = rospy.ServiceProxy('requestparam', node_infos)
		resp1 = getnodeflag();
		print('return value:%s'%resp1)
	except rospy.ServiceException, e:
		print("Service call failed: %s"%e)


if __name__ == '__main__':
	try:
		listener()
	except rospy.ROSInterruptException:
		print('ROSInterruptException occur')
		pass
	
