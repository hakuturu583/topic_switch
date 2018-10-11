# Topic Switch 
topic switch nodes for ROS.

| *master* |
|----------|
|[![Build Status](https://travis-ci.org/hakuturu583/topic_switch.svg?branch=master)](https://travis-ci.org/hakuturu583/topic_switch)

## node_check_switch 
### params
1. ~/check_target_node_name  
type: string  
name of the target node  

1. ~/topic_exist  
type: string  
name of the published topic if the target node exist

1. ~/topic_not_exist  
type: string  
name of the published topic if the target node does not exist

### test
```
roslaunch topic_switch sample.launch
```

```
rosnode kill /target_node
```