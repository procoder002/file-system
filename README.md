# In memory file system

* A custom shell interface to manage file-system
* Desinged using native data structure(tree and linked list)
* Supported basic filesystem operation - help, pwd, ls, cd, touch, mkdir, rm, cp, mv, touch, tree etc.
* Auto completion when tab key pressed
* Simple editor with vi(append only), cat, tail
* Commands can be stored in a file and that file can be used to create entire filesystem instead to firing them individually


## How to Use:

*  Clone the repo.
```sh
git clone https://github.com/procoder002/file-system.git
```
* Generate makefile using cmake
```sh
mkdir build
cd build
cmake ..
```
* Build to generate the binary (shell) and Run
```sh
make
./shell
```
* Now you are inside custom shell, which is denoted by the '*'
```sh
[username*hostname /]#
```
* Type help command for further guidance, '<>' denotes mandatory and '[]' denotes optional paramter
```sh
procoder@ubuntu:~/github$ help
    pwd                     present working directory
    ls      [path]          list file/directory
    tree                    display a directory structure
    cd      <path>          change directory
    touch   <file>          create a file
    mkdir   <dir>           create a directory
    rm      <file/dir>              remove a directory
    mv      <src>    <dst>          move a file/directory
    cp      <src>    <dst>          copy a file/directory
    load    <cmd-file>              load filesystem from a command file input
    vi      <file>          open a file to write (note: write is append only)
    cat     <file>          display a file content
    tail    <file>          display a last 10 line of a file content
    exit                    exit from custom shell

```
  
* Now using these commands to create your own filesystem, play with it. Once done, Press ctrl+c or type 'exit' to exit from this custom shell

### Build Requirement:
* g++ compiler(-std=c++11)
* cmake >= 2.8


### Future Enhancement:
* Recording Command History: an API 'record on' should write all subsequent commands into a file, which can be used to re-run the same scenario(using 'load' API). 'record off' should stop recoding.
* Filesystem Snapshot Creation: an API 'snap' should dump the current filesystem content into a file that can be transferred and entire filesystem should be able to restored from that.

### Reference

* https://www.geeksforgeeks.org/design-data-structures-algorithms-memory-file-system/
* https://leetcode.com/problems/design-file-system/description/
