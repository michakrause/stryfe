const int read_pin    = 3;
const int write_pin   = 1;
const int trigger_pin = 0;
const int motor_normal_speed = 100;

boolean was_low = false;
unsigned long last_trigger = 0;
int     last_trigger_time;


void beep(int number) {
  for (int x=0;x<number;x++) {
    analogWrite(write_pin, 0);
    delay(100);
    analogWrite(write_pin, 10);
    delay(100);
  }
  analogWrite(write_pin, 0);
}

int get_motor(int poti) {
  if      (poti < 3) return 16;
  else if (poti == 3) return 0;
  else if (poti < 33) return 19;
  else if (poti == 33) return 0;
  else if (poti < 105) return 22;
  else if (poti == 105) return 0;
  else if (poti < 190) return 25;
  else if (poti == 190) return 0;
  else if (poti < 280) return 31;
  else if (poti == 280) return 0;
  else if (poti < 370) return 39;
  else if (poti == 370) return 0;
  else if (poti < 450) return 48;
  else if (poti == 450) return 0;
  else if (poti < 615) return 61;
  else if (poti == 615) return 0;
  else if (poti < 680) return 76;
  else if (poti == 680) return 0;
  else if (poti < 780) return 95;
  else if (poti == 780) return 0;
  else if (poti < 880) return 119;
  else if (poti == 880) return 0;
  else if (poti < 915) return 149;
  else if (poti == 915) return 0;
  else if (poti < 950) return 186;
  else if (poti == 950) return 0;
} 

void setup()
{
  int     poti    = 0;
  pinMode(write_pin,   OUTPUT);   // sets the pin as output
  pinMode(trigger_pin, INPUT_PULLUP);

  poti  = analogRead(read_pin);

  if (poti <= 950) {
    analogWrite(write_pin,255);
    delay(get_motor(poti)*6);
  }
  else {
    beep(2);
  }
}

void loop() {
  int     poti    = 0;
  int motor = 0;

  poti = analogRead(read_pin);

  if (poti <= 950) {
    if (digitalRead(trigger_pin) == false) was_low = true;
    if (digitalRead(trigger_pin) && was_low) {
      analogWrite(write_pin,255);
      delay(45);
      was_low = false;
    }
    motor=get_motor(poti);
    analogWrite(write_pin, motor);
    if (!motor) delay(200);
  }
  else {
    if (digitalRead(trigger_pin) == false && was_low == false) {
      analogWrite(write_pin,255);
      last_trigger_time = millis() - last_trigger;            // calculate milliseconds betwen this trigger pull and the last one
      if (last_trigger_time > 5000) {
        delay(200);
      }
      else {
        delay((last_trigger_time / 50));                        // Run motor dependend on guessed remaining flywheel speed, and mode
      }
      analogWrite(write_pin,motor_normal_speed);
      was_low = true;
    }
    else if (digitalRead(trigger_pin) && was_low) {
      last_trigger = millis();
      was_low = false;
      analogWrite(write_pin,0);
    }
  }
}
