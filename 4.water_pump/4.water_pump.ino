void setup() //executed only once,for pin configuration
{
  // put your setup code here, to run once:
  pinMode(2,OUTPUT);
  pinMode(4,OUTPUT);
}

void loop() //executed many times
{
  // put your main code here, to run repeatedly:
  digitalWrite(2,HIGH); //function..first parameter is pin number
  digitalWrite(4,LOW);
  delay(5000); //1 second wait
  digitalWrite(2,LOW);
  digitalWrite(4,LOW);
  delay(5000);
}
