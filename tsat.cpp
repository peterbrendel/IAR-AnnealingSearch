/**
* Trabalho de IAR - Annealing Search
*  Professor Rafael Parpinelli
*  Graduandos
*      Andre Ruas
*      Peter Brendel
*
*  Compilação:
*     $ make -> Versão final
*     $ make debug -> Versão pra debug
**/

#include "utils/config.hpp"
#include "heuristics/sa.hpp"
#include <random>
#include <cstdio>
#include <cmath>

const double T0 = 1000, TN = 0.0001;
const int updt = 100000;
const int N = 35;
const double A = (T0 - TN) * (N + 1) / (N-1);
const double B = T0 - A;

void sorter(vector<byte> * arr){
    int arrsz = arr->size();
    for(int i=0; i < arrsz; i++){
        (*arr)[i] ^= ((double)rand() / RAND_MAX <= 0.5);
    }
}

void alphatemp(double * temp, int iter){
    *temp = (A/(iter)) + B;
    // double in = iter / 1000;
    // *temp = 0.99 * pow((0.5 / 0.99), in);
    // *temp = 1.0 / (1 + 1.78 * log(1+iter));
}

void slowerAlphatemp(double * temp, int iter){
    *temp = T0 * powf((TN / T0), (double)iter/(double)N);
}

int main(const int argc, const char* argv[]) {

    int varAmt, clauseAmt;
    int a, b, c, idx;
    string temp;

    if(argc < 2){
        cout << "Usage: ./a.out PathToInputFile" << endl;
        exit(1);
    }

    ifstream is (argv[1], fstream::in);

    // Read all lines until configuration (cnf) line is reached
    while(is >> temp && temp != "cnf");
    // Read configuration
    is >> varAmt >> clauseAmt;

    vector<byte> * variables = new vector<byte>();
    vector<Config*> * clauses = new vector<Config*>();
    for(int i=0; i<varAmt; i++){
        variables->push_back(0);
    }

    while(is.peek() != '%'){
        is >> a >> b >> c;
        is.ignore(numeric_limits<streamsize>::max(), '\n');
        clauses->push_back( new Config(*variables, a, b, c) );
    }
    assert(clauses->size() == clauseAmt);
    srand(time(NULL));
    Simanneal<vector<byte>, vector<Config*>> * annealer = new Simanneal<vector<byte>, vector<Config*>>(T0, updt, variables, clauses);

    #ifdef DEBUG
    int count = 0;
    //Test print ( operator<< )
    for(auto c : *clauses){
        cout << *c << endl;
        count += c->evaluate();
    }

    cout << "True = " << count << endl << "False = " << clauses->size() - count << endl;
    cout << "Annealer type: " << annealer->getType() << endl;

    // auto ans = annealer->Randomsearch(&sorter);
    // cout << "RandomSearch answer:\n";

    auto ans = annealer->Anneal(&sorter, &alphatemp);
    cout << "Simulated Annealing answer:\n";
    for(int i : ans.second.second){
        cout << i << " ";
    }cout << endl;
    cout << "K = " << ans.second.first << endl;

    #else
    for(int i=0; i<10; i++){
        // auto ans = annealer->Anneal(&sorter, &alphatemp);
        auto ans = annealer->Randomsearch(&sorter);
        for(auto i : ans.first){
          cout << i << " ";
        }cout << endl;
        cout << ans.second.first << endl;
        cout << "#\n";
    }
    #endif

    return 0;
}
