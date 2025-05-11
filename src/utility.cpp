#include "utility.h"
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * Split a string based on a delimitter and return list of strings
 */
std::vector<std::string> split(std::string& input, char delimiter) {
    size_t pos = 0;
    std::vector<std::string> V;
    std::string str = input;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        std::string token = str.substr(0, pos);
        if(!token.empty())
        {
            V.push_back(token);
        }
        str.erase(0, pos + 1);
    }
    std::string token = str.substr(0, pos);
    V.push_back(token);
    return V;
}


/**
 * Return a substring till the delimitter (prefix)
 */
std::string getPrefix(std::string& input, char delim) {
    if (input.empty()) return input;

    size_t last_slash = input.find_last_of(delim);
    if (last_slash == std::string::npos) return input;
    std::string prefix = input.substr(last_slash+1);
    input.erase(last_slash);
    return prefix;
}

/**
 * transform absolute path into its simplified canonical path.
 */

std::string simplifiedPath(std::string& path) {
    std::vector<std::string> pathVector = split(path, '/');
    std::stack<std::string> stk;

    for(auto& pv:  pathVector) {
        if(pv == "..") {
            if(!stk.empty()) stk.pop();
        } else {
            stk.push(pv);
        }
    }

    std::string simplePath;
    while(!stk.empty()) {
        simplePath = stk.top() + "/" + simplePath;
        stk.pop();
    }
    return "/" + simplePath;
}

/*
* Function to set the terminal to raw mode
*/
void setRawMode()
{
    struct termios newt;
    tcgetattr(STDIN_FILENO, &newt);
    newt.c_lflag &= ~(ICANON | ECHO);  // Disable canonical mode and echo
    newt.c_cc[VMIN] = 1;              // Minimum number of characters to read
    newt.c_cc[VTIME] = 0;             // No timeout
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

/* 
* Function to restore terminal to normal mode
*/
void resetTerminal()
{
    struct termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    oldt.c_lflag |= (ICANON | ECHO);  // Enable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}
