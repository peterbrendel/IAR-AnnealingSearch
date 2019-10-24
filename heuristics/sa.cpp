#include "../utils/utils.hpp"
#include "sa.hpp"

template<class T>
Simanneal<T>::Simanneal(int maxT, int minT, int iterations, int updates){
  this->maxT = maxT;
  this->minT = minT;
  this->iterations = iterations;
  this->updates = updates;
}

template<class T>
void Simanneal<T>::Randomsearch(){

  int updates = this->updates;

  while(updates--){
    int iterations = this->iterations;
    while(iterations--){

    }
  }

}
