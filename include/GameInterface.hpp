#ifndef OPEN_PLEASE
#define OPEN_PLEASE

// Global Headers

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <typeinfo>
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
  ModelC(string modelPath, Texture *ptrText = nullptr);
  ModelC(Model *_model, Texture *ptrText = nullptr);
  ~ModelC();

  Model *getModel() const;
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
  char state = 'S';

public:
  ItemC(Model *_model, Texture *_text, Vector3 _pos);
  ~ItemC();

  ModelC *getModelC() const;
  TextureC *getTextureC() const;
  Vector3 getPos() const;

  void setPos(Vector3 _pos);
};

class GuiItem {};

class NPC {};

union Data {
  TextureC *t;
  ItemC *i;
  ModelC *m;
  GuiItem *gi;
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
  ComponentC(GuiItem *elem);
  ComponentC(NPC *elem);
  ComponentC(ItemC *elem);

  void operator=(TextureC *elem);
  void operator=(ItemC *elem);
  void operator=(ModelC *elem);
  void operator=(GuiItem *elem);
  void operator=(NPC *elem);

  void clearC();
  template <typename T> T pickUp();
};

} // namespace RAW_COMPONETS

namespace IO_COMPONETS {

class Camera {};

class Input {};

class StackIN {};

} // namespace IO_COMPONETS

namespace MANAGERS {

template <typename T> class managerMemory {};

class Gui final {};
class Scene final {
private:
  map<string, RAW_COMPONETS::ComponentC> components;

  smptr<Gui> gui;
  smptr<Camera> camera;

public:
  ~Scene();

  // add texture
  void add(string key, string textPath, Texture *text = nullptr);
  // add model
  void add(string key, Texture *text, string modelPath, Model *model = nullptr);
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
