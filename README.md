# In memory file system

A custom shell interface to manage file-system
Desinged using native data structure(tree and linked list)
Supported basic filesystem operation ls, cd, mkdir, rm, cp, mv, touch, tree
Auto completion when tab key pressed
Simple editor with vi(append only), cat, tail
Commands can be stored in a file and that file can be used to create entire filesystem instead to firing 
commands individually


How to Use:
Clone the repo.

mkdir build
cd build
cmake ..

make 
(It will create a binary 'shell')

./shell

(This '*' denotes you are inside the custom shell)
[username*hostname /]#

Type help command for further guidance, create your own filesystem
Press ctrl+c to exit from this custom shell

Build Requirement:
g++ compiler(-std=c++11)
cmake >= 2.8.12


Future Enhancement:
Recording command history
Filesystem Snapshot creation
