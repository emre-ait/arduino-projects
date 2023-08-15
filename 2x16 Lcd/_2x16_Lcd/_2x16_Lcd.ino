#include <LiquidCrystal.h>
LiquidCrystal lcd(11,10,9,8,7,6,5,4,3,2); // (RS,E,D4,D5,D6,D7)
void setup() 
{
  lcd.begin(2,16);// (cols,rows)
  lcd.print("Deneme");
}

void loop() 
{
  lcd.setCursor(2,1);
  lcd.print(millis() / 1000);

}
