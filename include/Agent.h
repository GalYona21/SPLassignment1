#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "Session.h"

class Agent{
public:
    Agent();

    virtual Agent* clone() const=0;
    virtual ~Agent()=0;
    virtual void act(Session& session)=0;
    virtual int getNode() const=0;//added by us
};

class ContactTracer: public Agent{
public:
    ContactTracer();

    virtual Agent* clone() const;
    virtual void act(Session& session);
    virtual int getNode() const;//added by us
};


class Virus: public Agent{
public:
    Virus(int nodeInd);

    virtual int getNode() const;//added by us
    virtual Agent* clone() const;
    virtual void act(Session& session);
private:
    const int nodeInd;
};

#endif
