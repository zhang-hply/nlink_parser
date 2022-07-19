#include <nlink_parser/LinktrackNodeframe1.h>
#include <ros/ros.h>
#include <nav_msgs/Odometry.h>

nav_msgs::Odometry odometry_msg;

void nodeFrame1Callback(const nlink_parser::LinktrackNodeframe1 &msg){
    odometry_msg.header.stamp = ros::Time::now();
    odometry_msg.pose.pose.position.x = msg.nodes[0].pos_3d[0];
    odometry_msg.pose.pose.position.y = msg.nodes[0].pos_3d[1];
    odometry_msg.pose.pose.position.z = 0.0;
    odometry_msg.pose.pose.orientation.w = 1.0;
    odometry_msg.pose.pose.orientation.x = 0.0;
    odometry_msg.pose.pose.orientation.y = 0.0;
    odometry_msg.pose.pose.orientation.z = 0.0;
}

int main(int argc, char **argv){
  ros::init(argc, argv, "frame1_to_mavros");
  ros::NodeHandle nh;
  ros::Rate loop_rate(100);
  ros::Publisher odometry_pub = nh.advertise<nav_msgs::Odometry>("odometry1", 10);
  ros::Subscriber frame2_data = nh.subscribe("nlink_linktrack_nodeframe1", 10, &nodeFrame1Callback);

  while (ros::ok()){
        odometry_pub.publish(odometry_msg);
        ros::spinOnce();
        loop_rate.sleep();
  }
  

}