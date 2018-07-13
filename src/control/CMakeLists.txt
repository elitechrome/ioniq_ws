cmake_minimum_required(VERSION 2.8.3)
project(control)


find_package(catkin REQUIRED COMPONENTS
  msgs
  roscpp
  std_msgs
)

link_directories(
    /usr/lib
)
link_libraries(
    pcanbasic
)



catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES control
#  CATKIN_DEPENDS msgs roscpp std_msgs
#  DEPENDS system_lib
)
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

 add_executable(${PROJECT_NAME}_node src/main.cpp)

 target_link_libraries(${PROJECT_NAME}_node
   ${catkin_LIBRARIES}
 )
