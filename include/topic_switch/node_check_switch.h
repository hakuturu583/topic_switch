#ifndef NODE_CHECK_SWITCH_H_INCLUDED
#define NODE_CHECK_SWITCH_H_INCLUDED

//headers in ROS
#include <ros/ros.h>
#include <topic_tools/shape_shifter.h>

//headers in STL
#include <unordered_map>
//#include <memory>

class node_check_switch
{
public:
    node_check_switch();
    ~node_check_switch();
private:
    ros::NodeHandle nh_;
    ros::Subscriber* sub_ptr_;
    std::unordered_map<std::string,ros::Publisher> pubs_;
    std::string topic_exist_;
    std::string topic_not_exist_;
    std::string check_target_node_name_;
    void callback_(const ros::MessageEvent<topic_tools::ShapeShifter>& msg_event);
    void connection_callback_(const ros::SingleSubscriberPublisher&);
    void subscribe_();
    void unsubscribe_();
    volatile bool advertised_;
};

#endif  //NODE_CHECK_SWITCH_H_INCLUDED