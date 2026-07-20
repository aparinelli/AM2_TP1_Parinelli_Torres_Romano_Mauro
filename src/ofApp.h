#pragma once
#include "ofMain.h"
#ifndef TARGET_EMSCRIPTEN
#include "ofxCvHaarFinder.h"
#endif
#include <vector>
#include <string>

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

private:
    // Patron ap105 de Inkscape.
    float patScale     = 6.0f;   // tamano del tile       (q / w)
    float patAngle     = 30.0f;  // rotacion del patron   (z / x)
    float patOffX      = 0.0f;   // desplazamiento x      (flechas)
    float patOffY      = 0.0f;   // tile-grid y offset
    float patTile      = 76.0f;  // base tile size (SVG: 377.87 × 0.2 ≈ 76)
    ofPath patPath;
    ofPath path144;
    ofShader path144GradientShader;
    ofShader path144BlurShader;
    ofShader path144CameraShader;
    ofFbo path144MaskFbo;
    ofFbo path144BlurFbo[2];
    ofVideoGrabber path144Camera;
#ifndef TARGET_EMSCRIPTEN
    ofxCvHaarFinder path144FaceFinder;
#endif
    ofRectangle path144Bounds;
    glm::vec2 path144CameraFocus = {0.5f, 0.5f};
    glm::vec2 path144GradientCenter = {1618.6348f, 228.97741f};
    glm::vec2 path144GradientRadius = {267.87803f, 181.09991f};
    bool path144CameraReady = false;
    bool path144FaceFinderReady = false;
    bool path144TrackingEnabled = true;
    bool path144HasCameraFocus = false;
    float path144LastFaceSeenAt = -1000.0f;

    // Espirales animadas.
    struct Spiral {
        float cx, cy;
        float maxRadius;
        float revolutions;
        float argument;     // angulo inicial en radianes
        float expansion;    // 1 = Archimedean
        float strokeWidth;
        ofColor colStart, colEnd;
        float gradX0, gradX1;  // gradient fade-out x range (from SVG)
        float spinSpeed;       // radians/sec  (keys 1-4)
        int   steps = 900;
        ofMesh mesh;
    };
    Spiral sp1, sp2;

    // Estrellas negras tomadas del SVG.
    struct Star {
        std::string id;
        ofPath    path;
        glm::vec2 svgCenter;
        float freqX, freqY;
        float ampX,  ampY;
        float phaseX, phaseY;
        float angle    = 0.0f;
        float angleVel = 0.0f;
    };
    std::vector<Star> stars;

    // Caja amarilla con glow.
    std::vector<std::vector<glm::vec2>> boxFaces;
    glm::vec2 boxDrift = {0, 0};

    float t       = 0.0f;
    bool  paused  = false;
    bool  showHUD = true;

    static std::vector<glm::vec2> parsearPathSVGRelativo(const std::string& d);

    void configurarPatron();
    void configurarPath144();
    void configurarPath144Shader();
    void configurarPath144Camara();
    void seleccionarDispositivoCamaraPath144();
    void configurarRecursosCamaraPath144();
    void configurarDetectorRostroPath144();
    void configurarPath144CamaraShaders();
    void actualizarTrackingRostroPath144();
    void actualizarMascaraPath144();
    void configurarEspirales();
    void configurarEstrellas();
    void configurarCaja();
    void actualizarAnimacion();

    void armarMallaEspiral(Spiral& sp);
    void dibujarPatron();
    void dibujarPath144();
    void dibujarCamaraPath144();
    void dibujarCaja();
    void dibujarEstrellas();
    void dibujarEspirales();
    void dibujarHUD();
};
