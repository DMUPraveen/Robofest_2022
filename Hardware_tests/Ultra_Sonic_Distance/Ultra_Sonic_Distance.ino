/*int pin_trig = 4;
int pin_echo = 3;
int pin_led = 13;
int dt = 200;
float measure_t;
float speed_of_sound = 0.03531688985445323;
float distance;
*/
struct Ultra_Sonic{
  int pin_trig = 4;
  int pin_echo = 3;
  float speed_of_sound = 0.03531688985445323;

  Ultra_Sonic( int trig , int echo)
    : pin_trig(trig) , pin_echo(echo) 
   {
    pinMode( pin_trig , OUTPUT);
    pinMode( pin_echo , INPUT);
    }
  float measure()
  {
    digitalWrite( pin_trig , LOW );
    delayMicroseconds(2);
    digitalWrite( pin_trig , HIGH );
    delayMicroseconds(10);
    digitalWrite( pin_trig , LOW );

    return pulseIn( pin_echo , HIGH );
    
  }
  float Distance()
  {
    return measure()/2 * speed_of_sound;
    
  }
  
};

void setup() 
{
  
  Serial.begin(9600);
  auto d1 = Ultra_Sonic( 4 , 3);
  while(true){
    Serial.println( d1.Distance() );
  }
  
}
/*
void loop() 
{

unsigned long t = millis();

// Reading data
digitalWrite(pin_trig, LOW);
delayMicroseconds(2);
digitalWrite(pin_trig, HIGH);
delayMicroseconds(10);
digitalWrite(pin_trig, LOW);

measure_t = pulseIn(pin_echo, HIGH);

// Calculations
distance = measure_t / 2.0 * speed_of_sound;
if( distance <= 5)
{ 
  digitalWrite( pin_led , HIGH );
}
else
{
  digitalWrite( pin_led , LOW );  
}
// Display

//Serial.print("distance = ");
//Serial.println( distance );
//Serial.println(" cm");
Serial.println( millis() - t );

//delay(dt);
}
*/
