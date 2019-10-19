#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "geometry_msgs/Point.h"

int count = 0;
visualization_msgs::Marker points;

class SubscribeAndPublish
{
public:
	SubscribeAndPublish()
	{
		//Topic you want to publish
		pub_ = n_.advertise<visualization_msgs::Marker>("/output", 1);

		//Topic you want to subscribe
		sub_ = n_.subscribe("/input", 1, &SubscribeAndPublish::callback, this);
	}

	void callback(const geometry_msgs::Point& input)
	{
		points.header.frame_id = "/output";
		points.header.stamp = ros::Time::now();
		points.ns = "points";
		points.action = visualization_msgs::Marker::ADD;
		//points.pose.orientation.w = line_strip.pose.orientation.w = line_list.pose.orientation.w = 1.0;
		points.id = 0;
		points.type = visualization_msgs::Marker::POINTS;
		points.scale.x = 0.2;
		points.scale.y = 0.2;
		points.color.g = 1.0f;
		points.color.a = 1.0;
		//.... do something with the input and generate the output (points)...
		points.points.push_back(input);
		count++;
		if (count % 5 == 0)
		{
			pub_.publish(points);
			visualization_msgs::Marker mrk;
			points = mrk;
		}
		//sleep(1);
	}

private:
	ros::NodeHandle n_;
	ros::Publisher pub_;
	ros::Subscriber sub_;

};//End of class SubscribeAndPublish

int main(int argc, char** argv)
{
	//Initiate ROS
	ros::init(argc, argv, "answer");

	//Create an object of class SubscribeAndPublish that will take care of everything
	SubscribeAndPublish SAPObject;

	ros::spin();

	return 0;
}