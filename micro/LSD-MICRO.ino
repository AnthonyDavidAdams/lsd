// LSD MICRO v1.0
// Light Stimulation Device
// Anthony David Adams
// AnthonyDavidAdams.com/lsd
/****************************/


// Calibrate hz settings

int b = 22;   // beta 22hz
int a = 12;   // alpha 12hz
int d = 3;    // delta 3hz
int t = 6;    // theta 6hz
int g = 30;   // gamma 30hz
int l = 100;  // lambda 100hz

int Led = 13;

int hzDelay = 33 ;
float hz = b;

int duration = 0;
int totalDuration = 0;

long previousMillis = 0;

/******* SEQUENCE *******/
// SEQUENCES ARE LOADED VIA AN ARRAY
// ie. sequence[frequency delay][duration in seconds]
// a = alpha waves, b = beta waves,d = delta waves, t = theta waves, g = gamma waves
// you can also input an integer that is desried delay time (on / off).

unsigned int defaultSequence[][2] {

  {b, 300},    // beta
  {a, 300},   // alpha
  {d, 120},   // delta
  {t, 120},   // theta
  {g, 300},   // gamma
  {g, 60},    // gamma
  {t, 60},    // theta
  {d, 60},    // delta
  {a, 60},    // alpha
  {b, 60}     // beta

};

/************************/

unsigned long startMillis = millis();

int long result;

void setup() {
  pinMode(Led, OUTPUT);
  Serial.begin(9600);
}


void loop() {

  Serial.println("LSD: LIGHT STIMULATION DEVICE");
  Serial.println("");
  Serial.println("█░░ ▄▀▀ █▀▀▄");
  Serial.println("█░░ ▀▀▄ █░░█");
  Serial.println("▀▀▀ ▀▀▀ ▀▀▀");
  Serial.println("");
  Serial.println("WELCOME TO THE LSD EXPERIENCE");
  Serial.println("by Anthony David Adams");
  Serial.println("");
  //Serial.println("The default sequence will start automatically in 10 seconds.");
  Serial.println(">> Press [X] to select a custom sequence or [S] to START the default sequence now. <<");
  Serial.println("");

  for (;;) {
    switch (Serial.read()) {
      case 'X':
      case 'x':
        mainMenu();
        for (;;) {
          switch (Serial.read()) {
            case 'A':
            case 'a':
              {
                Serial.println("ALPHA");
                getDuration();
                unsigned int mySequence[][2] {
                  {a, result}
                };
                runSequence(mySequence, sizeof mySequence / sizeof mySequence[0]);
                break;
              }
            case 'B':
            case 'b':
              {
                Serial.println("BETA");
                getDuration();
                unsigned int mySequence[][2] {
                  {b, result}
                };
                runSequence(mySequence, sizeof mySequence / sizeof mySequence[0]);
                break;
              }
            case 'G':
            case 'g':
              {
                Serial.println("GAMMA");
                getDuration();
                unsigned int mySequence[][2] {
                  {g, result}
                };
                runSequence(mySequence, sizeof mySequence / sizeof mySequence[0]);
                break;
              }
            case 'D':
            case 'd':
              {
                Serial.println("DELTA");
                getDuration();
                unsigned int mySequence[][2] {
                  {d, result}
                };
                runSequence(mySequence, sizeof mySequence / sizeof mySequence[0]);
                break;
              }
            case 'T':
            case 't':
              {
                Serial.println("THETA");
                getDuration();
                unsigned int mySequence[][2] {
                  {t, result}
                };
                runSequence(mySequence, sizeof mySequence / sizeof mySequence[0]);
                break;
              }
            case 'L':
            case 'l':
              {
                Serial.println("LAMBDA");
                getDuration();
                unsigned int mySequence[][2] {
                  {l, result}
                };
                runSequence(mySequence, sizeof mySequence / sizeof mySequence[0]);
                break;
              }
            case 'S':
            case 's':
              {
                Serial.println("SPECTRUM");
                getDuration();
                unsigned int mySequence[][2] {
                  {b, result / 10},    // beta
                  {a, result / 10},   // alpha
                  {d, result / 10},   // delta
                  {t, result / 10},   // theta
                  {g, result / 10},   // gamma
                  {g, result / 10},    // gamma
                  {t, result / 10},    // theta
                  {d, result / 10},    // delta
                  {a, result / 10},    // alpha
                  {b, result / 10}     // beta
                };
                runSequence(mySequence, sizeof mySequence / sizeof mySequence[0]);
                break;
              }
            case 'C':
            case 'c':
              Serial.println("CUSTOM");
              break;
            case 'R':
            case 'r':
              Serial.println("DYNAMIC");
              break;
          }
        }
        break;

      case 'S':

        runSequence(defaultSequence, sizeof defaultSequence / sizeof defaultSequence[0]);
        break;

      default: continue;  // includes the case 'no input'
    }
  }
}

int getDuration() {
  Serial.println("");
  Serial.println("Type [A] for 12 Minutes");
  Serial.println("Type [B] for 24 Minutes");
  Serial.println("Type [C] for 48 Minutes");
  Serial.println("Type [D] for 60 Minutes");
  Serial.println("Type [E] for 90 Minutes");
  Serial.println("");
  Serial.println(">> Select Sequence Duration. <<");
  Serial.println("");

  result = 0;
  while (result == 0) {
    switch (Serial.read()) {
      case 'A':
      case 'a':
        result = 12 * 60;
        break;
      case 'B':
      case 'b':
        result = 24 * 60;
        break;
      case 'C':
      case 'c':
        result = 48 * 60;
        break;
      case 'D':
      case 'd':
        result = 60 * 60;
        break;
      case 'E':
      case 'e':
        result = 90 * 60;
        break;
      case 'Z': // hidden test setting for 10 seconds
      case 'z':
        result = 10;
        break;
      default: continue;
    }
  }

  return result;
}


void runSequence(unsigned int sequence[][2], size_t num_elements) {

  Serial.println("SEQUENCE LOADED");
  Serial.println();
  
  totalDuration = 0;
  for (int i = 0; i < num_elements; i++) {
    duration = sequence[i][1]; // in seconds
    totalDuration = totalDuration + duration;
  }

  Serial.print(totalDuration / 60);
  Serial.println(" Minutes Total");
  Serial.println();
  Serial.println();
  Serial.print("Consider your intention. Session will begin in 10 Seconds.");
  for (int i=0; i < 10; i++){
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.println();
  Serial.println("SEQUENCE BEGIN");
  Serial.println();

  for (int i = 0; i < num_elements; i++) {

    hz       = sequence[i][0];  // hz
    duration = sequence[i][1]; // in seconds

    hzDelay =  (1 / hz) * 1000; // the blink delay to generate the hz

    startMillis = millis();

    Serial.print("Section: ");
    Serial.print(i+1);
    Serial.print("/");
    Serial.print(num_elements);
    Serial.print("\t Frequency: ");
    Serial.print(hz);
    Serial.print("hz \tDelay: ");
    Serial.print(hzDelay);
    Serial.print("ms \t Duration: ");
    Serial.print(" ");
    Serial.print(duration);
    Serial.print("s \t Actual: ");

    while (((millis() - startMillis) / 1000 ) < duration) {
      digitalWrite(Led, HIGH);
      delay(hzDelay);
      digitalWrite(Led, LOW);
      delay(hzDelay);
    }
    Serial.print((millis() - startMillis) / 1000);
    Serial.println("s");
  }
  Serial.println();
  Serial.println("SEQUENCE END");
  Serial.println();
  
  Serial.println();
  mainMenu();
  return "COMPLETE";
}

void mainMenu() {
  Serial.println("********************************************************************************************");
  Serial.println();
  Serial.println("[B]ETA     13-30 Hz\t Awake, normal alert conciousness.");
  Serial.println("[A]LPHA     8-12 Hz\t Physically and mentally relaxed, awake but drowsey.");
  Serial.println("[D]ELTA     .5-3 Hz\t Deep (dreamless) sleep, loss of bodily awareness.");
  Serial.println("[T]HETA      4-7 Hz\t Reduced conciousess, deep meditation, dreams, light sleep, REM sleep.");
  Serial.println("[G]AMMA   31-120 Hz\t Heightened perception.");
  Serial.println("[L]AMBDA 100-200 Hz\t Mystical experience.");
  Serial.println("");
  Serial.println("[S]PECTRUM - Sample of Each hz State.");
  Serial.println("");
  Serial.println("");
  Serial.println(">> Select your sequence / frequency by entering the corresponding letter. <<");
  Serial.println("");
}
