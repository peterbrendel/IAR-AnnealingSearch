#ifndef SA_HPP
#define SA_HPP
#include "../utils/utils.hpp"
#include "../utils/base.hpp"
#include <typeinfo>

template <class T, class G>
class Simanneal {
private:
    T * dataset;
    G * clauses;

    int maxT;
    int minT;
    int iterations;
    int updates;

public:
    explicit Simanneal(int maxT = 2, int minT = 1000, int iterations = 1000, int updates = 100);
    Simanneal(int maxT, int minT, int iterations, int updates, T * dataset, G * clauses);

    void genRandVal(){}

    pair<int, T> Randomsearch(void (*f)(T*)){
      int updates = this->updates;
      int maxK = 0;
      T bestSet;

      while(updates--){
        int iterations = this->iterations;
        while(iterations--){
          int k = 0;
          f(this->dataset);
          for(auto c : *this->clauses){
            k += c->evaluate();
          }
          //cout << "Update " << this->updates - updates << " Iteration " << this->iterations - iterations << ": " << k << endl;
          if(k > maxK){
            maxK = k;
            bestSet = *this->dataset;
          }
        }
      }
      return {maxK, bestSet};
    }

    string getType() {
      return typeid(dataset).name();
    }

};

template <class T, class G>
Simanneal<T,G>::Simanneal(int maxT, int minT, int iterations, int updates){
  this->maxT = maxT;
  this->minT = minT;
  this->iterations = iterations;
  this->updates = updates;
  this->dataset = new T();
}

template <class T, class G>
Simanneal<T,G>::Simanneal(int maxT, int minT, int iterations, int updates, T * dataset, G * clauses){
  this->maxT = maxT;
  this->minT = minT;
  this->iterations = iterations;
  this->updates = updates;
  this->dataset = dataset;
  this->clauses = clauses;
  cout << "dataset content> ";
  for(int c : *(this->dataset)){
    cout << c << " ";
  } cout << endl;
}

#endif
