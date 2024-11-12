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

RAW_COMPONETS::ModelC::ModelC(string modelPath, Texture *ptrText) {

  auto customDeleter = [](Model *ptr) {
    UnloadModel(*ptr);
    delete ptr;

    cout << "Modelo Foi Desalocado" << '\n';
  };

  smptr<Model> createModel(new Model(LoadModel(modelPath.data())),
                           customDeleter);
  createModel->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *ptrText;

  model = createModel;
}
RAW_COMPONETS::ModelC::ModelC(Model *_model, Texture *ptrText) {
  auto customDeleter = [](Model *ptr) {
    UnloadModel(*ptr);
    delete ptr;

    cout << "Modelo Foi Desalocado" << '\n';
  };

  smptr<Model> createModel(_model, customDeleter);
  createModel->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *ptrText;

  model = createModel;
}

RAW_COMPONETS::ModelC::~ModelC() { cout << "Modelo Foi Destruido" << '\n'; }

Model *RAW_COMPONETS::ModelC::getModel() const { return model.get(); }

// TextureC class

RAW_COMPONETS::TextureC::TextureC(string textPath) {
  auto customDeleter = [](Texture *ptr) {
    UnloadTexture(*ptr);
    delete ptr;

    cout << "Textura Desalocada" << '\n';
  };

  smptr<Texture> createText(new Texture(LoadTexture(textPath.data())),
                            customDeleter);
  text = createText;
}
RAW_COMPONETS::TextureC::TextureC(Texture *_text) {
  auto customDeleter = [](Texture *ptr) {
    UnloadTexture(*ptr);
    delete ptr;

    cout << "Textura Desalocada" << '\n';
  };

  smptr<Texture> createText(_text, customDeleter);
  text = createText;
}

RAW_COMPONETS::TextureC::~TextureC() { cout << "Textura Destruida" << '\n'; }

Texture *RAW_COMPONETS::TextureC::getTexture() const { return text.get(); }

// Item class

RAW_COMPONETS::ItemC::ItemC(Model *_model, Texture *_text, Vector3 _pos) {
  auto customDeleterM = [](ModelC *ptr) {
    delete ptr;
    cout << "Desalocando Item..." << '\n';
  };

  auto customDeleterT = [](TextureC *ptr) { delete ptr; };

  smptr<ModelC> createModel(new ModelC(_model, _text), customDeleterM);
  smptr<TextureC> createText(new TextureC(_text), customDeleterT);

  createModel->getModel()->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture =
      *createText->getTexture();
  pos = _pos;
  text = createText;
  model = createModel;
}

RAW_COMPONETS::ItemC::~ItemC() { cout << "Item Destruido" << '\n'; }

raw::ModelC *RAW_COMPONETS::ItemC::getModelC() const { return model.get(); }

raw::TextureC *RAW_COMPONETS::ItemC::getTextureC() const { return text.get(); }

Vector3 RAW_COMPONETS::ItemC::getPos() const { return pos; }

void RAW_COMPONETS::ItemC::setPos(Vector3 _pos) { pos = _pos; }

// ComponentC

RAW_COMPONETS::ComponentC::ComponentC() {}

RAW_COMPONETS::ComponentC::ComponentC(raw::TextureC *elem) {
  data.t = elem, dataType = TEXTC;
}
RAW_COMPONETS::ComponentC::ComponentC(raw::ModelC *elem) {
  data.m = elem, dataType = MODELC;
}
RAW_COMPONETS::ComponentC::ComponentC(raw::ItemC *elem) {
  data.i = elem, dataType = ITEMC;
}
RAW_COMPONETS::ComponentC::ComponentC(raw::GuiItem *elem) {
  data.gi = elem, dataType = GUI_ITEM;
}
RAW_COMPONETS::ComponentC::ComponentC(raw::NPC *elem) {
  data.n = elem, dataType = NPCC;
}

void RAW_COMPONETS::ComponentC::operator=(raw::NPC *elem) {
  clearC();
  data.n = elem;
  dataType = NPCC;
}
void RAW_COMPONETS::ComponentC::operator=(raw::ModelC *elem) {
  clearC();
  data.m = elem;
  dataType = MODELC;
}
void RAW_COMPONETS::ComponentC::operator=(raw::ItemC *elem) {
  clearC();
  data.i = elem;
  dataType = ITEMC;
}
void RAW_COMPONETS::ComponentC::operator=(raw::TextureC *elem) {
  clearC();
  data.t = elem;
  dataType = TEXTC;
}
void RAW_COMPONETS::ComponentC::operator=(raw::GuiItem *elem) {
  clearC();
  data.gi = elem;
  dataType = GUI_ITEM;
}

void RAW_COMPONETS::ComponentC::clearC() {
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
template <typename T> T RAW_COMPONETS::ComponentC::pickUp() { return nullptr; }
template <> raw::NPC *RAW_COMPONETS::ComponentC::pickUp<raw::NPC *>() {
  if (dataType == NPCC)
    return data.n;
  else
    return nullptr;
}
template <> raw::ItemC *RAW_COMPONETS::ComponentC::pickUp<raw::ItemC *>() {
  if (dataType == ITEMC)
    return data.i;
  else
    return nullptr;
}
template <> raw::ModelC *RAW_COMPONETS::ComponentC::pickUp<raw::ModelC *>() {
  if (dataType == MODELC)
    return data.m;
  else
    return nullptr;
}
template <> raw::GuiItem *RAW_COMPONETS::ComponentC::pickUp<raw::GuiItem *>() {
  if (dataType == GUI_ITEM)
    return data.gi;
  else
    return nullptr;
}
template <>
raw::TextureC *RAW_COMPONETS::ComponentC::pickUp<raw::TextureC *>() {
  if (dataType == TEXTC)
    return data.t;
  else
    return nullptr;
}
// Managers Componets

// Scene class

MANAGERS::Scene::~Scene() {
  for (auto &c : components)
    c.second.clearC();
  cout << "Cena Foi Destruida" << '\n';
}

// add texture
void MANAGERS::Scene::add(string key, string textPath, Texture *text) {
  if (text != nullptr) {
    raw::ComponentC createC(new raw::TextureC(text));
    components.insert({key, createC});
  } else {
    raw::ComponentC createC(new raw::TextureC(textPath));
    components.insert({key, createC});
  }
}
// add model
void MANAGERS::Scene::add(string key, Texture *text, string modelPath,
                          Model *model) {
  if (model != nullptr) {
    raw::ComponentC createC(new raw::ModelC({model, text}));
    components.insert({key, createC});
  } else {
    raw::ComponentC createC(new raw::ModelC({modelPath, text}));
    components.insert({key, createC});
  }
}

// add item
void MANAGERS::Scene::add(string key, Model *model, Texture *text,
                          Vector3 pos) {
  raw::ComponentC createC(new raw::ItemC({model, text, pos}));
  components.insert({key, createC});
}

void MANAGERS::Scene::kill(string key) {
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

raw::ComponentC MANAGERS::Scene::get(string key) {
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
