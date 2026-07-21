# Start Screen Design

## Objetivo

Agregar una pantalla de comienzo antes de la escena actual. La pantalla muestra el titulo del juego con Caslon CP Swash y un prompt secundario que dice `Apreta [Enter] para empezar`. Al presionar Enter, la app pasa a la escena animada existente.

## Alcance

- La branch de trabajo se llama `demo`.
- La pantalla inicial es el primer estado visible de la app.
- El titulo usa `CaslonCPswash.otf`, copiada a `bin/data/fonts/` para que el proyecto no dependa de una ruta local.
- El prompt usa `Arial.ttf` como fuente secundaria, copiada a `bin/data/fonts/`.
- El icono de Enter se dibuja como una tecla compacta con simbolo `Enter`.
- El prompt completo usa una animacion ciclica de opacidad llamada `pulse`, tambien conocida como `breathing fade`.
- La escena actual no cambia de comportamiento despues de empezar.
- GitHub Pages debe desplegar tambien desde pushes a `demo`.

## Diseno

La app suma un estado booleano `startScreenActive`, inicializado en `true`. `draw()` mantiene el mismo escalado del canvas SVG y elige entre `dibujarPantallaInicio()` y la escena existente. `update()` sigue actualizando la camara para que el permiso y los frames no queden bloqueados, pero no avanza la animacion principal hasta que se presione Enter.

La pantalla usa los mismos `SVG_W` y `SVG_H` para mantener composicion consistente en desktop y web. El fondo es blanco, el titulo va centrado en negro, y el prompt va debajo con alpha calculado por `sin(ofGetElapsedTimef())`.

`keyPressed()` intercepta Enter mientras `startScreenActive` esta activo. Las teclas de debug y control existentes solo actuan cuando ya empezo la escena.

## Pruebas

Agregar un test shell que verifique:

- existe la fuente `bin/data/fonts/CaslonCPswash.otf`;
- `ofApp` declara y carga las fuentes de inicio;
- existe `dibujarPantallaInicio()`;
- el texto contiene `Apreta` y `para empezar`;
- la animacion se llama `pulse`;
- Enter apaga `startScreenActive`.

Agregar cobertura al test de Pages para verificar que el workflow corre en `main` y `demo`.
