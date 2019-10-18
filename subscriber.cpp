#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <iostream>
using namespace std;

void receive(const std_msgs::Int32 movement)
{
	ROS_INFO()("/subscriber: data: %d\n", movement.data);
	return;
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "subscriber");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("/topic", 1000, receive);
	ros::spin();
	return 0;
}