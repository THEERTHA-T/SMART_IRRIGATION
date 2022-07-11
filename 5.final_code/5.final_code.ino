#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

//********declare values***********

const int soil_moisture_pin = 34;
int soil_moisture_value = 0;
boolean flag = 0;

const int pin_1 = 2;
const int pin_2 = 4;

//********set wifi id and password***********

const char* wifi_id = "theertha";
const char * wifi_pswd = "theertha@123";

//*************telegram alert**************
// Telegram BOT Token (Get from Botfather)

#define BOT_TOKEN "5512723480:AAGJ_VMBJLgoZeJUrpHq-O5VGEpBm_EZEaE"

// Use @myidbot (IDBot) to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
//#define CHAT_ID "175753388"

#define CHAT_ID_Tele "1155740171"
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

AsyncWebServer server(80);
long previousMillisTelegram = 0;


void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i = 0; i < numNewMessages; i++)  {
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    if (text == "/start")
    {
      String reply = "Telegram Get Chat ID: " + chat_id + "\n";
      reply += "/getid - Chat ID\n";
      reply += "/location - Get Current Location\n";
      reply += "/reset - Reset Distance to 9\n";
      bot.sendMessage(chat_id, reply);
    }
    if (text == "/getid") {
      String reply = "Your Chat ID: " + chat_id + "\n";
      bot.sendMessage(chat_id, reply);
    }
    if (text == "/location") {
      String reply = "Location\n";
      reply += "Latitude: 1.12345\n";
      reply += "Longitude: 124.122315\n";
      bot.sendMessage(chat_id, reply);
    }
    if (text == "/reset") {
      String reply = "Resetting\n";
      bot.sendMessage(chat_id, reply);
    }
  }
}

void buttonPressed()
{
  Serial.println("TELEGRAM MESSAGE SENDING\n");
  String reply = "ALERT ---->> NEED WATER\n";
  bot.sendMessage(CHAT_ID_Tele, reply);
  Serial.println("TELEGRAM MESSAGE SENT\n");
}

void motor_on()
{
  Serial.println("NEED WATER");
  digitalWrite(pin_1, HIGH); //function..first parameter is pin number
  digitalWrite(pin_2, LOW);
  delay(1000);
  flag = 1; // no alert message there after
}

void motor_off()
{
  digitalWrite(pin_1, LOW);
  digitalWrite(pin_2, LOW);
  delay(1000);
  //flag = 0;
}

String processor(const String& var) {
  if (var == "BUTTONPLACEHOLDER") {
    float value_1 = float(soil_moisture_value);
    float value_2 = float(value_1 / 4200);
    float value_3 = float(value_2 * 100);
    String buttons = String(value_3); //convert value to percentage
    return buttons;
  }
  return String();
}

const char index_html[] PROGMEM = R"rawliteral(
%BUTTONPLACEHOLDER%
)rawliteral";


void loop() 
{
  // put your main code here, to run repeatedly:
    if (millis() - previousMillisTelegram >= 1000) {
    previousMillisTelegram = millis();
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages) 
    {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    if(soil_moisture_value>3500)
    {
      if(flag==0)
      {
        buttonPressed(); 
      }
    }

  soil_moisture_value=analogRead(soil_moisture_pin);
  Serial.print("Soil Moisture Value = ");
  Serial.println(soil_moisture_value);
  if(soil_moisture_value<3500)
  {
    //digitalWrite(pin_1,LOW);
    Serial.println("ENOUGH WATER");
    digitalWrite(pin_1,LOW);
    digitalWrite(pin_2,LOW);
  }
    delay(2000);
}
}


void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  //********wifi connection code***********
  
  WiFi.begin(wifi_id,wifi_pswd);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(1000);
    Serial.println("WIFI CONNECTING..!!");
  }
    soil_moisture_value=analogRead(soil_moisture_pin);
    Serial.print("\nIP address:");
    Serial.println(WiFi.localIP());
    Serial.println("WIFI CONNECTED..!!");
    pinMode(pin_1,OUTPUT);
    pinMode(pin_2,OUTPUT);
    Serial.print("Retrieving time: ");
    configTime(0, 0, "pool.ntp.org"); // get UTC time via NTP
    time_t now = time(nullptr);
    while (now < 24 * 3600)
    {
      Serial.print(".");
      delay(100);
      now = time(nullptr);
    }
    Serial.println(now);
    bot.sendMessage(CHAT_ID_Tele, "Smart Mate Device Started", "");
    
    server.on("/",HTTP_GET,[](AsyncWebServerRequest *request)
    {
      request->send_P(200,"text/html",index_html,processor);
    });

    server.on("/load_motor",HTTP_GET,[](AsyncWebServerRequest *request)
    {
      Serial.println("MOTOR LOAD..!!");
      request->send_P(200,"text/html",index_html,processor);
    });
    
    server.on("/on_motor",HTTP_GET,[](AsyncWebServerRequest *request)
    {
      Serial.println("MOTOR ON..!!");
      motor_on();
    });

    server.on("/off_motor",HTTP_GET,[](AsyncWebServerRequest *request)
    {
      Serial.println("MOTOR OFF..!!");
      motor_off();
    });
    server.begin();
}
