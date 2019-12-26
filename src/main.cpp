#include <ros/ros.h>
#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/point_cloud_conversion.h>
#include <nav_msgs/SetMap.h>
#include <nav_msgs/GetMap.h>

#include <pcl_ros/point_cloud.h>
#include <pcl_ros/transforms.h>

#include <costmap_2d/costmap_2d.h>

#include <move_base_virtual_wall_server/CreateWall.h>
#include <move_base_virtual_wall_server/DeleteWall.h>
#include <move_base_virtual_wall_server/DeleteAll.h>

class IDPointCloud
{
  public:
    pcl::PointCloud < pcl::PointXYZ > pc;
    int id;
    double start_x, start_y, end_x, end_y;
};

class Point2D
{
  public:
    int x;
    int y;
};

class VirtualWallServer
{
  public:
    VirtualWallServer()
    {

      odom_frame_ = "odom";
      map_frame_ = "map";

      first_map_received_ = false;

      cloud_pub = n.advertise <sensor_msgs::PointCloud2> ("/virtual_wall_cloud", 1, false);
      map_sub = n.subscribe(map_frame_, 1, &VirtualWallServer::mapCallback, this);

      ros::NodeHandle private_nh("~");

      create_wall_service = private_nh.advertiseService("create_wall", &VirtualWallServer::createWall, this);
      delete_wall_service = private_nh.advertiseService("delete_wall", &VirtualWallServer::deleteWall, this);
      delete_all_service = private_nh.advertiseService("delete_all", &VirtualWallServer::deleteAll, this);

      ros::Rate r(10);

      while (!first_map_received_){
        ROS_WARN("wait map ...");
        ros::spinOnce();
        r.sleep();
      }

      while (ros::ok())
      {
        ros::spinOnce();
        publishCloud();
        debugCloud();
        r.sleep();
      }
    }

  private:
    ros::NodeHandle n;
    ros::Publisher cloud_pub;
    ros::Subscriber map_sub;
    ros::ServiceServer create_wall_service;
    ros::ServiceServer delete_wall_service;
    ros::ServiceServer delete_all_service;

    void mapCallback(const nav_msgs::OccupancyGridConstPtr& msg)
    {
      if (first_map_received_)return;

      double origin_x = msg->info.origin.position.x;
      double origin_y = msg->info.origin.position.y;
      double resolution = msg->info.resolution;
      unsigned int size_x = msg->info.width;
      unsigned int size_y = msg->info.height;

      map_.resizeMap(size_x, size_y, resolution, origin_x, origin_y);
      first_map_received_ = true;
      return;
    }

    costmap_2d::Costmap2D map_;
    bool first_map_received_;

    bool createWall(move_base_virtual_wall_server::CreateWall::Request &req, move_base_virtual_wall_server::CreateWall::Response &res)
    {
      
      deleteWallHandler ((int)req.id);
      
      IDPointCloud id_pc;
      id_pc.id = req.id;
      id_pc.start_x = req.start_point.x;
      id_pc.start_y = req.start_point.y;
      id_pc.end_x = req.end_point.x;
      id_pc.end_y = req.end_point.y;
      
      createLineCloud (req.start_point.x, req.end_point.x, req.start_point.y, req.end_point.y, id_pc.pc);

      clouds_.push_back(id_pc);

      res.status = true;
      return true;
    }

    bool deleteWall(move_base_virtual_wall_server::DeleteWall::Request &req, move_base_virtual_wall_server::DeleteWall::Response &res)
    {
      if(deleteWallHandler((int)req.id))
      {
        res.status = true;
        return true;
      }
      else
      {
        res.status = false;
        return false;
      }
    }

    bool deleteAll(move_base_virtual_wall_server::DeleteAll::Request &req, move_base_virtual_wall_server::DeleteAll::Response &res)
    {
      clouds_.clear();
      res.status = true;
      return 1;
    }

    bool deleteWallHandler(int id)
    {
      bool status = false;
      auto it = clouds_.begin();
      while (it != clouds_.end())
      {
        if (it->id == id)
        {
          status = true;
          it = clouds_.erase(it);
        }
        else
        {
          it ++;
        }
      }
      return status;
    }

    std::vector < IDPointCloud > clouds_; 

    void createLineCloud(double wx0, double wx1, double wy0, double wy1, pcl::PointCloud < pcl::PointXYZ > &pc, double height = 0.3)
    {
      unsigned int mx0, my0;
      unsigned int mx1, my1;

      map_.worldToMap(wx0, wy0, mx0, my0);
      map_.worldToMap(wx1, wy1, mx1, my1);

      std::vector<Point2D> pts;
      getLineCells(mx0, mx1, my0, my1, pts);

      pcl::PointCloud<pcl::PointXYZ> pcl_cloud;
      pcl::PointXYZ pcl_point;

      for (size_t i = 0; i < pts.size(); ++i){

        unsigned int mx, my;
        double wx, wy;

        mx = pts[i].x;
        my = pts[i].y;
        map_.mapToWorld(mx, my, wx, wy); 

        pcl_point.x = wx;
        pcl_point.y = wy;
        pcl_point.z = height;

        pcl_cloud.push_back(pcl_point);
      }
      pc = pcl_cloud;
    }

    // base_local_planner::FootprintHelper から引用
    void getLineCells(int x0, int x1, int y0, int y1, std::vector < Point2D >& pts)
    {
      //Bresenham Ray-Tracing
      int deltax = abs(x1 - x0);        // The difference between the x's
      int deltay = abs(y1 - y0);        // The difference between the y's
      int x = x0;                       // Start x off at the first pixel
      int y = y0;                       // Start y off at the first pixel

      int xinc1, xinc2, yinc1, yinc2;
      int den, num, numadd, numpixels;

      Point2D pt;

      if (x1 >= x0)                 // The x-values are increasing
      {
        xinc1 = 1;
        xinc2 = 1;
      }
      else                          // The x-values are decreasing
      {
        xinc1 = -1;
        xinc2 = -1;
      }

      if (y1 >= y0)                 // The y-values are increasing
      {
        yinc1 = 1;
        yinc2 = 1;
      }
      else                          // The y-values are decreasing
      {
        yinc1 = -1;
        yinc2 = -1;
      }

      if (deltax >= deltay)         // There is at least one x-value for every y-value
      {
        xinc1 = 0;                  // Don't change the x when numerator >= denominator
        yinc2 = 0;                  // Don't change the y for every iteration
        den = deltax;
        num = deltax / 2;
        numadd = deltay;
        numpixels = deltax;         // There are more x-values than y-values
      }
      else                          // There is at least one y-value for every x-value
      {
        xinc2 = 0;                  // Don't change the x for every iteration
        yinc1 = 0;                  // Don't change the y when numerator >= denominator
        den = deltay;
        num = deltay / 2;
        numadd = deltax;
        numpixels = deltay;         // There are more y-values than x-values
      }

      for (int curpixel = 0; curpixel <= numpixels; curpixel++)
      {
        pt.x = x;      //Draw the current pixel
        pt.y = y;
        pts.push_back(pt);

        num += numadd;              // Increase the numerator by the top of the fraction
        if (num >= den)             // Check if numerator >= denominator
        {
          num -= den;               // Calculate the new numerator value
          x += xinc1;               // Change the x as appropriate
          y += yinc1;               // Change the y as appropriate
        }
        x += xinc2;                 // Change the x as appropriate
        y += yinc2;                 // Change the y as appropriate
      }
    }

    void publishCloud()
    {
      pcl::PointCloud < pcl::PointXYZ > sum_pcl_cloud;
      
      for (int i=0; i < clouds_.size(); i++)
      {
        sum_pcl_cloud += clouds_[i].pc;
      }

      sensor_msgs::PointCloud2 ros_cloud;

      pcl::toROSMsg (sum_pcl_cloud, ros_cloud);

      ros_cloud.header.frame_id = map_frame_;
      cloud_pub.publish (ros_cloud);
    }

    std::string odom_frame_, map_frame_;

    void debugCloud()
    {
      std::cout << "[id] [x0, y0] [x1, y1]" << std::endl;
      for (int i=0; i < clouds_.size(); i++)
      {
        std::cout << "[" << clouds_[i].id       << "] ";
        std::cout << "[" << clouds_[i].start_x  << ", " << clouds_[i].start_y << "] ";
        std::cout << "[" << clouds_[i].end_x    << ", " << clouds_[i].end_y   << "]" << std::endl;
      }
      std::cout << std::endl;
    }

};



int main(int argc, char **argv)
{
  ros::init(argc, argv, "virtual_wall_server");
  VirtualWallServer vs;
  return 0;
}
