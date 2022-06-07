void setup() //executed only once,for pin configuration
{
  // put your setup code here, to run once:
  pinMode(2,OUTPUT);
 //Serial.begin(115200);
}

void loop() //executed many times
{
  // put your main code here, to run repeatedly:
  digitalWrite(2,HIGH); //function..first parameter is pin number
  delay(1000); //1 second wait
  digitalWrite(2,LOW);
  delay(1000);
  //Serial.println("esp32io.com");
}
