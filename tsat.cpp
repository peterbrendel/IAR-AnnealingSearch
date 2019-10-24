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
        clauses[idx++] = new Config(variables, a, b, c);
    }
    assert(idx == clauseAmt);

    Simanneal<vector<byte>> * annealer = new Simanneal<vector<byte>>();

#ifdef DEBUG
    int count = 0;
    //Test print ( operator<< )
    for(auto c : clauses){
        cout << *c << endl;
        count += c->evaluate();
    }
    cout << "True = " << count << endl << "False = " << idx - count << endl;
    cout << "Annealer type: " << annealer->getType() << endl;
#endif

    return 0;
}
