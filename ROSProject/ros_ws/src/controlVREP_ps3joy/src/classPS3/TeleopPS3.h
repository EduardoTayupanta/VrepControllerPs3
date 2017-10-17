/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TeleopPS3.h
 * Author: wetayupanta
 *
 * Created on October 6, 2017, 3:14 PM
 */

#ifndef TELEOPPS3_H
#define TELEOPPS3_H

#include <ros/ros.h>

#include <actionlib_msgs/GoalID.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
#include <sensor_msgs/JointState.h>
#include <sensor_msgs/JoyFeedbackArray.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Empty.h>

#include "../button/values.h"

using namespace std;

class TeleopPS3 {
public:
    TeleopPS3();
    TeleopPS3(const TeleopPS3& orig);
    virtual ~TeleopPS3();
        
private:
    ros::NodeHandle nh_;
    ros::NodeHandle nh_schunk_;
    
    ros::Subscriber joy_sub_;
    ros::Publisher base_vel_pub_;
    
    void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);

    const static int select = PS3_BUTTON_SELECT;
    const static int l3 = PS3_BUTTON_STICK_LEFT;
    const static int r3 = PS3_BUTTON_STICK_RIGHT;
    const static int start = PS3_BUTTON_START;
    const static int button_up = PS3_BUTTON_CROSS_UP;
    const static int button_right = PS3_BUTTON_CROSS_RIGHT;
    const static int button_down = PS3_BUTTON_CROSS_DOWN;
    const static int button_left = PS3_BUTTON_CROSS_LEFT;
    const static int l2 = PS3_BUTTON_REAR_LEFT_2;
    const static int r2 = PS3_BUTTON_REAR_RIGHT_2;
    const static int l1 = PS3_BUTTON_REAR_LEFT_1;
    const static int r1 = PS3_BUTTON_REAR_RIGHT_1;
    const static int triangle = PS3_BUTTON_ACTION_TRIANGLE;
    const static int circle = PS3_BUTTON_ACTION_CIRCLE;
    const static int cross = PS3_BUTTON_ACTION_CROSS;
    const static int square = PS3_BUTTON_ACTION_SQUARE;
    const static int pairing = PS3_BUTTON_PAIRING;

    const static int right_left_stick_left = PS3_AXIS_STICK_LEFT_LEFTWARDS;
    const static int up_down_stick_left = PS3_AXIS_STICK_LEFT_UPWARDS;
    const static int right_left_stick_right = PS3_AXIS_STICK_RIGHT_LEFTWARDS;
    const static int up_down_stick_right = PS3_AXIS_STICK_RIGHT_UPWARDS;
    const static int axis_button_up = PS3_AXIS_BUTTON_CROSS_UP;
    const static int axis_button_right = PS3_AXIS_BUTTON_CROSS_RIGHT;
    const static int axis_button_down = PS3_AXIS_BUTTON_CROSS_DOWN;
    const static int axis_button_left = PS3_AXIS_BUTTON_CROSS_LEFT;
    const static int axis_l2 = PS3_AXIS_BUTTON_REAR_LEFT_2;
    const static int axis_r2 = PS3_AXIS_BUTTON_REAR_RIGHT_2;
    const static int axis_l1 = PS3_AXIS_BUTTON_REAR_LEFT_1;
    const static int axis_r1 = PS3_AXIS_BUTTON_REAR_RIGHT_1;
    const static int axis_triangle = PS3_AXIS_BUTTON_ACTION_TRIANGLE;
    const static int axis_circle = PS3_AXIS_BUTTON_ACTION_CIRCLE;
    const static int axis_cross = PS3_AXIS_BUTTON_ACTION_CROSS;
    const static int axis_square = PS3_AXIS_BUTTON_ACTION_SQUARE;
    const static int axis_accelerometer_right_left = PS3_AXIS_ACCELEROMETER_LEFT; // positive is left
    const static int axis_accelerometer_forward_backward = PS3_AXIS_ACCELEROMETER_FORWARD; // positive is forward
    const static int axis_accelerometer_up_down = PS3_AXIS_ACCELEROMETER_UP; // positive is up
    const static int axis_yaw = PS3_AXIS_GYRO_YAW; // positive is clockwise

    constexpr static double speed = 0.03; // .2 .5
    constexpr static double turn = 0.07; // .5 1
    //	constexpr static double gripper_speed = 0.08;
    constexpr static double velocity_gate_min = 0.005;

};

#endif /* TELEOPPS3_H */

