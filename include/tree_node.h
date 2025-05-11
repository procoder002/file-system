#ifndef TREE_NODE_H
#define TREE_NODE_H
#include <string>
#include <vector>
#include <fstream>

enum class FileType
{
    E_FILE,
    E_DIR,
    E_MAX
};

// add more metadata related to file into this structure
typedef struct FileDetails
{
    std::string      file_name;
    FileType    file_type;
    time_t      creation_date;
    size_t      file_size;

    std::vector<std::string>      file_content;
    FileDetails(std::string name, FileType type): file_name(name), file_type(type) {
    }
    FileDetails(FileDetails& f);

    void writeFile();
    void displayContent();
    void displayTailFile();

} FileDetails ;


typedef struct TreeNode {

    FileDetails*    file_details;
    TreeNode*       next;
    TreeNode*       prev;
    TreeNode*       parent;
    TreeNode*       child;

    TreeNode(FileDetails* f, TreeNode* p): file_details(f), parent(p), next(NULL), prev(NULL), child(NULL) { }
    ~TreeNode();
    TreeNode(const TreeNode& t);

    void printNode();
    void printTree(int tabcnt = 1);
    void appendTree(TreeNode* t);
    bool deleteNode(std::string& name);
    TreeNode* findNode(std::string& name);
    std::vector<TreeNode*> findPrefixMatchedNode(std::string& prefix);
    void moveNode(TreeNode* src);
    void copyNode(TreeNode* src);

    TreeNode* getTreeNodeFromPath(std::string& path);
    std::string getpwd();
} TreeNode;


#endif // TREE_NODE_H