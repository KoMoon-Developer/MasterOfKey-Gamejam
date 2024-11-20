#ifndef OPEN_PLEASE
#define OPEN_PLEASE

// Global Headers

#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

#ifndef EXTERNAL

// Other Headers

// https://github.com/nlohmann/json
#include <nlohmann/json.hpp>
// https://github.com/raysan5/raylib
#include <raylib.h>

#endif // !EXTERNAL

#ifndef OBJECTS
#define OBJECTS

using std::cout;
using std::map;
using std::string;
using std::vector;

template <typename T> using smptr = std::shared_ptr<T>;

using uint = unsigned int;

namespace RAW_COMPONENTS {

class ModelC {
private:
  smptr<Model> model;

public:
  ModelC();
  ModelC(string modelPath);
  ModelC(Model *_model);
  ~ModelC();

  Model *getModel() const;
  void setText(Texture *text);
};
class TextureC {
private:
  smptr<Texture> text;

public:
  TextureC();
  TextureC(string textPath);
  TextureC(Texture *_text);
  ~TextureC();

  Texture *getTexture() const;
};

class ItemC {
private:
  ModelC model;
  Vector3 pos;

public:
  ItemC(ModelC _model, Vector3 _pos) : model(_model), pos(_pos) {}
  ~ItemC();

  ModelC *getModelC() const;
  Vector3 getPosition() const;

  void setPos(Vector3 _pos);
  void movePos(Vector3 _pos);
};

class GuiItemC {};

class NPC {};

union Data {
  TextureC *t;
  ItemC *i;
  ModelC *m;
  GuiItemC *gi;
  NPC *n;
};

enum class Type { None, Text, Model, GUIitem, Npcc, Item };

#define NONE Type::None
#define TEXTC Type::Text
#define MODELC Type::Model
#define NPCC Type::Npcc
#define GUI_ITEM Type::GUIitem
#define ITEMC Type::Item

class ComponentC {
private:
  Data data;
  Type dataType = NONE;

public:
  ComponentC();
  ComponentC(TextureC *elem);
  ComponentC(ModelC *elem);
  ComponentC(GuiItemC *elem);
  ComponentC(NPC *elem);
  ComponentC(ItemC *elem);

  void operator=(TextureC *elem);
  void operator=(ItemC *elem);
  void operator=(ModelC *elem);
  void operator=(GuiItemC *elem);
  void operator=(NPC *elem);

  void clearC();
  template <typename T> T pickUp();
};

} // namespace RAW_COMPONENTS

namespace IO_COMPONENTS {

class CameraIO {
private:
  smptr<Camera> camera;

public:
  CameraIO();
  ~CameraIO();

  // config position
  void config(Vector3 pos);
  // config zoom
  void config(float zoom);
  // config camera Projection
  void config(int cameraType);

  Camera *getCamera();
};

class InputIN {};

class StackIN {};

} // namespace IO_COMPONENTS

namespace MANAGERS_COMPONENTS {

class Gui final {};
class Scene final {
private:
  map<string, RAW_COMPONENTS::ComponentC> components;

  smptr<Gui> gui = nullptr;
  smptr<IO_COMPONENTS::CameraIO> camera = nullptr;

public:
  ~Scene();

  void initCamera();
  IO_COMPONENTS::CameraIO *getCameraIO();

  // add texture
  void add(string key, string textPath, Texture *text = nullptr);
  // add model
  void add(string key, Model *model, string modelPath = nullptr);
  // add item
  void add(string key, RAW_COMPONENTS::ItemC *item,
           RAW_COMPONENTS::ModelC model = RAW_COMPONENTS::ModelC(),
           Texture *text = nullptr, Vector3 pos = Vector3({0.0f, 0.0f, 0.0f}));

  void kill(string Key);

  RAW_COMPONENTS::ComponentC get(string key);
  map<string, RAW_COMPONENTS::ComponentC> *getAll();
};

class UniversalManager final {};

} // namespace MANAGERS_COMPONENTS

#endif //! OBJECTS

#ifndef FUNC
#define FUNC

// Utility Functions

// Func fetchKey
template <typename M, typename M2>
extern bool fetchKey(M key, map<M, M2> *target);

#endif // !FUNC

namespace io = IO_COMPONENTS;
namespace mn = MANAGERS_COMPONENTS;
namespace raw = RAW_COMPONENTS;

#endif // !OPEN_PLEASE
