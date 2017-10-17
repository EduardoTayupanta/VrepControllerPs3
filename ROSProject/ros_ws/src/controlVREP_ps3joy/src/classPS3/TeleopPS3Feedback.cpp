/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TeleopPS3Feedback.cpp
 * Author: wetayupanta
 * 
 * Created on October 12, 2017, 12:00 PM
 */

#include "TeleopPS3Feedback.h"

TeleopPS3Feedback::TeleopPS3Feedback() {
    feedback_pub_ = nh_.advertise<sensor_msgs::JoyFeedbackArray>("/joy/set_feedback", 1);

    smach_enabled_sub_ = nh_.subscribe("/enable_smach", 3, &TeleopPS3Feedback::smachEnabledCallback, this);

    sendLEDs(false, true, false, true);
    sendRumble(0, 0);

    // init led arrays
    for (int id = 0; id < 4; id++) {
        leds_status[id].id = id;
        leds_status[id].intensity = 0;
        leds_knight_rider[id].id = id;
        leds_knight_rider[id].intensity = 0;
    }

    boost::thread(&TeleopPS3Feedback::knightRiderThread, this);
}

TeleopPS3Feedback::TeleopPS3Feedback(const TeleopPS3Feedback& orig) {
}

TeleopPS3Feedback::~TeleopPS3Feedback() {
}

void TeleopPS3Feedback::smachEnabledCallback(const std_msgs::BoolConstPtr& smach_enabled_msg) {
    bool smach_enabled = smach_enabled_msg->data;
    leds_status[LED_INDEX_SMACH_DISABLED].intensity = !smach_enabled ? 1 : 0;
    updateLEDs(false);
}

void TeleopPS3Feedback::sendRumble(INTENSITY rumble_low_freq, INTENSITY rumble_high_freq) {
    sensor_msgs::JoyFeedbackArray feedback_array;
    feedback_array.array.push_back(*getFeedbackRumble(0, rumble_low_freq));
    feedback_array.array.push_back(*getFeedbackRumble(1, rumble_high_freq));
    feedback_pub_.publish(feedback_array);
}

void TeleopPS3Feedback::sendLEDs(bool led0, bool led1, bool led2, bool led3) {
    sensor_msgs::JoyFeedbackArray feedback_array;
    feedback_array.array.push_back(*getFeedbackLED(0, led0));
    feedback_array.array.push_back(*getFeedbackLED(1, led1));
    feedback_array.array.push_back(*getFeedbackLED(2, led2));
    feedback_array.array.push_back(*getFeedbackLED(3, led3));
    feedback_pub_.publish(feedback_array);
}

void TeleopPS3Feedback::sendLEDs(LED leds[4]) {
    sensor_msgs::JoyFeedbackArray feedback_array;
    for (int i = 0; i < 4; i++)
        feedback_array.array.push_back(*getFeedbackLED(leds[i].id, leds[i].intensity));
    feedback_pub_.publish(feedback_array);
}

void TeleopPS3Feedback::knightRiderThread() {
    ros::WallDuration step;
    step.fromSec(0.2);

    ID id = 0;
    ID inc = +1;
    LED *leds = leds_knight_rider;

    while (ros::ok()) {
        // at this point every leds[i] is off

        leds[id].intensity = 1;
        //			sendLEDs(leds);
        updateLEDs(true);
        leds[id].intensity = 0;

        // at this point every leds[i] is off

        if (id == 0)
            inc = +1;
        else if (id == 3)
            inc = -1;

        id += inc;

        step.sleep();
    }
}

void TeleopPS3Feedback::updateLEDs(bool knight_rider = false) {
    static boost::mutex method_mutex;
    method_mutex.lock();

    bool sent_knight_rider_last_time = false;

    if (sent_knight_rider_last_time && knight_rider) {
        sendLEDs(leds_knight_rider);
    } else if (!sent_knight_rider_last_time && !knight_rider) {
        // only forward status leds if statii are set

        // check status leds for active leds
        bool status_set = false;
        for (int id = 0; id < 4; id++) {
            if (leds_status[id].intensity != 0) {
                status_set = true;
                break;
            }
        }
        if (status_set) {
            sendLEDs(leds_status);
        }
    } else // if both are different
    {
        // only forward knight rider leds if statii are not set

        // check status leds for active leds
        bool status_set = false;
        for (int id = 0; id < 4; id++) {
            if (leds_status[id].intensity != 0) {
                status_set = true;
                break;
            }
        }

        if (status_set) {
            if (!knight_rider) {
                sendLEDs(leds_status);
                sendRumble(0, 0.5);
                sent_knight_rider_last_time = false;
            } else {
                // ignore knight rider updates when statii are set
            }
        } else // statii not set
        {
            sendLEDs(leds_knight_rider);
            sendRumble(0, 0);
            sent_knight_rider_last_time = true;
        }
    }

    method_mutex.unlock();
}