#include "ofApp.h"

///////////////////////////////////////////////////////////////////////////
void ofApp::setup()
{
  ofSetWindowTitle("Prueba Camara");
  ofSetWindowShape(960, 540);
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
  fuente_texto.load("fonts/Arial.ttf", 52, true, true);

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

  textos_escenas[0] = "Primera escena: el título respira.";
  textos_escenas[1] = "Segunda escena: las letras flotan.";
  textos_escenas[2] = "Tercera escena: el pulso se queda.";

  ancho_boton = 300;
  alto_boton = 86;
  posicion_boton.set(ancho / 2 - ancho_boton / 2, 640);
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
    ancho_titulo += fuente_titulo.stringWidth(titulo_letras[i]);
  }

  float posicion_x = ancho / 2 - ancho_titulo / 2;

  for (int i = 0; i < cantidad_letras_titulo; i++)
  {
    ofSetColor(0, alpha_letras[i]);
    fuente_titulo.drawString(titulo_letras[i], posicion_x, 460);
    posicion_x += fuente_titulo.stringWidth(titulo_letras[i]);
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
  dibujarTextoAnimado(titulos_escenas[escena_actual], 450);

  string texto = textos_escenas[escena_actual];
  float texto_x = ancho / 2 - fuente_texto.stringWidth(texto) / 2;

  ofSetColor(0);
  fuente_texto.drawString(texto, texto_x, alto - 160);
  ofSetColor(255);
}

///////////////////////////////////////////////////////////////////////////
void ofApp::dibujarTextoAnimado(string texto, float y)
{
  float ancho_texto = 0;

  for (int i = 0; i < texto.length(); i++)
  {
    string letra = texto.substr(i, 1);
    ancho_texto += fuente_titulo.stringWidth(letra);
  }

  float x = ancho / 2 - ancho_texto / 2;

  for (int i = 0; i < texto.length(); i++)
  {
    string letra = texto.substr(i, 1);
    ofSetColor(0, alpha_letras[i]);
    fuente_titulo.drawString(letra, x, y);
    x += fuente_titulo.stringWidth(letra);
  }
}

///////////////////////////////////////////////////////////////////////////
void ofApp::avanzarEscena()
{
  escena_actual++;
  if (escena_actual > 2) escena_actual = 0;
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
    return;
  }

  if (!startScreenActive) avanzarEscena();
}

///////////////////////////////////////////////////////////////////////////
void ofApp::mouseReleased(int x, int y, int button)
{
}
