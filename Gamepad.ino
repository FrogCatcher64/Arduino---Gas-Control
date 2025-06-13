``` #include <PS2X_lib.h>  // PS2X v1.6

// definicje pinów 
#define PS2_DAT   12  // MISO → Arduino D12
#define PS2_CMD   11  // MOSI → Arduino D11
#define PS2_SEL   10  // CS   → Arduino D10
#define PS2_CLK   13  // SCK  → Arduino D13


// #define PS2_SEL 10
// #define PS2_ATT 9
// #define PS2_CLK 13
// #define PS2_CMD 11
// #define PS2_DAT 12

// tryby
#define pressures true    // true = odczyt analogowych sił przycisków
#define rumble    false   // true = wibracje

PS2X ps2x;

int error = 0;
byte type  = 0;

void setup(){
  Serial.begin(57600);
  delay(300);  // czas na rozruch modułu

  // inicjalizacja: clock, command, select, data, pressures?, rumble?
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

  if (error == 0) {
    Serial.println("Pad OK");
    Serial.print("pressures = ");  Serial.println(pressures ? "true" : "false");
    Serial.print("rumble    = ");  Serial.println(rumble    ? "true" : "false");
  }
  else if (error == 1) Serial.println("Brak kontrolera");
  else if (error == 2) Serial.println("Kontroler nie akceptuje polecen");
  else if (error == 3) Serial.println("Brak trybu pressures");
  
  // jaka wersja pada?
  type = ps2x.readType();
  switch(type) {
    case 0: Serial.println("Nieznany pad"); break;
    case 1: Serial.println("DualShock");     break;
    case 2: Serial.println("GuitarHero");    break;
    case 3: Serial.println("DualShock Wireless"); break;
  }
}

void loop() {

  ps2x.read_gamepad(false, 0);

  if (ps2x.Button(PSB_CROSS)) {
    Serial.println("Przycisk X wciśnięty");
  }
  if (ps2x.Button(PSB_CIRCLE)) {
    Serial.println("Przycisk O wciśnięty");
  }
  if (ps2x.Button(PSB_TRIANGLE)) {
    Serial.println("Przycisk Δ wciśnięty");
  }
  if (ps2x.Button(PSB_SQUARE)) {
    Serial.println("Przycisk □ wciśnięty");
  }



  if (ps2x.Button(PSB_PAD_UP)) {
    Serial.println("PAD UP");
  }
  if (ps2x.Button(PSB_PAD_RIGHT)) {
    Serial.println("PAD RIGHT");
  }
  if (ps2x.Button(PSB_PAD_DOWN)) {
    Serial.println("PAD DOWN");
  }
  if (ps2x.Button(PSB_PAD_LEFT)) {
    Serial.println("PAD LEFT");
  }


  if (ps2x.Button(PSB_L2)) {
    Serial.println("L2");
  }
  if (ps2x.Button(PSB_R2)) {
    Serial.println("R2");
  }
  if (ps2x.Button(PSB_L1)) {
    Serial.println("L1");
  }
  if (ps2x.Button(PSB_R1)) {
    Serial.println("R1");
  }

  if (ps2x.Button(PSB_SELECT)) {
    Serial.println("SELECT");
  }
  if (ps2x.Button(PSB_START)) {
    Serial.println("START");
  }
  if (ps2x.Button(PSB_L3)) {
    Serial.println("L3");
  }
  if (ps2x.Button(PSB_R3)) {
    Serial.println("R3");
  }


  int lx = ps2x.Analog(PSS_LX);
  int ly = ps2x.Analog(PSS_LY);
  int rx = ps2x.Analog(PSS_RX);
  int ry = ps2x.Analog(PSS_RY);

  Serial.print("LX: "); Serial.print(lx);
  Serial.print("  LY: "); Serial.print(ly);
  Serial.print("  RX: "); Serial.print(rx);
  Serial.print("  RY: "); Serial.println(ry);
  delay(1000);
}

```