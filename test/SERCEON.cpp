  server.on("/", []() {
    

    server.send(200, "text/html", pagina_template);
  });

  server.on("/display1",[](){
    animacion=1;
    server.sendHeader("Location", "/");
    server.send(302, "text/plain", ""); // 302 y send Header para que no me quede en /header
  });
  server.on("/display2",[](){
    animacion=2;
    server.sendHeader("Location", "/");
    server.send(302, "text/plain", ""); // 302 y send Header para que no me quede en /header
  });
  server.on("/cambiarnumero",off);

  server.begin();