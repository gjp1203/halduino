#include <Servo.h>
Servo motor;
Servo servo;
int pwm_val = -1;
int angle = -1;
int toggle_count = 0;
char incomingByte = 0;   // for incoming serial data
int command = 0;

// Positions:
const int WASHOUT_POS = 120;
const int START_POSITION = 90;
const int INSPECT_POSITION = 90;

// PWM Values:
const int PWM_GO_VAL = 1057;
const int PWM_STOP_VAL = 900;

// Cycles:
const int PWM_LOOPS = 2;
const int SPINS_PER_SAMPLE = 3;

// Delays:
const int WASHOUT_DELAY = 1000;
const int DELAY_BEOFRE_SWIRL = 1000;
const int DELAY_AFTER_SPINS = 1000;
const int PWM_DELAY = 80;

int loopCount = 0;
int position = START_POSITION;
unsigned long time;


void setup()
{
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  motor.attach(9);
  motor.writeMicroseconds(0);
  //pinMode(13, OUTPUT);
  servo.attach(6);
  //servo.write(0); 
  //pinMode(A4, INPUT_PULLUP);
}

int readFromBuffer() {
    char buffer[] = {
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
    }; // Receive up to 12 bytes

    while (!Serial.available()); // Wait for characters
    Serial.readBytesUntil('n', buffer, 12);
    return atoi(buffer);
}

void washout() {
  servo.write(WASHOUT_POS);  
}

void induceSwirl() {
  motor.writeMicroseconds(PWM_GO_VAL);
  for (int i = 0; i < PWM_LOOPS; i++)
    delay(PWM_DELAY);
  motor.writeMicroseconds(PWM_STOP_VAL);    
}

void stopSwirl() {
  motor.writeMicroseconds(PWM_STOP_VAL);
}


void setPosition(int pos) {
    position = pos;
}

void loop() {
    
  if (Serial.available() > 0) {
      // read the incoming byte:
      incomingByte = Serial.read();

      switch (incomingByte) {
      case '1':
        setPosition(START_POSITION);
        break;
      case '2':
        setPosition(WASHOUT_POS);
        break;
      case '3':
        setPosition(INSPECT_POSITION);
        break;
      case '4':
        induceSwirl();
        break;        
      default:
        break;
      }
      //Serial.println("Incoming byte: ");
      //Serial.println(incomingByte);
      
  }
  //Serial.println(position);
  servo.write(position);
  delay(300);

}
