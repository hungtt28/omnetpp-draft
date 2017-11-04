/*
 * WSN Geographic Routing base on Castialia/Omnetpp
 *
 *  Created on: Nov 3, 2017
 *      Author: hungtt28
 */
 
#ifndef _GEOPROTOCOL_H_
#define _GEOPROTOCOL_H_

#include <tuple>
#include "NeighborTable.h"
#include "GeoHelper.h"
#include "VirtualMobilityManager.h"
#include "GeoRoutingPacket_m.h"

using namespace std;

class GeoRouting;

class GeoProtocol {
		
	public:
		virtual std::tuple<int, GeoRoutingPacket*> findNextHop(GeoRouting *routing, GeoRoutingPacket* pkt);
		virtual GeoRoutingPacket* createGeoRoutingPacket(GeoRouting *routing);
		virtual void setProtocolMode(string protocolMode) {};
};

#endif