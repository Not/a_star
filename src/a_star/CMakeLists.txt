cmake_minimum_required(VERSION 3.0.2)
project(a_star)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++14)

find_package(catkin REQUIRED)
find_package( OpenCV REQUIRED )
catkin_package()

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(main 
  src/main.cpp
  src/graph.cpp
  src/node.cpp
  src/a_star.cpp 
  src/plot_nodes.cpp
  src/priorityqueueset.cpp
)


target_link_libraries(main
  ${catkin_LIBRARIES}
  ${OpenCV_LIBS}
) 