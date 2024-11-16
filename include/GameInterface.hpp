#ifndef OPEN_PLEASE
#define OPEN_PLEASE

// Global Headers

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

// https://github.com/raysan5/raylib
#include <raylib.h>

#ifndef OBJECTS
#define OBJECTS

using std::cout;
using std::map;
using std::string;
using std::vector;

template <typename T> using smptr = std::shared_ptr<T>;

using uint = unsigned int;

namespace RAW_COMPONETS {

class ModelC {
private:
  smptr<Model> model;

public:
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
  TextureC(string textPath);
  TextureC(Texture *_text);
  ~TextureC();

  Texture *getTexture() const;
};

class ItemC {
private:
  smptr<ModelC> model;
  smptr<TextureC> text;
  Vector3 pos;

public:
  ItemC(Model *_model, Texture *_text, Vector3 _pos);
  ~ItemC();

  ModelC *getModelC() const;
  TextureC *getTextureC() const;
  Vector3 getPos() const;

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

} // namespace RAW_COMPONETS

namespace IO_COMPONETS {

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

} // namespace IO_COMPONETS

namespace MANAGERS {

template <typename T> class managerMemory {};

class Gui final {};
class Scene final {
private:
  map<string, RAW_COMPONETS::ComponentC> components;

  smptr<Gui> gui = nullptr;
  smptr<IO_COMPONETS::CameraIO> camera = nullptr;

public:
  ~Scene();

  void initCamera();
  IO_COMPONETS::CameraIO *getCameraIO();

  // add texture
  void add(string key, string textPath, Texture *text = nullptr);
  // add model
  void add(string key, Model *model, string modelPath = nullptr);
  // add item
  void add(string key, Model *model, Texture *text, Vector3 pos);

  void kill(string Key);

  RAW_COMPONETS::ComponentC get(string key);
};

class UniversalManager final {};

} // namespace MANAGERS

#endif //! OBJECTS

#ifndef FUNC
#define FUNC

// Utility Functions

// Func fetchKey
template <typename M, typename M2>
extern bool fetchKey(M key, map<M, M2> *target);

#endif // !FUNC

#ifndef EXTERNAL

// Other Headers

// https://github.com/nlohmann/json
#include <nlohmann/json.hpp>

#endif // !EXTERNAL

namespace io = IO_COMPONETS;
namespace mn = MANAGERS;
namespace raw = RAW_COMPONETS;

#endif // !OPEN_PLEASE
