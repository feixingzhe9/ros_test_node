cmake_minimum_required(VERSION 2.8.3)
project(test)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  mrobot_msgs
  mrobot_srvs
)



catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES test
  CATKIN_DEPENDS roscpp std_msgs message_runtime
#  DEPENDS system_lib
)

###########
## Build ##
###########

set (CMAKE_CXX_FLAGS "-std=c++11")

include_directories(
include/test  ${catkin_INCLUDE_DIRS}
)


# catkin_add_nosetests(test)

add_executable(test_node 
           src/test.cpp
           )

add_dependencies(test_node
    ${catkin_EXPORTED_TARGETS}
)

target_link_libraries(test_node ${catkin_LIBRARIES})


install(TARGETS test_node
        ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

## Install project namespaced headers
install(DIRECTORY include/${PROJECT_NAME}/
        DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
        FILES_MATCHING PATTERN "*.h"
        PATTERN ".svn" EXCLUDE)

install(DIRECTORY launch

    DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
    USE_SOURCE_PERMISSIONS
    )
