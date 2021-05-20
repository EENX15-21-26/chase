#define MAX_PUBLISHERS 5
#define MAX_SUBSCRIBERS 5
#define IN_BUFFER_SIZE 100
#define OUT_BUFFER_SIZE 100

ros::NodeHandle_<ArduinoHardware, MAX_PUBLISHERS, MAX_SUBSCRIBERS, IN_BUFFER_SIZE, OUT_BUFFER_SIZE> nh;

void piCallback(const chase_msgs::ChaseArduino& msg) {
  setMode(msg.mode, msg.params);
}

ros::Subscriber<chase_msgs::ChaseArduino> sub("arduinoMsgs", &piCallback);

void initPiListener() {
  nh.initNode();
  nh.subscribe(sub);
}

void spin(){
  nh.spinOnce();
}


// Logging

void logInfo(float value){
  logInfo(String(value));
}
void logInfo(int value){
  logInfo(String(value));
}
void logInfo(long value){
  logInfo(String(value));
}
void logInfo(String msg){
  logInfo(msg.c_str());
}
void logInfo(const char* msg){
  nh.loginfo(msg);
}
/*void logInfo(const char* msg){
  Serial.println(msg);
}*/
