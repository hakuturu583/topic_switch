cmake_minimum_required(VERSION 2.8.3)
project(topic_switch)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  pluginlib
  topic_tools
  ros_type_introspection
)

catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES topic_switch
  CATKIN_DEPENDS roscpp rospy
#  DEPENDS system_lib
)

add_executable(node_check_switch src/node_check_switch_node.cpp src/node_check_switch.cpp)
target_link_libraries(node_check_switch ${catkin_LIBRARIES})

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

set(CPP_EXEC_NAMES node_check_switch)
foreach(cpp_exec_names ${CPP_EXEC_NAMES})
  install(TARGETS ${cpp_exec_names}
    RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
    )
endforeach(cpp_exec_names)

foreach(dir config launch)
  install(DIRECTORY ${dir}/
    DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/${dir})
endforeach(dir)