#include "../utils/utils.hpp"
#include "sa.hpp"

template<typename T>
Simanneal<T>::Simanneal(int maxT, int minT, int iterations, int updates){
  this->maxT = maxT;
  this->minT = minT;
  this->iterations = iterations;
  this->updates = updates;
}

template<typename T>
void Simanneal<T>::Randomsearch(){
  int iterations = this->itereations;

  while(iterations--){
    cout << this->evaluate() << endl;
  }

}
