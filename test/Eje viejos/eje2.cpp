
#include <Arduino.h>

#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "CESJT";
const char* password = "itisjtsmg";

int lectura = analogRead(sensorLuz);
int sensorLuz = 34; 
int atardecer = 2;
int noche = 3;
int dia = 1;

int porcentajeLuz = map(lectura, 0, 4095, 0, 225);
WebServer server(80);

const char pagina_template[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="es">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">

    <title>CONTROL DE VENTILADOR</title>
    <style>

        body {
            background-color: #ecf0f1;
            text-align: center;
        }

        h1 {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            color: #2c3e50;
        }

        .atardecer {
            background-color: #e67e22;
        }

        .noche {
            background-color: #2c3e50 ;
        }

        .dia {
            background-color: #f1c40f;
        }

        .lectura {
        border: 3px dotted white;
        border-radius: 20px;
        padding: 25px;
    }

    </style>

</head>

<body>

    <h1>LUZ AMBIENTAL</h1>

    <div class="lectura"></div>

</html>
)rawliteral";

void setup(){
     Serial.begin(115200);

  // conexion al wifi como antes
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  int timeout = 20; // 20 intentos de 500ms = 10 segundos
  while (WiFi.status() != WL_CONNECTED && timeout > 0) {
    delay(500);
    Serial.print(".");
    timeout--;
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nFallo la conexion. Reiniciando...");
    delay(1000);
    ESP.restart();
  }   
  Serial.println("\nWiFi conectado!");
  Serial.print("Dirección IP: http://");
  Serial.println(WiFi.localIP());

server.on("/", []() {

    int lectura = analogRead(sensorLuz);

    int porcentajeLuz = map(lectura, 0, 4095, 0, 225);

    String color;

if (sensorLuz = 3) {
     color = "#2c3e50";       // noche
}
else if (sensorLuz = 1) {
    color = "#f1c40f";       // dia
}
else if (sensorLuz = 2){
    color = "#e67e22";       // atardecer
}
});

}