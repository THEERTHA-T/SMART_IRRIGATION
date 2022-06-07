#include <WiFi.h>
const int soil_moisture_pin=34;
int soil_moisture_value=0;

const int pin_1=2;
const int pin_2=4;

const char* wifi_id="theertha";
const char * wifi_pswd="theertha123";

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  //wifi code
  WiFi.begin(wifi_id,wifi_pswd);
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(1000);
    Serial.println("WIFI CONNECTING..!!");
  }
  Serial.println(WiFi.localIP());
   pinMode(pin_1,OUTPUT);
  pinMode(pin_2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  soil_moisture_value=analogRead(soil_moisture_pin);
  Serial.println(soil_moisture_value);
  if(soil_moisture_value<3500)
  {
    //digitalWrite(pin_1,LOW);
    Serial.println("ENOUGH WATER");
    digitalWrite(pin_1,LOW);
   digitalWrite(pin_2,LOW);
     delay(5000);
     
  }
  else
  {
   // digitalWrite(pin_1,HIGH);
    Serial.println("NEED WATER");
    digitalWrite(pin_1,HIGH); //function..first parameter is pin number
  digitalWrite(pin_2,LOW);
  delay(5000);
    
  }
  
}
