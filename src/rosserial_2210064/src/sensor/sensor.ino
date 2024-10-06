#include <ros.h>
#include <std_msgs/Float32MultiArray.h>

#define TRIG 2
#define ECHO 4
#define SIGNAL 5

ros::NodeHandle nh;
std_msgs::Float32MultiArray sensor_data;

float collectSignal(){
  int signal = analogRead(SIGNAL);
  return map(signal, 0, 1023, 0, 1000) / 1000;
}

float collectEcho(){
  digitalWrite(TRIG, LOW);
  delay(20);
  digitalWrite(TRIG, HIGH);
  delay(40);
  digitalWrite(TRIG, LOW);
  int duration = pulseIn(ECHO, HIGH);

  float distance = duration*0.034 / 2;

  return distance;

}

ros::Publisher pub("/sensor_data", &sensor_data);

void setup() {
  // put your setup code here, to run once:
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(SIGNAL, INPUT);

  nh.initNode();
  nh.advertise(pub);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensor_data.data_length = 2;
  sensor_data.data[0] = collectSignal();
  sensor_data.data[1] = collectEcho();
  pub.publish(&sensor_data);
  nh.spinOnce();
  delay(100);
}
