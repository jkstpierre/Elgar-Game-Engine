/*
  Test Project
  Author: Joseph St. Pierre
  Year: 2018
*/

#include "elgar/Engine.hpp"
#include "elgar/audio/AudioSource.hpp"
#include "elgar/audio/AudioListener.hpp"
#include "elgar/core/AudioSystem.hpp"
#include "elgar/graphics/ImageLoader.hpp"
#include "elgar/core/Window.hpp"
#include "elgar/graphics/ShaderManager.hpp"
#include "elgar/core/IO.hpp"

#include "elgar/graphics/data/RGBA.hpp"
#include "elgar/graphics/renderers/SpriteRenderer.hpp"
#include "elgar/graphics/Camera.hpp"

#include "elgar/timers/FrameTimer.hpp"

#include <SDL2/SDL.h>

#include <stdio.h>
#include <iostream>
#include <typeinfo>

#include <unordered_map>

#include <glm/gtc/matrix_transform.hpp>

using namespace elgar;

#define WIDTH 1920
#define HEIGHT 1080
#define INSTANCE_COUNT  100000

Engine *engine = nullptr;

const Shader *shader = nullptr;
Texture *texture = nullptr;

std::vector<glm::mat4> models;

// Create a camera
Camera camera(
  glm::ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT, 0.0f, 1000.0f)
);

void update() {
  static FrameTimer *frame_timer = FrameTimer::GetInstance();

  static Keyboard *keyboard = Keyboard::GetInstance();
  if (!keyboard)
    return;

  if (keyboard->IsKeyPressed(SDLK_ESCAPE))
    engine->SetRunning(false);

  if (keyboard->IsKeyPressed(SDLK_RIGHT))
    camera.ChangePosition({100.0f * frame_timer->GetDeltaTime(), 0.0f, 0.0f});
  if (keyboard->IsKeyPressed(SDLK_LEFT))
    camera.ChangePosition({-100.0f * frame_timer->GetDeltaTime(), 0.0f, 0.0f});
  if (keyboard->IsKeyPressed(SDLK_UP))
    camera.ChangePosition({0.0f, 100.0f * frame_timer->GetDeltaTime(), 0.0f});
  if (keyboard->IsKeyPressed(SDLK_DOWN))
    camera.ChangePosition({0.0f, -100.0f * frame_timer->GetDeltaTime(), 0.0f});
}

void fixed_update() {

}

void render() {
  static SpriteRenderer *spr_rend = SpriteRenderer::GetInstance();

  // Nothing to do if renderer does not exist
  if (!spr_rend)
    return;

  camera.Draw(*shader);   // Draw the camera

  spr_rend->DrawInstanced(
    *shader,
    models,
    {0xFF, 0x25, 0x77, 0xFF},
    texture
  );

  spr_rend->Draw(
    *shader,
    glm::scale(glm::mat4(), {100.0f, 100.0f, 0.0f}),
    {0x12, 0x23, 0x34, 0xFF},
    texture
  );
}

int main() {
  // Create new instance of Elgar
  engine = new Engine("StarLight", WIDTH, HEIGHT, FULLSCREEN);

  ImageLoader *image_loader = ImageLoader::GetInstance();

  if (image_loader) {
    image_loader->LoadFromDisk("destroyer.png", "destroyer");
  }

  const Image *img = image_loader->Read("destroyer");

  if (img) {
    texture = new Texture(*img);  // Create a texture
  }

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

  if (texture)
    delete texture;

  // Unload resources from RAM
  delete engine;

  return 0;
}