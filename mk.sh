#!/bin/sh
if [ "$1" != "x86" ]
then
    source /opt/ros_catkin_ws/install_isolated/setup.bash
    catkin_make_isolated --install  --install-space intelligence --cmake-args -DCMAKE_BUILD_TYPE=Release -DANDROID=1 -DCMAKE_TOOLCHAIN_FILE=/opt/ros_catkin_ws/rostoolchain.cmake

else
    source  /opt/ros_catkin_x86/install_isolated/setup.bash
    catkin_make_isolated --install --install-space intelligence_x86  --cmake-args -DCMAKE_MODULE_PATH=/home/lianbin/intelligence_e01s/cmake_modules  -DCMAKE_BUILD_TYPE=Release
fi
