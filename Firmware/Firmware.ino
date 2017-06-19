//Use somente NEWLINE (\n) nos Terminais

#include <SoftwareSerial.h>

SoftwareSerial virtualSerial(10,11); //RX, TX

int terminalNum = 1;
char yourName[60];
int contLetter = 0;

void setup(){
  Serial.begin(9600);
  while(!Serial){}

  virtualSerial.begin(9600);
  virtualSerial.print("Terminal ");
  virtualSerial.print(terminalNum);
  virtualSerial.print(" iniciado!\n");

  Serial.print("Digite o seu nome: ");
  while(true){
    if(Serial.available()){
      char bufLetra = Serial.read();
      yourName[contLetter] = bufLetra;
      if(bufLetra == '\n' || bufLetra == '\r'){
        yourName[contLetter] = '\0';
        break;
      }
      contLetter++;
    }
  }
  Serial.println();
  Serial.print("Seja bem vindo ");
  Serial.println(yourName);
  virtualSerial.println();
  virtualSerial.print(yourName);
  virtualSerial.println(" acabou de se conectar!");
}

void loop() {
  if(virtualSerial.available()){
    Serial.write(virtualSerial.read());
  }
  if(Serial.available()){
    virtualSerial.write(yourName);
    virtualSerial.write(" disse : ");
    Serial.write("Voce disse : ");
    while(Serial.available()){
      char bufLetter = Serial.read();
      virtualSerial.write(bufLetter);
      Serial.write(bufLetter);
    }
  }
}
