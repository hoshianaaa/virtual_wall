# virtual_wall

generate virtual wall in ros navigation costmap 

<img src="https://github.com/hoshianaaa/move_base_virtual_wall_server/blob/master/images/wall.png" title="図２壁生成後 after" width="600px" alt="Fig.2 lawnMap">

## Preparation

+ Edit the parameter file costmap_common_params.yaml of move_baes with the following reference  
+ [param file](https://github.com/hoshianaaa/move_base_virtual_wall_server/blob/master/params/costmap_common_params.yaml)

## How to use

+ With move_base running, start the server with the following command

     $ rosrun move_base_virtual_wall_server virtual_wall_server
  
+ Sample of wall generation
    
     $ rosrun move_base_virtual_wall_server sample.py

## Movie
+ [YouTube](https://www.youtube.com/watch?v=yeid-L35hc0&feature=youtu.be)
