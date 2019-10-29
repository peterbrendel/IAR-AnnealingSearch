#include "utils.hpp"
#include "config.hpp"

Config::Config(vector<byte>& var, int a, int b, int c) {
    pair<byte*, byte> varA, varB, varC;
    varA = make_pair(&var[abs(a)-1], (int)(a<0));
    varB = make_pair(&var[abs(b)-1], (int)(b<0));
    varC = make_pair(&var[abs(c)-1], (int)(c<0));
    this->clause = make_tuple(varA,varB,varC);
    this->indexArr = make_tuple( abs(a)-1, abs(b)-1, abs(c)-1 );
}

int Config::evaluate() {
    var a, b, c;
    a = std::get<0>(this->clause);
    b = std::get<1>(this->clause);
    c = std::get<2>(this->clause);
    return (*a.first ^ a.second) |
           (*b.first ^ b.second) |
           (*c.first ^ c.second) ;
}

string Config::to_string() const {
    var a, b, c;
    int ida, idb, idc;
    int ba, bb, bc;
    char na, nb, nc;

    a   = std::get<0>(this->clause);
    b   = std::get<1>(this->clause);
    c   = std::get<2>(this->clause);
    ida = std::get<0>(this->indexArr);
    idb = std::get<1>(this->indexArr);
    idc = std::get<2>(this->indexArr);
    na  = a.second ? '~' : ' ';
    nb  = b.second ? '~' : ' ';
    nc  = c.second ? '~' : ' ';
    ba  = (*a.first ^ a.second);
    bb  = (*b.first ^ b.second);
    bc  = (*c.first ^ c.second);
    int sum =   (*a.first ^ a.second) |
    (*b.first ^ b.second) |
    (*c.first ^ c.second) ;

    ostringstream out;
    out << "(" << na << setw(2) << ida << ", " << nb << setw(2) << idb << ", " << nc << setw(2) << idc << ") = (" << ba << ", " << bb << ", " << bc << ") = " << sum;
    //cout << "(" << na << ida << ", " << nb << idb << ", " << nc << idc << ") = (" << ba << ", " << bb << ", " << bc << ")";
    return out.str();

}

ostream& operator<< (ostream& stream, const Config& obj){
    return stream << obj.to_string();
}
