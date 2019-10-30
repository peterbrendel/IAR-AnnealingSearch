#ifndef SA_HPP
#define SA_HPP
#include "../utils/utils.hpp"
#include "../utils/base.hpp"
#include <typeinfo>
#include <cstdio>
#include <cmath>

template <class T, class G>
class Simanneal {
private:
    T * dataset;
    G * clauses;

    double firstT;
    double iteraT;
    int iterations;
    int updates;
    int maxSuccess;

    int eval(){
        int val = 0;
        for(auto c : *this->clauses){
            val += c->evaluate();
        }
        return val;
    }

public:
    explicit Simanneal(double firstT = 2, int iterations = 1000, int updates = 100);
    Simanneal(double firstT, int iterations, int updates, int maxSuccess, T * dataset, G * clauses);

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
                // cout << "Update " << this->updates - updates << " Iteration " << this->iterations - iterations << ": " << k << endl;
                if(k > maxK){
                    maxK = k;
                    bestSet = *this->dataset;
                }
            }
        }
        return {maxK, bestSet};
    }

    pair<vector<int>, pair<int, T>> Anneal(void (*f)(T*, double temp), void (*g)(double*, int update)){
        this->  iteraT      = this->firstT;
        int     iterations  = this->iterations;
        int     updates     = this->updates;
        int     maxK        = 0;

        T       bestSet     = *this->dataset;
        int     bestEval    = this->eval();
        double  deltaBest   = (double)bestEval / this->clauses->size();

        T       iterSet     = *this->dataset;
        int     iterEval    = bestEval;
        double  deltaIter    = deltaBest;

        vector<int> history;
        history.push_back(bestEval);

        int j=1;
        int success;
        do {
            int i=1;
            success = 0;
            updates = this->updates;
            do{
                f(this->dataset, this->iteraT);
                int testEval = this->eval();
                double deltaTest = (double)testEval / this->clauses->size();
                double delta = deltaTest - deltaIter;
                // cout << delta << endl;

                #ifdef DEBUG
                cout << a << (a < b ? '<' : '>') << b << endl;
                #endif
                if(delta <= 0) {
                    success++;
                    history.push_back(testEval);
                    if(testEval < bestEval){
                        bestSet = *this->dataset;
                        deltaBest = deltaTest;
                        bestEval = testEval;
                    }
                } else {
                  double a = (double)rand() / RAND_MAX;
                  double b = exp(-delta / this->iteraT);
                  if(a < b){
                    
                  }
                }
                #ifdef DEBUG
                else{

                    cout << 'e';
                }
                #endif
                i++;
            } while(success < this->maxSuccess && i <= updates );

            g(&this->iteraT, j);
            j++;
            #ifdef DEBUG
            cout << "\ntemperature> " << this->iteraT << endl;
            #endif
        }while(success != 0 && j <= iterations);
        int trues = 0;
        for(auto c : *this->clauses){
            trues += c->evaluate();
        }

        return {history, {trues, bestSet}};
    }

    string getType() {
        return typeid(dataset).name();
    }

};

template <class T, class G>
Simanneal<T,G>::Simanneal(double firstT, int iterations, int updates){
    this->firstT = firstT;
    this->iterations = iterations;
    this->updates = updates;
    this->dataset = new T();
}

template <class T, class G>
Simanneal<T,G>::Simanneal(double firstT, int iterations, int updates, int maxSuccess, T * dataset, G * clauses){
    this->firstT = firstT;
    this->iterations = iterations;
    this->updates = updates;
    this->maxSuccess = maxSuccess;
    this->dataset = dataset;
    this->clauses = clauses;
    #ifdef DEBUG
    cout << "dataset content> ";
    for(int c : *(this->dataset)){
        cout << c << " ";
    } cout << endl;
    #endif
}

#endif
