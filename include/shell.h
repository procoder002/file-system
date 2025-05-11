#ifndef SHELL_H
#define SHELL_H

#include "file_system.h"

struct helpText {
  std::string                 command;
  std::string                 inputs;
  std::string                 description;
};

class Shell
{
  public:
    Shell();

    void startTerminal();

  private:
    void displayCLIPrompt();
    void populateHelpText();
    void readInputFromCLI();
    void readInputFromFile();
    void parserInputCommand();

    void onTabPressed();

    FileSystem     fs;
    std::string    username;
    std::string    hostname;
    
    std::vector<struct helpText> helptext;

    // this is needed when read from file is trigger
    bool              _read_from_file;
    std::string       _input_command;
    std::ifstream     _testfile;
};



#endif // SHELL_H