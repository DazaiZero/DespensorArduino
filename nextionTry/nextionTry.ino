void setup(){
  Serial.begin(9600);
  Serial.println(" Started ");
}

void loop(){
  if(Serial.available()){
    String data_From_display = "";
    delay(30);
    while(Serial.available()){
      data_From_display += char(Serial.read());
    }
    Serial.println(data_From_display);
    sendData(data_From_display);
  }
}

void sendData(String data_from_Dis){
  Serial.println("data from dis");
  Serial.println(data_from_Dis);
}