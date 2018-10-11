#include <topic_switch/node_check_switch.h>

node_check_switch::node_check_switch()
{
    advertised_ = false;
    nh_.param<std::string>(ros::this_node::getName()+"/check_target_node_name", check_target_node_name_, "target_node");
    nh_.param<std::string>(ros::this_node::getName()+"/topic_exist", topic_exist_, ros::this_node::getName()+"/topic_exist");
    nh_.param<std::string>(ros::this_node::getName()+"/topic_not_exist", topic_not_exist_, ros::this_node::getName()+"/topic_not_exist");
}

node_check_switch::~node_check_switch()
{

}

void node_check_switch::callback_(const ros::MessageEvent<topic_tools::ShapeShifter>& msg_event)
{
    boost::shared_ptr<topic_tools::ShapeShifter const> const &msg = msg_event.getConstMessage();
    boost::shared_ptr<const ros::M_string> const& connection_header = msg_event.getConnectionHeaderPtr();
    if (!advertised_)
    {
        if (connection_header)
        {
            bool latch = false;
            ros::M_string::const_iterator it = connection_header->find("latching");
            if((it != connection_header->end()) && (it->second == "1"))
            {
                ROS_DEBUG("input topic is latched; latching output topic to match");
                latch = true;
            }
        }
        advertised_ = true;
    }
    return;
}

void node_check_switch::connection_callback_(const ros::SingleSubscriberPublisher&)
{
    return;
}

void node_check_switch::subscribe_()
{
    sub_ptr_ = new ros::Subscriber(nh_.subscribe(ros::this_node::getName()+"/input",10,&node_check_switch::callback_,this));
    return;
}

void node_check_switch::unsubscribe_()
{
    if(sub_ptr_)
    {
        delete sub_ptr_;
        sub_ptr_ = NULL;
    }
    return;
}