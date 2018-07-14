#/bin/bash
echo "modprobe vcan"
sudo modprobe vcan

echo "set vcan0: "
sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0

echo "set vcan1: "
sudo ip link add dev vcan1 type vcan
sudo ip link set up vcan1
