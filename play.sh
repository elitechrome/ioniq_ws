#!/bin/bash
roslaunch dbc_converter play_candump.launch&

source ./devel/setup.bash
canplayer -I ./can_log/180713_ioniq_ccan.log vcan0=can0 &
canplayer -I ./can_log/180713_ioniq_egwy.log vcan1=can1 &
