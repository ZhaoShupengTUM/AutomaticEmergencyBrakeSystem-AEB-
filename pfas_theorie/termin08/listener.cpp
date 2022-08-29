#include "ros/ros.h"
#include "std_msgs/String.h"

void chatterCallback(const std_msgs::String& msg) {
  std::cout << "Listener reveived: " <<msg.data << std::endl;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("chatter", 5, chatterCallback);
  ros::spin();

  return 0;
}
