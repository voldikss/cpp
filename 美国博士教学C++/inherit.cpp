#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>
using namespace std;

class Shape{
    virtual void draw() = 0;
    virtual void rotate(int angle) = 0;
    virtual void move(Point to) = 0;
    virtual ~Shape(){}
};

class Circle : public Shape {
  private:
      int r;
      Point x;
  public:
      Circle(Point p, int radius);
      ~Circle() = default;
      virtual void draw();
      virtual void rotate();
      virtual void move(Point to) {
          x = to;
      }
};

class SmilyFace : public Circle {
  private:
      Shape *mouth;
      vector<Shape*> eyes;
  public:
      SmilyFace(Point p, int r): mouth(nullptr);
      ~SmilyFace() {
          delete mouth;
          for (auto p:eyes) {
              delete p;
          }
      }
      void move(Point to);
      void draw() const;
      void rotate() const;
      void add_eye(Shape *s) {
          eyes.push_back(s);
      }
      void set_mouth(Shape *s);
      virtual void wink(int i);
      //...
};

void SmilyFace::draw() const {
    Circle::draw();
    for (auto p: eyes)
        p->draw();
    mouth->draw();
}

void rotate_all(vector<Shape*>&v, int angle) {
    for (auto &p: v) {
        p->rotate(angle);
    }
}
