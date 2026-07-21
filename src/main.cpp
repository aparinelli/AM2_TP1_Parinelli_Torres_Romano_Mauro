#include "ofMain.h"
#include "ofApp.h"

#include <memory>

int main(){
#ifdef TARGET_EMSCRIPTEN
    // Silence window setup logs to avoid locale/ostream crashes in Emscripten.
    ofSetLogLevel(OF_LOG_SILENT);
    ofGLWindowSettings settings;
    settings.setSize(960, 540);
    settings.windowMode = OF_WINDOW;
    auto window = ofCreateWindow(settings);
    ofSetLogLevel(OF_LOG_NOTICE);
    ofRunApp(window, std::make_shared<ofApp>());
    ofRunMainLoop();
#else
    ofGLFWWindowSettings settings;
    settings.setSize(960, 540);
    settings.numSamples = 8;
    settings.windowMode = OF_WINDOW;
    auto window = ofCreateWindow(settings);
    ofRunApp(window, std::make_shared<ofApp>());
    ofRunMainLoop();
#endif
}
