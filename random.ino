#include <TrueRandom.h>
char input;
String command;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
  ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("init");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    input = Serial.read();
    switch(input){
      case '\n':
        executeCommand();
        command = "";
      default:
        if(input != '\n'){
        command += input;}
      break;
    }
  }
}

void executeCommand(){
    if(command.endsWith("bit")){
      Serial.print(TrueRandom.randomBit());
    }
    else if (command.endsWith("byte")){
      Serial.print(TrueRandom.randomByte());
    }
    else if (command.startsWith("range")){
      // Serializing range command:
      // \nrange{size1}{size2}{num1}{num2}
      // e.g. range135593
      int size1 = String(command.charAt(5)).toInt();
      int size2 = String(command.charAt(6)).toInt();
      int r1;
      int r2;
      if(size1>1){
        r1 = String(command.substring(7, 7+size1)).toInt();}
      else{
        r1 = String(command.charAt(7)).toInt();
      }
      if(size2>1){
        r2 = String(command.substring(7+size1, 7+size1+size2)).toInt();}
      else{
        r2 = String(command.charAt(7+size1)).toInt();
      }
      Serial.print(TrueRandom.random(r1,r2));
      
    }
    else{
      Serial.println(command);
    }
  }
