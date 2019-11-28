// LSD MICRO v0.1
// Light Stimulation Device
// Anthony David Adams
// AnthonyDavidAdams.com/lsd
/****************************/

//beta - 22hz
//alpha - 12hz
//delta - 3hz
//theta - 6hz
//gamma - 30hz

int Led = 13;

int b = 45;   // beta  delay
int a = 83;   // alpha delay
int d = 333;  // delta delay
int t = 166;  // theta delay
int g = 33;   // gamma delay

int hzDelay = b ;
int duration = 0;
int totalDuration = 0;

long previousMillis = 0;

/******* SEQUENCE *******/

int sequence[][2] {
  
  {b, 300},   // beta
  {a, 60},   // alpha
  {d, 60},   // delta
  {t, 60},   // theta
  {g, 300},   // gamma
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

    hzDelay = sequence[i][0];  // half of the hz for on / off
    duration = sequence[i][1]; // in seconds

    startMillis = millis();

    int y = round(duration * 500 / hzDelay);

    Serial.print("Section: ");
    Serial.print(i);
    Serial.print("\t Frequency: ");
    Serial.print(round(1000 / hzDelay));
    Serial.print("hz \tDuration: ");
    Serial.print(duration);
    Serial.println(" Seconds");

    for (int x = 0; x <= y; x++) {
      digitalWrite(Led, HIGH);
      delay(hzDelay);
      digitalWrite(Led, LOW);
      delay(hzDelay);
    }

  }
  Serial.println("SEQUENCE END");
  Serial.println();
  delay(1000);
}
