#include "utils.hpp"

class Config {
private:
    cnf clause;
    idarr indexArr;
public:
    Config(vector<byte>&, int, int, int);
    int evaluate();
    string to_string() const;
};

ostream& operator<< (ostream& stream, const Config& obj);
