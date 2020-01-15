# move_base_virtual_wall_server

move_baseのcostmapに仮想的な壁を生成できる  

## Images
写真のように,仮想的な壁を生成できる

<img src="https://github.com/hoshianaaa/move_base_virtual_wall_server/blob/master/images/wall.png" title="図２壁生成後 after" width="600px" alt="Fig.2 lawnMap">

## Preparation

以下を参考に,move_baesのパラメータファイルcostmap_common_params.yamlを編集する  
[パラメータファイル](https://github.com/hoshianaaa/move_base_virtual_wall_server/blob/master/params/costmap_common_params.yaml)

## How to use

move_baseが起動している状態で、以下のコマンドでサーバを立ち上げる


     $ rosrun move_base_virtual_wall_server virtual_wall_server
  
壁生成のサンプル
    
     $ rosrun move_base_virtual_wall_server sample.py

## Movie
https://www.youtube.com/watch?v=yeid-L35hc0&feature=youtu.be
