#include <ros/ros.h>
#include <geometry_msgs/PointStamped.h>
#include "geometry_msgs/Point.h"
#include <tf/transform_listener.h>
#include "time.h"


void transformPoint(const geometry_msgs::PointStamped& source_frame)
{
	try {
		listener.lookupTransform("core_frame", source_frame.header.frame_id,
			ros::Time(0), transform);
	}
	catch (tf::TransformException & ex) {
		ROS_ERROR("%s", ex.what());
	}
	geometry_msgs::Point point;
	point.x = transform.getOrigin().x();
	point.y = transform.getOrigin().y();
	point.z = transform.getOrigin().z();

	pub.publish(point)
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "transformPoint");
	ros::NodeHandle n;
	ros::Publisher pub = n.advertise<geometry_msgs::Point>("/output", 1);
	ros::TransformListener listener;
	ros::Subscriber sub = n.subscribe("/input", 1, transformPoint);
	ros::spin();
	return 0;
}