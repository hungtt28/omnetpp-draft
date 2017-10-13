/*
 * Test1.cc
 *
 *  Created on: Aug 18, 2017
 *      Author: Admin
 */
#include <string.h>
#include <omnetpp.h>
#include "GPSR_m.h"
#include "Coord.h"
#include <vector>

using namespace omnetpp;

enum GPSRForwardingMode {
    GPSR_GREEDY_ROUTING,
    GPSR_PERIMETER_ROUTING
};

enum GPSRPlanarizationMode {
    GPSR_GG_PLANARIZATION,
    GPSR_RNG_PLANARIZATION
};

#define determinant(a1, a2, b1, b2) (a1 * b2 - a2 * b1)

class Test1: public cSimpleModule {
protected:
	int curId = -1;
	std::vector<int> neighbor;
	std::vector<Coord*> neighbor_pos;
	Coord *curPos = new Coord(0, 0);
	int planarizationMode = 0;
    // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
	
	Coord* getNeighborPosition(int neighborAddress);
	int findNextHop(GPSR *msg);
	int findGreedyRoutingNextHop(GPSR *msg);
	int findPerimeterRoutingNextHop(GPSR *msg);
	double getVectorAngle(Coord *vector);
	double getNeighborAngle(Coord *neighborPos);
	std::vector<int> getPlanarNeighbors();
	int getNextPlanarNeighborCounterClockwise(const int startNeighborAddress, double startNeighborAngle);
	bool intersectSections(Coord *begin1, Coord *end1, Coord *begin2, Coord *end2);
};

// The module class needs to be registered with OMNeT++
Define_Module(Test1);

void Test1::initialize() {

    const char *str = par("neighbor_str").stringValue();
    neighbor = cStringTokenizer(str).asIntVector();;
	curPos->x = par("x").doubleValue();
	curPos->y = par("y").doubleValue();
	curId = par("id").longValue();
	planarizationMode = (GPSRPlanarizationMode)(int)par("planarizationMode");

    // double x = par("x").doubleValue();
    // double y = par("y").doubleValue();
    // double minDis = par("dis").doubleValue();
    // double range = this->getParentModule()->par("range");
	
    //set connection gate.out->neighbor.in
    int baseId_out = this->gateBaseId("out");
    setGateSize("out", neighbor.size());
    setGateSize("in", neighbor.size());

    for (unsigned int j = 0; j < neighbor.size(); j++) {
        cModule *temp = this->getParentModule()->getSubmodule("node", neighbor.at(j));
		
		neighbor_pos.push_back(new Coord(temp->par("x").doubleValue(), temp->par("y").doubleValue()));
		
        cGate *gate = this->gate(baseId_out + j);
        cGate *gModule = temp->getOrCreateFirstUnconnectedGate("in", 'i', false, true);
        gate->connectTo(gModule);
    }

    if (curId == 0) {
		GPSR *msg = new GPSR();
		msg->setMode(GPSR_GREEDY_ROUTING);
		msg->setDx(this->getParentModule()->par("xD"));
		msg->setDy(this->getParentModule()->par("yD"));
        scheduleAt(simTime(), msg);
    }
}

void Test1::handleMessage(cMessage *msg) {
	GPSR *gpsrMsg = check_and_cast<GPSR *>(msg);
    if (par("Dest").boolValue() == true)
        EV << "Complete." << endl;
    else {
		int nextHop = findNextHop(gpsrMsg);
		if (nextHop == -1)
			EV << "Drop message!" << endl;
		else {
			int iNext = -1;
			for (int i = 0; i < this->gateSize("out"); i++) {
				if (this->gate("out", i)->pathContains(this->getParentModule()->getSubmodule("node", nextHop), -1) == true) {
					iNext = i;
				}
			}
			if (iNext == -1)
				EV << "No found neighbor: " << nextHop << endl;
			else
				send(gpsrMsg, "out", iNext);
		}
    }
}

Coord* Test1::getNeighborPosition(int neighborAddress) {
	for (unsigned int i = 0; i < neighbor.size(); i++) {
		if (neighborAddress == neighbor.at(i)) {
			return neighbor_pos.at(i);
		}
	}
	return new Coord(0, 0);
}

int Test1::findNextHop(GPSR *msg) {
    switch (msg->getMode()) {
        case GPSR_GREEDY_ROUTING: return findGreedyRoutingNextHop(msg);
        case GPSR_PERIMETER_ROUTING: return findPerimeterRoutingNextHop(msg);
        default: throw cRuntimeError("Unknown routing mode");
    }
}

int Test1::findGreedyRoutingNextHop(GPSR *msg) {
	Coord* desPos = new Coord(msg->getDx(), msg->getDy());
	double minDis = curPos->distance(desPos);
	int bestNeighbor = -1;
	bool flag = false;
	// greedy
	for (unsigned int j = 0; j < neighbor.size(); j++) {
		Coord *neighborPos = neighbor_pos.at(j);
		double distNeighborToDes = neighborPos->distance(desPos);
		if (minDis >= distNeighborToDes) {
			flag = true;
			minDis = distNeighborToDes;
			bestNeighbor = neighbor.at(j);
		}
	}
	// if perimeter
	if (flag == false) {
		msg->setMode(GPSR_PERIMETER_ROUTING);
		msg->setLpx(curPos->x);
		msg->setLpy(curPos->y);
		msg->setFirstSenderAddress(curId);
		msg->setFirstReceiverAddress(-1);
		msg->setSenderAddress(-1);
		bestNeighbor = findPerimeterRoutingNextHop(msg);
		// return -1;
	}
	return bestNeighbor;
}

int Test1::findPerimeterRoutingNextHop(GPSR *msg) {
	Coord* desPos = new Coord(msg->getDx(), msg->getDy());
	double curDis = curPos->distance(desPos);
	Coord* beginPerimeterPos = new Coord(msg->getLpx(), msg->getLpy());
	double minDis = beginPerimeterPos->distance(desPos);
	int bestNeighbor = -1;
	if (curDis < minDis) {
		msg->setMode(GPSR_GREEDY_ROUTING);
		msg->setLpx(0);
		msg->setLpy(0);
		msg->setLfx(0);
		msg->setLfy(0);		
		bestNeighbor = findGreedyRoutingNextHop(msg);
	}
	else {
        int firstSender = msg->getFirstSenderAddress();
        int firstReceiver = msg->getFirstReceiverAddress();
        bool hasIntersection;
		bestNeighbor = msg->getSenderAddress();
        do {
            if (bestNeighbor == -1)
                bestNeighbor = getNextPlanarNeighborCounterClockwise(bestNeighbor, getNeighborAngle(desPos));
            else
                bestNeighbor = getNextPlanarNeighborCounterClockwise(bestNeighbor, getNeighborAngle(getNeighborPosition(bestNeighbor)));
            if (bestNeighbor == -1)
                break;
            Coord* bestNeighborPos = getNeighborPosition(bestNeighbor);
            hasIntersection = intersectSections(beginPerimeterPos, desPos, curPos, bestNeighborPos);
            if (hasIntersection) {
                msg->setFirstSenderAddress(curId);
                msg->setFirstReceiverAddress(-1);
            }
        } while (hasIntersection);
        if (firstSender == curId && firstReceiver == bestNeighbor) {
            bestNeighbor = -1;
        }
        else {
            if (msg->getFirstReceiverAddress() == -1)
                msg->setFirstReceiverAddress(bestNeighbor);
        }
	}
	msg->setSenderAddress(curId);
	return bestNeighbor;
}

//
// angle
//

double Test1::getVectorAngle(Coord *vector)
{
    double angle = atan2(-vector->y, vector->x);
    if (angle < 0)
        angle += 2 * M_PI;
    return angle;
}

double Test1::getNeighborAngle(Coord *neighborPos)
{
	Coord *vector = new Coord(neighborPos->x - curPos->x, neighborPos->y - curPos->y);
    return getVectorAngle(vector);
}

std::vector<int> Test1::getPlanarNeighbors()
{
    std::vector<int> planarNeighbors;
	for (unsigned int i = 0; i < neighbor.size(); i++) {
		Coord *neighborPos = neighbor_pos.at(i);
		if (planarizationMode == GPSR_RNG_PLANARIZATION) {
			double neighborDis = curPos->distance(neighborPos);
			for (unsigned int j = 0; j < neighbor.size(); j++) {
				if (i == j)
					continue;
				Coord *witnessPos = neighbor_pos.at(j);
				if (neighborDis > witnessPos->distance(curPos) && neighborDis > witnessPos->distance(neighborPos))
					goto eliminate;
			}
		}
		else if (planarizationMode == GPSR_GG_PLANARIZATION) {
			Coord *middlePos = new Coord((curPos->x + neighborPos->x) / 2, (curPos->y + neighborPos->y) / 2);
			double neighborDis = neighborPos->distance(middlePos);
			for (unsigned int j = 0; j < neighbor.size(); j++) {
				if (i == j)
					continue;
				Coord *witnessPos = neighbor_pos.at(j);
				if (neighborDis > witnessPos->distance(middlePos))
					goto eliminate;
			}
		}
        else
            throw cRuntimeError("Unknown planarization mode");
        planarNeighbors.push_back(neighbor.at(i));
      eliminate:;
    }
	return planarNeighbors;
}

int Test1::getNextPlanarNeighborCounterClockwise(const int startNeighborAddress, double startNeighborAngle)
{
    int bestNeighbor = startNeighborAddress;
    double bestNeighborAngleDifference = 2 * M_PI;
    std::vector<int> planarNeighbors = getPlanarNeighbors();
    for (auto & neighborAddress : planarNeighbors) {
		Coord *neighborPos = getNeighborPosition(neighborAddress);
        double neighborAngle = getNeighborAngle(neighborPos);
        double neighborAngleDifference = neighborAngle - startNeighborAngle;
        if (neighborAngleDifference < 0)
            neighborAngleDifference += 2 * M_PI;
        if (neighborAngleDifference != 0 && neighborAngleDifference < bestNeighborAngleDifference) {
            bestNeighborAngleDifference = neighborAngleDifference;
            bestNeighbor = neighborAddress;
        }
    }
    return bestNeighbor;
}

bool Test1::intersectSections(Coord *begin1, Coord *end1, Coord *begin2, Coord *end2)
{
    double x1 = begin1->x;
    double y1 = begin1->y;
    double x2 = end1->x;
    double y2 = end1->y;
    double x3 = begin2->x;
    double y3 = begin2->y;
    double x4 = end2->x;
    double y4 = end2->y;
    double a = determinant(x1, y1, x2, y2);
    double b = determinant(x3, y3, x4, y4);
    double c = determinant(x1 - x2, y1 - y2, x3 - x4, y3 - y4);
    double x = determinant(a, x1 - x2, b, x3 - x4) / c;
    double y = determinant(a, y1 - y2, b, y3 - y4) / c;
    if (x1 < x && x < x2 && x3 < x && x < x4 && y1 < y && y < y2 && y3 < y && y < y4)
        return true;
    else
        return false;
}
