#include <MasterOfKey.hpp>

using mn::Scene;
using raw::ItemC;
using raw::ModelC;

Scene *scene01() {
  Scene *scene = new Scene;
  scene->initCamera();
  scene->getCameraIO()->config(Vector3({10.0f, 3.0f, 0.0f}));

  scene->add("ChestModel", nullptr, "models/chest/untitled.obj");

  ItemC *item =
      new Chest(Difficult::Baby, scene->get("ChestModel").pickUp<ModelC>(),
                Vector3({0.0f, 0.0f, 0.0f}));

  scene->add("ChestITEM", item);

  return scene;
}

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "MasterOfKey");

  Scene *scene = scene01();

  Camera *camera = scene->getCameraIO()->getCamera();

  SetTargetFPS(120);

  while (!WindowShouldClose()) {
    if (IsCursorHidden())
      UpdateCamera(camera, CAMERA_FIRST_PERSON);

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
      if (IsCursorHidden())
        EnableCursor();
      else
        DisableCursor();
    }
    BeginDrawing();

    ClearBackground(RAYWHITE);

    BeginMode3D(*camera);

    DrawModel(
        *scene->get("ChestITEM").pickUp<ItemC *>()->getModelC()->getModel(),
        scene->get("ChestITEM").pickUp<ItemC *>()->getPosition(), 1.0f, WHITE);
    DrawGrid(10, 10.0f);

    EndMode3D();

    DrawFPS(10, 10);

    EndDrawing();
  }

  CloseWindow();

  system("cls");
  delete scene;
  return 0;
}
