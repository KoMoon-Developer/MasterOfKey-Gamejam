#include <GameInterface.hpp>
#include <functional>
#include <initializer_list>

template <typename T> using argsList = std::initializer_list<T>;
using std::function;

enum class Difficult : int {
  Baby = 0,
  Easy = 1,
  Normal = 2,
  Hard = 3,
  Extraodinary = 4
};

#define BABY Difficult::Baby;

template <typename T> class Challege {
private:
  T date;
  T objective;
  function<bool(T, T)> testFunc;

public:
  Challege(T _date, T _objective, function<bool(T, T)> func)
      : date(_date), objective(_objective), testFunc(func) {}
};

class Chest : public RAW_COMPONENTS::ItemC {
private:
  Difficult difficult = BABY;

public:
  Chest(Difficult _difficult, raw::ModelC model, Vector3 pos)
      : ItemC(model, pos), difficult(_difficult) {}

  void defineChalleges();

  bool openChest();
};
