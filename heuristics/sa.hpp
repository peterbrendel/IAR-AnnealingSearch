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
    int updates;

    int eval(){
        int val = 0;
        for(auto c : *this->clauses){
            val += c->evaluate();
        }
        return val;
    }

    double normalizeDelta(double delta, double left, double right){
        double normal = (delta) * (right - left) / ( this->clauses->size())  + left;
        return normal;
    }

public:
    explicit Simanneal(double firstT = 2, int updates = 1000);
    Simanneal(double firstT, int updates, T * dataset, G * clauses);

    pair<int, T> Randomsearch(void (*f)(T*)){
        int updates = this->updates;
        int maxK = 0;
        T bestSet;

        while(updates--){
            int iterations = this->updates;
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

    pair<vector<int>, pair<int, T>> Anneal(void (*f)(T*), void (*g)(double*, int update)){
        this->  iteraT      = this->firstT;
        int     updates     = this->updates;
        int     maxK        = 0;

        T       bestSet     = *this->dataset;
        int     bestEval    = this->eval();
        double  deltaBest   = (double)bestEval; /// this->clauses->size();

        T       iterSet     = *this->dataset;
        int     iterEval    = bestEval;
        double  deltaIter   = deltaBest;

        vector<int> history;
        history.push_back(bestEval);

        int j=1;
        do {
            int i=1;
            updates = this->updates;
            do{
                iterSet = *this->dataset;
                f(this->dataset);
                int testEval = this->eval();
                double deltaTest = (double)testEval; /// this->clauses->size();
                double delta = deltaIter - deltaTest;

                if(delta <= 0) {
                    deltaIter = deltaTest;
                    history.push_back(testEval);
                    #ifdef DEBUG
                    // cout << "small delta pick\n";
                    #endif
                    if(testEval > bestEval){
                        #ifdef DEBUG
                        cout << "newBest " << testEval << " > " << bestEval << "\n";
                        #endif
                        bestSet = *this->dataset;
                        deltaBest = deltaTest;
                        bestEval = testEval;
                    }
                } else {
                    double a = (double)rand() / RAND_MAX;
                    // cout << this->iteraT << endl;
                    // cout << -delta / this->iteraT * 10 << endl;
                    double b = exp(/*this->normalizeDelta(delta, -200, 0)*/(-delta * this->clauses->size() / 5.0) / (double)this->iteraT);
                    // cout << b << endl;
                    #ifdef DEBUG
                    printf("a > %.3lf\nb > %.3lf\n ", a, b);
                    #endif
                    if(a >= b){
                        #ifdef DEBUG
                        cout << "fallBack\n";
                        #endif
                        *this->dataset = iterSet;
                    } else {
                        #ifdef DEBUG
                        // cout << "pick\n";
                        #endif
                        // cout << "pick " << this->iteraT << endl;
                        deltaIter = deltaTest;
                        history.push_back(testEval);
                    }
                }
                i++;
            } while(i <= updates);

            g(&this->iteraT, j);
            j++;
            // cout << "\ntemperature> " << this->iteraT << endl;
            #ifdef DEBUG
             cout << "\ntemperature> " << this->iteraT << endl;
            #endif
        }while(this->iteraT > 0.001);
        int trues = 0;
        *this->dataset = bestSet;
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
Simanneal<T,G>::Simanneal(double firstT, int updates){
    this->firstT = firstT;
    this->updates = updates;
    this->dataset = new T();
}

template <class T, class G>
Simanneal<T,G>::Simanneal(double firstT, int updates, T * dataset, G * clauses){
    this->firstT = firstT;
    this->updates = updates;
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
