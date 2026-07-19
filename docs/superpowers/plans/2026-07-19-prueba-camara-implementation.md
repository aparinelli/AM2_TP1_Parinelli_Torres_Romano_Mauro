# Prueba Camara Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Rename the openFrameworks project to `prueba_camara`, refactor the camera/mask code into smaller helpers, unmirror the camera feed, and keep the detected face framed inside the masked `path144` box.

**Architecture:** Keep the existing single-app openFrameworks structure and make focused changes in `ofApp`. Add `ofxOpenCv` only for Haar face detection, with a centered crop fallback when detection is unavailable. Compute a path bounding rectangle in SVG canvas coordinates and let the camera shader cover that rectangle instead of the whole canvas.

**Tech Stack:** C++17-style openFrameworks 0.12.1, `ofVideoGrabber`, `ofShader`, `ofFbo`, `ofxOpenCv` / `ofxCvHaarFinder`, shell grep tests.

## Global Constraints

- Current project path starts as `/Users/alejoparinelli/facu/AM2/template_of`.
- Final project path must be `/Users/alejoparinelli/facu/AM2/prueba_camara`.
- Do not change the visual design of pattern, box, stars, or spirals.
- Do not add calibration UI.
- Use Haar face detection with a centered fallback; perfect detection in extreme lighting or angles is out of scope.
- Keep the refactor local to camera, mask, shader, and crop responsibilities.
- Preserve existing user work already present in modified files.

---

## File Structure

- Modify then rename: `/Users/alejoparinelli/facu/AM2/template_of/template_of.code-workspace` to `/Users/alejoparinelli/facu/AM2/prueba_camara/prueba_camara.code-workspace`
- Modify: `/Users/alejoparinelli/facu/AM2/prueba_camara/addons.make` so it contains `ofxOpenCv`
- Copy asset: `/Users/alejoparinelli/facu/AM2/prueba_camara/bin/data/haarcascade_frontalface_default.xml`
- Modify: `/Users/alejoparinelli/facu/AM2/prueba_camara/src/ofApp.h` for OpenCV include, path bounds, face tracking state, and focused helper declarations
- Modify: `/Users/alejoparinelli/facu/AM2/prueba_camara/src/ofApp.cpp` for helper extraction, face tracking, shader uniforms, path-bounds crop, and camera unmirroring
- Create: `/Users/alejoparinelli/facu/AM2/prueba_camara/tests/camera_tracking_test.sh`
- Existing tests stay: `/Users/alejoparinelli/facu/AM2/prueba_camara/tests/pattern_settings_test.sh` and `/Users/alejoparinelli/facu/AM2/prueba_camara/tests/star_paths_test.sh`

---

### Task 1: Project Rename And OpenCV Wiring

**Files:**
- Create: `/Users/alejoparinelli/facu/AM2/template_of/tests/camera_tracking_test.sh`
- Modify: `/Users/alejoparinelli/facu/AM2/template_of/addons.make`
- Rename: `/Users/alejoparinelli/facu/AM2/template_of/template_of.code-workspace` to `/Users/alejoparinelli/facu/AM2/prueba_camara/prueba_camara.code-workspace`
- Copy: `/Users/alejoparinelli/facu/AM2/of_v0.12.1_osx_release/examples/computer_vision/opencvHaarFinderExample/bin/data/haarcascade_frontalface_default.xml` to `/Users/alejoparinelli/facu/AM2/prueba_camara/bin/data/haarcascade_frontalface_default.xml`

**Interfaces:**
- Consumes: existing shell test pattern where each test discovers `root` from its own location.
- Produces: a renamed project directory and a data file loadable with `ofToDataPath("haarcascade_frontalface_default.xml", true)`.

- [ ] **Step 1: Write the failing test**

Create `/Users/alejoparinelli/facu/AM2/template_of/tests/camera_tracking_test.sh`:

```bash
#!/usr/bin/env bash
set -euo pipefail

root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

grep -Eq '^ofxOpenCv$' "$root/addons.make"
test -f "$root/bin/data/haarcascade_frontalface_default.xml"
grep -Eq '#include "ofxCvHaarFinder\.h"' "$root/src/ofApp.h"
grep -Eq 'ofxCvHaarFinder[[:space:]]+path144FaceFinder' "$root/src/ofApp.h"
grep -Eq 'ofRectangle[[:space:]]+path144Bounds' "$root/src/ofApp.h"
grep -Eq 'glm::vec2[[:space:]]+path144CameraFocus' "$root/src/ofApp.h"
grep -Eq 'actualizarTrackingRostroPath144\(\)' "$root/src/ofApp.h" "$root/src/ofApp.cpp"
grep -Eq 'path144FaceFinder\.findHaarObjects' "$root/src/ofApp.cpp"
grep -Eq 'uniform vec4 pathBounds' "$root/src/ofApp.cpp"
grep -Eq 'uniform vec2 focusCenter' "$root/src/ofApp.cpp"
grep -Eq 'uniform float mirrorCamera' "$root/src/ofApp.cpp"
grep -Eq 'targetUv[[:space:]]*=[[:space:]]*clamp\(\(canvasPosition - pathBounds\.xy\) / pathBounds\.zw' "$root/src/ofApp.cpp"
grep -Eq 'effectiveFocus\.x[[:space:]]*=[[:space:]]*1\.0 - effectiveFocus\.x' "$root/src/ofApp.cpp"
grep -Eq 'cameraUv\.x[[:space:]]*=[[:space:]]*1\.0 - cameraUv\.x' "$root/src/ofApp.cpp"
grep -Eq 'setUniform4f\("pathBounds"' "$root/src/ofApp.cpp"
grep -Eq 'setUniform2f\("focusCenter"' "$root/src/ofApp.cpp"
grep -Eq 'setUniform1f\("mirrorCamera",[[:space:]]*1\.0f\)' "$root/src/ofApp.cpp"
```

Make it executable:

```bash
chmod +x /Users/alejoparinelli/facu/AM2/template_of/tests/camera_tracking_test.sh
```

- [ ] **Step 2: Run test to verify it fails**

Run:

```bash
bash /Users/alejoparinelli/facu/AM2/template_of/tests/camera_tracking_test.sh
```

Expected: FAIL on `ofxOpenCv`, missing cascade, or missing OpenCV/crop symbols.

- [ ] **Step 3: Wire OpenCV and rename the project**

Set `/Users/alejoparinelli/facu/AM2/template_of/addons.make` to:

```make
ofxOpenCv
```

Copy the cascade:

```bash
cp /Users/alejoparinelli/facu/AM2/of_v0.12.1_osx_release/examples/computer_vision/opencvHaarFinderExample/bin/data/haarcascade_frontalface_default.xml /Users/alejoparinelli/facu/AM2/template_of/bin/data/haarcascade_frontalface_default.xml
```

Rename the workspace file before moving the directory:

```bash
mv /Users/alejoparinelli/facu/AM2/template_of/template_of.code-workspace /Users/alejoparinelli/facu/AM2/template_of/prueba_camara.code-workspace
```

Move the project directory:

```bash
mv /Users/alejoparinelli/facu/AM2/template_of /Users/alejoparinelli/facu/AM2/prueba_camara
```

- [ ] **Step 4: Run test again from the renamed path**

Run:

```bash
bash /Users/alejoparinelli/facu/AM2/prueba_camara/tests/camera_tracking_test.sh
```

Expected: still FAIL, now because C++ symbols and shader uniforms are not implemented yet.

- [ ] **Step 5: Commit setup changes**

Run:

```bash
git -C /Users/alejoparinelli/facu/AM2/prueba_camara add addons.make bin/data/haarcascade_frontalface_default.xml prueba_camara.code-workspace tests/camera_tracking_test.sh
git -C /Users/alejoparinelli/facu/AM2/prueba_camara add -u template_of.code-workspace
git -C /Users/alejoparinelli/facu/AM2/prueba_camara commit -m "chore: rename project and add camera tracking assets"
```

Expected: commit succeeds. The test is allowed to remain red because later tasks implement the required code.

---

### Task 2: Face Tracking State And Camera Helpers

**Files:**
- Modify: `/Users/alejoparinelli/facu/AM2/prueba_camara/src/ofApp.h`
- Modify: `/Users/alejoparinelli/facu/AM2/prueba_camara/src/ofApp.cpp`
- Test: `/Users/alejoparinelli/facu/AM2/prueba_camara/tests/camera_tracking_test.sh`

**Interfaces:**
- Consumes: `haarcascade_frontalface_default.xml` in `bin/data`.
- Produces:
  - `void configurarDetectorRostroPath144();`
  - `void actualizarTrackingRostroPath144();`
  - `ofRectangle path144Bounds;`
  - `glm::vec2 path144CameraFocus` normalized to `[0, 1]`;
  - `bool path144FaceFinderReady`.

- [ ] **Step 1: Confirm the test is red for C++ behavior**

Run:

```bash
bash /Users/alejoparinelli/facu/AM2/prueba_camara/tests/camera_tracking_test.sh
```

Expected: FAIL on missing `ofxCvHaarFinder`, `path144Bounds`, `path144CameraFocus`, or `actualizarTrackingRostroPath144`.

- [ ] **Step 2: Add declarations and state in `ofApp.h`**

Add this include below `#include "ofMain.h"`:

```cpp
#include "ofxCvHaarFinder.h"
```

Add these private members near the existing `path144Camera` state:

```cpp
    ofxCvHaarFinder path144FaceFinder;
    ofRectangle path144Bounds;
    glm::vec2 path144CameraFocus = {0.5f, 0.5f};
    bool path144FaceFinderReady = false;
    bool path144HasCameraFocus = false;
    float path144LastFaceSeenAt = -1000.0f;
```

Add these private method declarations near the existing camera helpers:

```cpp
    void seleccionarDispositivoCamaraPath144();
    void configurarRecursosCamaraPath144();
    void configurarDetectorRostroPath144();
    void actualizarTrackingRostroPath144();
```

- [ ] **Step 3: Add focused helpers in `ofApp.cpp`**

Add these helpers inside the anonymous namespace:

```cpp
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
    ofMesh mesh = path.getTessellation();
    const auto& vertices = mesh.getVertices();
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
```

- [ ] **Step 4: Replace monolithic camera setup with helper calls**

Change `configurarPath144()` so it stores the path bounds:

```cpp
void ofApp::configurarPath144() {
    path144 = parsearPathSVGOriginal(PATH144_D);
    path144.setFillColor(ofColor(255, 0, 0));
    path144.setStrokeWidth(0);
    path144Bounds = calcularBoundsPath(path144);
    configurarPath144Shader();
}
```

Replace `configurarPath144Camara()` with:

```cpp
void ofApp::configurarPath144Camara() {
    seleccionarDispositivoCamaraPath144();
    configurarRecursosCamaraPath144();
    configurarDetectorRostroPath144();
    configurarPath144CamaraShaders();
    actualizarMascaraPath144();
}
```

Add the extracted setup helpers:

```cpp
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

    if (selectedDeviceId < 0 && !devices.empty()) selectedDeviceId = devices.front().id;

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
}
```

- [ ] **Step 5: Update tracking on new camera frames**

Change `update()` to:

```cpp
void ofApp::update() {
    if (path144CameraReady) {
        path144Camera.update();
        if (path144Camera.isFrameNew()) actualizarTrackingRostroPath144();
    }
    if (paused) return;

    actualizarAnimacion();
}
```

Add:

```cpp
void ofApp::actualizarTrackingRostroPath144() {
    if (!path144FaceFinderReady) {
        path144CameraFocus = {0.5f, 0.5f};
        path144HasCameraFocus = false;
        return;
    }

    auto& pixels = path144Camera.getPixels();
    if (!pixels.isAllocated() || pixels.getWidth() <= 0 || pixels.getHeight() <= 0) {
        return;
    }

    path144FaceFinder.findHaarObjects(pixels, 80, 80);
    ofRectangle face = elegirCaraPrincipal(path144FaceFinder.blobs);

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
```

- [ ] **Step 6: Run test to verify partial pass**

Run:

```bash
bash /Users/alejoparinelli/facu/AM2/prueba_camara/tests/camera_tracking_test.sh
```

Expected: FAIL only on missing shader uniforms and uniform binding.

- [ ] **Step 7: Commit tracking state and helpers**

Run:

```bash
git -C /Users/alejoparinelli/facu/AM2/prueba_camara add src/ofApp.h src/ofApp.cpp tests/camera_tracking_test.sh
git -C /Users/alejoparinelli/facu/AM2/prueba_camara commit -m "feat: add face tracking state for path camera"
```

Expected: commit succeeds with the camera behavior test still red for shader work.

---

### Task 3: Path-Bounds Crop, Unmirror Shader, And Camera Refactor

**Files:**
- Modify: `/Users/alejoparinelli/facu/AM2/prueba_camara/src/ofApp.cpp`
- Test: `/Users/alejoparinelli/facu/AM2/prueba_camara/tests/camera_tracking_test.sh`

**Interfaces:**
- Consumes: `path144Bounds`, `path144CameraFocus`, and `path144CameraShader`.
- Produces:
  - shader uniforms `pathBounds`, `focusCenter`, `mirrorCamera`;
  - camera sampling using path-bounds target UV;
  - X-axis unmirror correction in both GLSL 150 and GLSL 120 shader variants.

- [ ] **Step 1: Confirm the test is red for shader behavior**

Run:

```bash
bash /Users/alejoparinelli/facu/AM2/prueba_camara/tests/camera_tracking_test.sh
```

Expected: FAIL on `uniform vec4 pathBounds`, `uniform vec2 focusCenter`, `uniform float mirrorCamera`, `effectiveFocus.x`, `cameraUv.x`, or the uniform setters.

- [ ] **Step 2: Replace `coverCameraCoord` in both camera fragment shaders**

In the GLSL 150 camera fragment shader, replace the old `coverCameraCoord` function and uniforms with:

```glsl
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
```

In the GLSL 120 shader, use the same body, but keep `varying vec2 vCanvasPosition;`, use `texture2DRect`, and write to `gl_FragColor`:

```glsl
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
```

- [ ] **Step 3: Bind the new uniforms in `dibujarCamaraPath144()`**

Change the shader binding block to:

```cpp
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
```

- [ ] **Step 4: Extract shader loading and blur pass helpers**

Add these anonymous-namespace helpers to reduce repeated shader setup and blur pass code:

```cpp
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
```

Use `cargarShader` in `configurarPath144Shader()` and `configurarPath144CamaraShaders()` instead of repeating `setupShaderFromSource` / `bindDefaults` / `linkProgram`.

Use `dibujarBlurPass` inside `actualizarMascaraPath144()`:

```cpp
    const float blurRadius = 6.0f;
    for (int i = 0; i < 4; i++) {
        dibujarBlurPass(path144BlurShader, path144BlurFbo[0], path144BlurFbo[1], {blurRadius, 0.0f});
        dibujarBlurPass(path144BlurShader, path144BlurFbo[1], path144BlurFbo[0], {0.0f, blurRadius});
    }
```

- [ ] **Step 5: Run the camera tracking test**

Run:

```bash
bash /Users/alejoparinelli/facu/AM2/prueba_camara/tests/camera_tracking_test.sh
```

Expected: PASS.

- [ ] **Step 6: Run existing shell tests**

Run:

```bash
bash /Users/alejoparinelli/facu/AM2/prueba_camara/tests/pattern_settings_test.sh
bash /Users/alejoparinelli/facu/AM2/prueba_camara/tests/star_paths_test.sh
```

Expected: both PASS with no output.

- [ ] **Step 7: Commit shader and refactor changes**

Run:

```bash
git -C /Users/alejoparinelli/facu/AM2/prueba_camara add src/ofApp.cpp src/ofApp.h tests/camera_tracking_test.sh
git -C /Users/alejoparinelli/facu/AM2/prueba_camara commit -m "feat: frame unmirrored camera inside path mask"
```

Expected: commit succeeds.

---

### Task 4: Build Verification And Cleanup

**Files:**
- Inspect: `/Users/alejoparinelli/facu/AM2/prueba_camara/src/ofApp.cpp`
- Inspect: `/Users/alejoparinelli/facu/AM2/prueba_camara/src/ofApp.h`
- Inspect: `/Users/alejoparinelli/facu/AM2/prueba_camara/addons.make`
- Inspect: `/Users/alejoparinelli/facu/AM2/prueba_camara/bin/data/haarcascade_frontalface_default.xml`

**Interfaces:**
- Consumes: all prior tasks.
- Produces: verified project at `/Users/alejoparinelli/facu/AM2/prueba_camara`.

- [ ] **Step 1: Run all shell tests**

Run:

```bash
for test_script in /Users/alejoparinelli/facu/AM2/prueba_camara/tests/*_test.sh; do
  bash "$test_script"
done
```

Expected: PASS with no output.

- [ ] **Step 2: Build the openFrameworks app**

Run:

```bash
make -C /Users/alejoparinelli/facu/AM2/prueba_camara
```

Expected: build succeeds. If the build fails on `ofxOpenCv` API names, inspect `/Users/alejoparinelli/facu/AM2/of_v0.12.1_osx_release/addons/ofxOpenCv/src/ofxCvHaarFinder.h` and adjust the call sites without changing the test intent.

- [ ] **Step 3: Check repository state**

Run:

```bash
git -C /Users/alejoparinelli/facu/AM2/prueba_camara status --short
git -C /Users/alejoparinelli/facu/AM2/prueba_camara log --oneline -5
```

Expected: only intentional tracked changes are present; recent commits include the design spec, setup, tracking, and shader/refactor work.

- [ ] **Step 4: Final report**

Report:

```text
Project renamed to /Users/alejoparinelli/facu/AM2/prueba_camara.
Camera is sampled unmirrored through mirrorCamera = 1.0f.
Face tracking uses ofxCvHaarFinder with centered fallback.
All shell tests passed.
make passed or failed with the exact compiler/linker error.
```
