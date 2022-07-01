#include <esp32cam.h>
#include <WebServer.h>
#include <WiFi.h>

static const char* WIFI_SSID = "House";
static const char* WIFI_PASS = "RosaKel01";

static auto resi = esp32cam::Resolution::find(800, 600);
static auto resl = esp32cam::Resolution::find(320,240);
static auto resh = esp32cam::Resolution::find(1600, 1200);

WebServer server(80);

void on_flash(){
  digitalWrite(4, HIGH);
  server.send(200);
  }

void off_flash(){
  digitalWrite(4, LOW);
  server.send(200);
  }

void JPG() {

  auto frame = esp32cam::capture();
  if (frame == nullptr) {
    Serial.println("CAPTURE FAIL");
    return;
  }
  Serial.println("cap...1");
  Serial.printf("CAPTURE OK %dx%d %db\n", frame->getWidth(), frame->getHeight(),static_cast<int>(frame->size()));

  server.setContentLength(frame->size());
  server.send(200, "image/jpeg");
  WiFiClient client = server.client();
  frame->writeTo(client);
  }

void setup()
{
  Serial.begin(115200);
  Serial.println();
  pinMode(4, OUTPUT);
  {
    using namespace esp32cam;
    Config cfg;
    cfg.setPins(pins::AiThinker);
    cfg.setResolution(resi);
    cfg.setJpeg(80);

    bool ok = Camera.begin(cfg);
    Serial.println(ok ? "camera ok" : "camera fail");
  }

  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi failure");
    delay(500);
  }

  Serial.println("WiFi connected");
  Serial.print("http://");
  Serial.println(WiFi.localIP());
  Serial.println("/cam.jpg");
  Serial.println("/cam.on.flash");
  Serial.println("/cam.off.flash");

  server.on("/cam.jpg",JPG);
  server.on("/cam.on.flash",on_flash);
  server.on("/cam.off.flash",off_flash);

  server.begin();
}

void loop()
{
  server.handleClient();
}
