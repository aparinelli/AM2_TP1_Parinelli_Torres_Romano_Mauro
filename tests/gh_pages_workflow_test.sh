#!/usr/bin/env bash
set -euo pipefail

root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
workflow="$root/.github/workflows/deploy.yml"

grep -Eq '^name: Build and Deploy to GitHub Pages$' "$workflow"
grep -Eq 'actions/configure-pages@v5' "$workflow"
grep -Eq 'actions/upload-pages-artifact@v3' "$workflow"
grep -Eq 'actions/deploy-pages@v4' "$workflow"
grep -Eq 'find bin/em -type f' "$workflow"
grep -Eq 'PLATFORM_PTHREAD = ' "$workflow"
grep -Eq 'CFLAG_PLATFORM_PTHREAD = ' "$workflow"
grep -Eq -- '-gsource-map' "$workflow"
grep -Eq -- '-sLOAD_SOURCE_MAP=1' "$workflow"
grep -Eq 'Patch oF random engine for Emscripten' "$workflow"
grep -Eq 'Patch generated Emscripten target lookup' "$workflow"
grep -Eq '#canvas' "$workflow"
! grep -Eq 'butler|itch\.io|BUTLER_API_KEY' "$workflow"
