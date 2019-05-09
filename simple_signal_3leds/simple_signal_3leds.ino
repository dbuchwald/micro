#define PIN_0 0
#define PIN_1 1
#define PIN_2 2
#define PIN_4 4

#define RED_LED 4
#define ORANGE_LED 2
#define GREEN_LED 1

#define NORMAL_MODE 0
#define EMERGENCY_MODE 1

#define READ_SLEEP 10
#define READS_PER_CYCLE 20

#define NORMAL_CYCLES_COUNT 4
#define EMERGENCY_CYCLES_COUNT 2

int normalCycles[NORMAL_CYCLES_COUNT]={4, 6, 1, 2};
int normalDelays[NORMAL_CYCLES_COUNT]={4, 1, 4, 1};
int emergencyCycles[EMERGENCY_CYCLES_COUNT]={2, 0};
int emergencyDelays[EMERGENCY_CYCLES_COUNT]={1, 1};
int currentCycle;
int currentPhase;
int currentMode;
int buttonPressed;
int lastButtonState;
int* cycles;
int* delays;
int cyclesCount;
int currentRead;
int modeSwitch;

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_0, OUTPUT);
  pinMode(PIN_1, OUTPUT);
  pinMode(PIN_2, OUTPUT);
  pinMode(PIN_4, INPUT);
  currentMode=NORMAL_MODE;
  cyclesCount=NORMAL_CYCLES_COUNT;
  cycles=normalCycles;
  delays=normalDelays;
  currentCycle=0;
  currentPhase=0;
  currentRead=0;
  lastButtonState=digitalRead(PIN_4);
}

void toggleLEDs(int state) {
  digitalWrite(PIN_2, state & RED_LED ? HIGH : LOW);
  digitalWrite(PIN_1, state & ORANGE_LED ? HIGH : LOW);
  digitalWrite(PIN_0, state & GREEN_LED ? HIGH : LOW);
}
void toggleMode() {

  if (currentMode == NORMAL_MODE) {
    currentMode=EMERGENCY_MODE;
    cyclesCount=EMERGENCY_CYCLES_COUNT;
    cycles=emergencyCycles;
    delays=emergencyDelays;
  } else {
    currentMode=NORMAL_MODE;
    cyclesCount=NORMAL_CYCLES_COUNT;
    cycles=normalCycles;
    delays=normalDelays;
  }
  currentCycle=0;
  currentPhase=0;
}

void loop() {
  // put your main code here, to run repeatedly:
  if (currentCycle>cyclesCount-1) {
    currentCycle=0;
  }
  toggleLEDs(cycles[currentCycle]);

  modeSwitch=0;
  for (currentRead=0; currentRead<READS_PER_CYCLE; currentRead++) {
    buttonPressed = digitalRead(PIN_4);
    if (buttonPressed && !lastButtonState) {
      modeSwitch=1;
    }
    lastButtonState = buttonPressed;
    delay(READ_SLEEP);    
  }

  if (modeSwitch) {
    toggleMode();
  } else {
    currentPhase++;
    if (currentPhase>delays[currentCycle]) {
      currentPhase=0;
      currentCycle++;
    }  
  }
}
