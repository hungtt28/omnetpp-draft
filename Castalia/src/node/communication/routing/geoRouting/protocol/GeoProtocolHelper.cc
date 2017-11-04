/*
 * WSN Geographic Routing base on Castialia/Omnetpp
 *
 *  Created on: Nov 3, 2017
 *      Author: hungtt28
 */

#include "GeoProtocolHelper.h"

GeoProtocol *getGeoProtocol(string protocolType, string protocolMode) {
	if (protocolType.compare(_GPSR_) == 0) {
		GPSR* gpsr = new GPSR();
		gpsr->setProtocolMode(protocolMode);
		return gpsr;
	}
	else {
		return new GeoProtocol();
	}
}