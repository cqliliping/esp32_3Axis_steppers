/*
20181204 添加速度改变和同时控制三个轴的按钮
*/
//20181111 Timer控制stepPin
#include <WiFi.h>
#include <Ticker.h>

double pluInterval = 0.02;
int pluNumbers = 4000;

Ticker timerA;
unsigned int aStepNow = 0;
unsigned int aStepWant = 0;
bool aState = true;
Ticker timerB;
unsigned int bStepNow = 0;
unsigned int bStepWant = 0;
bool bState = true;
Ticker timerC;
unsigned int cStepNow = 0;
unsigned int cStepWant = 0;
bool cState = true;
void aAxisChanged(){
  //int state = !state;
  aState = !aState;
  digitalWrite(16,aState);
  aStepNow++;
  if (aStepNow < aStepWant){
    
  }
  else {
    timerA.detach();
    Serial.println("aAxis Done");
  }
}
void bAxisChanged(){
  //int state = !state;
  bState = !bState;
  digitalWrite(5,bState);
  bStepNow++;
  if (bStepNow < bStepWant){
    
  }
  else {
    timerB.detach();
    Serial.println("bAxis Done");
  }
}
void cAxisChanged(){
  //int state = !state;
  cState = !cState;
  digitalWrite(19,cState);
  cStepNow++;
  if (cStepNow < cStepWant){
    
  }
  else {
    timerC.detach();
    Serial.println("cAxis Done");
  }
}

const char* ssid     = "HUAWEI-SCSD";
const char* password = "scsd2017";
int stepper=15; // stepper delay
WiFiServer server(80);

//20181111

void setup()
{
  timerA.detach();//20181111 避免刚起启动开启定时器
  timerB.detach();
  timerC.detach();
  
 Serial.begin(115200);

 pinMode(4, OUTPUT);      // 1轴方向
 pinMode(16, OUTPUT);      // 1轴脉冲
 pinMode(17, OUTPUT);       // 2轴方向
 pinMode(5, OUTPUT);      // 2轴脉冲
 pinMode(18, OUTPUT);      // 3轴方向
 pinMode(19, OUTPUT);      // 3轴脉冲

    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println("Place this IP address into a browser window");
    server.begin();

}

int value = 0;

void loop(){

  
 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             
    Serial.println("new client");          
    String currentLine = "";                   // make a String to hold incoming data from the client
    while (client.connected()) {            
      if (client.available()) {                // if there's client data
        char c = client.read();                // read a byte
          if (c == '\n') {                     // check for newline character, 
          if (currentLine.length() == 0) {     // if line is blank it means its the end of the client HTTP request
            client.println("<!DOCTYPE html>"); // open wrap the web page
            client.print("<html><head><meta name='viewport' content='initial-scale=1.0'><meta charset='utf-8'><style>#map {height: 100%;}html, body {height: 100%;margin: 0;padding: 0;}</style></head>");
            client.print("<body><h1>双创桌面机器人简单控制</h1>");
        // Gui buttons start here
                client.print("<input type=image style=width:50%;height:16% src='http://myrobotlab.org/sites/default/files/users/user25images/ButtonGreenLong.png'onmousedown=location.href='/slow' >");
                client.print("<input type=image style=width:50%;height:16% src='http://myrobotlab.org/sites/default/files/users/user25images/ButtonPurpleLong.png'onmousedown=location.href='/fast' >");
        
                client.print("<input type=image style=width:33%;height:16% src='http://myrobotlab.org/sites/default/files/users/user25images/ButtonBlueLong.png'onmousedown=location.href='/dec1' >");
                client.print("<input type=image style=width:33%;height:16% src='http://myrobotlab.org/sites/default/files/users/user25images/nixiesmall1.png'>");
                client.print("<input type=image style=width:33%;height:16% src='http://myrobotlab.org/sites/default/files/users/user25images/ButtonOrangeLong.png'onmousedown=location.href='/inc1' >");
                   
                client.print("<input type=image style=width:33%;height:16% src='http://myrobotlab.org/sites/default/files/users/user25images/ButtonPinkLong.png'onmousedown=location.href='/dec2' >");
                client.print("<input type=image style=width:33%;height:16% src='http://myrobotlab.org/sites/default/files/users/user25images/nixiesmall2.png'>");
                client.print("<input type=image style=width:33%;height:16% src='http://myrobotlab.org/sites/default/files/users/user25images/ButtonGreenLong.png'onmousedown=location.href='/inc2' >"); 

                client.print("<input type=image style=width:33%;height:16% src='http://myrobotlab.org/sites/default/files/users/user25images/ButtonTurqLong.png'onmousedown=location.href='/dec3' >");
                client.print("<input type=image style=width:33%;height:16% src='http://myrobotlab.org/sites/default/files/users/user25images/nixiesmall3.png'>");
                client.print("<input type=image style=width:33%;height:16% src='http://myrobotlab.org/sites/default/files/users/user25images/ButtonPurpleLong.png'onmousedown=location.href='/inc3' >"); 
                
                //client.print("<input type=image style=width:100%;height:20% src='http://myrobotlab.org/sites/default/files/users/user25images/ButtonRedLong.png'onmousedown=location.href='/stopall' >");
                client.print("<input type=image style=width:33%;height:16% src='http://myrobotlab.org/sites/default/files/users/user25images/ButtonYellowLong.png'onmousedown=location.href='/decAll' >");
                client.print("<input type=image style=width:33%;height:16% src='http://myrobotlab.org/sites/default/files/users/user25images/ButtonRedLong.png'onmousedown=location.href='/stopall' >");
                client.print("<input type=image style=width:33%;height:16% src='http://myrobotlab.org/sites/default/files/users/user25images/ButtonBlackLong.png'onmousedown=location.href='/incAll' >");
                client.print("</body></html>"); // close wrap the web page
            
            client.println(); // The HTTP response ends with an extra blank line:
          
            break;  // break out of the while loop:
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
         } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;       // add it to the end of the currentLine
        }

         if (currentLine.endsWith("GET /slow")) {
            Serial.println("GET /slow");
            pluInterval = 1 ;
            Serial.print("pluInterval =");
            Serial.println(pluInterval);
           
          }
         if (currentLine.endsWith("GET /fast")) {
            Serial.println("GET /fast");
            pluInterval = 0.02 ;
            Serial.print("pluInterval =");
            Serial.println(pluInterval);
           
          }
          
        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /dec1")) {digitalWrite(4, HIGH);
              Serial.println("GET /dec1");
//              timerEnd(timer);
//              timer = NULL;
              aStepNow = 0;
              aStepWant = 4000;
//              timerSemaphore = xSemaphoreCreateBinary();
//              timer = timerBegin(0, 80, true);
//              timerAttachInterrupt(timer, &onTimer, true);
//              //timerAlarmWrite(timer, 5, true);//Guru Meditation Error: Core  0 panic'ed (Interrupt wdt timeout on CPU1)
//              timerAlarmWrite(timer, 10, true);
//              timerAlarmEnable(timer); 
                timerA.detach();          
                timerA.attach_ms(pluInterval,aAxisChanged);
              //for (int i=0; i <= 43; i++){ digitalWrite(16, HIGH);delay(10);digitalWrite(16,LOW );delay(10); }
        }
         if (currentLine.endsWith("GET /inc1")) {digitalWrite(4, LOW);
              Serial.println("GET /inc1");
//              timerEnd(timer);
//              timer = NULL;
              aStepNow = 0;
              aStepWant = 4000;
//              timerSemaphore = xSemaphoreCreateBinary();
//              timer = timerBegin(0, 80, true);
//              timerAttachInterrupt(timer, &onTimer, true);
//              timerAlarmWrite(timer, 10, true);
//              timerAlarmEnable(timer);
              timerA.detach();
              timerA.attach_ms(pluInterval,aAxisChanged);
              //for (int i=0; i <= 43; i++){ digitalWrite(16, HIGH);delay(10);digitalWrite(16,LOW );delay(10); }
        }
         if (currentLine.endsWith("GET /dec2")) {digitalWrite(17, HIGH);
              Serial.println("GET /dec2");
              bStepNow = 0;
              bStepWant = 4000;
              timerB.detach();
              //timerB.attach_ms(1,bAxisChanged);
              timerB.attach_ms(pluInterval,bAxisChanged);
              //for (int i=0; i <= 43; i++){ digitalWrite(5, HIGH);delay(10);digitalWrite(5,LOW );delay(10); }
        }
         if (currentLine.endsWith("GET /inc2")) {digitalWrite(17, LOW);
              Serial.println("GET /inc2");
              bStepNow = 0;
              bStepWant = 4000;
              timerB.detach();
              timerB.attach_ms(pluInterval,bAxisChanged);
              //timerB.attach_ms(0.9,bAxisChanged);
              //for (int i=0; i <= 43; i++){ digitalWrite(5, HIGH);delay(10);digitalWrite(5,LOW );delay(10); }
        }
         if (currentLine.endsWith("GET /dec3")) {digitalWrite(18, LOW);
              Serial.println("GET /dec3");
              cStepNow = 0;
              cStepWant = 4000;
              timerC.detach();
              timerC.attach_ms(pluInterval,cAxisChanged);
              //for (int i=0; i <= 43; i++){ digitalWrite(19, HIGH);delay(10);digitalWrite(19,LOW );delay(10); }
        }
         if (currentLine.endsWith("GET /inc3")) {digitalWrite(18, HIGH);
              Serial.println("GET /inc3");
              cStepNow = 0;
              cStepWant = 4000;
              timerC.detach();
              timerC.attach_ms(pluInterval,cAxisChanged);
              //for (int i=0; i <= 43; i++){ digitalWrite(19, HIGH);delay(10);digitalWrite(19,LOW );delay(10); }
        }

         if (currentLine.endsWith("GET /decAll")) {
              Serial.println("GET /decAll");
              
              digitalWrite(4, HIGH);
              aStepNow = 0; aStepWant = 4000;
              timerA.detach();
              timerA.attach_ms(pluInterval,aAxisChanged);

              digitalWrite(17, HIGH);
              bStepNow = 0;bStepWant = 4000;
              timerB.detach();
              timerB.attach_ms(pluInterval,bAxisChanged);
              
              digitalWrite(18, LOW);
              cStepNow = 0;cStepWant = 4000;
              timerC.detach();
              timerC.attach_ms(pluInterval,cAxisChanged);
        }
         if (currentLine.endsWith("GET /incAll")) {
              Serial.println("GET /incAll");
              
              digitalWrite(4, LOW);
              aStepNow = 0; aStepWant = 4000;
              timerA.detach();
              timerA.attach_ms(pluInterval,aAxisChanged);

              digitalWrite(17, LOW);
              bStepNow = 0;bStepWant = 4000;
              timerB.detach();
              timerB.attach_ms(pluInterval,bAxisChanged);
              
              digitalWrite(18, HIGH);
              cStepNow = 0;cStepWant = 4000;
              timerC.detach();
              timerC.attach_ms(pluInterval,cAxisChanged);
        }

         if (currentLine.endsWith("GET /stopall")) {
          Serial.println("GET /stopall");
          timerA.detach();//
          timerB.detach();
          timerC.detach();
          }
        }
      }
    }
  }
