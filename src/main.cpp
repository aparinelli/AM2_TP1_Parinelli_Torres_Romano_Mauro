#include "ofMain.h"
#include "ofApp.h"

int main(){
#ifdef TARGET_EMSCRIPTEN
    // Silence setup-time logs to avoid locale/ostream crashes in oF shader setup.
    ofSetLogLevel(OF_LOG_SILENT);
    ofSetupOpenGL(1920, 1080, OF_WINDOW);
    ofSetLogLevel(OF_LOG_NOTICE);
    ofRunApp(new ofApp());
#else
    ofGLFWWindowSettings settings;
    settings.setSize(1920, 1080);
    settings.numSamples = 8;
    settings.windowMode = OF_WINDOW;
    auto window = ofCreateWindow(settings);
    ofRunApp(window, make_shared<ofApp>());
    ofRunMainLoop();
#endif
}
