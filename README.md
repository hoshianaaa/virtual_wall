# move_base_virtual_wall_server pkg

move_baseのcostmapに仮想の壁を生成できる  

## Images

例えば,上の写真から下の写真のように障害物を生成できる.

<img src="https://github.com/hoshianaaa/move_base_virtual_wall_server/blob/master/images/no_vritual_wall.png" title="図１ costmap" width="400px" alt="Fig.1 map">  

<img src="https://github.com/hoshianaaa/move_base_virtual_wall_server/blob/master/images/virtual_wall.png" title="図２壁生成後 after" width="400px" alt="Fig.2 lawnMap">

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
