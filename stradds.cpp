#include "ros/ros.h"
#include "my_service/AddStr.h"

bool add(my_service::AddStr::Request &req,
	my_service::AddStr::Response &res)
{
	res.str3 = req.str1 + req.str2;
	return true;
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "adds");
	ros::NodeHandle n;
	ros::ServiceServer service = n.advertiseService(ros::this_node::get_Name(), add);
	ros::spin();
	return 0;
}