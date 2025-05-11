#include <iostream>
#include <signal.h>
#include "shell.h"
#include "utility.h"

void signal_handler(int signal)
{
    std::cout << "Bye, visit again :) " << std::endl;
    resetTerminal();
    exit(1);
}

int main() {

    // add more signals to handle
    signal(SIGINT, signal_handler);
    
    std::cout << "\nWelcome to custom shell interface to manage file-system\n" << std::endl;
    
    Shell shell;
    shell.startTerminal();

    return 0;
}
