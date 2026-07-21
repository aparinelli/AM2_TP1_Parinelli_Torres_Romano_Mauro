#!/usr/bin/env bash
set -euo pipefail

root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
header_file="$root/src/ofApp.h"
app_file="$root/src/ofApp.cpp"
workflow_file="$root/.github/workflows/deploy.yml"
font_file="$root/bin/data/fonts/CaslonCPswash.otf"
secondary_font_file="$root/bin/data/fonts/Arial.ttf"

test -s "$font_file"
test -s "$secondary_font_file"

grep -Eq 'bool[[:space:]]+startScreenActive[[:space:]]*=[[:space:]]*true' "$header_file"
grep -Eq 'ofTrueTypeFont[[:space:]]+startTitleFont' "$header_file"
grep -Eq 'ofTrueTypeFont[[:space:]]+startPromptFont' "$header_file"
grep -Eq 'void[[:space:]]+configurarPantallaInicio\(\)' "$header_file"
grep -Eq 'void[[:space:]]+dibujarPantallaInicio\(\)' "$header_file"

grep -Eq 'CaslonCPswash\.otf' "$app_file"
grep -Eq 'Arial\.ttf' "$app_file"
grep -Eq 'startTitleFont\.load' "$app_file"
grep -Eq 'startPromptFont\.load' "$app_file"
grep -Eq 'void ofApp::dibujarPantallaInicio\(\)' "$app_file"
grep -Eq 'Prueba Camara|Prueba Cámara' "$app_file"
grep -Eq 'Apreta|Apretá' "$app_file"
grep -Eq 'para empezar' "$app_file"
grep -Eq 'pulse' "$app_file"
grep -Eq 'OF_KEY_RETURN|OF_KEY_ENTER' "$app_file"
grep -Eq 'startScreenActive[[:space:]]*=[[:space:]]*false' "$app_file"
grep -Eq 'if[[:space:]]*\([[:space:]]*startScreenActive[[:space:]]*\)' "$app_file"

grep -Eq 'branches:[[:space:]]*\[[^]]*main[^]]*demo[^]]*\]' "$workflow_file"
