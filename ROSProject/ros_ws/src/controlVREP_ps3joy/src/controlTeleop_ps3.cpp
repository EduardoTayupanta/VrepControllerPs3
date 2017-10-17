/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   controlTeleop_ps3.cpp
 * Author: wetayupanta
 *
 * Created on October 6, 2017, 3:12 PM
 */

#include "classPS3/TeleopPS3.h"
#include "classPS3/TeleopPS3Feedback.h"

/*
 * 
 */
int main(int argc, char** argv) {

    ros::init(argc, argv, "teleop_ps3");
    ROS_INFO("Starting PS3 controller Quadricopter ...");
    TeleopPS3 teleop_ps3;
    TeleopPS3Feedback teleop_ps3_feedback;
    ros::spin();
}

