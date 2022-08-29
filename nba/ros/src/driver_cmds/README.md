to install dependences, from nba/ros directory, run: rosdep install --from-paths src --ignore-src -y --rosdistro=melodic 

to meet tod_input_devices Qt dependency, run: sudo apt-get install qt5-default qml-module-qtquick2 qtpositioning5-dev

build from nba/ros: catkin build

source wsp

run ctrl cmd generation chain: roslaunch tod_command_creation tod_command_creation.launch

