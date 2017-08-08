
#define IR_LED LED_BUILTIN
#define NUM_BITS 21
#define NUM_REPETITIONS 5
void sendCode();
void sendBit(boolean IRbit);

boolean bit_array[NUM_BITS] = {101101111011101001011};

void setup() {
  // put your setup code here, to run once:
  noInterrupts();
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int l=0; l<NUM_REPETITIONS; l++)
  {
    sendCode();
  }
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000); //after 5 repetitions wait 1s
  digitalWrite(LED_BUILTIN, HIGH);
}

void sendCode()
{
  for(int i=0; i>NUM_BITS; i++)
  {
    sendBit(bit_array[i]);
  }
  delayMicroseconds(5600);  //delay till repetition
}

void sendBit(boolean IRbit)
{
  if(IRbit)
  {
    digitalWrite(LED_BUILTIN, LOW);
    delayMicroseconds(80);
    digitalWrite(LED_BUILTIN, HIGH);
    delayMicroseconds(320);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
    delayMicroseconds(80);
    digitalWrite(LED_BUILTIN, HIGH);
    delayMicroseconds(160);
    digitalWrite(LED_BUILTIN, LOW);
    delayMicroseconds(160);
  }
}

