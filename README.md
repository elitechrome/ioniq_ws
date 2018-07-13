# ioniq_ws 
This is ioniq_control workspace.
This workspace use only avl student and elitechrome.

This project based on Ubuntu 16.04, ROS Kinetic.

## Install required packages
```
$ sudo apt install can-utils
$ sudo apt install ros-kinetic-ros-canopen
```

## Enable Virtual CAN
```
$ sudo modprobe vcan
$ sudo ip link add dev vcan0 type vcan
$ sudo ip link set up vcan0
```
## Enable Real CAN(200ms)
```
$ sudo ip link set can0 up type can bitrate 500000 restart-ms 200
```

## Log CAN data
```
$ candump -L can0 > can0.log
```

## Play logged CAN data
```
$ canplayer -I candump-2017-05-19_101301.log vcan0=can0
``` 



## Further reading
https://www.kernel.org/doc/Documentation/networking/can.txt
https://github.com/stefanhoelzl/CANpy/blob/master/docs/DBC_Specification.md