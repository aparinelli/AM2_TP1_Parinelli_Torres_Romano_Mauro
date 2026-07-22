#!/usr/bin/env bash
set -euo pipefail

root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
workflow="$root/.github/workflows/deploy.yml"

assert_not_contains() {
  local pattern="$1"
  shift
  if grep -Eq -- "$pattern" "$@"; then
    echo "Unexpected pattern found: $pattern" >&2
    exit 1
  fi
}

grep -Eq '^name: Build and Deploy to GitHub Pages$' "$workflow"
if command -v ruby >/dev/null; then
  ruby -e 'require "yaml"; YAML.load_file(ARGV[0])' "$workflow"
fi
grep -Eq 'actions/configure-pages@v5' "$workflow"
grep -Eq 'actions/upload-pages-artifact@v3' "$workflow"
grep -Eq 'actions/deploy-pages@v4' "$workflow"
grep -Eq 'find bin/em -type f' "$workflow"
grep -Eq 'preentrega/12-8' "$workflow"
grep -Eq 'mkdir -p "\$_site_root"' "$workflow"
grep -Eq 'url=preentrega/12-8/' "$workflow"
grep -Eq 'PLATFORM_PTHREAD = ' "$workflow"
grep -Eq 'CFLAG_PLATFORM_PTHREAD = ' "$workflow"
grep -Eq -- '-fexceptions' "$workflow"
grep -Eq -- '-s MIN_WEBGL_VERSION=2' "$workflow"
grep -Eq -- '-s MAX_WEBGL_VERSION=2' "$workflow"
grep -Eq -- '-gsource-map' "$workflow"
grep -Eq -- '-sLOAD_SOURCE_MAP=1' "$workflow"
grep -Eq 'Patch oF Emscripten WebGL context setup' "$workflow"
grep -Eq 'failed to create a WebGL2 context' "$workflow"
grep -Eq 'emscripten_webgl_make_context_current' "$workflow"
grep -Eq 'EMSCRIPTEN_RESULT_SUCCESS' "$workflow"
assert_not_contains 'rendererMajor = 1|attrs\.antialias = 0|attrs\.stencil = 0' "$workflow"
assert_not_contains 'emscript en|emscrip ten' "$workflow"
grep -Eq 'Patch oF random engine for Emscripten' "$workflow"
grep -Eq 'Patch oF Emscripten video bridge signatures' "$workflow"
grep -Eq '"html5video_grabber_create": "i"' "$workflow"
grep -Eq 'sig_line = f"    \{name\}__sig' "$workflow"
grep -Eq 'html5video_player_loop: function\(id\)' "$workflow"
grep -Eq 'video\.playsInline = true' "$workflow"
grep -Eq 'audio: false' "$workflow"
grep -Eq 'width: \{ ideal: w \}' "$workflow"
grep -Eq 'height: \{ ideal: h \}' "$workflow"
grep -Eq 'frameRate = \{ ideal: framerate \}' "$workflow"
grep -Eq 'Module\.HEAPU8\.subarray\(dstPixels, dstPixels\+\(video\.width\*video\.height\*4\)\)' "$workflow"
grep -Fq "console.error(\\\"Couldn't init grabber!\\\", err);" "$workflow"
assert_not_contains 'console\.log\(e\)' "$workflow"
grep -Eq 'Normalize generated Emscripten HTML bootstrap' "$workflow"
grep -Eq 'prueba-camara-fit-screen' "$workflow"
grep -Eq 'html, body \{' "$workflow"
grep -Eq 'overflow: hidden' "$workflow"
grep -Eq '#logo, #controls, #status, #spinner, progress, textarea#output' "$workflow"
grep -Eq 'width: min\(100vw, calc\(100vh \* 16 / 9\)\)' "$workflow"
grep -Eq 'height: min\(calc\(100vw \* 9 / 16\), 100vh\)' "$workflow"
grep -Eq 'Path\("_site/preentrega/12-8/index.html"\)' "$workflow"
grep -Eq 'Path\("_site/preentrega/12-8/index.js"\)' "$workflow"
grep -Eq 'Module.canvas = Module.canvas \|\| document.getElementById\("canvas"\)' "$workflow"
grep -Eq 'script type="text/javascript" src="app\.js"' "$workflow"
grep -Eq 'script type="text/javascript" src="index\.js"' "$workflow"
grep -Eq 'Patch generated Emscripten target lookup' "$workflow"
grep -Eq 'findCanvasEventTarget=target=>Module\["canvas"\]' "$workflow"
grep -Eq '#canvas' "$workflow"
grep -Eq 'sed -i "/\^ofxOpenCv\$/d" addons.make' "$workflow"
assert_not_contains 'target === ""' "$workflow"
assert_not_contains 'butler|itch\.io|BUTLER_API_KEY' "$workflow"
