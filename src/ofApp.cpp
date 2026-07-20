#include "ofApp.h"
#include <sstream>
#include <algorithm>

namespace {
const float PAT_SOURCE_W = 377.87529f;
const float PAT_SOURCE_H = 377.95346f;
const int SVG_W = 1920;
const int SVG_H = 1080;

const std::string AP105_PATH_D = R"(M 18.012514,0.00328819 V 18.017953 H 0 v 9.608428 H 13.267106 L 0.00435402,40.889121 1.96535e-4,40.885321 V 55.186885 L 0.00435402,55.190665 27.573022,27.621997 h 0.04573 v -0.04347 L 55.187418,0.00986457 55.180615,0.00230551 H 40.868164 L 40.879124,0.01364409 27.618542,13.274192 V 0.00275906 Z m 67.818618,0 L 0,85.836574 V 292.10611 l 85.831132,85.83118 -0.01512,0.0151 H 292.00933 l -0.0197,-0.0227 85.8834,-85.88338 0.002,0.002 V 85.887749 l -0.002,0.0021 L 291.98318,0 Z m 236.860998,0 -0.007,0.00755905 27.56649,27.56647576 v 0.04611 h 0.0457 l 27.56867,27.568668 0.009,-0.0076 V 40.883036 l -0.009,0.0076 -13.26275,-13.26274 h 13.27147 v -9.60839 H 359.86677 V 0.0047622 h -9.61495 V 13.276195 l -13.2604,-13.26058555 0.011,-0.01133858 z M 95.071502,5.0731465 H 282.74272 L 372.814,95.144455 V 282.80042 l -90.07347,90.07566 H 95.07586 L 5.0023861,282.80257 V 95.142263 Z M 188.9082,22.26686 c -92.009795,0 -166.703434,74.693658 -166.703434,166.70342 0,92.0098 74.693639,166.71213 166.703434,166.71213 92.00979,0 166.70996,-74.70233 166.70996,-166.71213 0,-92.009762 -74.70017,-166.70342 -166.70996,-166.70342 z m 0,10.11583 c 86.54364,0 156.59412,70.04393 156.59412,156.58759 0,86.54366 -70.05048,156.59626 -156.59412,156.59626 -86.54365,0 -156.596305,-70.0526 -156.596305,-156.59626 0,-86.54366 70.052655,-156.58759 156.596305,-156.58759 z m 0,24.49576 c -72.89434,0 -132.091791,59.19748 -132.091791,132.09183 0,72.89435 59.197451,132.1005 132.091791,132.1005 72.89433,0 132.09832,-59.20615 132.09832,-132.1005 0,-72.89435 -59.20399,-132.09183 -132.09832,-132.09183 z m -5.05465,10.224745 v 0.0038 243.729755 C 125.37912,308.45933 77.591248,265.03082 68.493729,208.55515 h 87.653941 l -0.074,67.38743 C 134.78182,267.87979 117.29799,252.87434 106.187,233.51266 h 25.47362 v 13.95091 h 10.11586 V 223.39679 H 89.378751 l 3.316774,7.178 c 12.795735,27.68716 37.163225,48.88097 66.975815,57.7725 l 6.49417,1.93383 0.11543,-91.8418 H 67.285062 c -0.239546,-3.1262 -0.361512,-6.28528 -0.361512,-9.47342 0,-4.13775 0.208517,-8.2255 0.609782,-12.25663 h 98.747618 l -0.11543,-91.841804 -6.49417,1.936025 c -29.8126,8.891528 -54.18008,30.085379 -66.975821,57.772499 l -3.316778,7.17796 h 52.397689 v -24.06674 h -10.11585 v 13.95091 h -25.4671 c 11.11125,-19.35813 28.59097,-34.36165 49.88015,-42.423379 l 0.074,67.378699 H 68.972859 C 79.167791,111.48071 126.34323,69.441664 183.85356,67.103195 Z m 10.10713,0.0038 c 57.51126,2.337563 104.6856,44.376865 114.8807,99.490275 h -88.19405 l 0.0827,-67.37869 c 21.28811,8.062 38.76061,23.06589 49.87143,42.42331 h -25.46708 v -13.95085 h -10.11584 v 24.06679 h 52.39767 l -3.31678,-7.17804 c -12.79573,-27.6906 -37.1632,-48.885166 -66.9758,-57.776694 l -6.49418,-1.936025 -0.11543,91.841799 h 99.769 c 0.40124,4.03113 0.60761,8.11892 0.60761,12.25663 0,3.18815 -0.122,6.34723 -0.36151,9.47343 H 210.51407 l 0.11543,91.8418 6.49417,-1.93384 c 29.8126,-8.89152 54.18007,-30.08534 66.97581,-57.77249 l 3.31677,-7.17801 h -52.39767 v 24.06679 h 10.11585 v -13.95092 h 25.47364 c -11.11059,19.36097 -28.58718,34.36694 -49.87798,42.42992 l -0.0827,-67.38742 h 88.67534 c -9.09758,56.47642 -56.8866,99.90515 -115.362,102.28214 z m 183.91234,255.648755 -3.57376,3.57377 -23.99272,23.99274 h -0.0544 v 0.0544 l -27.56213,27.55997 0.0151,0.0151 h 14.30374 l -0.0132,-0.0113 13.25622,-13.2562 v 13.26924 h 9.61494 V 359.9323 h 18.00817 v -9.60624 h -13.26275 l 13.26056,-13.26058 0.002,0.002 V 322.75966 Z M 0,322.75951 v 14.30593 l 13.271463,13.25631 -13.271417645669,0.002 v 9.60839 L 18.012518,359.93014 v 18.02121 h 9.60624 v -13.28013 l 13.267105,13.26709 -0.01323,0.0113 H 55.16766 l 0.01965,-0.0227 z)";

const std::string PATH144_D = R"(m 1452.9632,210.52298 c -14.7839,5.91355 -49.0826,9.4617 -69.1887,14.19254 -20.1061,4.73085 -26.0197,10.64442 -29.5679,26.01969 -3.5481,15.37527 -4.7308,40.21226 -1.774,56.77024 2.9568,16.55798 10.0531,24.83697 27.7938,31.34189 17.7407,6.50492 46.1258,11.23577 65.0492,10.05306 18.9234,-1.18271 28.3851,-8.27899 35.4814,-13.6012 7.0963,-5.32221 11.8271,-8.87032 18.9234,-14.7839 7.0963,-5.91358 16.558,-14.19257 20.6975,-12.4185 4.1395,1.77407 2.9567,13.6012 4.1394,31.93326 1.1828,18.33205 4.7309,43.16905 12.4186,56.77024 7.6876,13.60119 19.5147,15.96662 38.4382,10.64441 18.9234,-5.3222 44.9431,-18.33205 61.5011,-27.79374 16.5579,-9.46169 23.6542,-15.37527 28.3851,-20.10613 4.7308,-4.73085 7.0962,-8.27898 9.4617,-10.64442 2.3654,-2.36544 4.7308,-3.54816 7.0962,-6.50496 2.3655,-2.95679 4.7309,-7.68761 7.0963,-6.50488 2.3654,1.18273 4.7309,8.27898 11.2358,12.41847 6.5049,4.13949 17.1493,5.3222 33.7073,-5.3222 16.558,-10.64441 39.0296,-33.11599 50.2653,-45.53447 11.2358,-12.41848 11.2358,-14.78391 6.5049,-22.47155 -4.7308,-7.68764 -14.1925,-20.69748 -19.5147,-27.79376 -5.3222,-7.09628 -6.5049,-8.27899 -6.5049,-8.87035 0,-0.59136 1.1827,-0.59136 3.5481,-0.59136 2.3654,0 5.9136,0 13.6012,-0.59136 7.6876,-0.59135 19.5148,-1.77407 37.2555,-10.64442 17.7407,-8.87036 41.3949,-25.42831 54.4048,-36.07273 13.0098,-10.64443 15.3753,-15.3753 11.2358,-19.51479 -4.1395,-4.13948 -14.7839,-7.68761 -21.8802,-10.6444 -7.0963,-2.95678 -10.6444,-5.32219 -27.7938,-5.91356 -17.1493,-0.59138 -47.8999,0.59134 -68.006,2.95676 -20.1061,2.36543 -29.5678,5.91357 -34.89,8.87035 -5.3222,2.95678 -6.505,5.32222 -5.3223,0.59136 1.1827,-4.73087 4.7309,-16.558 8.279,-30.1592 3.5481,-13.6012 7.0963,-28.97647 -1.1827,-39.029528 -8.279,-10.05306 -28.3851,-14.783914 -44.3517,-16.557985 -15.9666,-1.774072 -27.7938,-0.591353 -34.8901,5.322209 -7.0962,5.913562 -9.4617,16.557994 -9.4617,15.375284 0,-1.18271 2.3655,-14.192574 -12.4185,-27.202423 -14.7839,-13.009849 -46.7171,-26.019672 -66.8233,-26.611034 -20.1061,-0.591363 -28.3851,11.23577 -32.5246,20.697476 -4.1395,9.461706 -4.1395,16.557985 -2.9568,21.88021 1.1828,5.322226 3.5482,8.870349 4.7309,11.235771 1.1827,2.36542 1.1827,3.54813 0.5914,1.77406 -0.5914,-1.77407 -1.7741,-6.504922 -4.7309,-11.82714 -2.9568,-5.322218 -7.6876,-11.235752 -17.7407,-14.192543 -10.0531,-2.956791 -25.4283,-2.956791 -35.4814,5.91355 -10.0531,8.870341 -14.7839,26.611043 -15.9666,37.255483 -1.1827,10.64444 1.1827,14.19257 5.3222,16.55799 4.1395,2.36542 10.053,3.54812 12.4185,4.13948 2.3654,0.59136 1.1827,0.59136 -1.1828,0.59136 -2.3654,0 -5.9135,0 -13.0098,1.77407 -7.0963,1.77407 -17.7407,5.32221 -23.0629,9.4617 -5.3222,4.1395 -5.3222,8.87036 -2.3654,14.78393 2.9568,5.91358 8.8703,13.00982 12.4185,16.55797 3.5481,3.54815 4.7308,3.54815 7.6876,7.68765 2.9568,4.13951 7.6876,12.41851 -7.0963,18.33207 z)";

ofPath parsearPathSVGOriginal(const std::string& d) {
    ofxSvg svg;
    svg.loadFromString("<svg xmlns='http://www.w3.org/2000/svg'><path d='" + d + "'/></svg>");
    ofPath path;
    if (svg.getNumPath() > 0) {
        path = svg.getPathAt(0);
    }
    path.setFilled(true);
    path.setFillColor(ofColor::black);
    path.setStrokeWidth(0);
    path.setPolyWindingMode(OF_POLY_WINDING_ODD);
    path.setCurveResolution(48);
    return path;
}

bool contieneAlguna(const std::string& texto, const std::vector<std::string>& agujas) {
    for (const auto& aguja : agujas) {
        if (texto.find(aguja) != std::string::npos) return true;
    }
    return false;
}

bool esCamaraVirtual(const ofVideoDevice& device) {
    std::string name = ofToLower(device.deviceName + " " + device.hardwareName);
    return contieneAlguna(name, {"ndi", "virtual"});
}

bool esCamaraMac(const ofVideoDevice& device) {
    std::string name = ofToLower(device.deviceName + " " + device.hardwareName);
    return contieneAlguna(name, {"facetime", "macbook", "built-in", "integrated"});
}

ofRectangle calcularBoundsPath(const ofPath& path) {
    const auto& vertices = path.getTessellation().getVertices();
    if (vertices.empty()) return ofRectangle(0, 0, SVG_W, SVG_H);

    float minX = vertices.front().x;
    float maxX = vertices.front().x;
    float minY = vertices.front().y;
    float maxY = vertices.front().y;

    for (const auto& v : vertices) {
        minX = std::min(minX, v.x);
        maxX = std::max(maxX, v.x);
        minY = std::min(minY, v.y);
        maxY = std::max(maxY, v.y);
    }

    if (maxX <= minX || maxY <= minY) return ofRectangle(0, 0, SVG_W, SVG_H);
    return ofRectangle(minX, minY, maxX - minX, maxY - minY);
}

#ifndef TARGET_EMSCRIPTEN
ofRectangle elegirCaraPrincipal(const std::vector<ofxCvBlob>& blobs) {
    ofRectangle mejor;
    float mejorArea = 0.0f;
    for (const auto& blob : blobs) {
        float area = blob.boundingRect.getArea();
        if (area > mejorArea) {
            mejorArea = area;
            mejor = blob.boundingRect;
        }
    }
    return mejor;
}
#endif

void cargarShader(ofShader& shader, const std::string& vertex, const std::string& fragment, bool bindDefaults) {
    shader.setupShaderFromSource(GL_VERTEX_SHADER, vertex);
    shader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragment);
    if (bindDefaults) shader.bindDefaults();
    shader.linkProgram();
}

void dibujarBlurPass(ofShader& shader, ofFbo& source, ofFbo& target, const glm::vec2& direction) {
    target.begin();
    ofClear(0, 0, 0, 255);
    shader.begin();
    shader.setUniformTexture("sourceTex", source.getTexture(), 0);
    shader.setUniform2f("direction", direction);
    source.draw(0, 0);
    shader.end();
    target.end();
}
}

// Convierte paths relativos del SVG en puntos absolutos.
std::vector<glm::vec2> ofApp::parsearPathSVGRelativo(const std::string& d) {
    std::string s;
    for (char c : d)
        s += (c == ',' || c == 'm' || c == 'M' || c == 'z' || c == 'Z') ? ' ' : c;
    std::istringstream ss(s);
    std::vector<glm::vec2> pts;
    float x, y;
    if (!(ss >> x >> y)) return pts;
    pts.push_back({x, y});
    float cx = x, cy = y, dx, dy;
    while (ss >> dx >> dy) { cx += dx; cy += dy; pts.push_back({cx, cy}); }
    return pts;
}

// Arma una linea gruesa como triangle strip.
void ofApp::armarMallaEspiral(Spiral& sp) {
    sp.mesh.clear();
    sp.mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);

    std::vector<glm::vec3> pts;
    pts.reserve(sp.steps + 1);
    for (int i = 0; i <= sp.steps; i++) {
        float u = float(i) / sp.steps;
        float a = sp.argument + u * sp.revolutions * TWO_PI;
        float r = sp.maxRadius * pow(u, sp.expansion);
        pts.push_back({sp.cx + r * cos(a), sp.cy + r * sin(a), 0.f});
    }

    float hw = sp.strokeWidth * 0.5f;
    float span = sp.gradX1 - sp.gradX0;
    for (int i = 0; i < (int)pts.size(); i++) {
        glm::vec3 dir;
        if      (i == 0)                   dir = glm::normalize(pts[1]   - pts[0]);
        else if (i == (int)pts.size() - 1) dir = glm::normalize(pts[i]   - pts[i-1]);
        else                               dir = glm::normalize(pts[i+1] - pts[i-1]);

        glm::vec3 n = glm::vec3(-dir.y, dir.x, 0.f) * hw;

        float u = ofClamp((pts[i].x - sp.gradX0) / span, 0.f, 1.f);
        ofColor col = sp.colStart.getLerped(sp.colEnd, u);

        sp.mesh.addVertex(pts[i] + n);  sp.mesh.addColor(col);
        sp.mesh.addVertex(pts[i] - n);  sp.mesh.addColor(col);
    }
}

void ofApp::setup() {
    ofSetWindowTitle("drawing.svg · animated");
    ofSetFrameRate(60);
    ofBackground(255);
    ofSetCircleResolution(160);
    ofEnableSmoothing();
    ofEnableAntiAliasing();

    configurarPatron();
    configurarPath144();
    configurarPath144Camara();
    configurarEspirales();
    configurarEstrellas();
    configurarCaja();
}

void ofApp::configurarPatron() {
    patPath = parsearPathSVGOriginal(AP105_PATH_D);
}

void ofApp::configurarPath144() {
    path144 = parsearPathSVGOriginal(PATH144_D);
    path144.setFillColor(ofColor(255, 0, 0));
    path144.setStrokeWidth(0);
    path144Bounds = calcularBoundsPath(path144);
    configurarPath144Shader();
}

void ofApp::configurarPath144Shader() {
    if (ofIsGLProgrammableRenderer()) {
        const std::string vertexShader = R"(
            #version 150
            uniform mat4 modelViewProjectionMatrix;
            in vec4 position;
            out vec2 vPosition;

            void main() {
                vPosition = position.xy;
                gl_Position = modelViewProjectionMatrix * position;
            }
        )";

        const std::string fragmentShader = R"(
            #version 150
            uniform vec2 gradientCenter;
            uniform vec2 gradientRadius;
            in vec2 vPosition;
            out vec4 outputColor;

            void main() {
                vec2 p = (vPosition - gradientCenter) / gradientRadius;
                float alpha = clamp(1.0 - length(p), 0.0, 1.0);
                outputColor = vec4(1.0, 0.0, 0.0, alpha);
            }
        )";

        cargarShader(path144GradientShader, vertexShader, fragmentShader, true);
    } else {
        const std::string vertexShader = R"(
            #version 120
            varying vec2 vPosition;

            void main() {
                vPosition = gl_Vertex.xy;
                gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
            }
        )";

        const std::string fragmentShader = R"(
            #version 120
            uniform vec2 gradientCenter;
            uniform vec2 gradientRadius;
            varying vec2 vPosition;

            void main() {
                vec2 p = (vPosition - gradientCenter) / gradientRadius;
                float alpha = clamp(1.0 - length(p), 0.0, 1.0);
                gl_FragColor = vec4(1.0, 0.0, 0.0, alpha);
            }
        )";

        cargarShader(path144GradientShader, vertexShader, fragmentShader, false);
    }
}

void ofApp::configurarPath144Camara() {
    seleccionarDispositivoCamaraPath144();
    configurarRecursosCamaraPath144();
    configurarDetectorRostroPath144();
#ifndef TARGET_EMSCRIPTEN
    configurarPath144CamaraShaders();
#endif
    actualizarMascaraPath144();
}

void ofApp::seleccionarDispositivoCamaraPath144() {
    auto devices = path144Camera.listDevices();
    int selectedDeviceId = -1;

    for (auto& device : devices) {
        ofLogNotice("camera") << device.id << " : " << device.deviceName
                              << " / " << device.hardwareName;

        if (device.bAvailable && esCamaraMac(device) && !esCamaraVirtual(device)) {
            selectedDeviceId = device.id;
            break;
        }
    }

    if (selectedDeviceId < 0) {
        for (auto& device : devices) {
            if (device.bAvailable && !esCamaraVirtual(device)) {
                selectedDeviceId = device.id;
                break;
            }
        }
    }

    if (selectedDeviceId < 0 && !devices.empty()) {
        selectedDeviceId = devices.front().id;
    }

    if (selectedDeviceId >= 0) {
        ofLogNotice("camera") << "using device " << selectedDeviceId;
        path144Camera.setDeviceID(selectedDeviceId);
    } else {
        ofLogWarning("camera") << "no camera devices found";
    }
}

void ofApp::configurarRecursosCamaraPath144() {
    path144Camera.setDesiredFrameRate(30);
    path144Camera.setup(1280, 720);
    path144CameraReady = path144Camera.isInitialized();

    path144MaskFbo.allocate(SVG_W, SVG_H, GL_RGBA);
    path144BlurFbo[0].allocate(SVG_W, SVG_H, GL_RGBA);
    path144BlurFbo[1].allocate(SVG_W, SVG_H, GL_RGBA);
}

void ofApp::configurarDetectorRostroPath144() {
#ifndef TARGET_EMSCRIPTEN
    const auto cascadePath = ofToDataPath("haarcascade_frontalface_default.xml", true);
    if (!ofFile::doesFileExist(cascadePath)) {
        ofLogWarning("camera") << "missing haar cascade: " << cascadePath;
        path144FaceFinderReady = false;
        return;
    }

    path144FaceFinder.setup(cascadePath);
    path144FaceFinder.setScaleHaar(1.2f);
    path144FaceFinder.setNeighbors(2);
    path144FaceFinderReady = true;
#endif
}

void ofApp::configurarPath144CamaraShaders() {
    if (ofIsGLProgrammableRenderer()) {
        const std::string blurVertexShader = R"(
            #version 150
            uniform mat4 modelViewProjectionMatrix;
            in vec4 position;
            in vec2 texcoord;
            out vec2 vTexCoord;

            void main() {
                vTexCoord = texcoord;
                gl_Position = modelViewProjectionMatrix * position;
            }
        )";

        const std::string blurFragmentShader = R"(
            #version 150
            uniform sampler2DRect sourceTex;
            uniform vec2 direction;
            in vec2 vTexCoord;
            out vec4 outputColor;

            void main() {
                vec4 sum = texture(sourceTex, vTexCoord) * 0.227027;
                sum += texture(sourceTex, vTexCoord + direction * 1.384615) * 0.316216;
                sum += texture(sourceTex, vTexCoord - direction * 1.384615) * 0.316216;
                sum += texture(sourceTex, vTexCoord + direction * 3.230769) * 0.070270;
                sum += texture(sourceTex, vTexCoord - direction * 3.230769) * 0.070270;
                outputColor = sum;
            }
        )";

        const std::string cameraVertexShader = R"(
            #version 150
            uniform mat4 modelViewProjectionMatrix;
            in vec4 position;
            out vec2 vCanvasPosition;

            void main() {
                vCanvasPosition = position.xy;
                gl_Position = modelViewProjectionMatrix * position;
            }
        )";

        const std::string cameraFragmentShader = R"(
            #version 150
            uniform sampler2DRect cameraTex;
            uniform sampler2DRect maskTex;
            uniform vec2 cameraSize;
            uniform vec2 canvasSize;
            uniform vec4 pathBounds;
            uniform vec2 focusCenter;
            uniform float mirrorCamera;
            in vec2 vCanvasPosition;
            out vec4 outputColor;

            vec2 coverCameraCoord(vec2 canvasPosition) {
                vec2 targetUv = clamp((canvasPosition - pathBounds.xy) / pathBounds.zw, vec2(0.0), vec2(1.0));
                float targetAspect = pathBounds.z / pathBounds.w;
                float cameraAspect = cameraSize.x / cameraSize.y;
                vec2 sourceSize = vec2(1.0);

                if (cameraAspect > targetAspect) {
                    sourceSize.x = targetAspect / cameraAspect;
                } else {
                    sourceSize.y = cameraAspect / targetAspect;
                }

                vec2 effectiveFocus = clamp(focusCenter, vec2(0.0), vec2(1.0));
                if (mirrorCamera > 0.5) effectiveFocus.x = 1.0 - effectiveFocus.x;

                vec2 sourceMin = clamp(effectiveFocus - sourceSize * 0.5, vec2(0.0), vec2(1.0) - sourceSize);
                vec2 cameraUv = sourceMin + targetUv * sourceSize;
                if (mirrorCamera > 0.5) cameraUv.x = 1.0 - cameraUv.x;

                return cameraUv * cameraSize;
            }

            void main() {
                float mask = texture(maskTex, vCanvasPosition).r;
                vec3 cameraColor = texture(cameraTex, coverCameraCoord(vCanvasPosition)).rgb;
                outputColor = vec4(cameraColor, mask);
            }
        )";

        cargarShader(path144BlurShader, blurVertexShader, blurFragmentShader, true);
        cargarShader(path144CameraShader, cameraVertexShader, cameraFragmentShader, true);
    } else {
        const std::string blurVertexShader = R"(
            #version 120
            varying vec2 vTexCoord;

            void main() {
                vTexCoord = gl_MultiTexCoord0.xy;
                gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
            }
        )";

        const std::string blurFragmentShader = R"(
            #version 120
            uniform sampler2DRect sourceTex;
            uniform vec2 direction;
            varying vec2 vTexCoord;

            void main() {
                vec4 sum = texture2DRect(sourceTex, vTexCoord) * 0.227027;
                sum += texture2DRect(sourceTex, vTexCoord + direction * 1.384615) * 0.316216;
                sum += texture2DRect(sourceTex, vTexCoord - direction * 1.384615) * 0.316216;
                sum += texture2DRect(sourceTex, vTexCoord + direction * 3.230769) * 0.070270;
                sum += texture2DRect(sourceTex, vTexCoord - direction * 3.230769) * 0.070270;
                gl_FragColor = sum;
            }
        )";

        const std::string cameraVertexShader = R"(
            #version 120
            varying vec2 vCanvasPosition;

            void main() {
                vCanvasPosition = gl_Vertex.xy;
                gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
            }
        )";

        const std::string cameraFragmentShader = R"(
            #version 120
            uniform sampler2DRect cameraTex;
            uniform sampler2DRect maskTex;
            uniform vec2 cameraSize;
            uniform vec2 canvasSize;
            uniform vec4 pathBounds;
            uniform vec2 focusCenter;
            uniform float mirrorCamera;
            varying vec2 vCanvasPosition;

            vec2 coverCameraCoord(vec2 canvasPosition) {
                vec2 targetUv = clamp((canvasPosition - pathBounds.xy) / pathBounds.zw, vec2(0.0), vec2(1.0));
                float targetAspect = pathBounds.z / pathBounds.w;
                float cameraAspect = cameraSize.x / cameraSize.y;
                vec2 sourceSize = vec2(1.0);

                if (cameraAspect > targetAspect) {
                    sourceSize.x = targetAspect / cameraAspect;
                } else {
                    sourceSize.y = cameraAspect / targetAspect;
                }

                vec2 effectiveFocus = clamp(focusCenter, vec2(0.0), vec2(1.0));
                if (mirrorCamera > 0.5) effectiveFocus.x = 1.0 - effectiveFocus.x;

                vec2 sourceMin = clamp(effectiveFocus - sourceSize * 0.5, vec2(0.0), vec2(1.0) - sourceSize);
                vec2 cameraUv = sourceMin + targetUv * sourceSize;
                if (mirrorCamera > 0.5) cameraUv.x = 1.0 - cameraUv.x;

                return cameraUv * cameraSize;
            }

            void main() {
                float mask = texture2DRect(maskTex, vCanvasPosition).r;
                vec3 cameraColor = texture2DRect(cameraTex, coverCameraCoord(vCanvasPosition)).rgb;
                gl_FragColor = vec4(cameraColor, mask);
            }
        )";

        cargarShader(path144BlurShader, blurVertexShader, blurFragmentShader, false);
        cargarShader(path144CameraShader, cameraVertexShader, cameraFragmentShader, false);
    }
}

void ofApp::actualizarMascaraPath144() {
    path144MaskFbo.begin();
    ofClear(0, 0, 0, 255);
    ofFill();
    path144.setFillColor(ofColor::white);
    path144.draw();
    path144.setFillColor(ofColor(255, 0, 0));
    path144MaskFbo.end();

    path144BlurFbo[0].begin();
    ofClear(0, 0, 0, 255);
    path144MaskFbo.draw(0, 0);
    path144BlurFbo[0].end();

    if (!path144BlurShader.isLoaded()) return;

    const float blurRadius = 6.0f;
    for (int i = 0; i < 4; i++) {
        dibujarBlurPass(path144BlurShader, path144BlurFbo[0], path144BlurFbo[1], {blurRadius, 0.0f});
        dibujarBlurPass(path144BlurShader, path144BlurFbo[1], path144BlurFbo[0], {0.0f, blurRadius});
    }
}

void ofApp::configurarEspirales() {
    // Spiral 1 (path1)
    // sodipodi: cx=531.877 cy=290.411 radius=944.324 revolution=3
    //           argument=-18.444664  stroke=linearGradient61 (red→transparent)
    sp1.cx          = 531.877f;
    sp1.cy          = 290.411f;
    sp1.maxRadius   = 944.324f;
    sp1.revolutions = 3.0f;
    sp1.argument    = -18.4447f;
    sp1.expansion   = 1.0f;
    sp1.strokeWidth = 60.565f;
    sp1.colStart    = ofColor(255, 0, 0, 255);
    sp1.colEnd      = ofColor(255, 0, 0, 0);
    sp1.gradX0      = -265.89f;   // linearGradient61 x1
    sp1.gradX1      =  1486.66f;  // linearGradient61 x2
    sp1.spinSpeed   = 0.5f;

    // Spiral 2 (path2 + SVG matrix transform)
    // SVG: matrix(0.785,0,0,0.785,-50.30,-133.69) applied before drawing.
    {
        const float sc = 0.78531339f;
        sp2.cx          = sc * 1876.2537f - 50.29775f;
        sp2.cy          = sc * 861.44513f - 133.69286f;
        sp2.maxRadius   = sc * 1006.0836f;
        sp2.revolutions = 3.0f;
        sp2.argument    = -21.6643f;
        sp2.expansion   = 1.0f;
        sp2.strokeWidth = 60.565f * sc;
        sp2.colStart    = ofColor(255, 0, 214, 255);  // magenta #ff00d6
        sp2.colEnd      = ofColor(255, 0, 0,   0);
        sp2.gradX0      =  856.52f;   // linearGradient60 x1
        sp2.gradX1      = 2728.66f;   // linearGradient60 x2
        sp2.spinSpeed   = -0.3f;
    }

    armarMallaEspiral(sp1);
    armarMallaEspiral(sp2);
}

void ofApp::configurarEstrellas() {
    // Estrellas.
    // 4 irregular 9-pointed stars (fill:#262626).
    // Paths: "m X,Y [dx,dy]* z" parsed into absolute coords.
    struct SrcStar { std::string id; std::string d; glm::vec2 center; };
    const SrcStar starDefs[] = {
        {
            "path139",
            "m 1346.7693,448.11913 -7.4623,109.14037 192.4835,-42.99887 "
            "-124.0391,273.55488 -126.53,108.63787 27.893,-21.34117 "
            "-252.2303,74.11438 -73.29207,-188.03112 -112.8243,64.66065 "
            "-121.69763,-7.18217 5.77723,-75.41869 60.40026,-151.49079 "
            "36.91315,-107.26602 -13.15916,-56.8578 35.03273,-111.2162 "
            "300.71039,0.97289 13.8744,-112.6139 29.8305,139.90941 z",
            {1110.0961f, 562.2192f}
        },
        {
            "path140",
            "m 1463.625,150.98283 -38.5433,38.33562 35.1424,-150.137804 "
            "50.6,-54.614857 30.335,-53.647889 110.2148,53.953767 "
            "32.1085,-33.313342 51.2923,126.397197 104.8594,-41.849585 "
            "-88.5486,176.322403 26.5901,28.29094 42.3622,81.18872 "
            "-16.1808,42.57725 -131.9883,-21.8406 -24.9861,60.24679 "
            "-76.9442,-99.01931 -119.3103,65.06751 53.2913,-135.13025 z",
            {1632.1568f, 180.71332f}
        },
        {
            "path141",
            "m 522.28086,336.43821 -6.1085,29.74728 -94.28471,19.91867 "
            "-65.70705,65.61087 -34.33864,-34.297 -43.72232,-62.67352 "
            "-135.6539,5.90077 35.36839,9.63096 -91.243974,-75.97722 "
            "53.353144,-54.48316 -17.32816,-104.99929 138.18799,-67.212844 "
            "78.60476,23.17501 82.51013,-7.283019 73.88241,34.349733 "
            "12.23017,-21.514112 38.70576,161.851152 -96.44554,-36.29617 z",
            {327.00505f, 261.03034f}
        },
        {
            "path142",
            "m 1862.1805,980.71466 -76.398,41.45604 -36.8919,139.298 "
            "-75.9982,-70.0932 -133.9083,-8.3151 15.4648,-112.26444 "
            "-76.6467,-43.66825 -3.8027,-98.49 13.7612,-24.46528 "
            "117.5469,-38.038 -30.6042,-50.40896 140.3902,-2.91424 "
            "80.8284,-19.86242 -34.8856,33.56901 88.2342,-36.73681 "
            "45.6042,68.27784 119.6976,150.31551 -153.6225,13.34663 z",
            {1715.3423f, 892.09272f}
        }
    };

    for (auto& src : starDefs) {
        auto verts = parsearPathSVGRelativo(src.d);
        Star s;
        s.id = src.id;
        s.svgCenter = src.center;
        s.path.setFillColor(ofColor(38, 38, 38));
        s.path.setFilled(true);
        s.path.setStrokeWidth(0);
        if (!verts.empty()) {
            s.path.moveTo(verts[0].x, verts[0].y);
            for (size_t i = 1; i < verts.size(); i++)
                s.path.lineTo(verts[i].x, verts[i].y);
            s.path.close();
        }
        s.freqX  = ofRandom(0.08f, 0.18f);
        s.freqY  = ofRandom(0.07f, 0.15f);
        s.ampX   = ofRandom(40.f,  90.f);
        s.ampY   = ofRandom(30.f,  70.f);
        s.phaseX = ofRandom(TWO_PI);
        s.phaseY = ofRandom(TWO_PI);
        s.angleVel = ofRandom(-0.12f, 0.12f);
        stars.push_back(std::move(s));
    }

}

void ofApp::configurarCaja() {
    // Caras de la caja (g80, amarillo #fcfc03).
    // Negative X is intentional — box partially off the left canvas edge.
    boxFaces = {
        {{289.861f,390.770f},{666.929f,252.881f},{-129.895f,879.920f},{-119.258f,712.715f}},
        {{666.929f,252.881f},{-129.895f,879.920f},{42.112f,832.768f},{838.936f,205.729f}},
        {{289.861f,390.770f},{666.929f,252.881f},{838.936f,205.729f},{378.176f,366.560f}},
        {{-119.258f,712.715f},{-129.895f,879.920f},{42.112f,832.768f},{-30.943f,688.505f}},
        {{289.861f,390.770f},{-119.258f,712.715f},{-30.943f,688.505f},{378.176f,366.560f}},
        {{378.176f,366.560f},{838.936f,205.729f},{42.112f,832.768f},{-30.943f,688.505f}},
    };
}

void ofApp::update() {
    if (path144CameraReady) {
        path144Camera.update();
        if (path144Camera.isFrameNew()) actualizarTrackingRostroPath144();
    }
    if (paused) return;

    actualizarAnimacion();
}

void ofApp::actualizarTrackingRostroPath144() {
    if (!path144TrackingEnabled) {
        path144CameraFocus = {0.5f, 0.5f};
        path144HasCameraFocus = false;
        return;
    }

    if (!path144FaceFinderReady) {
        path144CameraFocus = {0.5f, 0.5f};
        path144HasCameraFocus = false;
        return;
    }

    auto& pixels = path144Camera.getPixels();
    if (!pixels.isAllocated() || pixels.getWidth() <= 0 || pixels.getHeight() <= 0) {
        return;
    }

#ifndef TARGET_EMSCRIPTEN
    path144FaceFinder.findHaarObjects(pixels, 80, 80);
    ofRectangle face = elegirCaraPrincipal(path144FaceFinder.blobs);
#else
    ofRectangle face;  // no face detection in Emscripten
#endif

    if (face.getArea() > 0.0f) {
        glm::vec2 target = {
            ofClamp(face.getCenter().x / pixels.getWidth(), 0.0f, 1.0f),
            ofClamp(face.getCenter().y / pixels.getHeight(), 0.0f, 1.0f)
        };

        path144CameraFocus = path144HasCameraFocus
            ? glm::mix(path144CameraFocus, target, 0.18f)
            : target;
        path144HasCameraFocus = true;
        path144LastFaceSeenAt = ofGetElapsedTimef();
        return;
    }

    if (ofGetElapsedTimef() - path144LastFaceSeenAt > 1.2f) {
        path144CameraFocus = glm::mix(path144CameraFocus, glm::vec2(0.5f, 0.5f), 0.04f);
        path144HasCameraFocus = false;
    }
}

void ofApp::actualizarAnimacion() {
    float dt = ofGetLastFrameTime();
    t += dt;

    sp1.argument += sp1.spinSpeed * dt;
    sp2.argument += sp2.spinSpeed * dt;
    armarMallaEspiral(sp1);
    armarMallaEspiral(sp2);

    for (auto& s : stars)
        s.angle += s.angleVel * dt;

    boxDrift.x = sin(t * 0.22f) * 55.0f;
    boxDrift.y = cos(t * 0.15f) * 35.0f;
}

void ofApp::dibujarPatron() {
    float tile = patTile * patScale;
    int cols = int(1920.0f / tile) + 6;
    int rows = int(1080.0f / tile) + 6;
    float ox = fmod(patOffX, tile) - 2.0f * tile;
    float oy = fmod(patOffY, tile) - 2.0f * tile;

    ofPushMatrix();
    ofTranslate(960, 540);
    ofRotateDeg(patAngle);
    ofTranslate(-960, -540);
    ofTranslate(ox, oy);

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            float tx = col * tile;
            float ty = row * tile;
            ofPushMatrix();
            ofTranslate(tx, ty);
            ofScale(tile / PAT_SOURCE_W, tile / PAT_SOURCE_H);
            patPath.draw();
            ofPopMatrix();
        }
    }
    ofPopMatrix();
}

void ofApp::dibujarPath144() {
    ofFill();
    if (!path144GradientShader.isLoaded()) {
        path144.draw();
        return;
    }

    path144GradientShader.begin();
    path144GradientShader.setUniform2f("gradientCenter", path144GradientCenter);
    path144GradientShader.setUniform2f("gradientRadius", path144GradientRadius);
    path144.draw();
    path144GradientShader.end();
}

void ofApp::dibujarCamaraPath144() {
    if (!path144CameraReady) return;
    if (!path144CameraShader.isLoaded()) return;

    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    path144CameraShader.begin();
    path144CameraShader.setUniformTexture("cameraTex", path144Camera.getTexture(), 0);
    path144CameraShader.setUniformTexture("maskTex", path144BlurFbo[0].getTexture(), 1);
    path144CameraShader.setUniform2f("cameraSize",
        path144Camera.getWidth(), path144Camera.getHeight());
    path144CameraShader.setUniform2f("canvasSize", SVG_W, SVG_H);
    path144CameraShader.setUniform4f("pathBounds",
        path144Bounds.x, path144Bounds.y, path144Bounds.width, path144Bounds.height);
    path144CameraShader.setUniform2f("focusCenter", path144CameraFocus);
    path144CameraShader.setUniform1f("mirrorCamera", 1.0f);
    ofSetColor(255);
    ofDrawRectangle(0, 0, SVG_W, SVG_H);
    path144CameraShader.end();
}

void ofApp::dibujarCaja() {
    const glm::vec2 boxCenter = {200.0f, 550.0f};
    ofFill();
    ofEnableBlendMode(OF_BLENDMODE_ADD);

    for (int pass = 28; pass >= 0; pass--) {
        float expand = 1.0f + pass * 0.065f;
        ofSetColor(252, 252, 3, 11);
        for (auto& face : boxFaces) {
            ofPushMatrix();
            ofTranslate(boxDrift.x, boxDrift.y);
            ofTranslate(boxCenter);
            ofScale(expand);
            ofTranslate(-boxCenter);
            ofBeginShape();
            for (auto& p : face) ofVertex(p.x, p.y);
            ofEndShape(true);
            ofPopMatrix();
        }
    }
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
}

void ofApp::dibujarEstrellas() {
    for (auto& s : stars) {
        float dx = s.ampX * sin(t * s.freqX + s.phaseX);
        float dy = s.ampY * cos(t * s.freqY + s.phaseY);
        ofPushMatrix();
        ofTranslate(dx, dy);
        ofTranslate(s.svgCenter.x, s.svgCenter.y);
        ofRotateRad(s.angle);
        ofTranslate(-s.svgCenter.x, -s.svgCenter.y);
        s.path.draw();
        ofPopMatrix();
    }
}

void ofApp::dibujarEspirales() {
    ofFill();
    sp1.mesh.draw();
    sp2.mesh.draw();
}

void ofApp::dibujarHUD() {
    if (!showHUD) return;
    std::string tracking = path144TrackingEnabled ? "on" : "off";
    std::string info =
        "── Pattern ──────────────────────\n"
        "  q/w    patScale     = " + ofToString(patScale,     2) + "\n"
        "  e/r    patTile      = " + ofToString(patTile,      1) + " px\n"
        "  z/x    patAngle     = " + ofToString(patAngle,      1) + "\n"
        "  arrows patOffset    = " + ofToString((int)patOffX)+","+ofToString((int)patOffY)+"\n"
        "── Spirals ──────────────────────\n"
        "  1/2    sp1 spinSpeed   = " + ofToString(sp1.spinSpeed, 2) + " rad/s\n"
        "  3/4    sp2 spinSpeed   = " + ofToString(sp2.spinSpeed, 2) + " rad/s\n"
        "  5/6    sp1 revolutions = " + ofToString(sp1.revolutions, 1) + "\n"
        "  7/8    sp2 revolutions = " + ofToString(sp2.revolutions, 1) + "\n"
        "  9/0    sp1 maxRadius   = " + ofToString((int)sp1.maxRadius) + "\n"
        "── Global ───────────────────────\n"
        "  SPACE  pause / resume\n"
        "  t      tracking = " + tracking + "\n"
        "  h      toggle HUD\n";
    ofDrawBitmapStringHighlight(info, 12, 18,
        ofColor(0,0,0,160), ofColor(255,255,255,180));
}

void ofApp::draw() {
    ofBackground(255);

    // Scale SVG space (1920×1080) to fit window
    float sc = std::min(ofGetWidth()  / 1920.0f,
                        ofGetHeight() / 1080.0f);
    float tx = (ofGetWidth()  - 1920.0f * sc) * 0.5f;
    float ty = (ofGetHeight() - 1080.0f * sc) * 0.5f;

    ofPushMatrix();
    ofTranslate(tx, ty);
    ofScale(sc);

    dibujarPatron();
    dibujarCaja();
    dibujarEstrellas();
    dibujarEspirales();
    dibujarPath144();
    dibujarCamaraPath144();

    ofPopMatrix();

    dibujarHUD();
}

void ofApp::keyPressed(int key) {
    switch (key) {
        case 'q': patScale     = std::max(0.2f, patScale     - 0.1f);  break;
        case 'w': patScale     = std::min(6.0f, patScale     + 0.1f);  break;
        case 'e': patTile      = std::max(20.f, patTile      - 5.0f);  break;
        case 'r': patTile      = std::min(200.f,patTile      + 5.0f);  break;
        case 'z': patAngle     -= 2.0f; break;
        case 'x': patAngle     += 2.0f; break;
        case OF_KEY_LEFT:  patOffX -= 10.0f; break;
        case OF_KEY_RIGHT: patOffX += 10.0f; break;
        case OF_KEY_UP:    patOffY -= 10.0f; break;
        case OF_KEY_DOWN:  patOffY += 10.0f; break;
        case '1': sp1.spinSpeed -= 0.2f; break;
        case '2': sp1.spinSpeed += 0.2f; break;
        case '3': sp2.spinSpeed -= 0.2f; break;
        case '4': sp2.spinSpeed += 0.2f; break;
        case '5': sp1.revolutions = std::max(0.5f, sp1.revolutions - 0.5f); break;
        case '6': sp1.revolutions = std::min(8.0f, sp1.revolutions + 0.5f); break;
        case '7': sp2.revolutions = std::max(0.5f, sp2.revolutions - 0.5f); break;
        case '8': sp2.revolutions = std::min(8.0f, sp2.revolutions + 0.5f); break;
        case '9': sp1.maxRadius   = std::max(100.f, sp1.maxRadius - 80.f);  break;
        case '0': sp1.maxRadius   = std::min(2000.f,sp1.maxRadius + 80.f);  break;
        case 't': path144TrackingEnabled = !path144TrackingEnabled; break;
        case ' ': paused  = !paused;  break;
        case 'h': showHUD = !showHUD; break;
    }
}

void ofApp::keyReleased(int key) {}
void ofApp::mouseMoved(int x, int y) {}
void ofApp::mouseDragged(int x, int y, int button) {}
void ofApp::mousePressed(int x, int y, int button) {}
void ofApp::mouseReleased(int x, int y, int button) {}
