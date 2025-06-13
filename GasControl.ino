 #include <PS2X_lib.h>  // PS2X v1.6
#include <SPI.h>

// PS2 pad
#define PS2_DAT  c:\Users\sonia\Desktop\GasControl\Gamepad.ino 12
#define PS2_CMD   11
#define PS2_SEL   10
#define PS2_CLK   13
#define pressures true
#define rumble    false

// Digital Potentiometer (AD5206)
#define POT_CS    9     // dowolny wolny pin cyfrowy

PS2X ps2x;
int error = 0;
byte type  = 0;

void setup() {
  Serial.begin(57600);
  delay(300);

  // Inicjalizacja SPI dla potencjometru
  pinMode(POT_CS, OUTPUT);
  digitalWrite(POT_CS, HIGH);
  SPI.begin();

  // Inicjalizacja pada PS2
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  if (error == 0) {
    Serial.println("Pad OK");
  } else if (error == 1) {
    Serial.println("Brak kontrolera");
  } else if (error == 2) {
    Serial.println("Kontroler nie akceptuje polecen");
  } else if (error == 3) {
    Serial.println("Brak trybu pressures");
  }

  type = ps2x.readType();
  switch(type) {
    case 0: Serial.println("Nieznany pad"); break;
    case 1: Serial.println("DualShock"); break;
    case 2: Serial.println("GuitarHero"); break;
    case 3: Serial.println("DualShock Wireless"); break;
  }
}

// Wysyła przez SPI komendę do AD5206:
//  - channel: 0–7
//  - value:   0–255
void potWrite(uint8_t channel, uint8_t value) {
  if (channel > 7) return;
  digitalWrite(POT_CS, LOW);
  SPI.transfer(channel & 0x07);
  SPI.transfer(value);
  digitalWrite(POT_CS, HIGH);
}

void loop() {
  ps2x.read_gamepad(false, 0);

  uint8_t ly = ps2x.Analog(PSS_LY);
  const uint8_t MID = 127;
  const uint8_t DEADZONE = 10;

  if (abs((int)ly - MID) > DEADZONE) {
    if (ly < MID) {
      // Gałka w górę
      uint8_t value = map(MID - ly, 0, MID - DEADZONE, 0, 255);
      potWrite(0, value);
    } else {
      // Gałka w dół – wyjście 0
      potWrite(0, 0);
    }
  } else {
    // Pozycja neutralna
    potWrite(0, 0);
  }

  delay(20);
}
 