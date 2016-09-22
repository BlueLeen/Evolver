#!/bin/bash
ECLIPSEVERSION=4.6
#export PYTHONPATH=${PYTHONPATH}:/usr/lib/python2.7:/usr/lib/python2.7/plat-i386-linux-gnu:/usr/lib/python2.7/lib-tk:/usr/lib/python2.7/lib-old:/usr/lib/python2.7/lib-dynload:/usr/local/lib/python2.7/dist-packages:/usr/lib/python2.7/dist-packages:usr/lib/python2.7/dist-packages/PILcompat:/usr/lib/python2.7/dist-packages/gtk-2.0:/usr/lib/python2.7/dist-packages/ubuntu-sso-client
#export PATH=/opt/android-18-arm-linux-androideabi-4.9/bin:${PATH}
#source ../ros_catkin_ws/install_isolated/setup.bash
source /home/su/Workspace/ros_catkin_ws/install_isolated/setup.bash
catkin_make_isolated --force-cmake -G"Eclipse CDT4 - Unix Makefiles"  --install  --install-space intelligence-eclipse -D_ECLIPSE_VERSION=$ECLIPSEVERSION -DCMAKE_BUILD_TYPE=Debug --cmake-args -DCMAKE_MODULE_PATH=/home/su/Workspace/ros_catkin_ws/android-e01s/cmake_modules
