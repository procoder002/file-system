#include "shell.h"
#include "utility.h"
#include <iostream>

Shell::Shell() {
    char user[64];
    getlogin_r(user, sizeof(user));
    username = user;

    char host[64];
    if( gethostname(host, sizeof(host)) == 0 )
    {
        hostname = host;
    }

    _read_from_file = false;
    populateHelpText();
}

void Shell::displayCLIPrompt()
{
    std::cout << "[" << username << "*" << hostname << " " << fs.getpwd() << "]" << "#" ;
}

void Shell::onTabPressed()
{
    std::string prefix = getPrefix(_input_command, ' ');
    std::vector<TreeNode*> nodes = fs.findPrefixMatchedNode(prefix);
    if(nodes.empty()) {
        if(nodes.empty()) return;
    };

    if(nodes.size() == 1) {
      std::string& file = nodes[0]->file_details->file_name;
      _input_command += ' ' + file;
      for(int i = prefix.length(); i < file.length(); i++) {
        std::cout << file[i];
      }
      return;
    }
    std::cout << std::endl;
    for(auto& node: nodes) {
        std::cout << node->file_details->file_name << " ";
    }
}

void Shell::readInputFromCLI() {
    while(true) {
        char ch = getchar();

        if(ch == '\n') {
            std::cout << std::endl;
            break;
        } else if(ch == 127) 
        {
            if(!_input_command.empty()) _input_command.pop_back();
            std::cout << "\b \b"; // Move the cursor back, print space to erase character, and move back again
        } else if(ch == '\t') 
        {
            onTabPressed(); //autocomplete
        } else {
            _input_command += ch;
            std::cout << ch;
        }
    }
    // getline(cin, input);
}

void Shell::readInputFromFile() {

    getline(_testfile, _input_command);
    std::cout << " >> " << _input_command << std::endl;
    if(_input_command.empty())
    {
        _read_from_file = false;
        _testfile.close();
        return;
    }
}

void Shell::startTerminal() {
    setRawMode();

    while (true)
    {
        displayCLIPrompt();

        _input_command.clear();

        if(_read_from_file) {
            readInputFromFile();
        } else {
            readInputFromCLI();
        }
        if(_input_command.empty()) continue;

        parserInputCommand();

        usleep(5000);
    }
}

void Shell::populateHelpText()
{
    helptext.push_back({"pwd", "", "present working directory"});
    helptext.push_back({"ls", "[path]", "list file/directory"});
    helptext.push_back({"tree", "", "display a directory structure"});
    helptext.push_back({"cd", "<path>", "change directory"});
    helptext.push_back({"touch", "<file>", "create a file"});
    helptext.push_back({"mkdir", "<dir>", "create a directory"});
    helptext.push_back({"rm", "<file/dir>", "remove a directory"});
    helptext.push_back({"mv", "<src>    <dst>", "move a file/directory"});
    helptext.push_back({"cp", "<src>    <dst>", "copy a file/directory"});
    helptext.push_back({"load", "<cmd-file>", "load filesystem from a command file input"});
    helptext.push_back({"vi", "<file>", "open a file to write (note: write is append only)"});
    helptext.push_back({"cat", "<file>", "display a file content"});
    helptext.push_back({"tail", "<file>", "display a last 10 line of a file content"});
    helptext.push_back({"exit", "", "exit from custom shell"});
}

void Shell::parserInputCommand() {

    std::vector<std::string>  cmd_vec = split(_input_command, ' ');

    if(cmd_vec[0] == "help")
    {
        for(auto& h: helptext) {
            std::cout << '\t' << h.command;
            std::cout << '\t' << h.inputs;
            std::cout << "\t\t" << h.description;
            std::cout << '\n';
        }
        std::cout << std::endl;
    }
    else if(cmd_vec[0] == "ls")
    {
        if(cmd_vec.size() > 2)
        {
            std::cout << "USAGE: ls [path]" << std::endl;
            return;
        }

        if(cmd_vec.size() == 2)
        {
            fs.displayDir(cmd_vec[1]);
        }
        else
        {
            std::string cmd = "";
            fs.displayDir(cmd);

        }
    }

    else if(cmd_vec[0] == "cd")
    {
        if(cmd_vec.size() != 2)
        {
            std::cout << "USAGE: cd <path>" << std::endl;
            return;
        }

        fs.changeDir(cmd_vec[1]);
    }

    else if(cmd_vec[0] == "pwd")
    {
        fs.displayPWD();
    }

    else if(cmd_vec[0] == "touch")
    {
        if(cmd_vec.size() != 2)
        {
            std::cout << "USAGE: touch <filename>" << std::endl;
            return;
        }

        fs.createFile(cmd_vec[1]);
    }

    else if(cmd_vec[0] == "mkdir")
    {
        if(cmd_vec.size() != 2)
        {
            std::cout << "USAGE: mkdir <dirname>" << std::endl;
            return;
        }

        fs.createDir(cmd_vec[1]);
    }

    else if(cmd_vec[0] == "rm")
    {
        if(cmd_vec.size() != 2)
        {
            std::cout << "USAGE: rm <filename>/<dir name>" << std::endl;
            return;
        }

        fs.deleteDir(cmd_vec[1]);
    }

    else if(cmd_vec[0] == "mv")
    {
        if(cmd_vec.size() != 3)
        {
            std::cout << "USAGE: mv <src> <dst>" << std::endl;
            return;
        }

        fs.moveDir(cmd_vec[1], cmd_vec[2]);
    }

    else if(cmd_vec[0] == "cp")
    {
        if(cmd_vec.size() != 3)
        {
            std::cout << "USAGE: cp <src> <dst>" << std::endl;
            return;
        }

        fs.copyDir(cmd_vec[1], cmd_vec[2]);
    }

    else if(cmd_vec[0] == "vi")
    {
        if(cmd_vec.size() != 2)
        {
            std::cout << "USAGE: vi <file>" << std::endl;
            return;
        }

        fs.writeIntoFile(cmd_vec[1]);
    }

    else if(cmd_vec[0] == "cat")
    {
        if(cmd_vec.size() != 2)
        {
            std::cout << "USAGE: cat <file>" << std::endl;
            return;
        }

        fs.displayFileContent(cmd_vec[1]);
    }

    else if(cmd_vec[0] == "tail")
    {
        if(cmd_vec.size() != 2)
        {
            std::cout << "USAGE: tail <file>" << std::endl;
            return;
        }

        fs.displayTailFile(cmd_vec[1]);
    }
    else if(cmd_vec[0] == "tree")
    {
        fs.displayTree();
    }
    //TODO: undo/redo

    else if(cmd_vec[0] == "load")
    {
        if(cmd_vec.size() != 2)
        {
            std::cout << "USAGE: load <filename>" << std::endl;
            return;
        }

        // file handling
        try {
            _testfile.open(cmd_vec[1].c_str());
            _read_from_file = true;
        } catch(const std::exception& e) {
            std::cout << "Unable to open file " << cmd_vec[1] << std::endl;
        }

    }

    else if(cmd_vec[0] == "exit")
    {
        std::cout << "Bye, visit again :)" << std::endl;
        resetTerminal();
        exit(0);
    }
    else
    {
        std::cout << "shell: " << cmd_vec[0] << " command not found..." << std::endl;
    }

}