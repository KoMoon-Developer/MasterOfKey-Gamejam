#include <GameInterface.hpp>

// Utility Functions

template <typename M, typename M2> bool fetchKey(M key, map<M, M2> *target) {
  if (target->find(key)->first == key)
    return true;

  else
    return false;
}

// Raw Componets

// ModelC class

RAW_COMPONENTS::ModelC::ModelC() {

  smptr<Model> createModel(nullptr);
  model = createModel;
}

RAW_COMPONENTS::ModelC::ModelC(string modelPath) {

  auto customDeleter = [](Model *ptr) {
    UnloadModel(*ptr);
    delete ptr;

    cout << "Modelo Foi Desalocado" << '\n';
  };

  smptr<Model> createModel(new Model(LoadModel(modelPath.data())),
                           customDeleter);

  model = createModel;
}
RAW_COMPONENTS::ModelC::ModelC(Model *_model) {
  auto customDeleter = [](Model *ptr) {
    UnloadModel(*ptr);
    delete ptr;

    cout << "Modelo Foi Desalocado" << '\n';
  };

  smptr<Model> createModel(_model, customDeleter);

  model = createModel;
}

RAW_COMPONENTS::ModelC::~ModelC() { cout << "Modelo Foi Destruido" << '\n'; }

Model *RAW_COMPONENTS::ModelC::getModel() const { return model.get(); }

void RAW_COMPONENTS::ModelC::setText(Texture *text) {
  model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *text;
}

// TextureC class

RAW_COMPONENTS::TextureC::TextureC() {
  smptr<Texture> createText(nullptr);
  text = createText;
}

RAW_COMPONENTS::TextureC::TextureC(string textPath) {
  auto customDeleter = [](Texture *ptr) {
    UnloadTexture(*ptr);
    delete ptr;

    cout << "Textura Desalocada" << '\n';
  };

  smptr<Texture> createText(new Texture(LoadTexture(textPath.data())),
                            customDeleter);
  text = createText;
}
RAW_COMPONENTS::TextureC::TextureC(Texture *_text) {
  auto customDeleter = [](Texture *ptr) {
    UnloadTexture(*ptr);
    delete ptr;

    cout << "Textura Desalocada" << '\n';
  };

  smptr<Texture> createText(_text, customDeleter);
  text = createText;
}

RAW_COMPONENTS::TextureC::~TextureC() { cout << "Textura Destruida" << '\n'; }

Texture *RAW_COMPONENTS::TextureC::getTexture() const { return text.get(); }

// Item class

RAW_COMPONENTS::ItemC::~ItemC() { cout << "Item Destruido" << '\n'; }

raw::ModelC *RAW_COMPONENTS::ItemC::getModelC() const {
  return (raw::ModelC *)&model;
}

Vector3 RAW_COMPONENTS::ItemC::getPosition() const { return pos; }

void RAW_COMPONENTS::ItemC::setPos(Vector3 _pos) { pos = _pos; }

void RAW_COMPONENTS::ItemC::movePos(Vector3 _pos) {
  pos.x += _pos.x;
  pos.y += _pos.y;
  pos.y += _pos.z;
}

// ComponentC

RAW_COMPONENTS::ComponentC::ComponentC() {}

RAW_COMPONENTS::ComponentC::ComponentC(raw::TextureC *elem) {
  data.t = elem, dataType = TEXTC;
}
RAW_COMPONENTS::ComponentC::ComponentC(raw::ModelC *elem) {
  data.m = elem, dataType = MODELC;
}
RAW_COMPONENTS::ComponentC::ComponentC(raw::ItemC *elem) {
  data.i = elem, dataType = ITEMC;
}
RAW_COMPONENTS::ComponentC::ComponentC(raw::GuiItemC *elem) {
  data.gi = elem, dataType = GUI_ITEM;
}
RAW_COMPONENTS::ComponentC::ComponentC(raw::NPC *elem) {
  data.n = elem, dataType = NPCC;
}

void RAW_COMPONENTS::ComponentC::operator=(raw::NPC *elem) {
  clearC();
  data.n = elem;
  dataType = NPCC;
}
void RAW_COMPONENTS::ComponentC::operator=(raw::ModelC *elem) {
  clearC();
  data.m = elem;
  dataType = MODELC;
}
void RAW_COMPONENTS::ComponentC::operator=(raw::ItemC *elem) {
  clearC();
  data.i = elem;
  dataType = ITEMC;
}
void RAW_COMPONENTS::ComponentC::operator=(raw::TextureC *elem) {
  clearC();
  data.t = elem;
  dataType = TEXTC;
}
void RAW_COMPONENTS::ComponentC::operator=(raw::GuiItemC *elem) {
  clearC();
  data.gi = elem;
  dataType = GUI_ITEM;
}

void RAW_COMPONENTS::ComponentC::clearC() {
  try {
    switch (dataType) {
    case MODELC:
      delete data.m;
      throw 1;
      break;
    case TEXTC:
      delete data.t;
      throw 1;
      break;
    case ITEMC:
      delete data.i;
      throw 1;
      break;
    case NPCC:
      delete data.n;
      throw 1;
      break;
    case GUI_ITEM:
      delete data.gi;
      throw 1;
      break;
    default:
      throw string("objeto nao NONE");
      break;
    }
  } catch (string error) {
    cout << "ERROR -> " << error << '\n';
  } catch (...) {
    cout << "Componente foi limpo" << '\n';
  }
}
template <typename T> T RAW_COMPONENTS::ComponentC::pickUp() { return nullptr; }
template <> raw::NPC *RAW_COMPONENTS::ComponentC::pickUp<raw::NPC *>() {
  if (dataType == NPCC)
    return data.n;
  else
    return nullptr;
}
template <> raw::ItemC *RAW_COMPONENTS::ComponentC::pickUp<raw::ItemC *>() {
  if (dataType == ITEMC)
    return data.i;
  else
    return nullptr;
}
template <> raw::ModelC *RAW_COMPONENTS::ComponentC::pickUp<raw::ModelC *>() {
  if (dataType == MODELC)
    return data.m;
  else
    return nullptr;
}
template <>
raw::GuiItemC *RAW_COMPONENTS::ComponentC::pickUp<raw::GuiItemC *>() {
  if (dataType == GUI_ITEM)
    return data.gi;
  else
    return nullptr;
}
template <>
raw::TextureC *RAW_COMPONENTS::ComponentC::pickUp<raw::TextureC *>() {
  if (dataType == TEXTC)
    return data.t;
  else
    return nullptr;
}
template <> raw::TextureC RAW_COMPONENTS::ComponentC::pickUp<raw::TextureC>() {

  if (dataType == TEXTC)
    return *data.t;
  else
    return raw::TextureC();
}
template <> raw::GuiItemC RAW_COMPONENTS::ComponentC::pickUp<raw::GuiItemC>() {
  if (dataType == GUI_ITEM)
    return *data.gi;
  else
    return raw::GuiItemC();
}
template <> raw::ModelC RAW_COMPONENTS::ComponentC::pickUp<raw::ModelC>() {
  if (dataType == MODELC)
    return *data.m;
  else
    return raw::ModelC();
}

// IO_Components

// Camera
IO_COMPONENTS::CameraIO::CameraIO() {
  auto customDeleter = [](Camera *ptr) {
    delete ptr;
    cout << "Camera foi desalocada" << '\n';
  };

  smptr<Camera> createCamera(new Camera({0}), customDeleter);
  createCamera->position = Vector3({20.0f, 20.0f, 20.0f});
  createCamera->target = Vector3({0.0f, 0.0f, 0.0f});
  createCamera->up = Vector3({0.0f, 1.0f, 0.0f});
  createCamera->fovy = 60.0f;
  createCamera->projection = CAMERA_PERSPECTIVE;

  camera = createCamera;
}

IO_COMPONENTS::CameraIO::~CameraIO() {
  cout << "Componente da Camera foi Destruido" << '\n';
}

void IO_COMPONENTS::CameraIO::config(Vector3 pos) { camera->position = pos; }
void IO_COMPONENTS::CameraIO::config(float zoom) { camera->fovy += zoom; }
void IO_COMPONENTS::CameraIO::config(int cameraType) {
  camera->projection = cameraType;
}

Camera *IO_COMPONENTS::CameraIO::getCamera() { return camera.get(); }

// Managers Componets

// Scene class

MANAGERS_COMPONENTS::Scene::~Scene() {
  for (auto &c : components)
    c.second.clearC();
  cout << "Cena Foi Destruida" << '\n';
}

void MANAGERS_COMPONENTS::Scene::initCamera() {

  auto customDeleter = [](io::CameraIO *ptr) { delete ptr; };
  smptr<io::CameraIO> createCamera(new io::CameraIO, customDeleter);
  camera = createCamera;
}

io::CameraIO *MANAGERS_COMPONENTS::Scene::getCameraIO() { return camera.get(); }

// add texture
void MANAGERS_COMPONENTS::Scene::add(string key, string textPath,
                                     Texture *text) {
  if (text != nullptr) {
    raw::ComponentC createC(new raw::TextureC(text));
    components.insert({key, createC});
  } else {
    raw::ComponentC createC(new raw::TextureC(textPath));
    components.insert({key, createC});
  }
}
// add model
void MANAGERS_COMPONENTS::Scene::add(string key, Model *model,
                                     string modelPath) {
  if (model != nullptr) {
    raw::ComponentC createC(new raw::ModelC(model));
    components.insert({key, createC});
  } else {
    raw::ComponentC createC(new raw::ModelC(modelPath));
    components.insert({key, createC});
  }
}

// add item
void MANAGERS_COMPONENTS::Scene::add(string key, raw::ItemC *item,
                                     raw::ModelC model, Texture *text,
                                     Vector3 pos) {
  if (item != nullptr) {
    components.insert({key, item});
  } else {
    raw::ComponentC createC(new raw::ItemC(model, pos));
    components.insert({key, createC});
  }
}

void MANAGERS_COMPONENTS::Scene::kill(string key) {
  try {
    if (fetchKey(key, &components)) {
      components.find(key)->second.clearC();
      components.erase(key);
    } else
      throw string("Alvo nao encontrado");

  } catch (string error) {
    cout << "ERRO -> " << error << '\n';
  }
}

raw::ComponentC MANAGERS_COMPONENTS::Scene::get(string key) {
  try {
    if (fetchKey(key, &components)) {
      return components.find(key)->second;
    } else
      throw string("Chave nao encontrada");

  } catch (string error) {
    cout << "ERROR -> " << error << '\n';
    return raw::ComponentC();
  }
}
