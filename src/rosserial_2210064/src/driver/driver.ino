#include<ros.h>
#include<geometry_msgs/Twist.h>

#define IN1 2
#define IN2 3
#define ENA 4
#define IN3 5
#define IN4 6
#define ENB 7

ros::NodeHandle nh;
geometry_msgs::Twist cmd_vel;

void driv_motor(int pin1, int pin2, int speed_pin, float speed) {
  int motor = speed*255;
  digitalWrite(speed_pin, motor);
  if(motor > 0){
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
  }
  else if(motor < 0){
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
  }
  else {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
  }
}


void cmd_vel_cb(const geometry_msgs::Twist& msg){
  float linear_speed = msg.linear.x;
  driv_motor(IN1, IN2, ENA, linear_speed);

  float angular_speed = msg.angular.z;
  driv_motor(IN3, IN4, ENB, angular_speed);
}

ros::Subscriber<geometry_msgs::Twist> sub("/cmd_vel", &cmd_vel_cb);


void setup(){
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  nh.spinOnce();
  delay(100);
}