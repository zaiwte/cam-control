/******************************************************************************************************************************
 * TITULO: Modo Soft Access Point  (AP)
 * DESCRIPCION: Este es el primer ejemplo pata demostrar el modo punto de acceso (AP) de un ESP32, creando un servidor sencillo 
 *              que responde con una pagina web sencilla en html/text a la petición en la IP configurada o designada por defecto. Parte de la serie ESP32 del canal jadsa tv
 * CANAL YOUTUBE: https://www.youtube.com/c/jadsatv
 * © 2020
 *******************************************************************************************************************************/
 
#include <WiFi.h>
#include <WebServer.h>
 
// Creamos nuestra propia red -> SSID & Password
const char* ssid = "wifi gratis";  
//const char* password = "jadsa2020"; // opcional softAP()
 

// Definimos la IP local
IPAddress ip(192,168,5,123);         //(192, 168, 1, 1)
IPAddress gateway(192,168,5,0);     //(192, 168, 1, 1)
IPAddress subnet(255,255,255,0);    //(255, 255, 255, 0)

WebServer server(80);  // puerto por defecto 80





void setup() {
  Serial.begin(115200);
 
  // Creamos el punto de acceso
  //WiFi.softAP(ssid, password); // Tiene mas parametros opcionales
  WiFi.softAP(ssid);
  WiFi.softAPConfig(ip, gateway, subnet);
  IPAddress ip = WiFi.softAPIP();
  Serial.println(ip);
 
 
  Serial.print("Nombre de mi red esp32: ");
  Serial.println(ssid);
 
  server.on("/", handleConnectionRoot);
 
  server.begin();
  Serial.println("Servidor HTTP iniciado");
  delay(150);
}
 
void loop() {
  server.handleClient();
}
 
// Nuestra respuesta en html
String answer = "<!DOCTYPE html>\
<html>\
<body>\
<h1>Hola desde ESP32 - Modo Punto de Acceso (AP)</h1>\
</body>\
</html>";

 
// Responder a la url raíz (root /)
void handleConnectionRoot() {
  server.send(200, "text/html", answer);
}
