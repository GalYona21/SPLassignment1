//
// Created by spl211 on 03/11/2020.
//
using namespace std;
#include "../include/Graph.h"
#include "../include/Tree.h"
#include "../include/Session.h"
#include "iostream"


Graph::Graph(std::vector<std::vector<int>> matrix) : edges(matrix),infectedNodes(),carryNodes() {//constructor
    for(size_t j=0;j<edges.size();j++){
        infectedNodes.push_back(false);
        carryNodes.push_back(false);
    }
}

Graph::Graph() : edges(),infectedNodes(),carryNodes() {

}

std::vector<std::vector<int>> Graph::getEdges() const {
    return edges;
}

void Graph::deleteEdge(const int& a, const int& b ) {
    edges[a][b]=0;
    edges[b][a]=0;
}

void Graph::infectNode(int nodeInd) {
    size_t a=nodeInd;
    if(a<infectedNodes.size()){
        infectedNodes[nodeInd]=true;
    }
}
bool Graph::isInfected(int nodeInd) {
    size_t a=nodeInd;
    if (a<infectedNodes.size())
        return infectedNodes[nodeInd];
    return false;
}

void Graph::carryNode(int nodeInd) {
    carryNodes[nodeInd]=true;
}

bool Graph::isCarryNode(int nodeInd) {
    size_t a=nodeInd;
    if(a<carryNodes.size()){
        return carryNodes[nodeInd];
    }
    return false;
}

Tree* Graph::BFS(const int& rootNode, const Session& session) {
    vector<Tree*> q;
    vector<bool> visited;
    Tree* BFStree=Tree::createTree(session ,rootNode);
    for(int i=0;i<session.getNodesNum();i++){//verify that all values in visited are false
        visited.push_back(false);
    }
    visited[rootNode]=true;
    Tree* temp;
    Tree* tempChild;
    q.push_back(BFStree);
    while(!q.empty()){
        temp=q.front();
        q.erase(q.begin());
        int i=0;
        for(size_t j=0;j<edges.size();j++){
            if(edges[temp->getRoot()][i]==1&&visited[i]==false){
                tempChild=Tree::createTree(session, i);
                q.push_back(tempChild);
                temp->addChild(tempChild);//enter *
                visited[i]=true;
            }
            i=i+1;
        }
    }

    return BFStree;
}

