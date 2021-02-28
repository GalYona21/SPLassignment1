#ifndef TREE_H_
#define TREE_H_

#include <vector>

class Session;

class Tree{
public:
    Tree(int rootLabel);//constructor
    Tree& operator=(const Tree& t);//copy assignment operator
    virtual ~Tree();//destructor
    Tree& operator=(Tree&& t);//move assignment operator
    Tree(const Tree& t);//copy constructor
    Tree(Tree&& t);//move constructor
    void copy(const Tree& t);
    void clear();
    void addChild(const Tree& child);
    void addChild(Tree* child);//added by gal
    bool hasChildren();//added by gal
    virtual Tree* clone() const=0;



    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;
    int getRoot();//added by gal
    std::vector<Tree*> getChildren();

private:
    int node;
    std::vector<Tree*> children;
};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual int traceTree();
    virtual Tree* clone() const;
private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual int traceTree();
    virtual Tree* clone() const;
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual int traceTree();
    virtual Tree* clone() const;
};

#endif
