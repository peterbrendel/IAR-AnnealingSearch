#ifndef SA_HPP
#define SA_HPP
#include "../utils/utils.hpp"
#include <typeinfo>

template <class T>
class Simanneal {
private:
    T   dataset;
    int maxT;
    int minT;
    int iterations;
    int updates;

public:
    explicit Simanneal(int maxT = 2, int minT = 1000, int iterations = 1000, int updates = 100);

    void Randomsearch(){
      int updates = this->updates;
      while(updates--){
        int iterations = this->iterations;
        while(iterations--){
        }
      }
    }

    string getType() {
      return typeid(dataset).name();
    }

};

template <class T>
Simanneal<T>::Simanneal(int maxT, int minT, int iterations, int updates){
  this->maxT = maxT;
  this->minT = minT;
  this->iterations = iterations;
  this->updates = updates;
}

#endif
