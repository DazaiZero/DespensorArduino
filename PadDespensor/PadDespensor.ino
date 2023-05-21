#include <Nextion.h>

#include <qrcode.h>

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
  &page0,
  NULL
};


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

void btnSSCallback(void *ptr){
  Serial.println("Button S Pressed");
    uint16_t len;
    uint16_t number;
    NexButton *btn = (NexButton *)ptr;
    Serial.println("btnSSCallback");
    Serial.println("ptr=");
    Serial.println((uint32_t)ptr); 

}

void btnSXCallback(void *ptr){
  Serial.println("Button X Pressed");
  
}

void btnSXLCallback(void *ptr){
  Serial.println("Button XL Pressed");
  
}

void btnQ1Callback(void *ptr){
  Serial.println("Button 1 Pressed");
  
}

void btnQ2Callback(void *ptr){
  Serial.println("Button 2 Pressed");
  // Generate QR code image data
  
}

void btnQ3Callback(void *ptr){
  Serial.println("Button 3 Pressed");
  
}

void btnQ4Callback(void *ptr){
  Serial.println("Button 4 Pressed");
  
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

  nexInit();

  //page0.attachPush(pageCallback, &page0);
  page0.attachPop(pageCallback, &page0);

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

  Serial.print("bkcmd=3");
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);


  // Get and print the initial page ID
  Serial.print("Initial page ID: ");
  Serial.println(currentPageId);

    // Generate QR code image data
    String qrImageData = generateQRCode(qrData);

    // Set QR code data to the Nextion QR code component on page 5
    qrText.setText(qrData.c_str());
  
  Serial.println("setup done"); 
}


void loop() {
  nexLoop(nex_listen_list);
  uint8_t currentPageId = currentPageId;

  // Print the current page ID
  Serial.print("Current page ID: ");
  Serial.println(currentPageId);

  // Other code logic here...

  delay(1000);
}

