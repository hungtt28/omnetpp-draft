/*
 * Test1.cc
 *
 *  Created on: Aug 18, 2017
 *      Author: Admin
 */
#include <string.h>
#include <omnetpp.h>
#include "Hello_m.h"
#include <vector>
using namespace omnetpp;

class Test1: public cSimpleModule {
protected:
    bool chkStuck = false;
    int iNext = -1;
    // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};
// The module class needs to be registered with OMNeT++
Define_Module(Test1);

void Test1::initialize() {

    const char *str = par("neighbor_str").stringValue();
    std::vector<int> neighbor = cStringTokenizer(str).asIntVector();;

//    int i = 0;
//    int j = 0;
    double x = par("x").doubleValue();
    double y = par("y").doubleValue();
    double minDis = par("dis").doubleValue();
    double range = this->getParentModule()->par("range");

    bool flag = false;

    //find neighbor

    int n = this->getParentModule()->par("n");

    //set connection
    //gate.out->neighbor.in, neighbor.out->gate.in
    int baseId_out = this->gateBaseId("out");
    setGateSize("out", neighbor.size());
    setGateSize("in", neighbor.size());
    cModule *Next;

    for (unsigned int j = 0; j < neighbor.size(); j++) {
        cModule *temp = this->getParentModule()->getSubmodule("node", neighbor.at(j));

        cGate *gate = this->gate(baseId_out + j);
        cGate *gModule = temp->getOrCreateFirstUnconnectedGate("in", 'i', false, true);
        gate->connectTo(gModule);

        if (minDis >= temp->par("dis").doubleValue()) {
            flag = true;
            minDis = temp->par("dis").doubleValue();
            Next = temp;
        }
    }

    if (flag == false)
        chkStuck = true;
    for (int i = 0; i < this->gateSize("out"); i++) {
        if (this->gate("out", i)->pathContains(Next, -1) == true)
            iNext = i;
    }

    Hello *msg1 = new Hello();
    Hello *msg2 = msg1->dup();
    if (par("Source").boolValue() == true) {
        scheduleAt(0.0, msg2);
    }
}
void Test1::handleMessage(cMessage *msg) {

    if (par("Dest").boolValue() == true)
        EV << "Complete." << endl;
    else {
        if (chkStuck == true) {
            EV << "Stuck Node" << endl;

        } else
            send(msg, "out", iNext);

    }

}
