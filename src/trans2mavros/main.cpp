#include <nlink_parser/LinktrackNodeframe2.h>
#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>

geometry_msgs::PoseStamped pose_msg;

void nodeFrame2Callback(const nlink_parser::LinktrackNodeframe2 &msg){

    pose_msg.header.stamp = ros::Time::now();
    pose_msg.pose.position.x = msg.pos_3d[0];
    pose_msg.pose.position.y = msg.pos_3d[1];
    pose_msg.pose.position.z = msg.pos_3d[2];
    pose_msg.pose.orientation.w = msg.quaternion[0];
    pose_msg.pose.orientation.x = msg.quaternion[1];
    pose_msg.pose.orientation.y = msg.quaternion[2];
    pose_msg.pose.orientation.z = msg.quaternion[3];
}

int main(int argc, char **argv){
  ros::init(argc, argv, "frame2_to_mavros");
  ros::NodeHandle nh;
  ros::Rate loop_rate(1000);
  ros::Publisher pose_pub = nh.advertise<geometry_msgs::PoseStamped>("pose", 10);
  ros::Subscriber frame2_data = nh.subscribe("nlink_linktrack_nodeframe2", 10, &nodeFrame2Callback);

  while (ros::ok()){
        pose_pub.publish(pose_msg);
        ros::spinOnce();
        loop_rate.sleep();
  }
  

}