#include "ofApp.h"

///////////////////////////////////////////////////////////////////////////
void ofApp::setup()
{
  // No esta en el md: ofSetWindowTitle() solo cambia el titulo de la ventana.
  ofSetWindowTitle("Apuestas");
  ofSetWindowShape(960, 540);
  // No esta en el md: ofSetFrameRate() fija la velocidad de dibujo.
  ofSetFrameRate(60);

  pantalla_completa = false;
  startScreenActive = true;
  escena_actual = 0;

  configurarPantallaInicio();
}

///////////////////////////////////////////////////////////////////////////
void ofApp::configurarPantallaInicio()
{
  fuente_titulo.load("fonts/CaslonCPswash.otf", 88, true, true);
  fuente_titulo_fallback.load("fonts/Arial.ttf", 88, true, true);
  fuente_texto.load("fonts/Arial.ttf", 52, true, true);
  fuente_texto_chico.load("fonts/Arial.ttf", 34, true, true);

  titulo_juego = "Prueba Cámara";

  titulo_letras[0] = "P";
  titulo_letras[1] = "r";
  titulo_letras[2] = "u";
  titulo_letras[3] = "e";
  titulo_letras[4] = "b";
  titulo_letras[5] = "a";
  titulo_letras[6] = " ";
  titulo_letras[7] = "C";
  titulo_letras[8] = "á";
  titulo_letras[9] = "m";
  titulo_letras[10] = "a";
  titulo_letras[11] = "r";
  titulo_letras[12] = "a";
  cantidad_letras_titulo = 13;

  for (int i = 0; i < 20; i++)
  {
    alpha_letras[i] = 120 + i * 6;
    sube_alpha_letras[i] = true;
  }

  titulos_escenas[0] = "Escena 1";
  titulos_escenas[1] = "Escena 2";
  titulos_escenas[2] = "Escena 3";
  titulos_escenas[3] = "Interfaz de apuestas";

  textos_escenas[0] = "Primera escena: el título respira.";
  textos_escenas[1] = "Segunda escena: las letras flotan.";
  textos_escenas[2] = "Tercera escena: el pulso se queda.";
  textos_escenas[3] = "Noticias, chat y modelo de crecimiento.";

  noticias_apuestas[0] = "Ganadores de apuestas: premios altos.";
  noticias_apuestas[1] = "Noticias generales: suben las visitas.";
  noticias_apuestas[2] = "Tragedias relacionadas: familias piden control.";

  mensajes_chat[0] = "lucas_22: duplique con una combinada";
  mensajes_chat[1] = "mar: dato para el partido?";
  mensajes_chat[2] = "toto: me recomienda seguir";
  mensajes_chat[3] = "ana: no puedo parar";
  mensajes_chat[4] = "maxi: entre por una promo";
  mensajes_chat[5] = "bot: nuevo bono disponible";

  ancho_boton = 300;
  alto_boton = 86;
  posicion_boton.set(ancho / 2 - ancho_boton / 2, 640);
  posicion_boton_anterior.set(1630, 700);
  posicion_boton_siguiente.set(1630, 810);
  alpha_boton = 150;
  sube_alpha_boton = true;
}

///////////////////////////////////////////////////////////////////////////
void ofApp::update()
{
  if (sube_alpha_boton)
  {
    alpha_boton += 3;
    if (alpha_boton >= 255) sube_alpha_boton = false;
  }
  else
  {
    alpha_boton -= 3;
    if (alpha_boton <= 150) sube_alpha_boton = true;
  }

  for (int i = 0; i < 20; i++)
  {
    if (sube_alpha_letras[i])
    {
      alpha_letras[i] += 2 + i % 3;
      if (alpha_letras[i] >= 255) sube_alpha_letras[i] = false;
    }
    else
    {
      alpha_letras[i] -= 2 + i % 3;
      if (alpha_letras[i] <= 120) sube_alpha_letras[i] = true;
    }
  }
}

///////////////////////////////////////////////////////////////////////////
void ofApp::draw()
{
  // No esta en el md: ofBackground() limpia la pantalla antes de dibujar cada frame.
  ofBackground(255);

  if (!pantalla_completa) ofScale(0.5, 0.5);

  if (startScreenActive)
  {
    dibujarPantallaInicio();
  }
  else
  {
    dibujarEscenaActual();
  }
}

///////////////////////////////////////////////////////////////////////////
void ofApp::dibujarPantallaInicio()
{
  float ancho_titulo = 0;

  for (int i = 0; i < cantidad_letras_titulo; i++)
  {
    ancho_titulo += anchoTextoConFallback(titulo_letras[i]);
  }

  float posicion_x = ancho / 2 - ancho_titulo / 2;

  for (int i = 0; i < cantidad_letras_titulo; i++)
  {
    dibujarTextoConFallback(titulo_letras[i], posicion_x, 460, alpha_letras[i]);
    posicion_x += anchoTextoConFallback(titulo_letras[i]);
  }

  ofSetColor(255, alpha_boton);
  ofDrawRectangle(posicion_boton, ancho_boton, alto_boton);

  ofSetColor(0, alpha_boton);
  ofDrawRectangle(posicion_boton.x, posicion_boton.y, ancho_boton, 4);
  ofDrawRectangle(posicion_boton.x, posicion_boton.y + alto_boton - 4, ancho_boton, 4);
  ofDrawRectangle(posicion_boton.x, posicion_boton.y, 4, alto_boton);
  ofDrawRectangle(posicion_boton.x + ancho_boton - 4, posicion_boton.y, 4, alto_boton);

  string texto_boton = "Empezar";
  float boton_texto_x = posicion_boton.x + ancho_boton / 2 - fuente_texto.stringWidth(texto_boton) / 2;
  float boton_texto_y = posicion_boton.y + 58;
  fuente_texto.drawString(texto_boton, boton_texto_x, boton_texto_y);

  ofSetColor(255);
}

///////////////////////////////////////////////////////////////////////////
void ofApp::dibujarEscenaActual()
{
  if (escena_actual == 3)
  {
    dibujarInterfazApuestas();
    // No esta en el md: return corta aca porque la escena 4 se dibuja completa aparte.
    return;
  }

  dibujarTextoAnimado(titulos_escenas[escena_actual], 450);

  string texto = textos_escenas[escena_actual];
  float texto_x = ancho / 2 - fuente_texto.stringWidth(texto) / 2;

  ofSetColor(0);
  fuente_texto.drawString(texto, texto_x, alto - 160);
  ofSetColor(255);
}

///////////////////////////////////////////////////////////////////////////
void ofApp::dibujarInterfazApuestas()
{
  ofSetColor(248);
  ofDrawRectangle(0, 0, ancho, alto);

  ofSetColor(0);
  fuente_texto.drawString("Apartado de noticias", 370, 90);

  for (int i = 0; i < 3; i++)
  {
    float caja_x = 360 + i * 400;
    ofSetColor(255);
    ofDrawRectangle(caja_x, 125, 360, 160);
    ofSetColor(0);
    ofDrawRectangle(caja_x, 125, 360, 4);
    ofDrawRectangle(caja_x, 281, 360, 4);
    ofDrawRectangle(caja_x, 125, 4, 160);
    ofDrawRectangle(caja_x + 356, 125, 4, 160);
    fuente_texto_chico.drawString(noticias_apuestas[i], caja_x + 18, 185);
  }

  ofSetColor(0);
  fuente_texto.drawString("Chat automatizado", 45, 120);

  ofSetColor(255);
  ofDrawRectangle(35, 150, 300, 830);
  ofSetColor(0);
  ofDrawRectangle(35, 150, 300, 4);
  ofDrawRectangle(35, 976, 300, 4);
  ofDrawRectangle(35, 150, 4, 830);
  ofDrawRectangle(331, 150, 4, 830);

  for (int i = 0; i < 6; i++)
  {
    ofSetColor(235);
    ofDrawRectangle(55, 190 + i * 120, 260, 82);
    ofSetColor(0);
    fuente_texto_chico.drawString(mensajes_chat[i], 70, 242 + i * 120);
  }

  ofSetColor(0);
  fuente_texto.drawString("Crecimiento cuadrático", 595, 370);

  float origen_x = 450;
  float origen_y = 900;
  float ancho_grafico = 980;
  float alto_grafico = 480;

  ofSetColor(255);
  ofDrawRectangle(origen_x - 50, origen_y - alto_grafico - 40, ancho_grafico + 110, alto_grafico + 95);

  ofSetColor(0);
  ofDrawLine(origen_x, origen_y, origen_x + ancho_grafico, origen_y);
  ofDrawLine(origen_x, origen_y, origen_x, origen_y - alto_grafico);

  for (int i = 1; i <= 5; i++)
  {
    float marca_x = origen_x + i * ancho_grafico / 5;
    float marca_y = origen_y - i * alto_grafico / 5;
    ofDrawLine(marca_x, origen_y - 8, marca_x, origen_y + 8);
    ofDrawLine(origen_x - 8, marca_y, origen_x + 8, marca_y);
    fuente_texto_chico.drawString(ofToString(i), marca_x - 10, origen_y + 55);
    fuente_texto_chico.drawString(ofToString(i), origen_x - 55, marca_y + 18);
  }

  ofSetColor(20, 95, 220);
  // No esta en el md: ofSetLineWidth() engrosa la curva del grafico.
  ofSetLineWidth(6);
  for (int i = 0; i < 80; i++)
  {
    float x_valor = i / 80.0f;
    float y_valor = x_valor * x_valor;
    float x_siguiente = (i + 1) / 80.0f;
    float y_siguiente = x_siguiente * x_siguiente;
    float x_1 = origen_x + x_valor * ancho_grafico;
    float y_1 = origen_y - y_valor * alto_grafico;
    float x_2 = origen_x + x_siguiente * ancho_grafico;
    float y_2 = origen_y - y_siguiente * alto_grafico;
    ofDrawLine(x_1, y_1, x_2, y_2);
  }
  // No esta en el md: ofSetLineWidth() vuelve al grosor normal para el resto del dibujo.
  ofSetLineWidth(1);

  ofSetColor(0);
  fuente_texto.drawString("y = x2", origen_x + ancho_grafico - 170, origen_y - alto_grafico + 60);

  ofSetColor(0);
  fuente_texto.drawString("Presentador", 1605, 120);

  ofSetColor(255);
  ofDrawRectangle(1585, 150, 300, 830);
  ofSetColor(0);
  ofDrawRectangle(1585, 150, 300, 4);
  ofDrawRectangle(1585, 976, 300, 4);
  ofDrawRectangle(1585, 150, 4, 830);
  ofDrawRectangle(1881, 150, 4, 830);

  fuente_texto.drawString("Entrada", 1640, 245);
  ofDrawLine(1640, 280, 1800, 280);
  fuente_texto.drawString("Salida", 1640, 405);
  ofDrawLine(1640, 440, 1800, 440);

  ofSetColor(235);
  ofDrawRectangle(posicion_boton_anterior, ancho_boton, alto_boton);
  ofDrawRectangle(posicion_boton_siguiente, ancho_boton, alto_boton);
  ofSetColor(0);
  fuente_texto.drawString("Anterior", posicion_boton_anterior.x + 48, posicion_boton_anterior.y + 58);
  fuente_texto.drawString("Siguiente", posicion_boton_siguiente.x + 35, posicion_boton_siguiente.y + 58);

  ofSetColor(255);
}

///////////////////////////////////////////////////////////////////////////
void ofApp::dibujarTextoAnimado(string texto, float y)
{
  float ancho_texto = 0;

  // No esta en el md: length() recorre la cantidad de caracteres del texto.
  for (int i = 0; i < texto.length(); i++)
  {
    // No esta en el md: substr() toma una letra para poder animarla por separado.
    string letra = texto.substr(i, 1);
    ancho_texto += anchoTextoConFallback(letra);
  }

  float x = ancho / 2 - ancho_texto / 2;

  // No esta en el md: se repite length() y substr() para dibujar letra por letra.
  for (int i = 0; i < texto.length(); i++)
  {
    string letra = texto.substr(i, 1);
    dibujarTextoConFallback(letra, x, y, alpha_letras[i]);
    x += anchoTextoConFallback(letra);
  }
}

///////////////////////////////////////////////////////////////////////////
void ofApp::dibujarTextoConFallback(string texto, float x, float y, float alpha)
{
  string letra = texto;

  if (letra == "á" || letra == "é" || letra == "í" || letra == "ó" || letra == "ú" ||
      letra == "Á" || letra == "É" || letra == "Í" || letra == "Ó" || letra == "Ú" ||
      letra == "0" || letra == "1" || letra == "2" || letra == "3" || letra == "4" ||
      letra == "5" || letra == "6" || letra == "7" || letra == "8" || letra == "9")
  {
    ofSetColor(0, alpha);
    fuente_titulo_fallback.drawString(letra, x, y);
  }
  else
  {
    ofSetColor(0, alpha);
    fuente_titulo.drawString(letra, x, y);
  }
}

///////////////////////////////////////////////////////////////////////////
float ofApp::anchoTextoConFallback(string texto)
{
  string letra = texto;

  if (letra == "á" || letra == "é" || letra == "í" || letra == "ó" || letra == "ú" ||
      letra == "Á" || letra == "É" || letra == "Í" || letra == "Ó" || letra == "Ú" ||
      letra == "0" || letra == "1" || letra == "2" || letra == "3" || letra == "4" ||
      letra == "5" || letra == "6" || letra == "7" || letra == "8" || letra == "9")
  {
    return fuente_titulo_fallback.stringWidth(letra);
  }

  return fuente_titulo.stringWidth(letra);
}

///////////////////////////////////////////////////////////////////////////
void ofApp::avanzarEscena()
{
  escena_actual++;
  if (escena_actual > 3) escena_actual = 0;
}

///////////////////////////////////////////////////////////////////////////
void ofApp::retrocederEscena()
{
  escena_actual--;
  if (escena_actual < 0) escena_actual = 3;
}

///////////////////////////////////////////////////////////////////////////
void ofApp::keyPressed(int key)
{
  if (key == 'f' || key == 'F')
  {
    pantalla_completa = !pantalla_completa;
    ofToggleFullscreen();
  }

  if (key == OF_KEY_RETURN)
  {
    if (startScreenActive)
    {
      startScreenActive = false;
    }
    else
    {
      avanzarEscena();
    }
  }
}

///////////////////////////////////////////////////////////////////////////
void ofApp::keyReleased(int key)
{
}

///////////////////////////////////////////////////////////////////////////
void ofApp::mouseMoved(int x, int y)
{
}

///////////////////////////////////////////////////////////////////////////
void ofApp::mouseDragged(int x, int y, int button)
{
}

///////////////////////////////////////////////////////////////////////////
void ofApp::mousePressed(int x, int y, int button)
{
  if (!pantalla_completa)
  {
    x = x * 2;
    y = y * 2;
  }

  if (startScreenActive &&
      x >= posicion_boton.x &&
      x <= posicion_boton.x + ancho_boton &&
      y >= posicion_boton.y &&
      y <= posicion_boton.y + alto_boton)
  {
    startScreenActive = false;
    // No esta en el md: return evita que el mismo click tambien avance de escena.
    return;
  }

  if (!startScreenActive && escena_actual == 3 &&
      x >= posicion_boton_anterior.x &&
      x <= posicion_boton_anterior.x + ancho_boton &&
      y >= posicion_boton_anterior.y &&
      y <= posicion_boton_anterior.y + alto_boton)
  {
    retrocederEscena();
    // No esta en el md: return deja el click resuelto en este boton.
    return;
  }

  if (!startScreenActive && escena_actual == 3 &&
      x >= posicion_boton_siguiente.x &&
      x <= posicion_boton_siguiente.x + ancho_boton &&
      y >= posicion_boton_siguiente.y &&
      y <= posicion_boton_siguiente.y + alto_boton)
  {
    avanzarEscena();
    // No esta en el md: return deja el click resuelto en este boton.
    return;
  }

  if (!startScreenActive) avanzarEscena();
}

///////////////////////////////////////////////////////////////////////////
void ofApp::mouseReleased(int x, int y, int button)
{
}
