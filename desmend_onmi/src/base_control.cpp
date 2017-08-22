#include "ros/ros.h"    //添加ros核心的头文件
#include "geometry_msgs/Twist.h"      //包含geometry_msgs::Twist消息头文件
#include <stdlib.h>
#include "desmend_onmi/vel.h" 
#include <dynamic_reconfigure/server.h>
#include <desmend_onmi/dynamic_turtleConfig.h>


class SubscribeAndPublish  
{  
public:  
  SubscribeAndPublish()  
  {  
    pub_ = n_.advertise<desmend_onmi::vel>("base_vel", 1);  
  
    sub_speed = n_.subscribe("turtle1/cmd_vel", 1, &SubscribeAndPublish::callback, this);  
  }  
  
  void callback(const geometry_msgs::Twist& msg)  
  {  
    ROS_INFO_STREAM(std::setprecision(2) << std::fixed << "velocity=("<< msg.linear.x <<","<< msg.linear.y <<")" <<" *direction="<<msg.angular.z);  
    desmend_onmi::vel speed;
    speed.A_Wheel=2*msg.linear.x+msg.angular.z;
    speed.B_Wheel=-msg.linear.x+msg.angular.z;
    speed.C_Wheel=-msg.linear.x+msg.angular.z;
    pub_.publish(speed);  
  }  
  
private:  
  ros::NodeHandle n_;   
  ros::Publisher pub_;  
  ros::Subscriber sub_speed;  
  
};




















geometry_msgs::Twist T;
void ConfigCb(desmend_onmi::dynamic_turtleConfig &config, uint32_t level)
{
	T.linear.x = config.speed;
	T.angular.z = T.linear.x / 2.0;
}




  
int main(int argc, char **argv)  
{  
  ros::init(argc, argv, "base_control");    
 
  //SubscribeAndPublish SAPObject;  











  ros::NodeHandle nh;

  dynamic_reconfigure::Server<desmend_onmi::dynamic_turtleConfig> server;
  dynamic_reconfigure::Server<desmend_onmi::dynamic_turtleConfig>::CallbackType f;

  f = boost::bind(&ConfigCb, _1, _2);
  server.setCallback(f);

  if(!nh.getParam("/speed", T.linear.x))
	{
		ROS_ERROR("Get Speed ERROR");
		return 0;
	}
  T.angular.z = T.linear.x / 2.0;
  ros::Publisher twist_pb = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 100);












  ros::Rate loop_rate(1);
  while(ros::ok())
 {





  twist_pb.publish(T);






  ros::spinOnce();  
  loop_rate.sleep();

 }
  return 0;  

} 


























