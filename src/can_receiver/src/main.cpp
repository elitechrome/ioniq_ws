#include <iostream>
#include <PCANBasic.h>
#include <ros/ros.h>

//Vehicle Information Msg
#include <msgs/steer.h>


const std::string topic_steer = "steer";

#define channel PCAN_USBBUS1

int main(int argc, char* argv[]){
    ros::init(argc, argv, "can_receiver");
    ros::NodeHandle nh("~"); //if you wirte this character "~" the the node name will be can_re~
    TPCANMsg msg;
    TPCANStatus stat;

    ros::Publisher steer_pub = nh.advertise<msgs::steer>(topic_steer,1);


    stat = CAN_Initialize(channel, PCAN_BAUD_500K);
    if(stat != PCAN_ERROR_OK){
        char error_message[50];
        CAN_GetErrorText(stat, 0x09, error_message);
        printf("%s\n",error_message);
        ROS_INFO("%s\n",error_message);
    }
    msgs::steer steer_msg;

    while(ros::ok()){
        ros::spinOnce();
        stat = CAN_Read(channel, &msg, NULL);
        if(stat !=PCAN_ERROR_OK){
//            char error[30];
//            CAN_GetErrorText(stat, 0x09, error);
//            printf("%s\n",error);
            continue;
        }
        if(msg.ID == 0x710){
            steer_msg.apm_fd_en = msg.DATA[0] & 0x01;
            steer_msg.mo_fd_sate= msg.DATA[0] & 0b1110;
            steer_msg.mod_fd_alvcnt= msg.DATA[7];
            steer_pub.publish(steer_msg);
        }
        else
            continue;
    }

    return 0;
}

