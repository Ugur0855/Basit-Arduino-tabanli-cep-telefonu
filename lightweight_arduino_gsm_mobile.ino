/*********************************************************************
PROJECT      : Simple-Arduino-Based-Mobile-Phone
Uğur
*********************************************************************/

//#include <SoftwareSerial.h>
#include <EEPROM.h>
#include <String.h>


//SoftwareSerial nextionSerial(2,3); //Rx, Tx
char msisdn[30], ATcomm[30];

char isimDizisi[50], noDizisi[50];
String rawMsg, pageNum, msg, pls;
int  bellektekiKisiSayisi;

//////////////////////////////////////////////////////////////////////////////////////////
void writeString(String stringData){
//Function to send commands to the Nextion display.
  for(int i=0; i < stringData.length(); i++){
    Serial2.write(stringData[i]);
    delay(10);
    }
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
void ekranaYaz(String ad, String numara, int contactSayisi){
  Serial.println(F("contactSayisi(ekranaYaz):"));
  Serial.println(contactSayisi);
  delay(50);
  String adString, noString;
  
    if(contactSayisi==0){
      Serial.println(F("Kişi yok:"));
    }
    else if(contactSayisi==1){
      Serial.println(F("Kişi 1(ekranaYaz):"));
      adString= "page4.t1.txt=";
      noString="page4.t2.txt=";
    }else if(contactSayisi==2){
      Serial.println(F("Kişi 2(ekranaYaz):"));
      adString= "page4.t6.txt=";
      noString="page4.t7.txt=";
    }else if(contactSayisi==3){
      Serial.println(F("Kişi 3(ekranaYaz):"));
      adString="page4.t11.txt=";
      noString="page4.t12.txt=";
    }
    
    Serial.println(F("lalala"));
    adString.concat('"');   
    delay(10);
    adString.concat(ad);
    delay(10);
    adString.concat('"');   
    delay(10);
    Serial.println(F("adString:"));   
    Serial.println(adString);
    writeString(adString);
    delay(50);
    
    noString.concat('"');
    delay(10);
    noString.concat(numara);
    delay(10);
    noString.concat('"');      
    delay(10);
    Serial.println(F("noString:"));
    Serial.println(noString);
    writeString(noString);
    delay(50);
}
//////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////
void setup2(int kisisayi){
  
  Serial.println(F("kisisayi(setup2): "));
  Serial.println(kisisayi);

  String ismi="";
  String numarasi="";

  int kisiAdresi, numaraAdresi;
  int max=50;
  int len=0;
  unsigned char k="";
  unsigned char m="";

  switch(kisisayi){
    case 0: 
      Serial.println(F("Rehbere henüz hiçbir kişi kaydedilmedi."));
      break;
    case 1:
      Serial.println(F("Rehberde 1 kişi var."));
      kisiAdresi=0; 
      numaraAdresi=20;
      break;
    case 2:
      Serial.println(F("Rehberde 2 kişi var."));
      kisiAdresi=40; 
      numaraAdresi=60;   
      break;
    case 3:
      Serial.println(F("Rehberde 3 kişi var."));
      kisiAdresi=80; 
      numaraAdresi=100; 
      break;
  }
  k=(char)EEPROM.read(kisiAdresi);
  delay(50);
  while(k != '\0' && len<50)   //Read until null character
  {    
    k=(char)EEPROM.read(kisiAdresi+len);
    delay(10);
    isimDizisi[len]=k;
    len++;
  }
  
  isimDizisi[len]='\0';
  ismi = String(isimDizisi);

  len=0;
      
  m=(char)EEPROM.read(numaraAdresi);
  Serial.println(F("m(numara adresi):"));
  Serial.println((int)m);
  delay(50);
  while(m!= '\0' && len<numaraAdresi)
  {
    m=(char)EEPROM.read(numaraAdresi+len);
    Serial.println(F("m(numara adresi+len):"));
    Serial.println((int)m);
    delay(50);
    noDizisi[len]=m;
    len++;
  }
  noDizisi[len]='\0';
  numarasi = String(noDizisi);

  Serial.println(F("ekranaYaz fonsiyonuna girecek veriler:"));
  Serial.println(F("ismi:"));
  Serial.println(ismi);
  Serial.println(F("numarasi:"));
  Serial.println(numarasi);
  
  ekranaYaz(ismi, numarasi, kisisayi);
  
  k="";
  m="";
  ismi="";
  numarasi="";

  memset(isimDizisi, '\0', 50);
  memset(noDizisi, '\0', 50);
  
}      


/////////////////////////////////////////////////////////////////////////////////////
//*******************************************************************************
/////////////////////////////////////////////////////////////////////////////////////


void setup(){
//Initialize HardwareSerial|SoftwareSerial|GSM module|Nextion display. Perform GSM Location Update.
 
  Serial.begin(9600);
  Serial2.begin(9600); 
  
  
  while(!Serial){
    ;
    }
  power_on();
  delay(3000);
  

  delay(50);
  Serial.println(F("0-20 ADRESLERİ:"));
  Serial.println((char)EEPROM.read(0));
  delay(10);
  Serial.println((char)EEPROM.read(1));
  delay(10);
  Serial.println((char)EEPROM.read(2));
  delay(10);
  Serial.println((char)EEPROM.read(3));
  delay(10);
  Serial.println((char)EEPROM.read(4));
  delay(10);
  Serial.println((char)EEPROM.read(5));
  delay(10);
  Serial.println((char)EEPROM.read(6));
  delay(10);
  
  Serial.println(F("20-40 ADRESLERİ:"));
  Serial.println((char)EEPROM.read(20));
  delay(10);
  Serial.println((char)EEPROM.read(21));
  delay(10);
  Serial.println((char)EEPROM.read(22));
  delay(10);
  Serial.println((char)EEPROM.read(23));
  delay(10);
  Serial.println((char)EEPROM.read(24));
  delay(10);
  Serial.println((char)EEPROM.read(25));
  delay(10);


  Serial.println(F("40-60 ADRESLERİ:"));
  Serial.println((char)EEPROM.read(40));
  delay(10);
  Serial.println((char)EEPROM.read(41));
  delay(10);
  Serial.println((char)EEPROM.read(42));
  delay(10);
  Serial.println((char)EEPROM.read(43));
  delay(10);
  Serial.println((char)EEPROM.read(44));
  delay(10);
  Serial.println((char)EEPROM.read(45));
  delay(10);

  Serial.println(F("60-80 ADRESLERİ:"));
  Serial.println((char)EEPROM.read(60));
  delay(10);
  Serial.println((char)EEPROM.read(61));
  delay(10);
  Serial.println((char)EEPROM.read(62));
  delay(10);
  Serial.println((char)EEPROM.read(63));
  delay(10);
  Serial.println((char)EEPROM.read(64));
  delay(10);
  Serial.println((char)EEPROM.read(65));
  delay(10);


  Serial.println("80-100 ADRESLERİ:");
  Serial.println((char)EEPROM.read(80));
  delay(10);
  Serial.println((char)EEPROM.read(81));
  delay(10);
  Serial.println((char)EEPROM.read(82));
  delay(10);
  Serial.println((char)EEPROM.read(83));
  delay(10);
  Serial.println((char)EEPROM.read(84));
  delay(10);
  Serial.println((char)EEPROM.read(85));
  delay(10);

  Serial.println("100-120 ADRESLERİ:");
  Serial.println((char)EEPROM.read(100));
  delay(10);
  Serial.println((char)EEPROM.read(101));
  delay(10);
  Serial.println((char)EEPROM.read(102));
  delay(10);
  Serial.println((char)EEPROM.read(103));
  delay(10);
  Serial.println((char)EEPROM.read(104));
  delay(10);
  Serial.println((char)EEPROM.read(105));
  delay(10);

  bellektekiKisiSayisi=EEPROM.read(400);

  Serial.println(F("BellektekiKisiSayisi(setup):"));
  Serial.println(bellektekiKisiSayisi);

  int bellekKisi2=bellektekiKisiSayisi;
  int i;
  
  for(i=0; i<bellektekiKisiSayisi; i++){
    setup2(bellekKisi2);
    bellekKisi2--;
    Serial.println(F("bellekKisi2(setup for un içi):"));
    Serial.println(bellekKisi2);
  }
    //Serial.println(F("bellekKisi2(setup for un dışı):"));
    //Serial.println(bellekKisi2);
}
 
////////////////////////////////////////////////////////////////////////////////////////////////////

void loop(){
  
  while(Serial2.available()){
    rawMsg.concat(char(Serial2.read()));//Read the SoftwareSerial.
    }
    delay(10); 
    if(rawMsg!=""){
      Serial.println(F("Ham veri:"));
      Serial.println(rawMsg);
    }
    delay(200);
  if(!Serial2.available()){                   
    if(rawMsg.length()){
      if((rawMsg[rawMsg.length()-4]=='0') && (rawMsg[rawMsg.length()-5]=='1')){ 
        //Eğer sayfa 10 daki Contact ADD dan veri gelirse sayfa numarasını 10 yapar.
        pageNum = "10";//Read Nextion: get the page number.
        Serial.println(F("Kişi eklendi. PageNum=10"));
      }
      else {
        pageNum = rawMsg[rawMsg.length()-4];//Read Nextion: get the page number.
        Serial.println(F("PageNum=Sondan 4.cü sayı."));
        Serial.println(F("pageNum:"));
        Serial.println(pageNum);
      }
    delay(50);
    if(pageNum=="10"){
      msg = rawMsg.substring(1, rawMsg.length()-5);           //Read Nextion: get the Raw Msges from Nextion.
    }
    else if(pageNum=="9"){
      msg = rawMsg.substring(1, rawMsg.length()-2);
    }
    else{
      msg = rawMsg.substring(1, rawMsg.length()-4);           //Read Nextion: get the Raw Msges from Nextion.
    }
    
    Serial.println(F("msg:"));
    Serial.println(msg);
    if((pageNum == "0") && (msg.length() != 0)){querySMS(msg);}   //Read Nextion: page0, Query all SMS from the GSM Buffer.
    if((pageNum == "1") && (msg.length() != 0)){connectCall(msg);}  //Read Nextion: page1, Dial and Call the B-number.
    if((pageNum == "2") && (msg.length() != 0)){releaseCall(msg);}  //Read Nextion: page2, Release the call.
    if((pageNum == "3") && (msg.length() != 0)){sendSMS(msg);}    //Read Nextion: Page3, Get the content typed in page 3 and send SMS.
    if((pageNum == "4") && (msg.length() != 0)){
      msg.remove(1);  
      Serial.println(F("msg(page4):"));
      Serial.println(msg);
      int msgInt=msg.toInt();
      switch(msgInt){
        int i;
        case 7:
          for(i=0; i<40; i++){
            EEPROM.write(i,0);
            }  
          break;
        case 8:
          for(i=40; i<80; i++){
            EEPROM.write(i,0);
            }  
          break;
        case 9:
          for(i=80; i<120; i++){
            EEPROM.write(i,0);
            }  
          break;
        }
      int a=EEPROM.read(400);
      Serial.println(F("a1"));
      Serial.println(a);
      a--;
      Serial.println(F("a2"));
      Serial.println(a);
      EEPROM.write(400,a);
      Serial.println(F("a3"));
      Serial.println(a);
      }
    if((pageNum == "5") && (msg.length() != 0)){answerCall(msg);}   //Read Nextion: page5, Answer Incoming calls.
    if((pageNum == "6") && (msg.length() != 0)){delReadSMS(msg);}     //Read Nextion: page6, Delete read SMS.
    if((pageNum == "7") && (msg.length() != 0)){delSMS(msg);}       //Read Nextion: page7, Delete all SMS (incl unread) from the GSM Buffer.
    if(msg == "de"){
      Serial.println(F("hafıza silinecek"));
      pinMode(13, OUTPUT);
      int i;
      for (i = 0 ; i < 401; i++){
        EEPROM.write(i, 0);
      }
      // turn the LED on and off 3 times when we're done
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
      delay(500);
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
      delay(500);
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
      Serial.println(F("hafıza silindi"));
      
      delay(50);
      Serial.println(F("0-20 ADRESLERİ:"));
      Serial.println((char)EEPROM.read(0));
      delay(10);
      Serial.println((char)EEPROM.read(1));
      delay(10);
      Serial.println((char)EEPROM.read(2));
      delay(10);
      Serial.println((char)EEPROM.read(3));
      delay(10);
      Serial.println((char)EEPROM.read(4));
      delay(10);
      Serial.println((char)EEPROM.read(5));
      delay(10);
      Serial.println((char)EEPROM.read(6));
      delay(10);
      
      Serial.println(F("20-40 ADRESLERİ:"));
      Serial.println((char)EEPROM.read(20));
      delay(10);
      Serial.println((char)EEPROM.read(21));
      delay(10);
      Serial.println((char)EEPROM.read(22));
      delay(10);
      Serial.println((char)EEPROM.read(23));
      delay(10);
      Serial.println((char)EEPROM.read(24));
      delay(10);
      Serial.println((char)EEPROM.read(25));
      delay(10);
    
      Serial.println(F("40-60 ADRESLERİ:"));
      Serial.println((char)EEPROM.read(40));
      delay(10);
      Serial.println((char)EEPROM.read(41));
      delay(10);
      Serial.println((char)EEPROM.read(42));
      delay(10);
      Serial.println((char)EEPROM.read(43));
      delay(10);
      Serial.println((char)EEPROM.read(44));
      delay(10);
      Serial.println((char)EEPROM.read(45));
      delay(10);
    
      Serial.println(F("60-80 ADRESLERİ:"));
      Serial.println((char)EEPROM.read(60));
      delay(10);
      Serial.println((char)EEPROM.read(61));
      delay(10);
      Serial.println((char)EEPROM.read(62));
      delay(10);
      Serial.println((char)EEPROM.read(63));
      delay(10);
      Serial.println((char)EEPROM.read(64));
      delay(10);
      Serial.println((char)EEPROM.read(65));
      delay(10);
      
      Serial.println(F("60-80 ADRESLERİ:"));
      Serial.println((char)EEPROM.read(60));
      delay(10);
      Serial.println((char)EEPROM.read(61));
      delay(10);
      Serial.println((char)EEPROM.read(62));
      delay(10);
      Serial.println((char)EEPROM.read(63));
      delay(10);
      Serial.println((char)EEPROM.read(64));
      delay(10);
      Serial.println((char)EEPROM.read(65));
      delay(10);

      Serial.println("80-100 ADRESLERİ:");
      Serial.println((char)EEPROM.read(80));
      delay(10);
      Serial.println((char)EEPROM.read(81));
      delay(10);
      Serial.println((char)EEPROM.read(82));
      delay(10);
      Serial.println((char)EEPROM.read(83));
      delay(10);
      Serial.println((char)EEPROM.read(84));
      delay(10);
      Serial.println((char)EEPROM.read(85));
      delay(10);
    
      Serial.println("100-120 ADRESLERİ:");
      Serial.println((char)EEPROM.read(100));
      delay(10);
      Serial.println((char)EEPROM.read(101));
      delay(10);
      Serial.println((char)EEPROM.read(102));
      delay(10);
      Serial.println((char)EEPROM.read(103));
      delay(10);
      Serial.println((char)EEPROM.read(104));
      delay(10);
      Serial.println((char)EEPROM.read(105));
      delay(10);

      EEPROM.write(400, 0);
      bellektekiKisiSayisi=EEPROM.read(400);
      Serial.println(F("bellektekiKisiSayisi(hafıza silindikten sonra):"));
      Serial.println(bellektekiKisiSayisi);
    }
    
    //if((pageNum == "8") && (msg.length() != 0)){contactReturn(msg);}
    if((pageNum == "9") && (msg.length() != 0)){
      Serial.println(F("msg(pageNum:9):"));
      Serial.println(msg);
      bellektekiKisiSayisi++;
      contactReturn(msg, bellektekiKisiSayisi);
    }
    
    if((pageNum == "10") && (msg.length() != 0)){
      Serial.println(F("bellektekiKisiSayisi:(if'in içi):"));
      Serial.println(bellektekiKisiSayisi);
      bellektekiKisiSayisi++;
      Serial.println(F("bellektekiKisiSayisi:(bellektekiKisiSayisi++; sonrası):"));
      Serial.println(bellektekiKisiSayisi);
      contactReturn(msg, bellektekiKisiSayisi);
      }
    rawMsg="";
    pageNum="";
    msg="";
    }
  }


  while(Serial.available()){
    pls=Serial.readString();//Read the HardwareSerial.
    Serial.println(F("pls:"));
    Serial.println(pls);
  }         
  if(!Serial.available() && pls.length()){
    if(pls.indexOf("NO CARRIER") != -1){                //Goto to page0, if B-party Hang up.
      String nextionCallStr = "page page0";
      writeString(nextionCallStr);
    sendATcommand("AT", "OK", 2000);    
    }
  if(pls.indexOf("BUSY") != -1){                    //Goto to page0, if B-Number rejects incoming calls.
      String nextionCallStr = "page page0";
      writeString(nextionCallStr);
    sendATcommand("AT", "OK", 2000);
  }
  if(pls.indexOf("NO ANSWER") != -1){                 //Goto to page0, if B-Number does not answer incoming calls.
      String nextionCallStr = "page page0";
      writeString(nextionCallStr);
    sendATcommand("AT", "OK", 2000);
  }   
    if(pls.indexOf("+CLIP") != -1){                   //Goto to page5, for any incoming calls.
    int msisdnFirstDelim = pls.indexOf("\"");
    int msisdnSeconddDelim = pls.indexOf("\"", msisdnFirstDelim+1);
    String mobNum = pls.substring(msisdnFirstDelim+1, msisdnSeconddDelim);
    String nextionCallStr = "page page5";
    writeString(nextionCallStr);
    nextionCallStr = "page5.t1.txt=\""+mobNum+"\"";
    writeString(nextionCallStr);
    nextionCallStr = "page5.t0.txt=\"Incoming Call\"";
    writeString(nextionCallStr);
    nextionCallStr = "page5.p0.pic=20";
    writeString(nextionCallStr);
    sendATcommand("AT", "OK", 2000);
    }
  if(pls.indexOf("+CMTI") != -1){                   //If new Msges|Query Msges|Display star picture.
    smsComputation();
    String nextionCallStr = "vis p2,1";
    writeString(nextionCallStr);
  }
  pls="";
  }
  
}



void power_on(){  
//Initialize GSM module, perform Location Update, latch to cellular network, read GSM SMS buffer.
  uint8_t answer = 0;
  while(answer == 0){
    answer = sendATcommand("AT", "OK", 2000);
    }
  while((sendATcommand("AT+CREG?", "+CREG: 0,1", 500) || sendATcommand("AT+CREG?", "+CREG: 0,5", 500)) == 0);
  writeString("page0.t0.txt=\"Searching...\"");
  delay(2000);
  searchNetwork();
  delay(2000);
  smsComputation(); 
}

int8_t sendATcommand(char* ATcommand, char* expected_answer, unsigned int timeout){
//Function to send AT commands and read responses to/from the GSM module.
  uint8_t x=0, answer=0; char GSMreponse[100]; unsigned long previous;
  memset(GSMreponse, '\0', 100); 
  delay(100);
  while(Serial.available()>0)
    Serial.read();
  Serial.println(ATcommand); 
  previous = millis();
  do{
    if(Serial.available() != 0){
      GSMreponse[x] = Serial.read();
      x++;
      if(strstr(GSMreponse, expected_answer) != NULL){
        answer = 1;
        }
    }
   }while((answer == 0) &&((millis() - previous) < timeout));
  return answer;
}

void searchNetwork(){
//Function to search for available cellular networks|Get network registration|Send attched network to Nextion display.
  String sendCOPScommand, readCOPScommad, networkOperator, sendNetOperator;
  int startCOPS=-1, copsFirstcomma, copsSecondcomma, copsNL;
  while(Serial.available())(Serial.read());
  sendCOPScommand="AT+COPS?"; Serial.println(sendCOPScommand);
  while(!Serial.available()); while(Serial.available()){readCOPScommad=Serial.readString();}
  if(readCOPScommad.indexOf("+COPS:") != -1){
    copsFirstcomma=readCOPScommad.indexOf(",", startCOPS+1);
    copsSecondcomma=readCOPScommad.indexOf(",", copsFirstcomma+2);
    copsNL=readCOPScommad.indexOf("\n", copsSecondcomma+1);
    networkOperator=readCOPScommad.substring(copsSecondcomma+2, copsNL-2);
    sendNetOperator="page0.t0.txt=\""+networkOperator+"\"";writeString(sendNetOperator);
  }sendCOPScommand=readCOPScommad=networkOperator="";copsFirstcomma=copsNL=0;
}

void querySMS(String querySMSContent){
//Function to query all SMS from the GSM buffer.
  Serial.println(querySMSContent);
}

void connectCall(String conCallContent){
//Function to Initiate Mobile Originated Call To Dial B-Number.
  String nextionCallStr = "page2.t0.txt=\"Connecting\"";writeString(nextionCallStr);
  while((sendATcommand("AT+CREG?", "+CREG: 0,1", 500) ||  //0,1:  User registered, home network.
    sendATcommand("AT+CREG?", "+CREG: 0,5", 500)) == 0);  //0,5:  User registered, roaming.
  conCallContent.toCharArray(msisdn, rawMsg.length());
  sprintf(ATcomm, "ATD%s;", msisdn);sendATcommand(ATcomm, "OK", 10000);
  nextionCallStr = "page2.t0.txt=\"Calling\"";writeString(nextionCallStr);
  memset(msisdn, '\0', 30);memset(ATcomm, '\0', 30);
}

void releaseCall(String relCallContent){
//Function to Hang up a call.
  Serial.println(relCallContent); 
}

void sendSMS(String sendSMSContent){
//Function to get content typed from Nextion|select SMS Message Format|Send SMS Message to B-number.
  Serial.println(F("Sms içeriği:"));
  Serial.println(sendSMSContent);
  delay(10);
  int firstDelim = sendSMSContent.indexOf(byte(189));//ilk DELİ yani mesajdaki 1/2 yazısının olduğu index değeri
  Serial.println(firstDelim);
  delay(10);
  int secondDelim = sendSMSContent.indexOf(byte(189), firstDelim+1);
  Serial.println(secondDelim);
  delay(10);
  String smsContent = sendSMSContent.substring(0, firstDelim);
  Serial.println(F("Sms içeriği:"));
  Serial.println(smsContent);
  delay(10);
  String phoneNumber = sendSMSContent.substring(firstDelim+1, secondDelim);
  Serial.println(F("Telefon NO::"));
  Serial.println(phoneNumber);
  delay(10);
  while((sendATcommand("AT+CREG?", "+CREG: 0,1", 500) || sendATcommand("AT+CREG?", "+CREG: 0,5", 500)) == 0);
  if(sendATcommand("AT+CMGF=1", "OK", 2500)){
    phoneNumber.toCharArray(msisdn, msg.length());
    sprintf(ATcomm, "AT+CMGS=\"%s\"", msisdn);
    if(sendATcommand(ATcomm, ">", 2000)){
      Serial.println(smsContent);
    Serial.write(0x1A);
      if(sendATcommand("", "OK", 20000)){
        Serial.println(F("message sent"));
      }
    else{Serial.println(F("error sending"));
    }
    }
  else{
    Serial.println(F("not found >"));
    }
  }
  smsContent="";
  phoneNumber="";
  memset(msisdn, '\0', 30);
  memset(ATcomm, '\0', 30);
}

void answerCall(String ansCallContent){
//Function to change Nextion text and picture, if Incoming call is accepted.
  Serial.println(ansCallContent);
  String nextionCallStr = "page5.t0.txt=\"Connected\"";
  writeString(nextionCallStr);
  nextionCallStr = "page5.p0.pic=21";
  writeString(nextionCallStr);
}

void smsComputation(){
//Function to Read SMS from GSM buffer. Normally, SMS buffer size=20 & select only 10 SMS.
  int startCPMS=-1, CPMS1comma, CPMS2comma, msgCount=0;
  int startCMGR=-1, cmgrIndex, cmgrNLindex, smsNLindex;
  String sendCPMScommand, readCPMScommand, CPMSMsgCount;
  String sendCMGRcommand, readCMGRcommand, inCMGR, inSMS, dspCount;
  sendCPMScommand = "AT+CPMS?";
  Serial.println(sendCPMScommand);
  while(!Serial.available());
  while(Serial.available()){
    readCPMScommand=Serial.readString();
    }
  if(readCPMScommand.indexOf("+CPMS:") != -1){
    CPMS1comma = readCPMScommand.indexOf(",", startCPMS+1);
    CPMS2comma = readCPMScommand.indexOf(",", CPMS1comma+1);
    CPMSMsgCount = readCPMScommand.substring(CPMS1comma+1, CPMS2comma);msgCount = CPMSMsgCount.toInt();
    dspCount="page6.t51.txt=\""+CPMSMsgCount+"\"";writeString(dspCount);
    if((msgCount > 0) && (msgCount <= 10)){writeString("page6.p1.pic=35");}
    if(msgCount > 10){writeString("page6.p1.pic=34");}int spotSelect = 0;
    while(Serial.available())(Serial.read());
    if(msgCount != 0){
      for(int iSMS=20; iSMS>0; iSMS--){
        sendCMGRcommand="AT+CMGR="+String(iSMS, DEC); Serial.println(sendCMGRcommand);
        while(!Serial.available()); while(Serial.available()){readCMGRcommand=Serial.readString();}
        if((readCMGRcommand.indexOf("+CMGR:")!=-1) && (spotSelect<(50))){
          cmgrIndex = readCMGRcommand.indexOf("+CMGR:", startCMGR+1);
          cmgrNLindex = readCMGRcommand.indexOf("\n", cmgrIndex+1);
          inCMGR = readCMGRcommand.substring(cmgrIndex, cmgrNLindex-1);
          smsNLindex = readCMGRcommand.indexOf("\n", cmgrNLindex+1);
          inSMS = readCMGRcommand.substring(cmgrNLindex+1, smsNLindex-1);
          readSMS(inCMGR, inSMS, iSMS, spotSelect);
          spotSelect=spotSelect+5;
        }startCMGR=-1;cmgrIndex=cmgrNLindex=smsNLindex=0;inCMGR=inSMS=readCMGRcommand="";
      }     
    }
  }readCPMScommand=CPMSMsgCount="";startCPMS=-1;CPMS1comma=CPMS2comma=msgCount=0;
}

void readSMS(String readinCMGR, String readinSMS, int readiSMS ,int readinspotSelect){
//Function to parse the loaded SMS from GSM module and present to Nextion display.
  int startComma=-1, firstColon, firstComma, secondComma, thirdComma;
  String smsSeqNum, smsStatus, smsBNumber, smsDateTime, actualSMS;
  String startOfPage="page6.t", middleOfPage=".txt=\"", pageContent;
  
  firstColon = readinCMGR.indexOf(":", startComma+1);firstComma = readinCMGR.indexOf(",", startComma+1);
  secondComma = readinCMGR.indexOf(",", firstComma+1);thirdComma = readinCMGR.indexOf(",", secondComma+1);smsSeqNum = String(readiSMS);
  smsStatus = readinCMGR.substring(firstColon+7, firstComma-1); smsBNumber = readinCMGR.substring(firstComma+2, secondComma-1);
  smsDateTime = readinCMGR.substring(thirdComma+2, readinCMGR.length()-1);actualSMS = readinSMS.substring(0, readinSMS.length());
  pageContent = startOfPage + readinspotSelect + middleOfPage + smsStatus+"\"";writeString(pageContent);readinspotSelect++;
  pageContent = startOfPage + readinspotSelect + middleOfPage + smsBNumber+"\"";writeString(pageContent);readinspotSelect++;
  pageContent = startOfPage + readinspotSelect + middleOfPage + smsSeqNum+"\"";writeString(pageContent);readinspotSelect++;
  pageContent = startOfPage + readinspotSelect + middleOfPage + smsDateTime+"\"";writeString(pageContent);readinspotSelect++;
  pageContent = startOfPage + readinspotSelect + middleOfPage + actualSMS+"\"";writeString(pageContent);
  smsSeqNum=smsStatus=smsBNumber=smsDateTime=actualSMS=pageContent="";firstColon=firstComma=secondComma=thirdComma=readinspotSelect=0;
}

void delReadSMS(String inDelReadSMS){
//Function to delete only read SMS from the GSM Buffer.
  Serial.println(inDelReadSMS);
}

void delSMS(String indelSMS){
//Function to delete all (Read/Unread) SMS from the GSM Buffer.
  Serial.println(indelSMS);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//                            msg, bellektekiKisiSayisi
void contactReturn(String contactInfo, int sayi){

  int firstDelim = contactInfo.indexOf(byte(189));//İlk DELİ yani mesajdaki 1/2 yazısının olduğu index değeri
  delay(10);
  int secondDelim= contactInfo.indexOf(byte(189), firstDelim+1);//İkinci DELİ yani mesajdaki 1/2 yazısının olduğu index değeri 
  delay(10);
  int thirdDelim = contactInfo.indexOf(byte(189), secondDelim+1);//Üçüncü DELİ yani mesajdaki 1/2 yazısının olduğu index değeri 
  delay(10);

  Serial.println(F("1."));
  Serial.println(firstDelim);
  Serial.println(F("2."));
  Serial.println(secondDelim);
  Serial.println(F("3."));
  Serial.println(thirdDelim);

  String mesaj = contactInfo.substring(firstDelim+1, secondDelim);
  Serial.println(F("mesaj: "));
  Serial.println(mesaj);
  
  String kisinumarasi = contactInfo.substring(secondDelim+1, thirdDelim);
  
  kisinumarasi.remove(1);
  Serial.println(F("2Düzenlenen kişi numarasi(hangi kişi düzenlendi ve tekrar yazılacak): "));
  Serial.println(kisinumarasi);
  delay(10);
  int bellektekiler=EEPROM.read(400);
  sayi=bellektekiler;
  
  if(sayi<4){
      
    Serial.println(F("Sayı: "));
    Serial.println(sayi);
    
    //Adreslerin yeri belirleniyor  
    int conNameAddressNo, conTelNoAddressNo;
    
    if(kisinumarasi=="20" || kisinumarasi=="0" || kisinumarasi=="5" || kisinumarasi=="10"){
      
      int sayi2=kisinumarasi.toInt();
      
      Serial.println(F("Sayı2: "));
      Serial.println(sayi2);
      switch(sayi2){
        case 20:
          Serial.println(F("Case 20:"));
          conNameAddressNo=120;
          conTelNoAddressNo=140;
          break;
        case 0:
          Serial.println(F("Case 0:"));    
          conNameAddressNo=0;
          conTelNoAddressNo=20;
          break;
        case 5:
          Serial.println(F("Case 5:"));
          conNameAddressNo=40;
          conTelNoAddressNo=60;
          break;
        case 10:
          Serial.println(F("Case 10:"));
          conNameAddressNo=80;
          conTelNoAddressNo=100;
          break;
        default:
          Serial.println(F("Rehbere 3'dan fazla kişi kaydedilemez.(contact return kişi numarası switch case)"));
          break;
      }
    }
    else{
      sayi++;
      Serial.println(F("sayi(elsenin içindeki):"));
      Serial.println(sayi);
      int sayi2=kisinumarasi.toInt();
      if(sayi2==10 && sayi==2){
          sayi==3;
        }
      switch(sayi){
        case 1:
          Serial.println(F("Case 1:"));
          conNameAddressNo=0;
          conTelNoAddressNo=20;
          break;
        case 2:
          Serial.println(F("Case 2:"));    
          conNameAddressNo=40;
          conTelNoAddressNo=60;
          break;
        case 3:
          Serial.println(F("Case 3:"));
          conNameAddressNo=80;
          conTelNoAddressNo=100;
          break;
        default:
          Serial.println(F("Rehbere 3'dan fazla kişi kaydedilemez."));
          break;
      }
    }
  
    if(kisinumarasi=="20" || kisinumarasi=="0" || kisinumarasi=="5" || kisinumarasi=="10"){
      
      Serial.println(F("bir şey yapılmayacaktı."));
      String contactName = contactInfo.substring(0, firstDelim);
      Serial.println(F("Eklenen kişi ismi: "));
      Serial.println(contactName);
      Serial.println(F("conNameAddressNo(contactReturn): "));
      Serial.println(conNameAddressNo);
      Serial.println(F("contactName(contactReturn): "));
      Serial.println(contactName);
      write_String(conNameAddressNo, contactName);
      
      String isim;
      isim = read_String(conNameAddressNo);
      Serial.print(F("Read Data:"));
      Serial.println(isim);
      delay(10);
      
      String telNo = contactInfo.substring(firstDelim+1, secondDelim);
      Serial.println(F("Eklenen kişinin numarası: "));
      Serial.println(telNo);
      Serial.println(F("conTelNoAddressNo(contactReturn):"));
      Serial.println(conTelNoAddressNo);
      Serial.println(F("telNo(contactReturn):"));
      Serial.println(telNo);
      write_String(conTelNoAddressNo, telNo);
      
      String numara;
      numara = read_String(conTelNoAddressNo);
      Serial.println(F("Read Data:"));
      Serial.println(numara);
      delay(10);
    }
    else{
  
      
      Serial.println(F("Contact add in döndürdüğü ham veriden sonra düzenlenen mesaj(msg): "));
      Serial.println(F("Aynı zamanda contactInfo fonsiyonuna giren veri:"));
      Serial.println(contactInfo);
      delay(10);   
      
      String contactName = contactInfo.substring(0, firstDelim);
      Serial.println(F("Eklenen kişi ismi: "));
      Serial.println(contactName);
      delay(10);
      Serial.println(F("conNameAddressNo(contactReturn): "));
      Serial.println(conNameAddressNo);
      Serial.println(F("contactName(contactReturn): "));
      Serial.println(contactName);
      write_String(conNameAddressNo, contactName);
      
      String isim;
      isim = read_String(conNameAddressNo);
      Serial.print(F("Read Data:"));
      Serial.println(isim);
      delay(10);
      
      String telNo = contactInfo.substring(firstDelim+1, secondDelim);
      Serial.println(F("Eklenen kişinin numarası: "));
      Serial.println(telNo);
      delay(10);
      Serial.println(F("sayi(contactReturn):"));
      Serial.println(sayi);
      Serial.println(F("conTelNoAddressNo(contactReturn):"));
      Serial.println(conTelNoAddressNo);
      Serial.println(F("telNo(contactReturn):"));
      Serial.println(telNo);
      write_String(conTelNoAddressNo, telNo);
      
      String numara;
      numara = read_String(conTelNoAddressNo);
      Serial.println(F("Read Data:"));
      Serial.println(numara);
      delay(10);
    
      //Kişinin bilgileri bellekte saklandı.
      //Şimdi bellekteki bilgileri lcd ekranda görüntülememiz lazım
      //onu da loop fonksiyonunun içinde değil en başta setup 
      //fonskiyonunun içinde yapmamız lazım
      //karttaki daha önce eklenmiş rehber
      //bilgilerini görmek için 
      //ekranaYaz fonsiyonun ile bellekten okuma yapıyoruz 
  
      Serial.println(F("EkranaYaza geldik"));
      ekranaYaz(contactName, telNo, sayi);
      delay(100);
      Serial.println(F("EkranaYaz bitti"));
          
      //400.cü adrese kaç tane kişi kaydedildiğini yazıyoruz.
  
      EEPROM.write(400,sayi);
      delay(20);
      
      unsigned char k;
      k=EEPROM.read(400);
      delay(50);
      sayi=(int)k;
  
      Serial.println(F("k:"));   
      Serial.println(k);   
      Serial.println(F("sayi:"));    
      Serial.println(sayi);
      }
  }
    else{
    Serial.println(F("Rehbere 3'ten fazla kişi eklenemez."));
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
//Arduno kartın EEPROM'a hafızasına yazma fonksiyonu
void write_String(char add,String data)
{
  int _size = data.length();
  int i;
  for(i=0;i<_size;i++)
  {
    EEPROM.write(add+i,data[i]);
  }
  EEPROM.write(add+_size,'\0');   //Add termination null character for String Data
}
/////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////
String read_String(char add){
  
  int i;
  char data[100]; //Max 100 Bytes
  int len=0;
  unsigned char k;
  k=EEPROM.read(add);
  while(k != '\0' && len<500)   //Read until null character
  {    
    k=EEPROM.read(add+len);
    data[len]=k;
    len++;
  }
  data[len]='\0';
  return String(data);
}
