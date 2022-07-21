#include <nlink_parser/LinktrackNodeframe1.h>
#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_datatypes.h>

nav_msgs::Odometry odometry_msg;

void nodeFrame1Callback(const nlink_parser::LinktrackNodeframe1 &msg){
    odometry_msg.header.stamp = ros::Time::now();
    odometry_msg.pose.pose.position.x = msg.nodes[0].pos_3d[0];
    odometry_msg.pose.pose.position.y = msg.nodes[0].pos_3d[1];
    odometry_msg.pose.pose.position.z = 1.0;
}

void telloOdomCallback(const nav_msgs::Odometry & msg){
    tf::Quaternion quat;
    tf::quaternionMsgToTF(msg.pose.pose.orientation, quat);
    double r,p,y;
    tf::Matrix3x3(quat).getRPY(r, p, y);
    r=0.0;
    p=0.0;
    y = -y;
    odometry_msg.pose.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(r,p,y);
    // odometry_msg.pose.pose.orientation = msg.pose.pose.orientation
}

int main(int argc, char **argv){
  ros::init(argc, argv, "frame1_to_mavros");
  ros::NodeHandle nh;
  ros::Rate loop_rate(20);
  ros::Publisher odometry_pub = nh.advertise<nav_msgs::Odometry>("odometry1", 10);
  ros::Subscriber frame1_data = nh.subscribe("nlink_linktrack_nodeframe1", 10, &nodeFrame1Callback);
  ros::Subscriber odom_sub = nh.subscribe("/tello/odom", 10, &telloOdomCallback);

  while (ros::ok()){
        odometry_pub.publish(odometry_msg);
        ros::spinOnce();
        loop_rate.sleep();
  }
  

}