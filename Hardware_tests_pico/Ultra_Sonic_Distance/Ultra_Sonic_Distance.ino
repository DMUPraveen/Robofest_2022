
/* Sensor Object */
struct Ultra_Sonic 
{
  // Pins
  int pin_trig ;
  int pin_echo ;

  // constants
  float k;
  float speed_of_sound = 0.03531688985445323;

  Ultra_Sonic( int trig , int echo , float k)
    : pin_trig(trig) , pin_echo(echo), k(k)
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

    return measure() / 2 * speed_of_sound;


  }

  float filter( float d_prev )
  {
    return ( k * Distance() + ( 1 - k ) * d_prev );
  }

};

void setup()
{
  // filter constant
  float k = 0.15;
  Serial.begin(9600);

  // sensor objects
  auto d1 = Ultra_Sonic( 5, 6 , k );
  auto d2 = Ultra_Sonic( 7, 8 , k );
  auto d3 = Ultra_Sonic( 9, 10 , k );

  // store data
  float d1_data[2] = { 0 , 0 };
  float d2_data[2] = { 0 , 0 };
  float d3_data[2] = { 0 , 0 };


  while (true) 
  {

    d1_data[1] = d1.filter( d1_data[0] );
    d2_data[1] = d2.filter( d2_data[0] );
    d3_data[1] = d3.filter( d3_data[0] );
    

    /*if( (d_1 < 500) && (d_2 < 500) && (d_3 < 500) )
      {*/
    //unsigned long t1 = millis();
    Serial.print( d1_data[1] ); Serial.print("\t");

    //Serial.print( millis() - t1 );Serial.print("\t");
    //unsigned long t2 = millis();
    Serial.print( d2_data[1] ); Serial.print("\t");

    //Serial.print( millis() - t2  );Serial.print("\t");
    //unsigned long t3 = millis();
    Serial.print( d3_data[1] ); Serial.println("\t");

    //Serial.println( millis() - t3 );
    /*}*/

    // changing variables
    d1_data[0] = d1_data[1];
    d2_data[0] = d2_data[1];
    d3_data[0] = d3_data[1];


  }


}
