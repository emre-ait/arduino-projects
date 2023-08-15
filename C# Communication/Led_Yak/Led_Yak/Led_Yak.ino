int led1 = 2;
int led2 = 3;
int led3 = 4;
void setup() {
  // put your setup code here, to run once:
pinMode(led1,OUTPUT);
pinMode(led2,OUTPUT);
pinMode(led3,OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available())
    {
      int a = Serial.read();
      if(a == '1')
        {
          digitalWrite(led1,HIGH);
        }
      if(a == '2')
        {
          digitalWrite(led1,LOW);
        }
       if(a == '3')
        {
          digitalWrite(led2,HIGH);
        }
      if(a == '4')
        {
          digitalWrite(led2,LOW);
        }
       if(a == '5')
        {
          digitalWrite(led3,HIGH);
        }
      if(a == '6')
        {
          digitalWrite(led3,LOW);
        }
    }
}
