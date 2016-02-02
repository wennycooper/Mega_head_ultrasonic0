#include <ros.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/Float32.h>
#include <Ultrasonic.h>

#define TRIG_PIN  30
#define ECHO_PIN  31


std_msgs::Float32 _dist;
ros::Publisher pub_dist("/andbot/LidarLite/Distance", &_dist);

ros::NodeHandle nh;

float ping() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  return (float) pulseIn(ECHO_PIN, HIGH, 23529)/58;
}

void setup() {
  // put your setup code here, to run once:
  nh.initNode();
  nh.advertise(pub_dist);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  float cm = ping();
 
//  Serial.print("MS: ");
//  Serial.print(microsec);
//  Serial.print(", CM: ");
//  Serial.println(cmMsec);
//  Serial.print(", IN: ");
//  Serial.println(inMsec);


  _dist.data = cm;

  
  pub_dist.publish(&_dist);
  nh.spinOnce();
  delay(100);

}
