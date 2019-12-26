#! /usr/bin/env python

import rospy
from move_base_virtual_wall_server.srv import CreateWall
from move_base_virtual_wall_server.srv import CreateWallRequest

rospy.wait_for_service('/virtual_wall_server/create_wall')
create_wall_client = rospy.ServiceProxy('/virtual_wall_server/create_wall', CreateWall)

req = CreateWallRequest()

def create_wall_func(id, start_point, end_point):
  global create_wall_client
  global req
  
  req.id = id
  req.start_point.x = start_point[0]
  req.start_point.y = start_point[1]
  req.end_point.x = end_point[0]
  req.end_point.y = end_point[1]

  create_wall_client(req)

for i in range(10):

  if i % 2:
    create_wall_func(i, [1.2*i, 2], [1.2*i, 7])
  else:
    bias = 2.5
    create_wall_func(i, [1.2*i, 2 + bias], [1.2*i, 7 + bias])

