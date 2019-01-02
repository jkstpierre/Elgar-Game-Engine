/*
  Test Project
  Author: Joseph St. Pierre
  Year: 2018
*/

#include "elgar/Engine.hpp"
#include "elgar/audio/AudioSource.hpp"
#include "elgar/audio/AudioListener.hpp"
#include "elgar/core/AudioSystem.hpp"
#include "elgar/graphics/TextureManager.hpp"
#include "elgar/core/Window.hpp"
#include "elgar/graphics/ShaderManager.hpp"
#include "elgar/core/IO.hpp"

#include "elgar/graphics/data/RGBA.hpp"
#include "elgar/graphics/data/Sprite.hpp"
#include "elgar/graphics/Camera.hpp"

#include "elgar/timers/FrameTimer.hpp"

#include <SDL2/SDL.h>

#include <stdio.h>
#include <iostream>
#include <typeinfo>

#include <unordered_map>

#include <glm/gtc/matrix_transform.hpp>

using namespace elgar;

#define WIDTH 800
#define HEIGHT 600
#define INSTANCE_COUNT  10000

Engine *engine = nullptr;

Sprite *sprite = nullptr;

const Shader *shader = nullptr;

std::vector<glm::mat4> models;

// Create a camera
Camera camera(
  glm::ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT, 0.0f, 1000.0f)
);

void update() {
  static FrameTimer *frame_timer = FrameTimer::GetInstance();

  if (Keyboard::IsKeyPressed(SDLK_ESCAPE))
    engine->SetRunning(false);

  if (Keyboard::IsKeyPressed(SDLK_RIGHT))
    camera.ChangePosition({100 * frame_timer->GetDeltaTime(), 0.0f, 0.0f});
  
  std::cout << frame_timer->GetFPS() << std::endl;
}

void fixed_update() {

}

void render() {
  camera.Draw(*shader);
  sprite->DrawInstanced(
    *shader,
    {0xFF, 0x25, 0x77, 0xFF},
    models
  );

  sprite->Draw(
    *shader,
    {0xFF, 0xFF, 0x99, 0xFF},
    glm::scale(glm::translate(glm::mat4(), {300.0f, 300.0f, 0.0f}), {75.0f, 75.0f, 0.0f})
  );
}

int main() {
  // Create new instance of Elgar
  engine = new Engine("StarLight", WIDTH, HEIGHT, NONE);

  Window::GetInstance()->SetVerticalSync(false);

  TextureManager::GetInstance()->BuildTexture("destroyer.png", "destroyer");

  sprite = new Sprite(TextureManager::GetInstance()->GetTexture("destroyer"));

  shader = ShaderManager::GetInstance()->GetShader(BASIC_SHADER_PROGRAM);

  for(int i = 0; i < INSTANCE_COUNT; i++) {
    models.push_back(
      glm::scale(
        glm::translate(glm::mat4(), {25.0f * i, 25.0f * i, 0.0f}),
        {25.0f, 25.0f, 0.0f}
      )
    );
  }

  engine->Run(update, fixed_update, render);

  delete sprite;

  // Unload resources from RAM
  delete engine;

  return 0;
}