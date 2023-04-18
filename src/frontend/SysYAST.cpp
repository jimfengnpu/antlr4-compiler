
#include "SysYAST.h"


ParseTree * SysYAST::BuildAST(ParseTree * t) {
    ParseTree* root = t;
    ParseTree * run = t;
    size_t childIndex = 0;
    std::stack<size_t> stack;
    while(childIndex < run->children.size()) {
        ParseTree* child = run->children[childIndex];
        std::cout<< Trees::getNodeText(child, std::vector<std::string>()) << " ";
        if(child->getTreeType() == ParseTreeType::RULE &&
         child->children.size() == 1 &&
         child->children[0]->getTreeType() == ParseTreeType::RULE) {
            child->children[0]->parent = run;
            run->children[childIndex] = child->children[0];
            child = child->children[0];
        }
        if(!child->children.empty()) {
            stack.push(childIndex);
            run = child;
            childIndex = 0;
        }else {
            while( ++childIndex < run->children.size() ) {
                if(stack.size() > 0) {
                    childIndex = stack.top();
                    stack.pop();
                    run = run->parent;
                }else {
                    break;
                }
            }
        }
    }
    return root;
}