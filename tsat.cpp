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

#include "utils/utils.hpp"
#include "heuristics/sa.hpp"

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

    vector<byte> variables(varAmt);
    vector<Config*> clauses(clauseAmt);

    idx = 0;
    while(is.peek() != '%'){
        is >> a >> b >> c;
        is.ignore(numeric_limits<streamsize>::max(), '\n');
        clauses[idx++] = new Config(variables, a, b, c, 0);
    }
    assert(idx == clauseAmt);

#ifdef DEBUG
    int count = 0;
    //Test print ( operator<< )
    for(auto c : clauses){
        cout << *c << endl;
        count += c->evaluate();
    }
    cout << "True = " << count << endl << "False = " << idx - count << endl;

    clauses[0]->Randomsearch();
#endif

    return 0;
}
