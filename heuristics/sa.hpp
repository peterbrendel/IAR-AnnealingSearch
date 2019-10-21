#pragma once
#include "../utils/utils.hpp"

template<typename T>
class Simanneal {
private:
    int maxT;
    int minT;
    int iterations;
    int updates;

    virtual int evaluate() = 0;

    T best_state;
    T state;

public:
    void Randomsearch();
    Simanneal(int maxT, int minT, int iterations, int updates);
};

template<typename T>
Simanneal<T>::Simanneal(int maxT, int minT, int iterations, int updates){
  this->maxT = maxT;
  this->minT = minT;
  this->iterations = iterations;
  this->updates = updates;
}

template<typename T>
void Simanneal<T>::Randomsearch(){
  int iterations = this->iterations;

  while(iterations--){
    cout << this->evaluate() << endl;
  }

}
