#include "GameInterface.hpp"

enum class Difficult : int {
  Baby = 0,
  Easy = 1,
  Normal = 2,
  Hard = 3,
  Extraodinary = 4
};

class Challege {};

class Chest : public RAW_COMPONETS::ItemC {
private:
  Difficult difficult;
  smptr<Challege[]> challeges;

public:
  Chest(Model *model, Texture *text, Vector3 pos, Difficult _difficult)
      : ItemC(model, text, pos), difficult(_difficult) {}
};
