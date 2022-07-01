#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
//********declare values***********

const int soil_moisture_pin = 34;
int soil_moisture_value = 0;

const int pin_1 = 2;
const int pin_2 = 4;

//********set wifi id and password***********

const char* wifi_id = "theertha";
const char * wifi_pswd = "theertha@123";

AsyncWebServer server(80);

void motor_on()
{
  Serial.println("NEED WATER");
  digitalWrite(pin_1, HIGH); //function..first parameter is pin number
  digitalWrite(pin_2, LOW);
  delay(1000);
}

void motor_off()
{
  digitalWrite(pin_1, LOW);
  digitalWrite(pin_2, LOW);
  delay(1000);

}

const char index_html[] PROGMEM = R"rawliteral(
<html>
<body>
<h2>hello world</h2>
%BUTTONPLACEHOLDER%
</body>
</html>
)rawliteral";

String processor(const String& var){
  if(var=="BUTTONPLACEHOLDER"){
    String buttons="<h2>ok</h2>";
    return buttons;
  }
  return String();
}

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  //********wifi connection code***********
  
  WiFi.begin(wifi_id,wifi_pswd);
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(1000);
    Serial.println("WIFI CONNECTING..!!");
  }
  
  Serial.println(WiFi.localIP());
   Serial.println("WIFI CONNECTED..!!");
   pinMode(pin_1,OUTPUT);
  pinMode(pin_2,OUTPUT);
  
  server.on("/",HTTP_GET,[](AsyncWebServerRequest *request){
    request->send_P(200,"text/html",index_html,processor);
  });

   server.on("/on_motor",HTTP_GET,[](AsyncWebServerRequest *request){
          Serial.println("MOTOR ON..!!");
          motor_on();
    //request->send_P(200,"text/html",index_html,processor);
  });

   server.on("/off_motor",HTTP_GET,[](AsyncWebServerRequest *request){
          Serial.println("MOTOR OFF..!!");
          motor_off();
    //request->send_P(200,"text/html",index_html,processor);
  });
  
  
  server.begin();
}

void loop() 
{
  // put your main code here, to run repeatedly:
  
  soil_moisture_value=analogRead(soil_moisture_pin);
  Serial.println(soil_moisture_value);
  if(soil_moisture_value<3500)
  {
    //digitalWrite(pin_1,LOW);
    Serial.println("ENOUGH WATER");
    digitalWrite(pin_1,LOW);
    digitalWrite(pin_2,LOW);
     //delay(5000);
     
 }
  //else
  //{
   // digitalWrite(pin_1,HIGH);
    //Serial.println("NEED WATER");
    //digitalWrite(pin_1,HIGH); //function..first parameter is pin number
  //digitalWrite(pin_2,LOW);
  //delay(5000); 
  //}

  delay(2000);
}
