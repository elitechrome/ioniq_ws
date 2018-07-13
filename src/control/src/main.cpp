#include <stdio.h>
#include <ros/ros.h>
#include <PCANBasic.h>

#define channel PCAN_USBBUS1

int main(int argc, char** argv){
    ros::init(argc, argv, "control_node");
    ros::NodeHandle nh("~");
    TPCANStatus stat;
    TPCANMsg conf_msg, val_msg;
    uint8_t AlvCnt = 0;
    bool msg_flag = false;
    ros::Rate loop(100);

    conf_msg.ID = 0x156;
    conf_msg.MSGTYPE = MSGTYPE_STANDARD;
    conf_msg.LEN = 8;
    memset(conf_msg.DATA, 0, sizeof(uint8_t)*8);

    val_msg.ID = 0x157;
    val_msg.MSGTYPE = MSGTYPE_STANDARD;
    val_msg.LEN = 7;
    memset(val_msg.DATA, 0, sizeof(uint8_t)*7);

    stat = CAN_Initialize(channel, PCAN_BAUD_500K);
    if(stat != PCAN_ERROR_OK){
        char error_message[50];
        CAN_GetErrorText(stat, 0x09, error_message);
        printf("%s\n",error_message);
        ROS_INFO("%s\n",error_message);
    }
    int32_t tar_steer = 200;
    while(ros::ok()){
        if(!msg_flag){
            conf_msg.DATA[0] |= 0x01;
            conf_msg.DATA[1] = 75;
            conf_msg.DATA[7] = AlvCnt++;
            msg_flag =true;
            stat = CAN_Write(channel,&conf_msg);
        }
        else{
            val_msg.DATA[0] = (BYTE)(tar_steer & 0xff);
            val_msg.DATA[1] = (BYTE)((tar_steer & 0xff00)>>8);
            msg_flag =false;
            stat = CAN_Write(channel, &val_msg);
        }

        loop.sleep();

    }
}
