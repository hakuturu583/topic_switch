#include <ros/ros.h>

#include <topic_switch/node_check_switch.h>

int main(int argc, char *argv[])
{
  ros::init(argc, argv, "node_check_switch");
  node_check_switch switcher;
  ros::spin();
  return 0;
}