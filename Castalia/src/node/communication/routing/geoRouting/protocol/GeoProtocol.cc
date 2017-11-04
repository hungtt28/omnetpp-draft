/*
 * WSN Geographic Routing base on Castialia/Omnetpp
 *
 *  Created on: Nov 3, 2017
 *      Author: hungtt28
 */

#include "GeoProtocol.h"
#include "GeoRouting.h"

std::tuple<int, GeoRoutingPacket*> GeoProtocol::findNextHop(GeoRouting *routing, GeoRoutingPacket* pkt) {
	
	GeoRoutingPacket *dataPacket = pkt->dup();
	NodeLocation_type desLocation = dataPacket->getDestinationLocation();
	
	int nextHop = -1;
	double dist = -1;
	double minDist = distance(routing->getCurLocation(), desLocation);
	
	NeighborTable *neighborTable = routing->getNeighborTable();
	for (int i = 0; i < neighborTable->size(); i++) {
		NeighborRecord *neighborRecord = neighborTable->getRecord(i);
		dist = distance(neighborRecord->getLocation(), desLocation);
		if (dist < minDist) {
			minDist = dist;
			nextHop = neighborRecord->getId();
		}
	}
	return std::make_tuple(nextHop, dataPacket);
}


GeoRoutingPacket* GeoProtocol::createGeoRoutingPacket(GeoRouting *routing) {
	return new GeoRoutingPacket("GEO routing data packet", NETWORK_LAYER_PACKET);
}