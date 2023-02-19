
#define IR_LED 4
#define NUM_BITS 21
#define NUM_REPETITIONS 5

#define DEBUG 0
#if DEBUG
  #define delayMicroseconds(x) delay(x)
#endif

#define LOW_TIME 92
#define FULL_HIGH_TIME 352
#define HALF_HIGH_TIME FULL_HIGH_TIME/2

void sendCode();
void sendBit(boolean IRbit);

boolean bit_array[NUM_BITS] = {1,0,1,1,0,1,1,1,1,0,1,1,1,0,1,0,0,1,0,1,1};

void setup() {
  // put your setup code here, to run once:
  //noInterrupts();
  pinMode(IR_LED, OUTPUT);
  digitalWrite(IR_LED, HIGH);
  delayMicroseconds(10720);
  
}

void loop() {
  // put your main code here, to run repeatedly:
#if DEBUG
  delay(1000);
  sendBit(true);
  sendBit(true);
  delay(1000);
  sendBit(false);
  sendBit(false);
#endif 
  for(int l=0; l<NUM_REPETITIONS; l++)
  {
    sendCode();
  }
  digitalWrite(IR_LED, HIGH);
  delayMicroseconds(10720);
}

void sendCode()
{
  for(int i=0; i<NUM_BITS; i++)
  {
    sendBit(bit_array[i]);
  }
  delayMicroseconds(5600);  //delay till repetition
}

void sendBit(boolean IRbit)
{
  if(IRbit)
  {
    digitalWrite(IR_LED, LOW);
    delayMicroseconds(LOW_TIME);
    digitalWrite(IR_LED, HIGH);
    delayMicroseconds(FULL_HIGH_TIME);
  }
  else
  {
    digitalWrite(IR_LED, LOW);
    delayMicroseconds(LOW_TIME);
    digitalWrite(IR_LED, HIGH);
    delayMicroseconds(HALF_HIGH_TIME);
    digitalWrite(IR_LED, LOW);
    delayMicroseconds(HALF_HIGH_TIME);
  }
}

