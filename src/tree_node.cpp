#include "tree_node.h"
#include <iostream>
#include <editline/readline.h>
#include "utility.h"

FileDetails::FileDetails(FileDetails& f) {
    this->file_name = f.file_name;
    this->file_type = f.file_type;
}

void FileDetails::writeFile() {
    resetTerminal();
    auto& content = this->file_content;
    std::string str;
    while(str != ":wq") {
        content.push_back(str);
        getline(std::cin, str);
    }
    setRawMode();
}

void FileDetails::displayContent() {
    for(auto& c: file_content)
        std::cout << c << std::endl;
}

void FileDetails::displayTailFile() {
    int start = 0, size = file_content.size();
    if(size > 10) start = size - 10;

    for(int i = start; i < size; i++) {
        std::cout << file_content[i] << std::endl;
    }
}

TreeNode::~TreeNode()
{
    TreeNode* cur = this->child;

    while(cur != NULL)
    {
        TreeNode* tmp = cur;
        cur = cur->next;
        delete tmp;
    }

    next = prev = parent = child = NULL;
    if(file_details) delete file_details;
}

TreeNode::TreeNode(const TreeNode& t) : next(NULL), prev(NULL) {

    FileDetails* cloneFile = new FileDetails(*t.file_details);
    this->file_details = cloneFile;
    this->child = NULL;

    //copy recursive
    TreeNode* cur = t.child, *prevChild = NULL;
    while(cur != NULL) {
        TreeNode* cloneChild = new TreeNode(*cur);
        cloneChild->parent = this;
        if(this->child == NULL) this->child = cloneChild;

        cloneChild->prev = prevChild;
        if(prevChild) prevChild->next = cloneChild;

        prevChild = cloneChild;
        cur = cur->next;
    }
}

void TreeNode::printNode()
{
    TreeNode* cur = this->child;

    while(cur != NULL)
    {
        if(cur->file_details->file_type == FileType::E_DIR)
        {
            std::cout << cur->file_details->file_name << "/ " ;
        }
        else if(cur->file_details->file_type == FileType::E_FILE)
        {
            std::cout << cur->file_details->file_name << " " ;
        }

        cur = cur->next;
    }
}

void TreeNode::printTree(int tabcnt) {
    TreeNode* cur = this->child;
    std::string tab;
    for(int i = 0; i < 2*tabcnt; i++) tab += ' ';
    tab += " |-";
    std::cout << std::endl;
    while(cur != NULL) {
        if(cur->file_details->file_type == FileType::E_DIR) {
            std::cout << tab << cur->file_details->file_name << "/ ";
            cur->printTree(tabcnt+1);
        } else {
            std::cout << tab << cur->file_details->file_name << " " << std::endl;
        }
        cur = cur->next;
    }
    std::cout << std::endl;
}

void TreeNode::appendTree(TreeNode* t)
{
    TreeNode* cur = this->child;
    if(cur == NULL) {
        /*TreeNode* dummyHead = new TreeNode("", FileType::E_DIR, this);
        TreeNode* dummyTail = new TreeNode("", FileType::E_DIR, this);
        dummyHead->next = t;
        t->next = dummyTail;
        dummyTail->prev = t;
        t->prev = dummyHead;
        this->child = dummyHead;*/

        this->child = t;
        t->parent = this;
        return;
    }

    while(cur->next != NULL)
    {
        cur = cur->next;
    }

    cur->next = t;
    t->prev = cur;
    t->parent = this;
}

bool TreeNode::deleteNode(std::string& name)
{
    TreeNode* cur = this->child;

    while(cur != NULL)
    {
        if (cur->file_details->file_name == name)
        {
            if(cur->prev == NULL) { // first element in list
                this->child = cur->next;
                cur->next->prev = NULL;
            } else {
                cur->prev->next = cur->next;
                if(cur->next) cur->next->prev = cur->prev;
            }

            delete cur;
            return true;
        }

        cur = cur->next;
    }
    return false;
}

TreeNode* TreeNode::findNode(std::string& name)
{
    TreeNode* cur = this->child;

    while(cur != NULL)
    {
        if (cur->file_details->file_name == name)
        {
            return cur;
        }
        cur = cur->next;
    }

    return NULL;
}

std::vector<TreeNode*> TreeNode::findPrefixMatchedNode(std::string& prefix) {
    TreeNode* cur = this->child;
    std::vector<TreeNode*> nodes;

    while(cur != NULL)
    {
        if (cur->file_details->file_name.find(prefix) != std::string::npos)
        {
            nodes.push_back(cur);
        }
        cur = cur->next;
    }

    return nodes;
}

void TreeNode::moveNode(TreeNode* src) {

    if(src->prev) {
        src->prev->next = src->next;
        if(src->next) src->next->prev = src->prev;
    } else {
        src->parent->child = src->next;
        src->parent = NULL;
        if(src->next) src->next->prev = NULL;
        src->next = NULL;
    }

    appendTree(src);
}

void TreeNode::copyNode(TreeNode* src) {
    TreeNode* clone = new TreeNode(*src);

    appendTree(clone);
}

TreeNode* TreeNode::getTreeNodeFromPath(std::string& path) {
    if(path.empty()) return this;
    //path = simplifiedPath(path);
    std::vector<std::string> pathVector = split(path, '/');

    TreeNode* cur = this;
    for(auto& filename: pathVector) {
        if(cur == NULL) return NULL;

        if(filename.empty() || filename == ".") {
            continue;
        }
        else if(filename == "..") {
            cur = cur->parent;
        } else {
            cur = cur->findNode(filename);
        }
    }

    return cur;
}

std::string TreeNode::getpwd() {
    TreeNode* cur = this;
    std::stack<std::string> stk;

    while(cur != NULL) {
        stk.push(cur->file_details->file_name);

        cur = cur->parent;
    }
    std::string pwd;
    while(!stk.empty()) {
        pwd += stk.top() + "/";
        stk.pop();
    }

    return pwd;
}


