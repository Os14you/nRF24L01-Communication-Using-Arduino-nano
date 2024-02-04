#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const int CE = 7,
          CSN = 8;

const char strkey[] = "YZIMNyzimneUAQKCstoduPWXHapwFBRJxhqfbrjkcgvlESTODGVL";
const char digitsKey[] = "!@#$%^&*()";
const char alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const uint64_t address = 0xA1B2C3D4;

RF24 radio(CE, CSN);

// setup function
void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  radio.begin();
  radio.enableDynamicPayloads();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  delay(2500);
}

// loop function
void loop() {
  if (radio.available()) {
    uint8_t len = radio.getDynamicPayloadSize();
    char encrypted[len];
    
    radio.read(&encrypted, len);
    String text = Decode(encrypted, len);
    encrypted[len]='\0';
    Serial.print("text: "); 
    Serial.println(text); 
    Serial.print("encrypted massage: "); 
    Serial.println(encrypted); 
    Serial.print(""); 
  } 
}

// decryption function
String Decode(char encrypted[], int string_length){
  String text;
  for(int i=0;i<string_length;i++){ 
    if     (encrypted[i]>='A' && encrypted[i]<='z'){ for(int j=0;;j++){ if(strkey[j]   == encrypted[i]){ text += alpha[j]  ;break; }}}
    else if(encrypted[i]>='0' && encrypted[i]<='9'){ for(int j=0;;j++){ if(digitsKey[j]== encrypted[i]){ text += ('0' + j) ;break; }}}
  }
  return text;
}