#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include "Tree.h"

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);
    Graph();

    /*Graph(const Graph& g);//copy constuctor
    virtual ~Graph();//destructor
    Graph& operator=(const Graph& g);//copy assignment operator
    Graph(Graph& g);//move operator
    Graph& operator=(Graph& g);//move assignment operator
     */
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    Tree* BFS(const int& rootNode, const Session& session);//added by gal

    void carryNode(int nodeInd);
    bool isCarryNode(int nodeInd);
    std::vector<std::vector<int>> getEdges() const;//added by gal
    void deleteEdge(const int& a, const int& b);
private:
    std::vector<std::vector<int>> edges;
    std::vector<bool> infectedNodes;
    std::vector<bool> carryNodes;

};

#endif
