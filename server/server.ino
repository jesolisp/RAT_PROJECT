#include <WiFi.h>
#include <WebServer.h>

/* Put your SSID & Password */
const char* ssid = "ESP32_SSID";  // Enter SSID here
const char* password = "12345678";  //Enter Password here

/* Put IP Address details */
IPAddress local_ip(192,168,1,10);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

/* Set up the server object */
WebServer server(80);

/* Keep track of the sensor data sent by the client */
float gx = 0;
float gy = 0;
float gz = 0;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  delay(1000);

  /* Configure the server's routes */
  /*server.on("/",handleIndex);
  server.on("/update",handleUpdate);*/
  server.on("/readGX", handle_gX);
  server.on("/readGY", handle_gY);
  server.on("/readGZ", handle_gZ);
  server.on("/readGXYZ", handleAll);
  
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void handle_gX(){
  gx = server.arg("value").toFloat();
  server.send(200,"text/plain",String(gx));
}

void handle_gY(){
  gy = server.arg("value").toFloat();
  server.send(200,"text/plain",String(gy));
}

void handle_gZ(){
  gz = server.arg("value").toFloat();
  server.send(200,"text/plain",String(gz));
}

void handleAll() {
  String gxyz = String(gx) + " ; " + String(gy) + " ; " + String(gz);
  Serial.println(gxyz);
  server.send(200, "text/plain", gxyz); //Send ADC values only to client ajax request
}

/*
void handleIndex(){
  server.send(200,"text/plain",String(sensor_value));
}

void handleUpdate(){
  sensor_value = server.arg("value").toFloat();
  Serial.println(sensor_value);
  server.send(200,"text/plain","Updated");
}*/
