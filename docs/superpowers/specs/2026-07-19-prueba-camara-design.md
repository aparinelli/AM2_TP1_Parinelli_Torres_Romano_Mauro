# Prueba Camara Design

## Objetivo

Renombrar el proyecto openFrameworks de `template_of` a `prueba_camara` y ajustar la experiencia de camara en `path144` para que:

- la imagen no se vea espejada;
- el rostro quede encuadrado dentro de la caja visual del path enmascarado;
- las partes complejas de camara, shaders y recorte queden separadas en helpers mas cortos.

## Contexto

El proyecto actual vive en `/Users/alejoparinelli/facu/AM2/template_of`. La aplicacion renderiza un canvas SVG de `1920x1080`, dibuja patron, caja, estrellas, espirales y el path `path144`. La camara se mezcla con una mascara FBO basada en `path144`.

Hoy el shader de camara calcula un recorte tipo cover contra todo el canvas `1920x1080`. Eso no garantiza que el rostro quede dentro de la forma enmascarada, porque `path144` ocupa una region mucho mas chica. Tambien la textura de camara se samplea tal como llega del dispositivo, sin correccion explicita de espejo.

La instalacion local de openFrameworks incluye `ofxOpenCv` y el cascade `haarcascade_frontalface_default.xml`, por lo que se puede agregar deteccion de rostro sin introducir dependencias externas.

## Enfoques Considerados

### Enfoque recomendado: deteccion Haar con fallback centrado

Usar `ofxCvHaarFinder` para detectar el rostro sobre los frames de camara. El centro detectado se suaviza en el tiempo y se pasa al shader como centro de recorte. Si no hay deteccion, se usa el centro del frame.

Ventajas:

- cumple mejor el requisito de mantener el rostro encuadrado;
- usa un addon oficial ya disponible;
- mantiene fallback estable cuando no detecta cara.

Costos:

- agrega `ofxOpenCv` a `addons.make`;
- requiere copiar el cascade a `bin/data`;
- la deteccion Haar puede fallar con mala luz, angulos extremos o caras muy pequeñas.

### Alternativa: crop fijo centrado al bounding box del path

Calcular el bounding box de `path144` y hacer cover de la camara contra ese rectangulo, sin detectar rostro.

Ventajas:

- menos codigo y menos dependencia;
- comportamiento estable.

Costos:

- no garantiza encuadre del rostro si la persona se mueve;
- solo resuelve parcialmente el pedido.

### Alternativa descartada: segmentacion o tracking avanzado

Usar un tracker mas moderno o segmentacion facial.

Ventajas:

- podria ser mas preciso.

Costos:

- demasiado grande para este proyecto;
- requiere dependencias o modelos adicionales;
- complica la compilacion local y web.

## Diseno

### Renombre del proyecto

Mover `/Users/alejoparinelli/facu/AM2/template_of` a `/Users/alejoparinelli/facu/AM2/prueba_camara`.

Actualizar referencias internas visibles que usen el nombre viejo:

- `template_of.code-workspace` pasa a `prueba_camara.code-workspace`;
- nombres de workspace o rutas locales que mencionen `template_of`, si aparecen en archivos de texto.

No se modifican artefactos binarios ni caches de editor salvo que el build lo requiera.

### Refactor de camara

Separar la zona grande de `ofApp.cpp` en helpers pequenos dentro del mismo archivo y con declaraciones en `ofApp.h`.

Unidades propuestas:

- seleccion de dispositivo: elegir camara fisica disponible, priorizando FaceTime/MacBook/built-in y evitando virtuales;
- recursos de camara: setup de `ofVideoGrabber`, FBO de mascara y FBOs de blur;
- shaders: funciones que devuelvan o instalen fuentes GLSL para renderer programmable y fixed;
- mascara: render del path blanco y blur en pasadas;
- tracking de rostro: actualizacion de pixels OpenCV, deteccion Haar y suavizado del centro;
- dibujo de camara: bind de texturas/uniforms y draw del rectangulo full-canvas.

El objetivo del refactor es bajar complejidad localizada, no reestructurar toda la app.

### Encuadre y no espejo

Calcular `path144Bounds` a partir de `path144.getTessellation().getVertices()` o una fuente equivalente de vertices del path. Ese rectangulo representa la caja visual donde la camara debe encuadrarse.

Agregar estado de tracking:

- `ofxCvHaarFinder faceFinder`;
- `ofPixels cameraPixels`;
- `glm::vec2 cameraFocus = {0.5f, 0.5f}`;
- `bool hasCameraFocus = false`;
- parametros de suavizado y margen para que el rostro no quede pegado al borde.

En cada frame nuevo de camara:

1. leer pixels de la camara;
2. detectar caras con Haar;
3. elegir la cara de mayor area;
4. convertir su centro a UV normalizado de camara;
5. suavizar contra `cameraFocus`;
6. si no hay deteccion, mantener el ultimo foco por un tiempo corto o volver al centro.

En el shader:

- usar el aspect ratio de `path144Bounds` como destino del cover, no el aspect ratio del canvas completo;
- centrar el crop alrededor de `cameraFocus`;
- clamplear el crop para no samplear fuera de la textura;
- invertir X al samplear la textura para corregir espejo.

La mascara se sigue leyendo en coordenadas de canvas, asi que el borde difuminado de `path144` mantiene su forma actual.

## Manejo de Errores

Si no hay camara, el overlay de camara no se dibuja y se registra warning como ahora.

Si no carga el cascade Haar, la app usa crop centrado y registra warning.

Si el shader no carga, la camara no se dibuja para evitar un rectangulo opaco incorrecto.

Si no se puede calcular `path144Bounds`, se usa el canvas completo como fallback.

## Pruebas

Agregar tests shell focalizados, consistentes con los tests existentes:

- verificar que `ofxOpenCv` este en `addons.make`;
- verificar que el cascade exista en `bin/data`;
- verificar que el shader use `pathBounds`, `focusCenter` y una correccion de espejo en X;
- verificar que existan helpers de deteccion/encuadre para evitar volver a meter toda la logica en un bloque monolitico.

Ejecutar los tests existentes y los nuevos. Si el entorno permite build local de openFrameworks, ejecutar tambien `make`.

## Fuera de Alcance

No se cambia el diseno visual de patron, caja, estrellas ni espirales.

No se agrega una UI de calibracion.

No se garantiza deteccion perfecta de rostro en condiciones extremas; el requisito se satisface con seguimiento Haar y fallback centrado.
