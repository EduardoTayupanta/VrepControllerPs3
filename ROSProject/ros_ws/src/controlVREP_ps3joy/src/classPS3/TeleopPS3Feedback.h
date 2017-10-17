/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TeleopPS3Feedback.h
 * Author: wetayupanta
 *
 * Created on October 12, 2017, 12:00 PM
 */

#ifndef TELEOPPS3FEEDBACK_H
#define TELEOPPS3FEEDBACK_H

#include <ros/ros.h>

#include <boost/thread.hpp>

#include <actionlib_msgs/GoalID.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
#include <sensor_msgs/JointState.h>
#include <sensor_msgs/JoyFeedbackArray.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Empty.h>

#include "../button/values.h"

using namespace std;

class TeleopPS3Feedback {
public:
    typedef sensor_msgs::JoyFeedback::_id_type ID;
    typedef sensor_msgs::JoyFeedback::_intensity_type INTENSITY;

    struct LED {
        ID id;
        INTENSITY intensity;
    };

    TeleopPS3Feedback();
    TeleopPS3Feedback(const TeleopPS3Feedback& orig);
    virtual ~TeleopPS3Feedback();
private:
    ros::NodeHandle nh_;

    ros::Publisher feedback_pub_;
    ros::Subscriber bumper_sub_;
    ros::Subscriber smach_enabled_sub_;

    LED leds_status[4];
    LED leds_knight_rider[4];

    constexpr static int LED_INDEX_MOTOR_STOP = 0;
    constexpr static int LED_INDEX_SMACH_DISABLED = 0;
protected:
    void smachEnabledCallback(const std_msgs::BoolConstPtr& smach_enabled_msg);

    void sendRumble(INTENSITY rumble_low_freq, INTENSITY rumble_high_freq);
    void sendLEDs(bool led0, bool led1, bool led2, bool led3);
    void sendLEDs(LED leds[4]);
    void knightRiderThread();
    void updateLEDs(bool knight_rider);

    sensor_msgs::JoyFeedbackPtr getFeedbackLED(LED led) {
        return getFeedbackLED(led.id, led.intensity);
    }

    /* id is 0-3 */
    sensor_msgs::JoyFeedbackPtr getFeedbackLED(ID id, INTENSITY intensity) {
        sensor_msgs::JoyFeedbackPtr feedback(new sensor_msgs::JoyFeedback());
        feedback->type = sensor_msgs::JoyFeedback::TYPE_LED;
        feedback->id = id;
        feedback->intensity = intensity;
        return feedback;
    }

    /* id is 0-1 */
    sensor_msgs::JoyFeedbackPtr getFeedbackRumble(ID id, INTENSITY intensity) {
        sensor_msgs::JoyFeedbackPtr feedback(new sensor_msgs::JoyFeedback());
        feedback->type = sensor_msgs::JoyFeedback::TYPE_RUMBLE;
        feedback->id = id;
        feedback->intensity = intensity;
        return feedback;
    }

};

#endif /* TELEOPPS3FEEDBACK_H */

