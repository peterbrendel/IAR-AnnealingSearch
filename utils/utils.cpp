#include "utils.hpp"

ostream& operator<< (ostream& stream, const Config& obj){
    return stream << obj.to_string();
}
