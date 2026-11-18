#include <Wifi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "CESJT";
const char* password = "itisjtsmg";

const int ledPin = 2;


AsyncWebServer server (80);

bool ledEncendido = true;

const char pagin_template[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta charset='utf-8'>
    <title>MONITOR DE ENTRADAS DIGITALES</title>
    <style>
    body { background-color: red; text-align:center; padding-top: 50px}
    .titulo { font-family: 'Courier', monospoce; font-weight: bold; font-style: italic; font-size: 32px; color: white;}
    .botom {width: 120px; height: 60px; backgroud-color:yellow; color: black;border:2px solid black; border-radius:10px;}
)rawliteral";