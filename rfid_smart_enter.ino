#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);

int BUZZ_PIN = 3;
int RELAY_PIN = 5;
int SUCCESS_LED = 7;
int ERROR_LED = 6;

void setup() {
  pinMode(SUCCESS_LED, OUTPUT);
  pinMode(ERROR_LED, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
  SPI.begin();
  mfrc522.PCD_Init();
}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent())
    return;

  // чтение
  if ( !mfrc522.PICC_ReadCardSerial())
    return;

  view_data(mfrc522.uid.uidByte, mfrc522.uid.size);
}


void check_data(int card_id){
  card_id == 105 ? success() : error();
}

void view_data (byte *buf, size_t size) {
  check_data(buf[1]);
}

void success(){
  digitalWrite(SUCCESS_LED, HIGH);
  tone(BUZZ_PIN, 1500, 500);
  delay(100);
  tone(BUZZ_PIN, 1000, 500);
  delay(100);
  tone(BUZZ_PIN, 1200, 500);
  delay(100);
  tone(BUZZ_PIN, 1500, 500);
  delay(1000);
  digitalWrite(SUCCESS_LED, LOW);
  digitalWrite(RELAY_PIN, LOW);
  delay(5000);
  digitalWrite(RELAY_PIN, HIGH);
  tone(BUZZ_PIN, 100, 500);
}

void error(){
  digitalWrite(ERROR_LED, HIGH);
  tone(BUZZ_PIN, 100, 500);
  delay(1000);
  digitalWrite(ERROR_LED, LOW);
}
