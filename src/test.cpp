#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/UInt8MultiArray.h"
#include "json.hpp"
#include "mrobot_srvs/JString.h"
#include "mrobot_srvs/KVPair.h"

using json = nlohmann::json;
void callback(const std_msgs::String::ConstPtr msg)
{
    //ROS_INFO("test_node_callback");
    auto j = json::parse(msg->data.c_str());
    if(j.find("sub_name") != j.end())
    {
        //ROS_INFO("find sub_name");
        if(j["sub_name"] == "get_version")
        {
           // ROS_INFO("find get_version");
            //if(j["data"]["dev_name"] == "_24v_printer")
            if(j["data"].find("hw_version") != j["data"].end())
            {
                ROS_INFO("find hw_version");
            }
            {
                if(j["data"]["set_dev"] == true)
                {

                }
                else if(j["data"]["set_dev"] == false)
                {

                }

            }
        }
        if(j["sub_name"] == "get_adc_data")
        {
            if(j["data"].find("_12v_voltage") != j["data"].end())
            {
                //ROS_INFO("_12v_voltage:%d",j["data"]["_12v_voltage"]);
            }
        }
    }
    if(j.find("sub_name") != j.end())
    {
        if(j["sub_name"] == "set_module_state")
        {
            //ROS_INFO("find get_module_state");

            if(j["data"]["door_ctrl_state"] == true)
            {
             //   ROS_INFO("door_ctrl_state is on");
            }
            if(j["data"]["door_ctrl_state"] == false)
            {
              //  ROS_INFO("door_ctrl_state is off");
            }
        }
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv,"test_node");
    ros::NodeHandle n;
    ros::Publisher test_pub = n.advertise<std_msgs::String>("rx_noah_powerboard_node",1000);
    ros::Publisher conveyor_test_pub = n.advertise<std_msgs::String>("conveyor_ctrl",1000);
    ros::Publisher conveyor_lock_test_pub = n.advertise<std_msgs::String>("conveyor_lock_ctrl",1000);
    ros::Publisher test_navigation_pub = n.advertise<std_msgs::String>("lane_follower_node/camera_using_n",1000);
    ros::Subscriber test_sub = n.subscribe("tx_noah_powerboard_node", 1000, &callback);
    ros::Publisher test_power_pub = n.advertise<std_msgs::UInt8MultiArray>("app_pub_power",1000);
    ros::Publisher starline_test_pub = n.advertise<std_msgs::String>("map_server_mrobot/region_params_changer/sensor_params",1000);
    ros::Publisher sensor_to_starline_pub = n.advertise<std_msgs::UInt8MultiArray>("sensor_to_starline_node",1000);
    ros::Publisher serials_leds_turnning_pub = n.advertise<std_msgs::UInt8MultiArray>("serials_leds_turnning_ctrl",1000);
    ros::Publisher basestate_pub = n.advertise<std_msgs::UInt8MultiArray>("basestate",1000);
    //ros::Publisher basestate_pub_2 = n.advertise<std_msgs::String>("basestate",1000);
    ros::Publisher remote_power_ctrl_pub = n.advertise<std_msgs::UInt8MultiArray>("remote_power_ctrl",1000);
    ros::Publisher test_agent_pub = n.advertise<std_msgs::String>("agent_pub",1000);
    ros::Publisher test_leds_ctrl_pub = n.advertise<std_msgs::String>("led_ctrl", 10);

    ros::ServiceClient service_client = n.serviceClient<mrobot_srvs::JString>("smartlock/update_super_admin");
    ros::ServiceClient unlock_service_client = n.serviceClient<mrobot_srvs::JString>("smartlock/unlock");
    ros::ServiceClient factory_settings_service_client = n.serviceClient<mrobot_srvs::KVPair>("factory_settings/set_param");
    ros::ServiceClient led_ctrl_service_client = n.serviceClient<mrobot_srvs::JString>("led_ctrl");
    ros::ServiceClient conveyor_rfid_info_service_client = n.serviceClient<mrobot_srvs::JString>("/conveyor/rfid_info");
    mrobot_srvs::JString srv;
    mrobot_srvs::KVPair factory_settings_srv;
    //srv.request.request = "\{ \'super_pwd\': \'1111\' \}";
    srv.request.request =  "{\"data\":\"{\\\"pub_name\\\":\\\"binding_credit_card_employees\\\"}\"}";
    ros::Rate loop_rate(0.3);
    json j;
    static uint32_t cnt = 0;
    static uint8_t flag = 0;
    uint32_t sonar_en = 0x12345678;
    uint32_t laser_en = 0x87654321;
    sleep(1);
    while(ros::ok())
    {
        {
            bool state;

            std_msgs::String pub_json_msg;
            std::stringstream ss;
            state = cnt % 3 == 0 ? true:false;
            cnt++;
            if(flag == 0)
            {

               // flag = 1;
#if 0
                {

    #if 0
                j.clear();
                j =
                {
                    {"pub_name","status_led_ctrl"},
                    {
                        "data",
                        {
                            {"wifi","ok"},
                            {"trans", "warn"},
                            {"battery", "err"},
                        }
                    },
                };
    #else
                j = 
                {
                    {"pub_name","serial_leds_ctrl"},
                    {
                        "data",
                        {
                            {"period", 50},
                            {"color", 
                                {
                                   {"r", 0},
                                   {"g", 15},
                                   {"b", 0},
                                }
                            },
                        }
                    },
                };
    #endif
                    std_msgs::String pub_json_msg;
                    std::stringstream ss;
                    ss.clear();
                    ss << j;
                    pub_json_msg.data.clear();
                    pub_json_msg.data = ss.str();
                    srv.request.request = pub_json_msg.data;
                    led_ctrl_service_client.call(srv);
                    ROS_INFO("led ctrl call ");
                }
#endif



#if 0
                {
    #if 0
                j = 
                {
                    {"pub_name","write_info"},
                    {
                        "data",
                        {
                            {"dst_id", 0x1234},
                            {"src_id", 0x5678},
                            {"time", 
                                {
                                   {"hour", 17},
                                   {"minute", 32},
                                }
                            },
                        }
                    },
                };
    #else

                j = 
                {
                    {"pub_name","get_id"},
                };

    #endif
                    std_msgs::String pub_json_msg;
                    std::stringstream ss;
                    ss.clear();
                    ss << j;
                    pub_json_msg.data.clear();
                    pub_json_msg.data = ss.str();
                    srv.request.request = pub_json_msg.data;
                    conveyor_rfid_info_service_client.call(srv);
                    ROS_INFO("get conveyor rfid id call returned:  srv.response.response: %s", srv.response.response.c_str());
                    //ROS_WARN("factory_settings_srv returned,  success: %d,  value  :%s ", factory_settings_srv.response.success, factory_settings_srv.response.value.c_str());
                }
#endif


#if 0
                {

                    j.clear();
                    j =
                    {
                        {"lock_index", 0x0f},
                    };
                    std_msgs::String pub_json_msg;
                    std::stringstream ss;
                    ss.clear();
                    ss << j;
                    pub_json_msg.data.clear();
                    pub_json_msg.data = ss.str();
                    srv.request.request = pub_json_msg.data;
                    unlock_service_client.call(srv);
                    ROS_INFO("unlock call");
                }
#endif


#if 0
                {

                    j.clear();
                    j =
                    {
                        {"lock_index", 0x07},
                    };
                    std_msgs::String pub_json_msg;
                    std::stringstream ss;
                    ss.clear();
                    ss << j;
                    pub_json_msg.data.clear();
                    pub_json_msg.data = ss.str();
                    srv.request.request = pub_json_msg.data;
                    unlock_service_client.call(srv);
                    ROS_INFO("unlock call");
                }
#endif


#if 0

                j.clear();
                j =
                {
                    {"super_rfid","1007"},
                    {"super_pwd", "1234"},
                };
                std_msgs::String pub_json_msg_5;
                std::stringstream ss_5;
                ss_5.clear();
                ss_5 << j;
                pub_json_msg_5.data.clear();
                pub_json_msg_5.data = ss_5.str();
                srv.request.request = pub_json_msg_5.data;
                service_client.call(srv);
				ROS_INFO("call service returned");
#endif

#if 0

                j.clear();
                j =
                {
                    {"lock_num", 9},
                    {"audio-channel-test", "x86"},
                };
                std_msgs::String pub_json_msg_5;
                std::stringstream ss_5;
                ss_5.clear();
                ss_5 << j;
                pub_json_msg_5.data.clear();
                pub_json_msg_5.data = ss_5.str();
                //srv.request.request = pub_json_msg_5.data;
                factory_settings_srv.request.key = "conveyor_lock";
                factory_settings_srv.request.value = "false";
                //ROS_INFO("%s", pub_json_msg_5.data);
                //factory_settings_service_client.call(srv);
                ROS_INFO("factory_settings_srv requied,  key: %s,  value  :%s ", factory_settings_srv.request.key.c_str(), factory_settings_srv.request.value.c_str());
                factory_settings_service_client.call(factory_settings_srv);
                ROS_WARN("factory_settings_srv returned,  success: %d,  value  :%s ", factory_settings_srv.response.success, factory_settings_srv.response.value.c_str());
#endif


#if 0

                std_msgs::String led;
                #if 0
                if(cnt % 4 == 0)
                {
                    led.data = "00";
                    ROS_INFO("set camera led : 00");
                }
                if(cnt % 4 == 1)
                {
                    //led.data = "01";
                    ROS_INFO("set camera led : 01");
                }
                if(cnt % 4 == 2)
                {
                    led.data = "10";
                    ROS_INFO("set camera led : 10");
                }
                if(cnt % 4 == 3)
                {
                    led.data = "11";
                    ROS_INFO("set camera led : 11");
                }
                #endif
                if(cnt % 2 == 1)
                {
                    led.data = "101";
                }
                if(cnt % 2 == 0)
                {
                    led.data = "100";
                }
                test_navigation_pub.publish(led);
                ROS_INFO("led: %s", led.data.data());

#endif
#if 0

            {

                std_msgs::UInt8MultiArray array;
                for(uint8_t i = 0; i < 13 + 10; i++)
                {
                    if(i < 10)
                    {
                        array.data.push_back(i);
                    }
                    else
                    {
                        array.data.push_back(i*2);
                    }
                }
                sensor_to_starline_pub.publish(array);
            }

#endif
#if 0

            {

                std_msgs::UInt8MultiArray array;
                static uint8_t cnt = 0;
                cnt++;
                array.data.push_back(cnt % 3);
                serials_leds_turnning_pub.publish(array);
                ROS_INFO("set serials leds turnning: %d",cnt % 3);
            }

#endif

#if 0

            {

                std_msgs::UInt8MultiArray array;
                static uint8_t cnt = 0;
                cnt++;
                array.data.push_back(0);
                array.data.push_back(0);
                if(cnt % 15 == 0)
                {
                    array.data.push_back(1<<4);
                }
                else if(cnt % 15 == 7)
                {
                    array.data.push_back(0);
                }
                basestate_pub.publish(array);
                ROS_WARN("base status test pub");
                //ROS_INFO("set serials leds turnning: %d",cnt % 3);
            }

#endif

#if 0
                std_msgs::String array_2;
                array_2.data = "123456";
                basestate_pub_2.publish(array_2);
                ROS_WARN("base status test pub 2");
#endif

#if 0

            {

                std_msgs::UInt8MultiArray array;
                static uint8_t cnt = 0;
                //cnt++;
                cnt = 2;
                array.data.push_back(cnt);
                remote_power_ctrl_pub.publish(array);
                ROS_INFO("set remote power ctrl: %d",cnt);
            }

#endif

#if 0
                std_msgs::UInt8MultiArray test_power;
                test_power.data.push_back(0);
                test_power_pub.publish(test_power);
                ROS_INFO("power request");
#endif

#if 0
                static int door_id = 0;
                if(door_id < 4)
                {
                    door_id++;
                }
                else
                {
                    door_id = 1;
                }

                j.clear();
                j =
                {
                    {"pub_name","set_module_state"},
                    {
                        "data",
                        {
                            {"dev_name","door_ctrl_state"},
                            {"set_state",(bool)state},
                            {"door_id",door_id},
                            //{"door_id",NULL},
                        }
                    },
                };
                std_msgs::String pub_json_msg_5;
                std::stringstream ss_5;
                ss_5.clear();
                ss_5 << j;
                pub_json_msg_5.data.clear();
                pub_json_msg_5.data = ss_5.str();
                test_pub.publish(pub_json_msg_5);
                //ROS_INFO("set door ctrl %d",state);
                ROS_INFO("set door %d ctrl %d",door_id,state);
                //usleep(500*1000);
#endif


#if 1
                j.clear();
                j =
                {
                    {"pub_name","conveyor_ctrl"},
                    {
                        "data",
                        {
                            {"set_mode","load"},
                            {"lock", true},
                        }
                    },
                };
                std_msgs::String pub_json_msg_8;
                std::stringstream ss_8;
                ss_8.clear();
                ss_8 << j;
                pub_json_msg_8.data.clear();
                pub_json_msg_8.data = ss_8.str();
                conveyor_test_pub.publish(pub_json_msg_8);
                ROS_WARN("start conveyor control . . .");
#endif


#if 0
    #if 0
                j.clear();
                j =
                {
                    {"pub_name","status_led_ctrl"},
                    {
                        "data",
                        {
                            {"wifi","ok"},
                            {"trans", "err"},
                            {"battery", "warn"},
                        }
                    },
                };
    #else
                j = 
                {
                    {"pub_name","serial_leds_ctrl"},
                    {
                        "data",
                        {
                            {"period", 50},
                            {"color", 
                                {
                                   {"r", 0},
                                   {"g", 15},
                                   {"b", 0},
                                }
                            },
                            {"trans", "err"},
                        }
                    },
                };
    #endif
                std_msgs::String pub_json_msg_10;
                std::stringstream ss_10;
                ss_10.clear();
                ss_10 << j;
                pub_json_msg_10.data.clear();
                pub_json_msg_10.data = ss_10.str();
                test_leds_ctrl_pub.publish(pub_json_msg_10);
                ROS_WARN("start status leds control . . .");
#endif

#if 0
                j.clear();
                j =
                {
                    {"pub_name","conveyor_lock_ctrl"},
                    {
                        "data",
                        {
                            {"lock_ctrl","lock"},
                        }
                    },
                };
                std_msgs::String pub_json_msg_9;
                std::stringstream ss_9;
                ss_9.clear();
                ss_9 << j;
                pub_json_msg_9.data.clear();
                pub_json_msg_9.data = ss_9.str();
                conveyor_lock_test_pub.publish(pub_json_msg_9);
                ROS_WARN("start conveyor lock control . . .");
#endif


#if 0
                std::vector<int> worker_id_vec;

                int uuid_random = random();
                std::string uuid_str = std::to_string(uuid_random);
                j.clear();
                j =
                {
                    {"uuid",uuid_str.data()},
                    {"pub_name","binding_credit_card_employees"},
                    {
                        "data",
                        {
                            /*
                            {"0",{1,2,3,4,5,6,7,8}},
                            {"1",{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32}},
                            {"2",{5,6,7,8,10,12,14}},
                            {"3",{2,9,10,11,12,13}},
                            {"31",{8,4,17,11,13,18}},
                            {"32",{2,9,10,11,12,13}},
                            {"33",{1,3,90,41,52,33}},
                            */
                            {"2",{97,678}},
                        }
                    },
                };
                std_msgs::String pub_json_msg_7;
                std::stringstream ss_7;
                ss_7.clear();
                ss_7 << j;
                pub_json_msg_7.data.clear();
                pub_json_msg_7.data = ss_7.str();
                test_agent_pub.publish(pub_json_msg_7);
                ROS_INFO("test agent pub ...");
                /*
                j.clear();
                j =
                {
                    {"pub_name","container_super_password"},
                    {"uuid",uuid_str.data()},
                    {
                        "data",
                        {
                            {"password",{{"boxNum", 1},{"password","3322"}}},

                        }
                    },
                };
                std_msgs::String pub_json_msg_6;
                std::stringstream ss_6;
                ss_6.clear();
                ss_6 << j;
                pub_json_msg_6.data.clear();
                pub_json_msg_6.data = ss_6.str();
                test_agent_pub.publish(pub_json_msg_6);
                 */
#endif


#if 0
                j.clear();
                j =
                {
                    {
                        "params",
                        {
                            {"enable_supersonic",(uint32_t)sonar_en},
                            {"enable_microlaser",(uint32_t)laser_en},
                        }
                    },
                };
                std_msgs::String pub_json_msg_6;
                std::stringstream ss_6;
                ss_6.clear();
                ss_6 << j;
                pub_json_msg_6.data.clear();
                pub_json_msg_6.data = ss_6.str();
                starline_test_pub.publish(pub_json_msg_6);
#endif




#if 0
                j.clear();
                j =
                {
                    {"pub_name","set_module_state"},
                    {
                        "data",
                        {
                            {"dev_name","_24v_printer"},
                            {"set_state",(bool)state},
                        }
                    },
                };
                ss.clear();
                ss << j;
                pub_json_msg.data.clear();
                pub_json_msg.data = ss.str();
                test_pub.publish(pub_json_msg);
                ROS_INFO("set 24v printer: %d",state);
#endif


#if 0
                j.clear();
                j =
                {
                    {"pub_name","set_module_state"},
                    {
                        "data",
                        {
                            {"dev_name","_24v_dcdc"},
                            {"set_state",(bool)state},
                        }
                    },
                };
                std_msgs::String pub_json_msg_2;
                std::stringstream ss_2;
                ss_2.clear();
                ss_2 << j;
                pub_json_msg_2.data.clear();
                pub_json_msg_2.data = ss_2.str();
                test_pub.publish(pub_json_msg_2);
                usleep(500*1000);
#endif


#if 0
                j.clear();
                j =
                {
                    {"pub_name","set_module_state"},
                    {
                        "data",
                        {
                            {"dev_name","_5v_dcdc"},
                            {"set_state",(bool)state},
                        }
                    },
                };
                std_msgs::String pub_json_msg_4;
                std::stringstream ss_4;
                ss_4.clear();
                ss_4 << j;
                pub_json_msg_4.data.clear();
                pub_json_msg_4.data = ss_4.str();
                test_pub.publish(pub_json_msg_4);
                ROS_INFO("set 5v dcdc: %d",state);
                //usleep(500*1000);
#endif

#if 0
                j.clear();
                j =
                {
                    {"pub_name","set_module_state"},
                    {
                        "data",
                        {
                            {"dev_name","_12v_dcdc"},
                            {"set_state",(bool)state},
                        }
                    },
                };
                std_msgs::String pub_json_msg_3;
                std::stringstream ss_3;
                ss_3.clear();
                ss_3 << j;
                pub_json_msg_3.data.clear();
                pub_json_msg_3.data = ss_3.str();
                test_pub.publish(pub_json_msg_3);
                ROS_INFO("set 12v dcdc: %d",state);
                //usleep(500*1000);
#endif
            }

        }

        ros::spinOnce();
        loop_rate.sleep();
    }
}
