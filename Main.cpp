#include <GameInterface.hpp>
#include <cstdlib>

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
  Camera camera = {0};
  camera.position = Vector3({20.0f, 20.0f, 20.0f}); // Camera position
  camera.target = Vector3({0.0f, 0.0f, 0.0f});      // Camera looking at point
  camera.up =
      Vector3({0.0f, 1.0f, 0.0f}); // Camera up vector (rotation towards target)
  camera.fovy = 60.0f;             // Camera field-of-view Y
  camera.projection = CAMERA_PERSPECTIVE; // Camera projection type

  mn::Scene scene1;
  raw::TextureC targetT("models/castle/castle_diffuse.png");

  scene1.add("CastleText", "models/castle/castle_diffuse.png");
  raw::TextureC *ptr = scene1.get("CastleText").pickUp<raw::TextureC *>();
  raw::ComponentC ptr1(&targetT);

  raw::ModelC targetM("models/castle/house.obj",
                      ptr1.pickUp<raw::TextureC *>()->getTexture());
  raw::ComponentC ptr2(&targetM);

  scene1.add("CastleModel", ptr1.pickUp<raw::TextureC *>()->getTexture(),
             "models/castle/house.obj");

  Vector3 towerPos = {0.0f, 0.0f, 0.0f}; // Set model position
  SetTargetFPS(60); // Set our game to run at 60 frames-per-second

  float x = 0;

  //--------------------------------------------------------------------------------------
  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------
    if (IsCursorHidden())
      UpdateCamera(&camera, CAMERA_FIRST_PERSON); // Update camera

    // Toggle camera controls
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
      if (IsCursorHidden())
        EnableCursor();
      else
        DisableCursor();
    }

    camera.up =
        Vector3({x, 1.0f, 0.0f}); // Camera up vector (rotation towards target)

    BeginDrawing();

    ClearBackground(RAYWHITE);

    BeginMode3D(camera);

    // Draw the tower
    // WARNING: If scale is different than 1.0f,
    // not considered by GetRayCollisionModel()

    DrawModel(*scene1.get("CastleModel").pickUp<raw::ModelC *>()->getModel(),
              towerPos, 1.0f, WHITE);

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
