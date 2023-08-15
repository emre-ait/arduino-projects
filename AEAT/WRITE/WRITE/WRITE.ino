/*   Tested for CALT HAE28 Absolute Rotary Encoder
 *   
 *   Encoder Red (Power +)  <-> Arduino +5V
 *   Encoder Black (GND)    <-> Arduino GND
 *   Encoder Blue (Clock)   <-> Arduino Pin 5
 *   Encoder Green (DATA)   <-> Arduino Pin 6
 *   Encoder Yellow (CS)    <-> Arduino Pin 7
 */
 
const int CLOCK_PIN = 11; // Blue Pin
const int DATA_PIN = 10; // Green Pin
const int CS_PIN = 9; // Yellow Pin
const int BIT_COUNT = 16; // 12 Bit Mode
const int PROG_PIN = 12;
const int MAG_LO_PIN = 8; // MAGNETIC FIELD LOW and When PROG_MODE enable OPT_PROG_STAT
const int MAG_HI_PIN = 7; // MAGNETIC FEILD HIGH and When PROG_MODE enable OPT_ERR
unsigned long old_sample = 0;
void setup()
{
  //setup our pins
  pinMode(DATA_PIN, INPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(CS_PIN, OUTPUT);
  pinMode(PROG_PIN, OUTPUT);
  pinMode(MAG_LO_PIN, INPUT);
  pinMode(MAG_HI_PIN, INPUT);
  //give some default values
  digitalWrite(PROG_PIN, LOW);
  digitalWrite(CLOCK_PIN, HIGH);
  digitalWrite(CS_PIN, HIGH);
  Serial.begin(115200);
  Serial.println("e: a - position, d - programming, e - exit current mode");
}

void loop()
{
  if (Serial.available())
  {
    switch (Serial.read())
    {
    case 'a':
      while (Serial.read()!='e')
      {
        float reading = readPosition();
        if (reading >= -0.5)
        {
          Serial.print("Reading: ");
          Serial.println(reading, 4);
        }
        delay(50);
      }
      break;
     
     case 'd':
      int32_t out1 = 0b00000000000000000100101100000111;
      int32_t out1_rev = 0b11100000110100100000000000000000;
      int32_t out2 = 0b00000000000000000000001100000111;
      int32_t out2_rev = 0b11100000110000000000000000000000;
      SSI_Shift_Out(DATA_PIN, CLOCK_PIN, CS_PIN, PROG_PIN);
      Serial.print("OTP ERROR");
      Serial.println(digitalRead(MAG_HI_PIN));
      Serial.print("OTP PARITY CHECK VALID");
      Serial.println(digitalRead(MAG_LO_PIN));
      break;

      case 'r':
      while (Serial.read()!='e')
      {
        float reading = readPosition();
        if (reading >= -0.5)
        {
          Serial.print("Reading: ");
          Serial.println(reading, 2);
        }
        delay(100);
      }
      break;
    default:
      break;
    }
  }
}

//read the current angular position
float readPosition()
{
  // Read the same position data twice to check for errors
  unsigned long sample1 = shiftIn(DATA_PIN, CLOCK_PIN, CS_PIN, BIT_COUNT);
  delayMicroseconds(200);
  unsigned long sample2 = shiftIn(DATA_PIN, CLOCK_PIN, CS_PIN, BIT_COUNT);
  delayMicroseconds(200); // Clock must be high for 20 microseconds before a new sample can be taken
  if (sample1 != sample2) return -1.0;
  Serial.print("Raw Data:");
  Serial.println(sample1); 
  if (sample1 <= old_sample +1 && sample1 >= old_sample -1)
  {
      sample1 = old_sample;
  } 
  old_sample = sample1;
  return (((sample1) * 360.0) / 65535.0);
}

//read in a byte of data from the digital input of the board.
unsigned long shiftIn(const int data_pin, const int clock_pin, const int cs_pin, const int bit_count)
{
  unsigned long data = 0;

  digitalWrite(cs_pin, LOW);
  delayMicroseconds(2);
  for (int i = 0; i < bit_count; i++)
  {
    data <<= 1;
    digitalWrite(clock_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(clock_pin, HIGH);
    delayMicroseconds(2);

    data |= digitalRead(data_pin);
  }
  digitalWrite(cs_pin, HIGH);
  /*
  Serial.print("Data: ");
  Serial.println(data);*/
  return data;
}

void SSI_Shift_Out(const int data_pin, const int clock_pin, const int cs_pin, const int prog_pin) {
  digitalWrite(clock_pin, HIGH);  // clock pin high
  delayMicroseconds(1);
  digitalWrite(prog_pin, HIGH);   // Set PROG_PIN to HIGH for change operation mode to PROGRAM MODE
  delayMicroseconds(100);
  pinMode(data_pin, OUTPUT);      // Set DATA_PIN to output pin
  digitalWrite(data_pin, HIGH);   // DataPin Set to 1 for prepearing OTP
  delayMicroseconds(1000);

  digitalWrite(cs_pin, LOW);      // ChipSelect pin low
  delayMicroseconds(1);
  
  digitalWrite(clock_pin, LOW);   // clock pin low
  delayMicroseconds(1);
  digitalWrite(clock_pin, HIGH);  // clock pin high
  
  delayMicroseconds(1);
  

  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,1);   // Parity bit 1
  delayMicroseconds(1);
  digitalWrite(clock_pin, HIGH);  // clock pin high
  
  delayMicroseconds(1);
  

  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,0);   // Data 31.bit 
  delayMicroseconds(1);
  digitalWrite(clock_pin, HIGH);  // clock pin high
  
  delayMicroseconds(1);
  

  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,0);   // Data 30.bit 
  delayMicroseconds(1);
  digitalWrite(clock_pin, HIGH);  // clock pin high
  
  delayMicroseconds(1);
  

  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,0);   // Data 29.bit 
  delayMicroseconds(1);
  digitalWrite(clock_pin, HIGH);  // clock pin high
  
  delayMicroseconds(1);
  

  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,0);   // Data 28.bit 
  delayMicroseconds(1);
  digitalWrite(clock_pin, HIGH);  // clock pin high
  
  delayMicroseconds(1);
  

  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,0);   // Data 27.bit 
  delayMicroseconds(1);
  digitalWrite(clock_pin, HIGH);  // clock pin high
  
  delayMicroseconds(1);
  

  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,0);   // Data 26.bit 
  delayMicroseconds(1);
  digitalWrite(clock_pin, HIGH);  // clock pin high
  
  delayMicroseconds(1);
  

  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,0);   // Data 25.bit 
  delayMicroseconds(1);
  digitalWrite(clock_pin, HIGH);  // clock pin high
  
  delayMicroseconds(1);
  

  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,0);   // Data 24.bit 
  delayMicroseconds(1);
  digitalWrite(clock_pin, HIGH);  // clock pin high
  
  delayMicroseconds(1);
  

  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,0);   // Data 23.bit
  delayMicroseconds(1);
   
  digitalWrite(clock_pin, HIGH);  // clock pin high
  
  delayMicroseconds(1);
  

  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,0);   // Data 22.bit 
  delayMicroseconds(1);
  digitalWrite(clock_pin, HIGH);  // clock pin high
  
  delayMicroseconds(1);
  

  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,0);   // Data 21.bit 
  delayMicroseconds(1);
  digitalWrite(clock_pin, HIGH);  // clock pin high
   
  delayMicroseconds(1);
  

  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,0);   // Data 20.bit
  delayMicroseconds(1);
  digitalWrite(clock_pin, HIGH);  // clock pin high
  
  delayMicroseconds(1);
   

  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,0);   // Data 19.bit
  delayMicroseconds(1);
  digitalWrite(clock_pin, HIGH);  // clock pin high
  
  delayMicroseconds(1);
  

  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,0);   // Data 18.bit
  delayMicroseconds(1);
  digitalWrite(clock_pin, HIGH);  // clock pin high
  
  delayMicroseconds(1);
  
  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,0);   // Data 17.bit

  delayMicroseconds(1);
  digitalWrite(clock_pin, HIGH);  // clock pin high
  
  delayMicroseconds(1);
  

  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,0);   // Data 16.bit
  delayMicroseconds(1);
  digitalWrite(clock_pin, HIGH);  // clock pin high
  
  delayMicroseconds(1);
  

  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,0);   // Data 15.bit
  delayMicroseconds(1);
  digitalWrite(clock_pin, HIGH);  // clock pin high
  
  delayMicroseconds(1);
  

  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,0);   // Data 14.bit
  delayMicroseconds(1);
  digitalWrite(clock_pin, HIGH);  // clock pin high
  
  delayMicroseconds(1);
  

  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,0);   // Data 13.bit
  delayMicroseconds(1);
  digitalWrite(clock_pin, HIGH);  // clock pin high
  
  delayMicroseconds(1);
  

  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,0);   // Data 12.bit
  delayMicroseconds(1);
  digitalWrite(clock_pin, HIGH);  // clock pin high
  
  delayMicroseconds(1);
  

  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,0);   // Data 11.bit
  delayMicroseconds(1);
  digitalWrite(clock_pin, HIGH);  // clock pin high
  
  delayMicroseconds(1);
  

  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,1);   // Data 10.bit
  delayMicroseconds(1);
  digitalWrite(clock_pin, HIGH);  // clock pin high
 
  delayMicroseconds(1);
  

  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,1);   // Data 9.bit
  delayMicroseconds(1);
  digitalWrite(clock_pin, HIGH);  // clock pin high
  
  delayMicroseconds(1);
  

  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,1);   // Data 8.bit
  delayMicroseconds(1);
  digitalWrite(clock_pin, HIGH);  // clock pin high
  
  delayMicroseconds(1);
  

  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,1);   // Data 7.bit
  delayMicroseconds(1);
  digitalWrite(clock_pin, HIGH);  // clock pin high
  
  delayMicroseconds(1);
  

  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,0);   // Data 6.bit
  delayMicroseconds(1);
  digitalWrite(clock_pin, HIGH);  // clock pin high
  
  delayMicroseconds(1);
  

  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,0);   // Data 5.bit
  delayMicroseconds(1);
  digitalWrite(clock_pin, HIGH);  // clock pin high
  
  delayMicroseconds(1);
  

  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,0);   // Data 4.bit
  delayMicroseconds(1);
  digitalWrite(clock_pin, HIGH);  // clock pin high
  
  delayMicroseconds(1);
  

  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,0);   // Data 3.bit
  delayMicroseconds(1);
  digitalWrite(clock_pin, HIGH);  // clock pin high
  
  delayMicroseconds(1);
  

  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,0);   // Data 2.bit
  delayMicroseconds(1);
  digitalWrite(clock_pin, HIGH);  // clock pin high
  
  delayMicroseconds(1);
  

  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,0);   // Data 1.bit
  delayMicroseconds(1);
  digitalWrite(clock_pin, HIGH);  // clock pin high
  
  delayMicroseconds(1);

  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,0);   // Data 0.bit
  delayMicroseconds(1);

  digitalWrite(clock_pin, HIGH);  // clock pin high
  
  delayMicroseconds(1);


  digitalWrite(clock_pin, LOW);   // clock pin low
  bitWrite (PORTB,2,1);   // Even Parity bit
  delayMicroseconds(1);
  
 

  digitalWrite(cs_pin, HIGH);
  delayMicroseconds(1);

  digitalWrite(prog_pin, LOW);
  delayMicroseconds(100);
  pinMode(data_pin, INPUT);
  delayMicroseconds(1000);
}
