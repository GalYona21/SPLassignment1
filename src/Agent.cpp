//
// Created by spl211 on 03/11/2020.
//

#include "../include/Agent.h"
#include "iostream"

using namespace std;

Agent::Agent() {
}

int ContactTracer::getNode() const {
    return -1;
}



Agent * ContactTracer::clone() const {
    return new ContactTracer(*this);
}

Agent::~Agent(){

}

ContactTracer::ContactTracer() {}

void ContactTracer::act(Session& session) {
    Graph &g = session.getGraph();
    if (!session.isInfectedQueueEmpty()) {
        int infected=session.dequeueInfected();
        Tree* bfs = g.BFS( infected, session);
        int tracedNode = bfs->traceTree();
        int j=0;
        for (size_t i = 0; i < g.getEdges().size(); i++) {
            if (g.getEdges()[tracedNode][j] == 1) {
                g.deleteEdge(tracedNode, j);
            }
            j=j+1;
        }
        delete bfs;
    }
}


Virus::Virus(int nodeInd) : nodeInd(nodeInd){}

Agent * Virus::clone() const {
    return new Virus(*this);
}

int Virus::getNode() const {
    return  nodeInd;
}

void Virus::act(Session& session) {
    Graph& g=session.getGraph();
    vector<vector<int>> edges= g.getEdges();
    bool found=false;
    int i=0;
    if(!g.isInfected(nodeInd)) {
        g.infectNode(nodeInd);
        g.carryNode(nodeInd);
        session.enqueueInfected(nodeInd);
    }
    size_t j=0;
   while(j<edges.size()&&!found){
        if(edges[nodeInd][i]==1&&!g.isInfected(i)&&!g.isCarryNode(i)){
            Virus virus(i);
            session.addAgent(virus);
            found=true;
            g.carryNode(i);
        }
        i=i+1;
        j=j+1;
    }
}


