/*******************************************************************
    A telegram bot that sends you a message when ESP
    starts up

    Parts:
    ESP32 D1 Mini stlye Dev board* - http://s.click.aliexpress.com/e/C6ds4my
    (or any ESP32 board)

      = Affilate

    If you find what I do useful and would like to support me,
    please consider becoming a sponsor on Github
    https://github.com/sponsors/witnessmenow/


    Written by Brian Lough
    YouTube: https://www.youtube.com/brianlough
    Tindie: https://www.tindie.com/stores/brianlough/
    Twitter: https://twitter.com/witnessmenow
 *******************************************************************/

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// Wifi network station credentials
#define WIFI_SSID "theertha"
#define WIFI_PASSWORD "theertha@123"

// Telegram BOT Token (Get from Botfather)
#define BOT_TOKEN "5512723480:AAGJ_VMBJLgoZeJUrpHq-O5VGEpBm_EZEaE"

// Use @myidbot (IDBot) to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
//#define CHAT_ID "175753388"
#define CHAT_ID_Tele "1155740171"
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

int distance = 9;
void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i = 0; i < numNewMessages; i++)  {
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    if (text == "/start")    {
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
      String reply = "Distance Set to 9\n";
      distance = 9;
      bot.sendMessage(chat_id, reply);
    }

  }
}
void buttonPressed() {
  if (distance < 10) {
    Serial.println("Telegram Message Sending");
    String reply = "I am in need of Help\n";
    //reply += "Lat:" + Latitude + "\n";
    //reply += "Lon:" + Longitude + "\n";
    bot.sendMessage(CHAT_ID_Tele, reply);
    Serial.println("Telegram Message Sent");
    distance = 11;
  }
}
void setup() {
  Serial.begin(115200);
  Serial.println();

  // attempt to connect to Wifi network:
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

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
}
long previousMillisTelegram = 0;
void loop() {
  if (millis() - previousMillisTelegram >= 1000) {
    previousMillisTelegram = millis();
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
buttonPressed();

  }
}
