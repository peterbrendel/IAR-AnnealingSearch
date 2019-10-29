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

void sorter(vector<byte> * arr, double temp){
    int arrsz = arr->size();
    for(int i=0; i < arrsz; i++){
        (*arr)[i] ^= ((double)rand() / RAND_MAX < temp ? 1 : 0);
    }
}

void alphatemp(double * temp, int iter){
    // cout << 1.0 / (1 + 2 * log(1+iter)) << endl;
    *temp = 1.0 / (1 + 1.47 * log(1+iter));
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
    Simanneal<vector<byte>, vector<Config*>> * annealer = new Simanneal<vector<byte>, vector<Config*>>(0.90, 1000, 100, 100, variables, clauses);

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
    for(int i : ans.second){
        cout << i << " ";
    }cout << endl;
    cout << "K = " << ans.first << endl;
    #endif

    return 0;
}
