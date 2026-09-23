
// ============================================================
// Walking Pad Custom Remote - 3-Button Controller
// Address: 0x03
// Power:   0x82
// Speed +: 0x8A
// Speed -: 0x86
// ============================================================

#define IR_SEND_PIN 4
#include <IRremote.hpp>

// Button Pin Definitions
#define BTN_SPEED_DOWN 2
#define BTN_POWER      3
#define BTN_SPEED_UP   5

// Walking Pad IR Codes
const uint8_t TARGET_ADDRESS = 0x03;
const uint8_t CMD_POWER      = 0x82;
const uint8_t CMD_SPEED_UP   = 0x8A;
const uint8_t CMD_SPEED_DOWN = 0x86;

void setup() {
  Serial.begin(115200);

  // Configure buttons with internal pull-up resistors
  pinMode(BTN_POWER, INPUT_PULLUP);
  pinMode(BTN_SPEED_UP, INPUT_PULLUP);
  pinMode(BTN_SPEED_DOWN, INPUT_PULLUP);

  // Initialize the IR transmitter on D4
  IrSender.begin(IR_SEND_PIN);

  Serial.println(F("=== Walking Pad 3-Button Controller Ready ==="));
  Serial.println(F("D3: Power Toggle (0x82)"));
  Serial.println(F("D5: Speed +      (0x8A)"));
  Serial.println(F("D2: Speed -      (0x86)"));
}

void sendCommand(uint8_t command, const char* label) {
  Serial.print(F("Sending "));
  Serial.print(label);
  Serial.print(F(" [0x"));
  Serial.print(command, HEX);
  Serial.println(F("]"));

  // Send single frame without repeat pulse
  IrSender.sendNEC(TARGET_ADDRESS, command, 0);

  // Brief delay to prevent double-triggering
  delay(300);
}

void loop() {
  // Check Power Button (D3)
  if (digitalRead(BTN_POWER) == LOW) {
    sendCommand(CMD_POWER, "POWER");
    while (digitalRead(BTN_POWER) == LOW) { delay(10); } // Wait for release
  }

  // Check Speed Up Button (D5)
  if (digitalRead(BTN_SPEED_UP) == LOW) {
    sendCommand(CMD_SPEED_UP, "SPEED +");
    while (digitalRead(BTN_SPEED_UP) == LOW) { delay(10); } // Wait for release
  }

  // Check Speed Down Button (D2)
  if (digitalRead(BTN_SPEED_DOWN) == LOW) {
    sendCommand(CMD_SPEED_DOWN, "SPEED -");
    while (digitalRead(BTN_SPEED_DOWN) == LOW) { delay(10); } // Wait for release
  }
}
