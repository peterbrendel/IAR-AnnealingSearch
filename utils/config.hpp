#include "utils.hpp"
#include "base.hpp"

class Config : public Base {
private:
    cnf clause;
    idarr indexArr;
public:
    Config(vector<byte>&, int, int, int);
    int evaluate();
    string to_string() const;
};

ostream& operator<< (ostream& stream, const Config& obj);
