/*
  Test Project
  Author: Joseph St. Pierre
  Year: 2018
*/

#include "elgar/Engine.hpp"
#include "elgar/audio/AudioSource.hpp"
#include "elgar/audio/AudioListener.hpp"
#include "elgar/core/AudioSystem.hpp"
#include "elgar/core/Window.hpp"
#include "elgar/graphics/ShaderManager.hpp"
#include "elgar/core/IO.hpp"

#include "elgar/graphics/data/RGBA.hpp"
#include "elgar/graphics/data/Sprite.hpp"

#include "elgar/timers/FrameTimer.hpp"

#include <SDL2/SDL.h>

#include <stdio.h>
#include <iostream>
#include <typeinfo>

#include <unordered_map>

using namespace elgar;

Engine *engine = nullptr;

Sprite *sprite = nullptr;

const Shader *shader = nullptr;

void update() {
  if (Keyboard::IsKeyPressed(SDLK_ESCAPE))
    engine->SetRunning(false);
 
}

void fixed_update() {

}

void render() {
  sprite->Draw(*shader, {0xFF, 0xFF, 0xFF, 0xFF}, glm::mat4());
}

int main() {
  // Create new instance of Elgar
  engine = new Engine("StarLight", 1024, 768, NONE);

  sprite = new Sprite();

  shader = ShaderManager::GetInstance()->GetShader(BASIC_SHADER_PROGRAM);

  engine->Run(update, fixed_update, render);

  delete sprite;

  // Unload resources from RAM
  delete engine;

  return 0;
}