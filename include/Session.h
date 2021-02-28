#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include "Graph.h"

class Agent;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    Session(const std::string& path);
    Session(const Session& session);//copy operator
    Session& operator=(const Session& session);//copy assignment operator
    ~Session();//destructor
    Session(Session&& session);//move operator
    Session& operator=(Session&& session);//move assignment operator

    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);

    void enqueueInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const;

    void copy(const Session& session);
    void clear();
    bool isInfectedQueueEmpty();
    //void addInfectednode();
    int getCycleNum() const;
    int getNodesNum() const;
    void makeVirusesCarry();
    bool isTerminationConditionsMet();
    Graph& getGraph();
private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    std::vector<int> infectedQueue;
    int cycleNum;
};

#endif
