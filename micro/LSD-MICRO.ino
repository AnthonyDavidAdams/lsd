// LSD MICRO v0.1
// Light Stimulation Device
// Anthony David Adams
// AnthonyDavidAdams.com/lsd
/****************************/

//beta -  22hz
//alpha - 12hz
//delta - 3hz
//theta - 6hz
//gamma - 30hz

int Led = 13;

int b = 22;   // beta hz
int a = 12;   // alpha hz
int d = 3;  // delta hz
int t = 6;  // theta hz
int g = 30;   // gamma hz

float hz = b ;
int hzDelay = 33;

int duration = 0;
int totalDuration = 0;

long previousMillis = 0;

/******* SEQUENCE *******/
// SEQUENCES ARE LOADED VIA AN ARRAY
// ie. sequence[frequency delay][duration in seconds]
// a = alpha waves, b = beta waves,d = delta waves, t = theta waves, g = gamma waves
// you can also input an integer that is desried delay time (on / off).

int sequence[][2] {

  {b, 10} ,  // beta
  {a, 10},  // alpha
  {d, 1},  // delta
  {t, 1},  // theta
  {g, 300},  // gamma
  {g, 60},   // gamma
  {t, 60},   // theta
  {d, 60},   // delta
  {a, 60},   // alpha
  {b, 60}     // beta

};

/************************/

unsigned long startMillis = millis();

void setup() {
  pinMode(Led, OUTPUT);
  Serial.begin(9600);

  Serial.println("LSD: LIGHT STIMULATION DEVICE");
  Serial.println("");
  Serial.println("█░░ ▄▀▀ █▀▀▄");
  Serial.println("█░░ ▀▀▄ █░░█");
  Serial.println("▀▀▀ ▀▀▀ ▀▀▀");

}



void loop() {

  Serial.print("SEQUENCE START");
  Serial.println();
  totalDuration = 0;
  for (int i = 0; i < (sizeof sequence / sizeof sequence[0]); i++) {
    duration = sequence[i][1]; // in seconds
    totalDuration = totalDuration + duration;
  }

  Serial.print(totalDuration / 60);
  Serial.println(" Minutes total");
  Serial.println();
  Serial.println();

  for (int i = 0; i < (sizeof sequence / sizeof sequence[0]); i++) {

    hz = sequence[i][0];
    duration = sequence[i][1]; // in seconds
    
    hzDelay =  (1 / hz) * 1000;
    
    startMillis = millis();
    
    Serial.print("Section: ");
    Serial.print(i);
    Serial.print("\t Frequency: ");
    Serial.print(hz);
    Serial.print("hz \tDelay: ");
    Serial.print(hzDelay);
    Serial.print("\t Duration: ");
    Serial.print(" ");
    Serial.print(duration);
    Serial.print(" Seconds \t Actual: ");
    
    while(((millis() - startMillis)/1000 )< duration) {
      digitalWrite(Led, HIGH);
      delay(hzDelay);
      digitalWrite(Led, LOW);
      delay(hzDelay);
    }
    Serial.print((millis() - startMillis)/1000);
    Serial.println(" Seconds");
  }
  Serial.println("SEQUENCE END");
  Serial.println();
  delay(300000); // 5 MINUTE END OF SESSION PAUSE
}
