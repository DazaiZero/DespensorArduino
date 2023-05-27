#include <Nextion.h>

#include <qrcode.h>

int coinPin = 4;
int coinVal = 1;
int mot1pin = 8;
int mot2pin = 7;
uint8_t sizeSelected = 0;
uint8_t coinInserted = 0;
uint8_t upiDone = 0;
uint8_t qSelected = 0;
uint8_t fRenter = 0;
bool pageChanged = true;
char data;

NexButton btnStart = NexButton(0, 5, "btnStart"); 
NexButton btnSS = NexButton(1, 3, "btnS");
NexButton btnSX = NexButton(1, 4, "btnX");
NexButton btnSXL = NexButton(1, 5, "btnXL");
NexPage page0 = NexPage(5, 0, "page0");

  //NexText qrImage = NexText(5, 5, "qr0");

NexText qrText = NexText(5, 5, "qr0");

String qrData = "Hello, World!";


uint8_t currentPageId = 0;

NexButton btnQ1 = NexButton(2, 8, "btnQ1");
NexButton btnQ2 = NexButton(2, 6, "btnQ2");
NexButton btnQ3 = NexButton(2, 5, "btnQ3");
NexButton btnQ4 = NexButton(2, 7, "btnQ4");
NexButton btnRenter = NexButton(2, 3, "btnRenter");
NexButton btnBack = NexButton(2, 4, "btnBack");

NexButton btnCoin = NexButton(3, 3, "btnCoin");

char buffer[100] = {0};

NexTouch *nex_listen_list[] = {
  &btnStart,
  &btnSS,
  &btnSX,
  &btnSXL,
  &btnQ1,
  &btnQ2,
  &btnQ3,
  &btnQ4,
  &btnRenter,
  &btnBack,
  &btnCoin,
  &page0,
  NULL
};

void(* resetFunc) (void) = 0;  // declare reset fuction at address 0

String generateQRCode(String data) {
  QRCode qrcode;
  uint8_t qrcodeData[qrcode_getBufferSize(3)];
  qrcode_initText(&qrcode, qrcodeData, 3, 0, data.c_str());

  String imageData = "";
  for (int y = 0; y < qrcode.size; y++) {
    for (int x = 0; x < qrcode.size; x++) {
      if (qrcode_getModule(&qrcode, x, y)) {
        imageData += "1";
      } else {
        imageData += "0";
      }
    }
  }

  return imageData;
}



void btnStartCallback(void *ptr){
  Serial.println("Button Start Pressed");
  
}

void btnCoinCallback(void *ptr){
  Serial.println("Button Coin Pressed");
  pageChanged = true;
}

void btnSSCallback(void *ptr){
  Serial.println("Button S Pressed");
  sizeSelected = 1;

}

void btnSXCallback(void *ptr){
  Serial.println("Button X Pressed");
  sizeSelected = 2;

}

void btnSXLCallback(void *ptr){
  Serial.println("Button XL Pressed");
  sizeSelected = 3;

}

void btnQ1Callback(void *ptr){
  Serial.println("Button 1 Pressed");
  qSelected = 1;
}

void btnQ2Callback(void *ptr){
  Serial.println("Button 2 Pressed");
  // Generate QR code image data
  qSelected = 2;
}

void btnQ3Callback(void *ptr){
  Serial.println("Button 3 Pressed");
  qSelected = 3;
}

void btnQ4Callback(void *ptr){
  Serial.println("Button 4 Pressed");
  qSelected = 4;
}

void btnRenterCallback(void *ptr){
  Serial.println("Button Re-Enter Pressed");
  
}

void btnBackCallback(void *ptr){
  Serial.println("Button Back Pressed");
  
}

void pageCallback(void *ptr) {
  // Get the page object
  Serial.println("Page Event Pressed");
  NexPage *page = (NexPage *)ptr;

  // Get the page ID
  //currentPageId = page->getID();

  // Check if the program is first initialized on page 5
  //if (currentPageId == 5) {
    // Generate QR code image data
    String qrImageData = generateQRCode(qrData);

    // Set QR code data to the Nextion QR code component on page 5
    qrText.setText(qrData.c_str());
    page0.show();
  //}
}

void setup() {

  Serial.begin(9600);
  pinMode(coinPin, INPUT);
  pinMode(mot1pin, OUTPUT);
  pinMode(mot2pin, OUTPUT);

  nexInit();

  //page0.attachPush(pageCallback, &page0);
  page0.attachPop(pageCallback, &page0);
  btnCoin.attachPop(btnCoinCallback,&btnCoin);
  btnSS.attachPop(btnSSCallback, &btnSS);
  btnStart.attachPop(btnStartCallback, &btnStart);
  btnSX.attachPop(btnSXCallback, &btnSX);
  btnSXL.attachPop(btnSXLCallback, &btnSXL);
  btnQ1.attachPop(btnQ1Callback, &btnQ1);
  btnQ2.attachPop(btnQ2Callback, &btnQ2);
  btnQ3.attachPop(btnQ3Callback, &btnQ3);
  btnQ4.attachPop(btnQ4Callback, &btnQ4);
  btnRenter.attachPop(btnRenterCallback, &btnRenter);
  btnBack.attachPop(btnBackCallback, &btnBack);

  digitalWrite(mot1pin, LOW);
	digitalWrite(mot2pin, LOW);

  // Get and print the initial page ID
  Serial.print("Initial page ID: ");
  Serial.println(currentPageId);

    // Generate QR code image data
    String qrImageData = generateQRCode(qrData);

    // Set QR code data to the Nextion QR code component on page 5
    qrText.setText(qrData.c_str());
  
  Serial.println("setup done"); 
}

void despense(){
  analogWrite(mot1pin, 255);
	analogWrite(mot2pin, 255);
  // Turn on motor A & B
  Serial.println("qSelected");
  Serial.println(qSelected);
  digitalWrite(mot1pin, LOW);
	digitalWrite(mot2pin, LOW);
  delay(200);
  if(qSelected == 1){
	  digitalWrite(mot1pin, HIGH);
	  digitalWrite(mot2pin, LOW);
	  delay(4000);
  }else if(qSelected == 2){
	  digitalWrite(mot1pin, HIGH);
	  digitalWrite(mot2pin, HIGH);
	  delay(4000);
  }else if(qSelected == 3){
    digitalWrite(mot1pin, HIGH);
	  digitalWrite(mot2pin, HIGH);
	  delay(4000);
    digitalWrite(mot1pin, LOW);
	  digitalWrite(mot2pin, LOW);
	  delay(2000);
    digitalWrite(mot1pin, LOW);
	  delay(4000);
  }else if(qSelected == 4){
    digitalWrite(mot1pin, HIGH);
	  digitalWrite(mot2pin, HIGH);
	  delay(4000);
    digitalWrite(mot1pin, LOW);
	  digitalWrite(mot2pin, LOW);
	  delay(200);
    digitalWrite(mot1pin, HIGH);
	  digitalWrite(mot2pin, HIGH);
	  delay(4000);
    digitalWrite(mot1pin, LOW);
	  digitalWrite(mot2pin, LOW);
	  delay(200);
  }
	// Turn off motors
	digitalWrite(mot1pin, LOW);
	digitalWrite(mot2pin, LOW);
}

void loop() {
  nexLoop(nex_listen_list);

  coinVal = digitalRead(coinPin);
  //Serial.println(coinVal);
  
  if(coinVal == 0){
    //Serial.println(coinVal);
    if(pageChanged){
      Serial.println(pageChanged);
      delay(500);
      despense();
      delay(200);
      Serial.print("page 6");
      Serial.write(0xFF);
      Serial.write(0xFF);
      Serial.write(0xFF);
      delay(200);
      Serial.print("page 6");
      Serial.write(0xFF);
      Serial.write(0xFF);
      Serial.write(0xFF);
       //pageChanged = false;
      delay(10000);
      resetFunc(); //call reset
    } 
  }

}




