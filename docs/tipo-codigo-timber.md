# Tipo de codigo Timber

Este proyecto queda refactorizado para usar el mismo tipo de codigo que aparece en los ejemplos `timber*`, tomando como referencia principal `/Users/alejoparinelli/facu/AM2/timber_parte_2/05_incremento_barra_tiempo`.

## Estructura

- Un solo `ofApp.h` y un solo `ofApp.cpp`.
- Variables declaradas en `ofApp.h`, dentro de `class ofApp`, como en Timber.
- Logica directa en `setup()`, `update()`, `draw()`, `keyPressed()`, `keyReleased()` y, para este proyecto, `mousePressed()` porque el boton debe ser clickeable.
- Funciones auxiliares simples declaradas en `ofApp.h`, como `moverRamas()` en Timber.

## Tipos y datos permitidos

- `ofImage`, `ofTrueTypeFont`, `ofVec2f`, `ofSoundPlayer` si hiciera falta audio.
- `bool`, `int`, `float`, `string`.
- Arreglos fijos, por ejemplo `string textos_escenas[3]` o `float alpha_letras[20]`.
- `enum` simple si se necesita representar estados.

## Funciones de openFrameworks usadas en Timber

- Ventana: `ofSetWindowShape()`, `ofToggleFullscreen()`, `ofHideCursor()`.
- Dibujo: `ofScale()`, `ofSetColor()`, `ofDrawRectangle()`, `drawString()`, `draw()`.
- Texto: `ofTrueTypeFont.load()`, `stringWidth()`, `ofToString()`.
- Movimiento y tiempo de juego: variables `float`, cambios en `update()`, `ofRandom()` si hace falta.
- Interaccion: `keyPressed()`, `keyReleased()` y comparaciones directas con teclas.

## Reglas para este refactor

- La resolucion de ventana sigue el ejemplo Timber: `960 x 540`.
- Las coordenadas de diseno trabajan en `1920 x 1080` y se dibujan con `ofScale(0.5, 0.5)` cuando no hay pantalla completa.
- Las escenas se guardan en arreglos fijos de 3 posiciones.
- El texto se centra con `stringWidth()`.
- Las tildes se sostienen cargando las fuentes con `load("archivo.ttf", tamano, true, true)`, usando el set completo de caracteres.

## No usar

- `std::vector`.
- `struct Scene`.
- `namespace` para helpers.
- `ofTrueTypeFontSettings`.
- `ofUTF8Iterator` y `ofUTF8ToString`.
- `ofRectangle`.
- `glm::vec2`.
- `ofDrawRectRounded`.
- Escalado responsive con `ofPushMatrix()`, `ofTranslate()` y calculo de offsets.
