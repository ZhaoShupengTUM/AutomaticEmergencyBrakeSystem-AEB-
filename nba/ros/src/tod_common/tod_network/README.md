# tod_network
This package contains classes for serializing, sending and receiving ROS messages and configs. Transmission can either be done via UDP or TCP (using MQTT).

### Dependencies
  * ROS Packages:
    * roscpp
    * tod_msgs
  * [PahoMqttCpp](https://github.com/eclipse/paho.mqtt.cpp)
    ```
    sudo apt-get install doxygen graphviz -y
    cd ~/Downloads
    git clone https://github.com/eclipse/paho.mqtt.c.git
    cd paho.mqtt.c/
    git checkout v1.3.1
    sudo cmake -Bbuild -H. -DPAHO_WITH_SSL=ON -DPAHO_ENABLE_TESTING=OFF
    sudo cmake --build build/ --target install
    sudo ldconfig
    cd ~/Downloads
    sudo rm -r paho.mqtt.c/
    echo -e "${green}----- Installing PahoMqtt C++ -------${nocolor}"
    cd ~/Downloads
    git clone https://github.com/eclipse/paho.mqtt.cpp.git
    cd paho.mqtt.cpp/
    git checkout v1.1
    sudo cmake -Bbuild -H. -DPAHO_BUILD_DOCUMENTATION=TRUE -DPAHO_BUILD_SAMPLES=TRUE
    sudo cmake --build build/ --target install
    sudo ldconfig
    cd ~/Downloads
    sudo rm -r paho.mqtt.cpp/
    ```

### Usage (not for open source)
Add to CMakeLists.txt:
```
find_package(catkin REQUIRED COMPONENTS tod_network)
find_package(PahoMqttCpp REQUIRED)

catkin_package(
    ...
    CATKIN_DEPENDS ... tod_network
)

# add_executable(...)

target_link_libraries(<node_name>
    PahoMqttCpp::paho-mqttpp3
	)
```
Add to package.xml:
```
<build_depend>tod_network</build_depend>
<build_export_depend>tod_network</build_export_depend>
<exec_depend>tod_network</exec_depend>
```

Include in *.cpp:
```
#include "tod_network/tod_network.h"
```

### Samples (not for open source)
Look at *test/samples/* folder.
In order to test the sample packages, copy the respective package folder (f. e.: samples/ros_msg_sender_receiver) to the package level of your catkin workspace (f. e.: tof/wsp/src/ros_msg_sender_receiver). Otherwise, catkin will not find the package.

