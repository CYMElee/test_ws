#include "ros/ros.h"
#include "geometry_msgs/PoseStamped.h"




geometry_msgs::PoseStamped pos;


void host(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    pos = *msg;
}


int main(int argc, char **argv)
{
    ros::init(argc,argv,"vision");
    ros::NodeHandle nh;

    ros::Publisher position_pub = nh.advertise<geometry_msgs::PoseStamped>("mavros/vision_pose/pose", 2);
    ros::Subscriber host_sub = nh.subscribe<geometry_msgs::PoseStamped>("/MAV1/mavros/local_position/pose", 10, host);
    ros::Rate rate(100);
    while(ros::ok())
    {
        ROS_INFO("MAV1: %.3f, %.3f , %.3f",pos.pose.position.x,pos.pose.position.y,pos.pose.position.z);
        position_pub.publish(pos);
        ros::spinOnce();
        rate.sleep();
    }
    return 0;
}