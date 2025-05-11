#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>
#include <stack>

extern std::vector<std::string> split(std::string& input, char delimiter);
extern std::string getPrefix(std::string& input, char delim);
extern std::string simplifiedPath(std::string& path);


extern void setRawMode();
extern void resetTerminal();
#endif // UTILITY_H