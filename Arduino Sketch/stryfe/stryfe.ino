const int motor_min = 15; // Lowest Motor Speed possible
const int read_write_factor = 1020 / (255 - motor_min);

const int read_pin    = 3;
const int write_pin   = 1;
const int trigger_pin = 0;

boolean was_low = false;
int     poti    = 0;
int     motor   = 255;

void beep() {
    analogWrite(write_pin, 10);
    delay(100);
    analogWrite(write_pin, 0);
    delay(100);
}  

void setup()
{
  pinMode(write_pin,   OUTPUT);   // sets the pin as output
  pinMode(trigger_pin, INPUT_PULLUP);

  poti  = analogRead(read_pin);
  if (poti > 1020) {
    beep();
    beep();
  }
  else {
    analogWrite(write_pin,255);
    motor = motor_min + (poti / read_write_factor);
    delay(motor*4);
  }
}

void loop()
{
  poti = analogRead(read_pin);
  if (poti < 1020) {
    if (digitalRead(trigger_pin) == false) was_low = true;
    if (digitalRead(trigger_pin) && was_low) {
      analogWrite(write_pin,255);
      delay(50);
      was_low = false;
    } 
    motor = motor_min + (poti / read_write_factor);
  }
  else {
    if (digitalRead(trigger_pin)) motor = 0;
    else motor = 255;
  }
  if (motor > 255) motor = 255;
  analogWrite(write_pin, motor);  // analogRead values go from 0 to 1023, analogWrite values from 0 to 255
}
