# move_base_virtual_wall_server pkg

Virtual wall server for move_base in ROS navigation pkg  

## Images

For example, if you use the map (Fig. 1), you can make the following map (Fig. 2). 

<img src="https://github.com/KentaKubota/road_surface_recognition/blob/master/images/map.png" title="Fig.1 map" width="600px" alt="Fig.1 map">

<img src="https://github.com/KentaKubota/road_surface_recognition/blob/master/images/lawnMap.png" title="Fig.2 lawnMap" width="600px" alt="Fig.2 lawnMap">

## Preparation

Please install `laser_geometry` pkg in your catkin_ws/src/ because this pkg uses laser_geometry pkg function.
<https://github.com/ros-perception/laser_geometry.git>

## How to use

    1. $ roslaunch road_surface_recognition build_reflection_mapping.launch

    2. $ rosrun map_server map_server ~/catkin_ws/src/road_surface_recognition/test/map.yaml

    3. $ unzip ~/catkin_ws/src/road_surface_recognition/test/bagFile.zip  
       $ rosbag play ~/catkin_ws/src/road_surface_recognition/test/bagFile.bag

**Run following command when bagfile is finished.**

    4. $ rosservice call /up_map 

**If you can see following message on your terminal,**  
**`Published an OccupancyGrid data of which topic name is occupancyGrid,`**  
**finally, run following command.**
 
    5. $ rosrun map_server map_saver -f mapFileName map:=lawnOccupancyGrid
 
**You can get occupancy grid map named mapFileName on your terminal having done command.**
