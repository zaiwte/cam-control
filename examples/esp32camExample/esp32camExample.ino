#include <esp32cam.h>

static auto hiRes = esp32cam::Resolution::find(800, 600);

void serveJpg()
{
  auto frame = esp32cam::capture();
  if (frame == nullptr) {
    Serial.println("CAPTURE FAIL");
    return;
  }
  Serial.println("cap...1");
  Serial.printf("CAPTURE OK %dx%d %db\n", frame->getWidth(), frame->getHeight(),static_cast<int>(frame->size()));
  if(Serial.available()){  //id data is available to read
    char val = Serial.read();
    Serial.println(val);
    if(val == 'e'){       
      digitalWrite(4, HIGH);
      delay(2000);
      digitalWrite(4, LOW);
      delay(2000);
    }
    if(val=='r'){
      ESP.restart();
      };}
}

void  setup(){
  Serial.begin(9600);
  
  {
    using namespace esp32cam;
    Config cfg;
    cfg.setPins(pins::AiThinker);
    cfg.setResolution(hiRes);
    cfg.setBufferCount(2);
    cfg.setJpeg(80);
 
    bool ok = Camera.begin(cfg);
    Serial.println(ok ? "CAMERA OK" : "CAMERA FAIL");
  }
  pinMode(4, OUTPUT);
  Serial.print("se rest");
}
 
void loop()
{
  serveJpg();
  delay(1000);
}
