/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TeleopPS3.cpp
 * Author: wetayupanta
 * 
 * Created on October 6, 2017, 3:14 PM
 */

#include "TeleopPS3.h"

TeleopPS3::TeleopPS3() : nh_schunk_("schunk") {
    base_vel_pub_ = nh_.advertise<geometry_msgs::Twist>("cmd_vel", 3);

    joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 1, &TeleopPS3::joyCallback, this);
}

TeleopPS3::TeleopPS3(const TeleopPS3& orig) {
}

TeleopPS3::~TeleopPS3() {
}

void TeleopPS3::joyCallback(const sensor_msgs::Joy::ConstPtr& joy) {
    geometry_msgs::TwistPtr velocity_msg(new geometry_msgs::Twist);
    static bool sent_zero_last_time = false;

    //    if (joy->buttons[button_up]) {
    //        std::stringstream ss;
    //        ss << "Press value " << joy->axes[axis_button_up];
    //        cout << ss.str() << "\n \n";
    //    }

    //    cout << joy->buttons[l2] << "\n \n";


    if (joy->buttons[l2] || joy->buttons[r2]) {
        double speedfactor = 1 + (-joy->axes[axis_r2]) + (-joy->axes[axis_l2]); // up to thrice the speed if turbo

        velocity_msg->linear.x = joy->axes[up_down_stick_left] * speed * speedfactor;
        velocity_msg->linear.y = joy->axes[right_left_stick_left] * speed * speedfactor;
        velocity_msg->linear.z = joy->axes[up_down_stick_right] * speed * speedfactor;
        velocity_msg->angular.z = joy->axes[right_left_stick_right] * turn * speedfactor;

        ROS_DEBUG("effective linear x = %f, effective linear y = %f, effective linear z = %f, effective angular z = %f",
                velocity_msg->linear.x,
                velocity_msg->linear.y,
                velocity_msg->linear.z,
                velocity_msg->angular.z);

        // do not repeat zero'd messages on idle to not disturb other publishers
        if (fabs(velocity_msg->linear.x) <= velocity_gate_min &&
                fabs(velocity_msg->linear.y) <= velocity_gate_min &&
                fabs(velocity_msg->linear.z) <= velocity_gate_min &&
                fabs(velocity_msg->angular.z) <= velocity_gate_min) {
            velocity_msg->linear.x = 0;
            velocity_msg->linear.y = 0;
            velocity_msg->linear.z = 0;
            velocity_msg->angular.z = 0;
            if (sent_zero_last_time == false) {
                sent_zero_last_time = true;
                base_vel_pub_.publish(velocity_msg);
                ROS_DEBUG("Sent zero'd.");
            } else
                ROS_DEBUG("Sent nothing.");
        } else {
            sent_zero_last_time = false;
            base_vel_pub_.publish(velocity_msg);
            ROS_DEBUG("Sent values.");
        }

    } else {
        // leave message zero'd
        // do not repeat zero'd messages on idle to not disturb other publishers
        if (sent_zero_last_time == false) {
            sent_zero_last_time = true;
            base_vel_pub_.publish(velocity_msg);
            ROS_DEBUG("Sent zero'd.");
        } else
            ROS_DEBUG("Sent nothing.");
    }

}