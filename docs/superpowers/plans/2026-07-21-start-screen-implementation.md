# Start Screen Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Build a start screen on branch `demo` and make GitHub Pages deploy from `demo`.

**Architecture:** Add a small app state before the existing scene, draw the start screen in SVG canvas coordinates, and keep the current scene untouched after Enter. Extend the existing shell tests to cover the UI state and Pages branch trigger.

**Tech Stack:** openFrameworks C++, shell tests, GitHub Actions Pages workflow.

## Global Constraints

- Branch name is exactly `demo`.
- Title font asset is `bin/data/fonts/CaslonCPswash.otf`.
- Secondary prompt font asset is `bin/data/fonts/Arial.ttf`.
- Prompt text is `Apreta [Enter] para empezar`.
- Prompt animation is named `pulse`.
- GitHub Pages deploys on pushes to `main` and `demo`.

---

### Task 1: Start Screen Test And Assets

**Files:**
- Create: `tests/start_screen_test.sh`
- Create: `bin/data/fonts/CaslonCPswash.otf`
- Modify: `.github/workflows/deploy.yml`

**Interfaces:**
- Produces: test expectations for `startScreenActive`, `dibujarPantallaInicio`, `pulse`, and the font path.

- [ ] **Step 1: Copy font asset**

Run: `mkdir -p bin/data/fonts && cp /Users/alejoparinelli/Library/Fonts/CaslonCPswash.otf bin/data/fonts/CaslonCPswash.otf`

- [ ] **Step 2: Write failing test**

Create `tests/start_screen_test.sh` with grep assertions for the start screen declarations, drawing function, prompt copy, pulse animation, Enter handling, and Pages `demo` trigger.

- [ ] **Step 3: Verify red**

Run: `bash tests/start_screen_test.sh`

Expected: fail because `ofApp` does not yet declare the start screen state or drawing code.

### Task 2: Start Screen Implementation

**Files:**
- Modify: `src/ofApp.h`
- Modify: `src/ofApp.cpp`

**Interfaces:**
- Consumes: `startScreenActive` boolean and `dibujarPantallaInicio()` expected by Task 1.
- Produces: Enter-to-start behavior and pulse prompt rendering.

- [ ] **Step 1: Add state and font declarations**

Add `startScreenActive`, title and prompt fonts, and helper declarations to `ofApp.h`.

- [ ] **Step 2: Load fonts in setup**

Add `configurarPantallaInicio()` and call it from `setup()`.

- [ ] **Step 3: Draw the start screen**

Add `dibujarPantallaInicio()` using the title font, prompt font, an Enter key icon, and `pulse` alpha.

- [ ] **Step 4: Gate Enter and scene controls**

Update `keyPressed()` so Enter starts the scene and other controls are ignored while the start screen is active.

- [ ] **Step 5: Verify green**

Run: `bash tests/start_screen_test.sh`

Expected: pass.

### Task 3: Pages Trigger And Full Verification

**Files:**
- Modify: `.github/workflows/deploy.yml`

**Interfaces:**
- Produces: workflow trigger for branch `demo`.

- [ ] **Step 1: Add demo to Pages branches**

Change `branches: [main]` to `branches: [main, demo]`.

- [ ] **Step 2: Run all shell tests**

Run: `for test in tests/*.sh; do bash "$test"; done`

Expected: all tests exit 0.

- [ ] **Step 3: Commit and push**

Run: `git add . && git commit -m "feat: add start screen" && git push -u origin demo`
