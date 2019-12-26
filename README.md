# move_base_virtual_wall_server pkg

move_baseのcostmapに仮想の壁を生成できる  

## Images

例えば,上の写真から下の写真のように障害物を生成できる.

<img src="https://github.com/hoshianaaa/move_base_virtual_wall_server/blob/master/images/no_vritual_wall.png" title="図１ costmap" width="400px" alt="Fig.1 map">  

<img src="https://github.com/hoshianaaa/move_base_virtual_wall_server/blob/master/images/virtual_wall.png" title="図２壁生成後 after" width="400px" alt="Fig.2 lawnMap">

## Preparation

以下を参考に,move_baesのパラメータファイルcostmap_common_params.yamlを編集する  
https://github.com/hoshianaaa/move_base_virtual_wall_server/blob/master/params/costmap_common_params.yaml

## How to use

move_baseが起動している状態で、以下のコマンドでサーバが立ち上げる


    1. $ rosrun move_base_virtual_wall_server virtual_wall_server
  
壁生成のサンプル
    
    2. $ rosrun move_base_virtual_wall_server sample2.py
