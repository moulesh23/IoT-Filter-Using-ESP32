#include <HTTPClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>

const int inp=34;
const int val=0;
 
void setup() 
{
 
  Serial.begin(115200);                            //Serial connection
  WiFi.begin("SSID", "9642073373");   //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) 
  {  //Wait for the WiFI connection completion
 
    delay(500);
    Serial.println("Waiting for connection");
 
  }
 
}
 
void loop() 
{

  val = analogRead(inp);
  op=map(val,350,4095,1,100);
 
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    const int capacity = JSON_OBJECT_SIZE(1);
    StaticJsonBuffer<capacity> jb;

    JsonObject& obj = jb.createObject();
    obj["hardness"] = op;

    HTTPClient http;    //Declare object of class HTTPClient
 
    http.begin("http://122.166.154.2:8200/addhardness");      //Specify request destination
    http.addHeader("Content-Type", "application/json");  //Specify content-type header

    char JSONmessageBuffer[300];
    obj.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    Serial.println(JSONmessageBuffer);
 
    int httpCode = http.POST(JSONmessageBuffer);   //Send the request
    //Serial.println(obj);
    String payload = http.getString();                                        //Get the response payload
 
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
 
    http.end();  //Close connection
 
  } else {
 
    Serial.println("Error in WiFi connection");
 
  }
 
  delay(10000);  //Send a request every 30 seconds
 
}
