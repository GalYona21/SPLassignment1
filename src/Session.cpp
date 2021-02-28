//
// Created by spl211 on 03/11/2020.
//

#include "../include/Session.h"
#include "../include/json.hpp"
#include "fstream"
#include "../include/Agent.h"
#include "iostream"

using namespace std;

Session::Session(const std::string &path) : g(),treeType(),agents(),infectedQueue(),cycleNum(){
    ifstream i(path);
    nlohmann::json j;
    i >> j;
    g=Graph(j["graph"]);
    if(j["tree"]=="C") {
        treeType = TreeType::Cycle;
    }
    else if(j["tree"]=="M"){
        treeType=TreeType::MaxRank;
    }
    else{
        treeType=TreeType::Root;
    }
    for(auto& elem: j["agents"]){
        if(elem[0]=="V"){
            addAgent(Virus(elem[1]));
        }
        else{
            addAgent(ContactTracer());
        }
    }
    cycleNum=0;
}

Session::Session(const Session &session) : g(),treeType(),agents(),infectedQueue(),cycleNum() {//copy constructor
    copy(session);
}

Session& Session::operator=(const Session &session) {//copy assignment constructor
    if(this!=&session) {
        clear();
        copy(session);
    }
    return *this;
}

Session::~Session() {//destructor
    int j=0;//declared to avoid using unsigned int as an index
    for(size_t i=0;i<agents.size();i++){
        delete agents[j];
        j=j+1;
    }
    agents.clear();
}

Session::Session(Session&& session) :g(),treeType(),agents(),infectedQueue(),cycleNum() {//move constructor
    copy(session);
    session.clear();
}

Session& Session::operator=(Session&& session) {//move assignment operator
    if(this!=&session){
        clear();
        copy(session);
        session.clear();

    }
    return *this;
}

void Session::clear() {
    int i=0;
    for(size_t j=0;j<agents.size();j++){
        delete agents[i];
        i=i+1;
    }
    agents.clear();
}

void Session::simulate() {
    std::vector<int> infectedVertices;
    bool notFinished=true;
    makeVirusesCarry();
    while(notFinished){
        int agentSize=agents.size();

        for(int i=0;i<agentSize;i++){//every agent call act function by ascending order
            agents[i]->act(*this);
        }
        notFinished=!isTerminationConditionsMet();
        cycleNum=cycleNum+1;
    }
    int i=0;
    for(size_t j=0;j<g.getEdges().size();j++){
        if(g.isInfected(i)){
            infectedVertices.push_back(i);
        }
        i=i+1;
    }
    nlohmann::json j;
    j["infected"]= infectedVertices;
    j["graph"]=g.getEdges();
    ofstream o("./output.json");
    o << j << endl;
}

void Session::copy(const Session& session) {
    treeType = session.treeType;
    int i=0;
    for (size_t j = 0; j < session.agents.size(); j++) {
        agents.push_back(session.agents[i]->clone());
        i=i+1;
    }
    g=Graph(session.g.getEdges());
    infectedQueue = session.infectedQueue;
    cycleNum=session.getCycleNum();
}

void Session::addAgent(const Agent &agent) {
    Agent* copy=agent.clone();
    agents.push_back(copy);
}

int Session::getCycleNum() const {
    return cycleNum;
}

int Session::dequeueInfected() {
    int output=infectedQueue.front();
    infectedQueue.erase(infectedQueue.begin());
    return output;
}
void Session::enqueueInfected(int node) {
    infectedQueue.push_back(node);
}
TreeType Session::getTreeType() const {
    return treeType;
}
bool Session::isInfectedQueueEmpty() {
    return infectedQueue.empty();
}
bool Session::isTerminationConditionsMet() {
    vector<vector<int>> edges=g.getEdges();
    int i=0;
    size_t k=0;
    while(k<edges.size()){
        if(g.isCarryNode(i)){
            int j=0;
            for(size_t a=0;a<edges.size();a++){//check that all i neighbors are infected
                if(edges[i][j]==1&&!(g.isInfected(j))){
                       return false;
                }
                j=j+1;
            }
        }
        i=i+1;
        k=k+1;
    }
    return true;
}

void Session::makeVirusesCarry() {
    int i=0;
    for(size_t j=0;j<agents.size();j++){
        if(agents[i]->getNode()>=0){
            g.carryNode(agents[i]->getNode());
        }
        i=i+1;
    }
}

int Session::getNodesNum() const {
    return g.getEdges().size();
}

Graph& Session::getGraph() {
    return g;
}

void Session::setGraph(const Graph &graph) {
    g=graph;
}