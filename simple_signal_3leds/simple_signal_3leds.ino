#define PIN_0 0
#define PIN_1 1
#define PIN_2 2

#define RED_LED 4
#define ORANGE_LED 2
#define GREEN_LED 1

#define CYCLE_SLEEP 200

#define CYCLES_COUNT 4

int cycles[CYCLES_COUNT]={4, 6, 1, 2};
int delays[CYCLES_COUNT]={4, 1, 4, 1};
int currentCycle;
int currentPhase;

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_0, OUTPUT);
  pinMode(PIN_1, OUTPUT);
  pinMode(PIN_2, OUTPUT);
  currentCycle=0;
  currentPhase=0;
}

void toggleLEDs(int state) {
  
  digitalWrite(PIN_2, state & RED_LED ? HIGH : LOW);
  digitalWrite(PIN_1, state & ORANGE_LED ? HIGH : LOW);
  digitalWrite(PIN_0, state & GREEN_LED ? HIGH : LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (currentCycle>CYCLES_COUNT-1) {
    currentCycle=0;
  }
  toggleLEDs(cycles[currentCycle]);
  delay(CYCLE_SLEEP);
  currentPhase++;
  if (currentPhase>delays[currentCycle]) {
    currentPhase=0;
    currentCycle++;
  }
}
