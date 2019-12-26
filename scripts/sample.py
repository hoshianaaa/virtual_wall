#! /usr/bin/env python

import rospy
from move_base_virtual_wall_server.srv import CreateWall
from move_base_virtual_wall_server.srv import CreateWallRequest

rospy.wait_for_service('/virtual_wall_server/create_wall')
create_wall = rospy.ServiceProxy('/virtual_wall_server/create_wall', CreateWall)

req = CreateWallRequest()

req.id = 0
req.start_point.x = 2.0
req.start_point.y = -5.0
req.end_point.x = 2.0
req.end_point.y = 5.0

create_wall(req)
