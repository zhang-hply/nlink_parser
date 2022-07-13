#include <nlink_parser/LinktrackNodeframe2.h>
#include <ros/ros.h>
#include <nav_msgs/Odometry.h>

nav_msgs::Odometry odometry_msg;

void nodeFrame2Callback(const nlink_parser::LinktrackNodeframe2 &msg){
    odometry_msg.header.stamp = ros::Time::now();
    odometry_msg.pose.pose.position.x = msg.pos_3d[0];
    odometry_msg.pose.pose.position.y = msg.pos_3d[1];
    odometry_msg.pose.pose.position.z = msg.pos_3d[2];
    odometry_msg.pose.pose.orientation.w = msg.quaternion[0];
    odometry_msg.pose.pose.orientation.x = msg.quaternion[1];
    odometry_msg.pose.pose.orientation.y = msg.quaternion[2];
    odometry_msg.pose.pose.orientation.z = msg.quaternion[3];
}

int main(int argc, char **argv){
  ros::init(argc, argv, "frame2_to_mavros");
  ros::NodeHandle nh;
  ros::Rate loop_rate(100);
  ros::Publisher odometry_pub = nh.advertise<nav_msgs::Odometry>("odometry2", 10);
  ros::Subscriber frame2_data = nh.subscribe("nlink_linktrack_nodeframe2", 10, &nodeFrame2Callback);

  while (ros::ok()){
        odometry_pub.publish(odometry_msg);
        ros::spinOnce();
        loop_rate.sleep();
  }
  

}