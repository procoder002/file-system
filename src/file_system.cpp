#include "file_system.h"
#include <iostream>
#include "utility.h"

FileSystem::FileSystem() {
    FileDetails* fileinfo = new FileDetails("", FileType::E_DIR);
    root = new TreeNode(fileinfo, NULL);

    curr = root;
    last_visited_node = curr;

    pwd = "/";
}

void FileSystem::displayPWD()
{
    std::cout << pwd << std::endl;
}


void FileSystem::displayDir(std::string& path)
{
    if(path.empty())
    {
        curr->printNode();
    }
    else
    {
        TreeNode* node = getTreePtr(path);
        if(node) node->printNode();
        else std::cout << "FileSystem: " << path << " No such file or directory";
    }

    std::cout << std::endl;
}

TreeNode* FileSystem::getTreePtr(std::string& path) {

    TreeNode* ptr = path[0] == '/' ? root: curr;

    return ptr->getTreeNodeFromPath(path);
}

void FileSystem::createFile(std::string& name)
{
    FileDetails* fileinfo = new FileDetails(name, FileType::E_FILE);
    TreeNode* t = new TreeNode(fileinfo, curr);

    curr->appendTree(t);
}

void FileSystem::createDir(std::string& name)
{
    FileDetails* fileinfo = new FileDetails(name, FileType::E_DIR);
    TreeNode* t = new TreeNode(fileinfo, curr);

    curr->appendTree(t);
}

void FileSystem::deleteDir(std::string& name)
{
    if(curr->deleteNode(name) == false) {
        std::cout << "shell: " << name << " No such file or directory" << std::endl;
    }
}

bool FileSystem::validatePath(std::string& srcPath, std::string& dstPath, std::pair<TreeNode*, TreeNode*>& ptr) {
    if(srcPath.empty() || dstPath.empty()) {
        std::cout << "shell: src/dst path can't be empty" << std::endl;
        return false;
    }

    TreeNode* srcptr = getTreePtr(srcPath);
    if(srcptr == NULL) {
        std::cout << "shell: " << srcPath << " No such file or directory" << std::endl;
        return false;
    }
    TreeNode* dstptr = getTreePtr(dstPath);
    if(dstptr == NULL) {
        std::cout << "shell: " << dstPath << " No such file or directory" << std::endl;
        return false;
    }

    ptr.first = srcptr;
    ptr.second = dstptr;

    return true;
}

void FileSystem::moveDir(std::string& srcPath, std::string& dstPath) {
    std::pair<TreeNode*, TreeNode*> ptr;
    if(!validatePath(srcPath, dstPath, ptr)) return;
    ptr.second->moveNode(ptr.first);
}

void FileSystem::copyDir(std::string& srcPath, std::string& dstPath) {
    std::pair<TreeNode*, TreeNode*> ptr;
    if(!validatePath(srcPath, dstPath, ptr)) return;
    ptr.second->copyNode(ptr.first);
}

void FileSystem::changeDir(std::string& path)
{
    if(path == "/")
    {
        last_visited_node = curr;
        curr = root;
        pwd = "/";
        return;
    }
    else if (path == "-") {
        std::swap(curr, last_visited_node);
        pwd = curr->getpwd();
        return;
    }

    TreeNode* tmp = getTreePtr(path);
    if(tmp != NULL)
    {
        pwd = tmp->getpwd();
        last_visited_node = curr;
        curr = tmp;
    } else {
        std::cout << "shell: cd " << path << " : No such file or directory" << std::endl;
    }
}

void FileSystem::writeIntoFile(std::string& name) {
    TreeNode* ptr = curr->findNode(name);
    if(ptr == NULL) {
        std::cout << "shell: vi " << name << " : No such file or directory" << std::endl;
        return;
    }
    ptr->file_details->writeFile();
}

void FileSystem::displayFileContent(std::string& name) {
    TreeNode* ptr = curr->findNode(name);
    if(ptr == NULL) {
        std::cout << "shell: cat " << name << " : No such file or directory" << std::endl;
        return;
    }
    ptr->file_details->displayContent();
}

void FileSystem::displayTailFile(std::string& name) {
     TreeNode* ptr = curr->findNode(name);
    if(ptr == NULL) {
        std::cout << "shell: cat " << name << " : No such file or directory" << std::endl;
        return;
    }
    ptr->file_details->displayTailFile();
}

void FileSystem::displayTree() {
    curr->printTree();
}
