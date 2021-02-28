//
// Created by spl211 on 03/11/2020.
//

#include "../include/Session.h"
#include "../include/Tree.h"
#include "iostream"

using namespace std;

Tree::Tree(int rootLabel) : node(rootLabel), children(){
}
Tree& Tree::operator=(const Tree &other) {//copy  assignment operator
    if(&other!=this){
        clear();
        copy(other);
    }
    return *this;
}

Tree::Tree(const Tree &t) : node(t.node), children(t.children) {//copy constructor
    copy(t);
}

Tree::~Tree() {//destructor
    clear();
}

Tree::Tree( Tree&& t) : node(),children(){//move constructor
    //if(this!=&t){
        copy(t);
        t.clear();
    //}
}

Tree& Tree::operator=(Tree &&other) {//move assignment operator
    if(&other!=this){
        clear();
        copy(other);
        other.clear();
    }
    return *this;
}

void Tree::copy(const Tree& t) {
    node=t.node;
    int i=0;
    for(size_t j=0;j<t.children.size();j++){
        children.push_back(t.children[i]->clone());
        i=i+1;
    }
}

void Tree::clear() {
    int size=children.size();
    for (int i = 0; i <size; i++) {
        delete children[i];
    }
    children.clear();
}





Tree * Tree::createTree(const Session &session, int rootLabel) {
    Tree* tree;
    int treeTypeNum=session.getTreeType();
    if(treeTypeNum==0) {
        tree = new CycleTree(rootLabel, session.getCycleNum());
    }
    else if(treeTypeNum==1){
        tree = new MaxRankTree(rootLabel);
    }
    else{
        tree = new RootTree(rootLabel);
    }

    return tree;

}



void Tree::addChild(const Tree &child) {
Tree* c=child.clone();
children.push_back(c);
}

void Tree::addChild(Tree *child) {
    children.push_back(child);
}

int Tree::getRoot() {
    return node;
}

std::vector<Tree *> Tree::getChildren() {
    return children;
}

bool Tree::hasChildren() {
    if(children.empty()){
        return false;
    }
    return true;
}

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {}

int MaxRankTree::traceTree() {
    size_t maxChildren=0;
    int output=getRoot();
    Tree* temp;
    vector<Tree*> childrenTemp;
    vector<Tree*> q;
    q.push_back(this);
    while(!q.empty()){
        temp=q.front();
        q.erase(q.begin());
        if(temp->hasChildren()) {
            childrenTemp = temp->getChildren();
            int i=0;
            for (size_t j = 0; j < childrenTemp.size(); j++) {
                q.push_back(childrenTemp[i]);
                i=i+1;
            }
        }
        if(childrenTemp.size() > maxChildren){
            maxChildren=childrenTemp.size();
            output=temp->getRoot();
        }
    }
    return output;
}

Tree * MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}

RootTree::RootTree(int rootLabel) : Tree(rootLabel) {}

Tree * RootTree::clone() const {
    return new RootTree(*this);
}

int RootTree::traceTree() {
    return Tree::getRoot();
}

CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle){}

int CycleTree::traceTree() {
    Tree* child(this);
    int i=0;
    while(i<currCycle&&(*child).hasChildren()){
        child=child->getChildren().front();
        i=i+1;
    }
    return (*child).getRoot();
}

Tree * CycleTree::clone() const {
    return new CycleTree(*this);
}


