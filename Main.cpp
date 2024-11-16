#include <GameInterface.hpp>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight,
             "raylib [models] example - mesh picking");

  // Define the camera to look into our 3d world
  mn::Scene scene1;
  scene1.initCamera();
  raw::TextureC targetT("models/castle/castle_diffuse.png");

  scene1.add("CastleText", "models/castle/castle_diffuse.png");
  raw::TextureC *ptr = scene1.get("CastleText").pickUp<raw::TextureC *>();
  raw::ComponentC ptr1(&targetT);

  raw::ModelC targetM("models/castle/house.obj");
  raw::ComponentC ptr2(&targetM);

  scene1.add("ChestText", "models/chest/wood2.png");

  scene1.add("CastleModel", nullptr, "models/castle/house.obj");
  scene1.add("ChestModel", nullptr, "models/chest/untitled.obj");

  raw::TextureC *ptr02 = scene1.get("ChestText").pickUp<raw::TextureC *>();

  scene1.get("ChestModel")
      .pickUp<raw::ModelC *>()
      ->setText(ptr02->getTexture());
  scene1.get("CastleModel").pickUp<raw::ModelC *>()->setText(ptr->getTexture());

  Vector3 towerPos = {0.0f, 0.0f, 0.0f};
  Vector3 chestPos = {30.0f, 20.0f, 0.0f}; // Set model position
  SetTargetFPS(60); // Set our game to run at 60 frames-per-second

  //--------------------------------------------------------------------------------------
  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------
    if (IsCursorHidden())
      UpdateCamera(scene1.getCameraIO()->getCamera(),
                   CAMERA_FIRST_PERSON); // Update camera

    // Toggle camera controls
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
      if (IsCursorHidden())
        EnableCursor();
      else
        DisableCursor();
    }

    BeginDrawing();

    ClearBackground(RAYWHITE);

    BeginMode3D(*scene1.getCameraIO()->getCamera());

    // Draw the tower
    // WARNING: If scale is different than 1.0f,
    // not considered by GetRayCollisionModel()

    DrawModel(*scene1.get("CastleModel").pickUp<raw::ModelC *>()->getModel(),
              towerPos, 1.0f, WHITE);
    DrawModel(*scene1.get("ChestModel").pickUp<raw::ModelC *>()->getModel(),
              chestPos, 5.0f, WHITE);

    DrawGrid(10, 10.0f);

    EndMode3D();

    DrawFPS(10, 10);

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  system("cls");
  return 0;
}
