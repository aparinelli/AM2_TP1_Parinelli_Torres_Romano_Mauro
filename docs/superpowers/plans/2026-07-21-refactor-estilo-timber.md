# Refactor Estilo Timber Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Refactorizar la pantalla y escenas para usar solo el vocabulario de codigo observado en los proyectos `timber*`.

**Architecture:** El proyecto conserva un unico `ofApp` procedural. Las escenas se representan con arreglos fijos y variables simples, la ventana usa el esquema Timber `960 x 540` con coordenadas de diseno `1920 x 1080`, y los textos se dibujan con `ofTrueTypeFont.drawString()` y `stringWidth()`.

**Tech Stack:** openFrameworks, C++ simple estilo clase unica, shell tests.

## Global Constraints

- Usar como referencia principal `/Users/alejoparinelli/facu/AM2/timber_parte_2/05_incremento_barra_tiempo`.
- Mantener el boton `Empezar` clickeable.
- Mantener tres escenas con texto inferior.
- Mantener las tildes renderizables mediante `ofTrueTypeFont.load(..., true, true)`.
- No usar `std::vector`, `struct Scene`, `ofRectangle`, `glm::vec2`, `ofTrueTypeFontSettings`, `ofUTF8Iterator`, `ofUTF8ToString`, `ofDrawRectRounded`, `namespace`, `ofPushMatrix` ni `ofTranslate` en `ofApp`.

---

### Task 1: Test de vocabulario Timber

**Files:**
- Modify: `tests/start_screen_test.sh`
- Create: `docs/tipo-codigo-timber.md`

**Interfaces:**
- Consumes: archivos `src/main.cpp`, `src/ofApp.h`, `src/ofApp.cpp`.
- Produces: validaciones que rechazan codigo fuera del estilo Timber.

- [x] **Step 1: Write the failing test**

Actualizar `tests/start_screen_test.sh` para exigir resolucion `960 x 540`, arreglos fijos, `ofVec2f`, `stringWidth()`, `ofDrawRectangle()` y ausencia de abstracciones modernas.

- [x] **Step 2: Run test to verify it fails**

Run: `bash tests/start_screen_test.sh`
Expected: FAIL porque `src/ofApp` todavia usa `std::vector`, `struct Scene`, `ofRectangle`, `ofTrueTypeFontSettings` y escalado responsive.

### Task 2: Refactor de `ofApp`

**Files:**
- Modify: `src/ofApp.h`
- Modify: `src/ofApp.cpp`
- Modify: `src/main.cpp`

**Interfaces:**
- Consumes: fuentes en `bin/data/fonts`.
- Produces: pantalla inicial y tres escenas dibujadas solo con codigo estilo Timber.

- [x] **Step 1: Replace header state**

Usar variables simples: `string titulos_escenas[3]`, `string textos_escenas[3]`, `ofVec2f posicion_boton`, `float alpha_boton`, `float alpha_letras[20]`, `bool sube_alpha_letras[20]`.

- [x] **Step 2: Replace drawing and update logic**

Usar `ofScale(0.5, 0.5)`, `stringWidth()`, `drawString()`, `ofDrawRectangle()` y comparaciones directas para el click del boton.

- [x] **Step 3: Run tests and build**

Run: `bash tests/start_screen_test.sh`
Expected: PASS.

Run: `make -j4`
Expected: PASS.
