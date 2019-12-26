# move_base_virtual_wall_server pkg

move_baseのcostmapに仮想の壁を生成できる  

## Images
写真のように,仮想の壁を生成できる

<img src="https://github.com/hoshianaaa/move_base_virtual_wall_server/blob/master/images/wall.png" title="図２壁生成後 after" width="400px" alt="Fig.2 lawnMap">

## Preparation

以下を参考に,move_baesのパラメータファイルcostmap_common_params.yamlを編集する  
https://github.com/hoshianaaa/move_base_virtual_wall_server/blob/master/params/costmap_common_params.yaml

## How to use

move_baseが起動している状態で、以下のコマンドでサーバを立ち上げる


    1. $ rosrun move_base_virtual_wall_server virtual_wall_server
  
壁生成のサンプル
    
    2. $ rosrun move_base_virtual_wall_server sample.py
