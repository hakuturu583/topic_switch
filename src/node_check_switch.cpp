#include <topic_switch/node_check_switch.h>

node_check_switch::node_check_switch()
{
    advertised_ = false;
    nh_.param<std::string>(ros::this_node::getName()+"/check_target_node_name", check_target_node_name_, "target_node");
    nh_.param<std::string>(ros::this_node::getName()+"/topic_exist", topic_exist_, ros::this_node::getName()+"/topic_exist");
    nh_.param<std::string>(ros::this_node::getName()+"/topic_not_exist", topic_not_exist_, ros::this_node::getName()+"/topic_not_exist");
    subscribe_();
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
            exist_pub_ = msg->advertise(nh_, topic_exist_, 10, false);
            not_exist_pub_ = msg->advertise(nh_, topic_not_exist_, 10, false);
        }
        advertised_ = true;
    }
    if(target_node_exists_())
    {
        exist_pub_.publish(msg);
    }
    else
    {
        not_exist_pub_.publish(msg);
    }
    return;
}

bool node_check_switch::target_node_exists_()
{
    std::vector<std::string> detected_nodes;
    ros::master::getNodes(detected_nodes);
    for(auto itr = detected_nodes.rbegin(); itr != detected_nodes.rend(); ++itr)
    {
        if(*itr == check_target_node_name_)
        {
            return true;
        }
    }
    return false;
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