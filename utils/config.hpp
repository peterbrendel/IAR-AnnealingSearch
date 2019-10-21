#pragma once
#include "../heuristics/sa.hpp"

class Config : Simanneal<int> {
private:
    cnf clause;
    idarr indexArr;
public:
    Config(vector<byte>&, int, int, int, int);
    int evaluate();
    string to_string() const;
};
