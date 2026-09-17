#include <Arduino.h>

#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "CESJT";
const char* password = "itisjtsmg";

WebServer server(80);

bool cambio=false;
int led=5;
int pot=15;
int luz=0;

String tension="0", toggle="ON";
const char pagina_template[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
<meta http-equiu="refresh"content"20">
<meta charset="UTF-8">
<title>Monitor Tensión</title>
<style>
  body {
    background-color: red;
    text-align: center;
  }

  .titulo {
    font-family: Courier, monospace;
    font-weight: bold;
    font-style: italic;
    font-size: 32px;
    text-transform: uppercase;
  }

  .borde {
    width: 170px;
    height: 100px;
    border: 5px solid black;
    border-radius: 18px;
    background-color: black;
    margin: 0 auto;
    display: flex;
    align-items: center;
    justify-content: center;
  }

  .pantalla {
    width: 160px;
    height: 90px;
    border: 1px solid black;
    border-radius: 10px;
    background-color: cyan;
    margin: 4px;
    display: flex;
    align-items: center;
    justify-content: center;
  }

  .pantalla.apagada {
    background-color: black;
  }

  .boton {
    width: 80px;
    height: 45px;
    background-color: yellow;
    color: black;
    border: 2px solid black;
    border-radius: 80px;
    margin-top: 20px;
  }
</style>
</head>
<body>

  <h1 class="titulo">Monitor Tensión</h1>

  <div class="borde">
    <div class="pantalla" id="pantalla">
      <span id="texto">&nbsp;&nbsp;Tensión: <strong id="valor">5.00</strong>V</span>
    </div>
  </div>

  <a href="/off"><button class="boton" id="botonToggle" onclick="toggleLed()">APAGAR</button></a>

  <script>
    let encendido = true;

    function toggleLed() {
      encendido = !encendido;
      const pantalla = document.getElementById('pantalla');
      const texto = document.getElementById('texto');
      const boton = document.getElementById('botonToggle');

      if (encendido) {
        pantalla.classList.remove('apagada');
        texto.style.visibility = 'visible';
        boton.textContent = 'APAGAR';
      } else {
        pantalla.classList.add('apagada');
        texto.style.visibility = 'hidden';
        boton.textContent = 'ENCENDER';
      }
    }
  </script>

</body>
</html>
)rawliteral";

void setup() {
Serial.begin(115200);

Serial.print("Conectando a ");
Serial.println(ssid);
WiFi.begin(ssid, password);

int timeout = 20; 
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

pinMode(led, OUTPUT);
pinMode(pot, INPUT);

server.on("/", []() {
    String pagina = pagina_template;
    pagina.replace("__TEXTO_TENSION__", tension);
    pagina.replace("__TOGGLE__", toggle);
    server.send(200, "text/html", pagina);
});

server.on("/cambio", []() {
    String pagina = pagina_template;     
    cambio = !cambio;
    if(cambio = 1){
        analogWrite(led, HIGH);
        toggle="OFF";
    }else{
        if(cambio = 0){
            analogWrite(led, LOW);
            toggle="ON";
        }
    }
});
server.begin();
}
void loop(){
    server.handleClient();
    int Lectura = analogRead(pot);
    luz=map(Lectura, 0, 4095, 0, 255);
    tension=luz;
    analogWrite(led, luz);
}