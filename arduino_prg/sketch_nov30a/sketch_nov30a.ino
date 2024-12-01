const int enA = 9;
const int in1 = 2;
const int in2 = 3;

const int speed_left = 120;
const int speed_right = 120;

const unsigned long int runtime = 3000;   // fordulat / ezredmásodperc
unsigned long int runtime_run = 0;

const unsigned long int stoptime = 3000;  // megállás idő ezredmásodpercben

const unsigned long int move_time = 8;    // mozgásidő órában
const unsigned long int cycle_day = 25;   // ciklus / nap
const unsigned long int turn_cycle = 13;  // fordulat / ciklus

const unsigned long int pause_cycle = (( move_time * 60 * 60 - ( cycle_day * (2 * turn_cycle * (runtime / 1000) + (stoptime / 1000))  ) ) / cycle_day ) * 1000; // pihenőidő ciklusok között ezredmásodpercben


void setup() {
  Serial.begin(57600);

  pinMode(LED_BUILTIN, OUTPUT);
  
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}


void turn_left( ){
  long i = runtime * (long)turn_cycle;
  Serial.print("fordul: "); 
  Serial.print( i );
  Serial.print( "ms" );
  Serial.println(" balra - oraval azonosan");
  digitalWrite(LED_BUILTIN, HIGH);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, speed_left);

  delay( i );
}


void turn_right( ){
  long i = runtime * (long)turn_cycle;
  Serial.print("fordul: "); 
  Serial.print( i );
  Serial.print( " ms" );
  Serial.println(" jobbra - oraval ellen");
  digitalWrite(LED_BUILTIN, HIGH);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, speed_right);
  delay( i );
}


void stoped(int stoptime){
  Serial.print("STOP megáll ");
  Serial.print( stoptime );
  Serial.println( " ms" );
  digitalWrite(LED_BUILTIN, LOW);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  delay(stoptime);
}


void waiting(){
  Serial.print("WAIT várakozik ");
  Serial.print( pause_cycle );
  Serial.println( " ms" );
  digitalWrite(LED_BUILTIN, LOW);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  delay( pause_cycle );
}

void test_left(int fordul){
  long i = runtime * fordul;
  Serial.print("fordul: "); 
  Serial.print( i );
  Serial.print( "ms" );
  Serial.println(" balra - oraval azonosan");
  digitalWrite(LED_BUILTIN, HIGH);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, speed_left);

  delay( i );

}

void test_right(int fordul){
  long i = runtime * fordul;
  Serial.print("fordul: "); 
  Serial.print( i );
  Serial.print( "ms" );
  Serial.println(" jobbra - oraval ellentetes");
  digitalWrite(LED_BUILTIN, HIGH);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, speed_left);

  delay( i );

}
void loop() {

  //test_left(13);
  //test_right(13);
  //stoped( 60 * 1000 );
  

  
  for( int j = 0; j < 24 / move_time -1; j ++ ){

    if ( j == 0){
      for( int i = 0; i < cycle_day -1; i ++ ){
        turn_left();
        stoped( stoptime );

        turn_right();

        waiting();
      }
    }else{
      delay(24 / move_time * 60 * 60 * 1000);
    }
  }


}  