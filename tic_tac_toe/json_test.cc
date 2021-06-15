#include <cstdio>
// #include <stringstream>
#include "json/json.h"

int main() {

    Json::Value root;

    root["x"] = 100;
    root["y"] = "Hundred";
    
    std::stringstream ss;
    ss << root;

    printf("%s\n", ss.str().c_str());
    return 0;

}