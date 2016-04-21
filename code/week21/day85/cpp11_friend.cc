#include <iostream>
using namespace std;

template <typename T> class DefenderT {
public:
  friend T;
  void Defence(int x, int y) {}
  void Trakle(int x, int y) {}

private:
  int pos_x = 15;
  int pos_y = 0;
  int speed = 2;
  int stamina = 120;
};


template <typename T> class AttackerT {
public:
  friend T;
  void Move(int x, int y) {}
  void SpeedUp(float ratio) {}

private:
  int pos_x = 0;
  int pos_y = -30;
  int speed = 3;
  int stamina = 100;
};

using Defender = DefenderT<int>;
using Attacker = AttackerT<int>;

#ifdef UNIT_TEST
class Validator {
public:
  void Validate(int x, int y, DefenderTest &d) {}
  void Validate(int x, int y, AttackerTest &d) {}
};

using DefenderTest = DefenderT<Validator>;
using AttackerTest = AttackerT<Validator>;

int main()
{
  AttackerTest a;
  DefenderTest d;
  a.Move(15, 30);
  d.Defence(15, 30);
  a.SpeedUp(1.5f);
  d.Defence(15, 30);

  Validator v;
  v.Validate(7, 0, d);
  v.Validate(1, -10, a);

  return 0;
}
#endif
