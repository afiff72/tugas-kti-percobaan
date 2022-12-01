/*AT-MO PRODUCTION
RFID DAN RELAY
tolong jika menggunakan code ini
mohon masukan sumber seperti di bawah ini

"AT-MO PRODUCTION 
EDIT BY OGI SINATRA"

* MOSI: Pin 11 / ICSP-4
* MISO: Pin 12 / ICSP-1
* SCK: Pin 13 / ISCP-3
* SS/SDA: Pin 10
* RST: Pin 9

*/

#include <RFID.h>
#include <SPI.h>
#include <Servo.h>

#define SS_PIN 10 //pin RFID yang bisa di ubah
#define RST_PIN 9 //pin RFID yang bisa di ubah

#define RELAY_ON 0
#define RELAY_OFF 1
#define RELAY_1  8   // pin yang digunakan yaitu pin 8

RFID rfid(SS_PIN,RST_PIN);

Servo myservo;
int pos = 0;

const int Merah = 3; //pin Led yang digunakan
const int hijau = 2; //pin Led yang digunakan



int serNum[5];

int cards[][5] = {
  {169,135,30,201,249
}  

  };
  


bool access = false;

void setup(){

 myservo.attach(7);
    Serial.begin(9600);
    SPI.begin();
    rfid.init();

    pinMode(Merah, OUTPUT);
    pinMode(hijau, OUTPUT);
    pinMode(RELAY_1, OUTPUT);

    digitalWrite(RELAY_1, RELAY_ON);
    digitalWrite(Merah, LOW);
    digitalWrite(hijau, LOW);

    
}


void loop(){  

       
    
    if(rfid.isCard()){
    
        if(rfid.readCardSerial()){
            Serial.print(rfid.serNum[0]);
            Serial.print(" ");
            Serial.print(rfid.serNum[1]);
            Serial.print(" ");
            Serial.print(rfid.serNum[2]);
            Serial.print(" ");
            Serial.print(rfid.serNum[3]);
            Serial.print(" ");
            Serial.print(rfid.serNum[4]);
            Serial.println("");
            
            for(int x = 0; x < sizeof(cards); x++){
              for(int i = 0; i < sizeof(rfid.serNum); i++ ){
                  if(rfid.serNum[i] != cards[x][i]) {
                      access = false;
                      break;
                  } else {
                      access = true;
                  }
              }
              if(access) break;
            }
           
        }
        
       if(access){
          Serial.println("Berhasil;");
          digitalWrite(hijau, HIGH);
          digitalWrite(RELAY_1, RELAY_OFF);
          delay(2000); 
          digitalWrite(hijau, LOW);
          
        for (pos = 40; pos >= 0;) {    // servo
          myservo.write(pos);              
          delay(15);                       
  }
          } 
      
      else {
           Serial.println("Gagal"); 
           digitalWrite(Merah, HIGH);
           delay(500);
           digitalWrite(Merah, LOW); 
           delay(500);
           digitalWrite(Merah, HIGH);
           delay(500);
           digitalWrite(Merah, LOW);
           delay(500); 
        
           }  
           
       
    }
    
    rfid.halt();
}
