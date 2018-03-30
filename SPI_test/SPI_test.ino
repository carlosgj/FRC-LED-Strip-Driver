#include <SPI.h>

char commandString[5];
unsigned char i = 0;
boolean commandComplete = false;

void setup() {
  SPI.begin();
  Serial.begin(115200);
  Serial.println("Starting...");
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
}

void loop() {
  if (Serial.available()) {
    commandString[i] = Serial.read();
    if (commandString[i] == '\n' || i>=4) {
      commandComplete = true;
    }
    i++;
  }
  if (commandComplete) {
    i--;
    Serial.print("Got string \"");
    for (unsigned char j = 0; j < i; j++) {
      Serial.print(commandString[j]);
    }
    Serial.print('"');
    Serial.println();

    char commandChar = commandString[0];
    if(commandChar == 'R' || commandChar == 'G' || commandChar == 'B' ||
    commandChar == 'r' || commandChar == 'g' || commandChar == 'b' ||
    commandChar == 'P'){
      commandString[i+1] = 0;
      commandString[0] = commandString[1];
      commandString[1] = commandString[2];
      commandString[2] = commandString[3];
      commandString[3] = commandString[4];
      //Serial.print("Number string: ");
      //Serial.println(commandString);
      unsigned char value = atoi(commandString);
      Serial.print("Parsed number: ");
      Serial.println(value);
      digitalWrite(2, LOW);
      SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE3));
      SPI.transfer((unsigned char)commandChar);
      SPI.endTransaction();
      digitalWrite(2, HIGH);
      delayMicroseconds(5);
      digitalWrite(2, LOW);
      SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE3));
      SPI.transfer(value);
      SPI.endTransaction();
      digitalWrite(2, HIGH);
    }
else{
  Serial.println("Invalid command.");
}
    
    i = 0;
    commandComplete = false;
  }
}
