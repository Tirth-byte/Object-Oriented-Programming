// Write a C++ Program to demonstrate Run time Polymorphism
#include <iostream>
using namespace std;
class Animal {
    public:
      virtual void sound() {
        cout << "This is a generic animal sound." << endl;
      }
};

class Dog : public Animal {
    public:
      void sound() override {
        cout << "Woof! Woof!" << endl;
      }
};

class Cat : public Animal {
    public:
      void sound() override {
        cout << "the cat says: Meow Meow!" << endl;
      }
};
int main() {
    Animal* animlptr;
    Dog dog;
    Cat cat;
    animlptr = &dog;
    animlptr->sound(); 
    animlptr = &cat;
    animlptr->sound();
    return 0;
}