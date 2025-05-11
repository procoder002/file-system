#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include "tree_node.h"
#include <unistd.h>

class FileSystem
{
  public:
    FileSystem();

    // name should be filename only not url
    void createFile(std::string& name);
    void createDir(std::string& name);
    void deleteDir(std::string& name);
    void moveDir(std::string& srcPath, std::string& dstPath);
    void copyDir(std::string& srcPath, std::string& dstPath);

    void writeIntoFile(std::string& name);
    void displayFileContent(std::string& name);
    void displayTailFile(std::string& name);

    void displayTree();

    void displayPWD();
    std::string getpwd() { return pwd; }

    void displayDir(std::string& path);
    void changeDir(std::string& path);

    std::vector<TreeNode*> findPrefixMatchedNode(std::string& prefix) { return curr->findPrefixMatchedNode(prefix); }

  private:
    TreeNode* getTreePtr(std::string& path);
    bool validatePath(std::string& srcPath, std::string& dstPath, std::pair<TreeNode*, TreeNode*>& ptr);

    TreeNode* root;
    TreeNode* curr;
    TreeNode* last_visited_node;
    std::string    pwd;
};

#endif // FILE_SYSTEM_H