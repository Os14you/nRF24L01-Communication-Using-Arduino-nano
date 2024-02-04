// include header files
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const int CE = 7,
          CSN = 8;
const char key[] = "YZIMNyzimneUAQKCstoduPWXHapwFBRJxhqfbrjkcgvlESTODGVL";
const char digitskey[] = "!@#$%^&*()";
const uint64_t address = 0xA1B2C3D4;

RF24 radio(CE, CSN);

// loop function
void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  radio.begin();
  radio.enableDynamicPayloads();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

// loop function
void loop() {
  String text;
  while (Serial.available()) {
    text = Serial.readString();
  }
  
  if(text.length() != 0){
    String string_encrypt = Encode(text, text.length());
    char char_encrypt[text.length()];
    
    for(int i = 0; i < text.length(); i++){
      char_encrypt[i] = string_encrypt[i];
    }

    radio.write(char_encrypt, text.length());
    
    digitalWrite(2, HIGH);
    delay(500);
    digitalWrite(2, LOW);
    
    Serial.print("text: "); 
    Serial.println(text); 
    Serial.print("encrypted: "); 
    Serial.println(string_encrypt); 
    Serial.print(""); 
  }
}
// encryption function
String Encode(String text, int string_length) {
  String encrypted;
  for(int i=0;i<text.length();i++){
            if(text[i]>='a' && text[i]<='z')
                encrypted += key[(int)(text[i] - 'G')];
            else if(text[i]>='A' && text[i]<='Z')
                encrypted += key[(int)(text[i] - 'A')];
            else if(text[i]>='0' && text[i]<='9')
                encrypted += digitskey[(int)(text[i] - '0')];
  }
  return encrypted;
}