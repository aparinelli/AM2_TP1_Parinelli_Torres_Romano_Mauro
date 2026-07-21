#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);

    float ancho = 1920;
    float alto = 1080;

    bool pantalla_completa;
    bool startScreenActive = true;
    int escena_actual;

    ofTrueTypeFont fuente_titulo;
    ofTrueTypeFont fuente_texto;

    string titulo_juego;
    string titulo_letras[20];
    int cantidad_letras_titulo;
    float alpha_letras[20];
    bool sube_alpha_letras[20];

    string titulos_escenas[3];
    string textos_escenas[3];

    ofVec2f posicion_boton;
    float ancho_boton;
    float alto_boton;
    float alpha_boton;
    bool sube_alpha_boton;

    void configurarPantallaInicio();
    void dibujarPantallaInicio();
    void dibujarEscenaActual();
    void dibujarTextoAnimado(string texto, float y);
    void avanzarEscena();
};
