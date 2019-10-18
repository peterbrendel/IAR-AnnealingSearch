#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef unsigned char byte;
typedef pair<byte*, byte> var;
typedef tuple<var,var,var> cnf;
typedef tuple<byte,byte,byte> idarr;

#include "config.hpp"

ostream& operator<< (ostream& stream, const Config& obj);
