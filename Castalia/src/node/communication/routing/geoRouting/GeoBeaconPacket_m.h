//
// Generated file, do not edit! Created by nedtool 4.6 from src/node/communication/routing/geoRouting/GeoBeaconPacket.msg.
//

#ifndef _GEOBEACONPACKET_M_H_
#define _GEOBEACONPACKET_M_H_

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0406
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
#include "GeoPacket_m.h"
#include "VirtualMobilityManager.h"
// }}

/**
 * Class generated from <tt>src/node/communication/routing/geoRouting/GeoBeaconPacket.msg:32</tt> by nedtool.
 * <pre>
 * //
 * // The GPSR beacon packet is sent periodically by all GPSR routers to notify
 * // the neighbors about the router's address and position.
 * //
 * packet GeoBeaconPacket extends GeoPacket
 * {
 *     int geoPacketType = GEO_BEACON_PACKET;
 *     NodeLocation_type nodeLocation;
 * }
 * </pre>
 */
class GeoBeaconPacket : public ::GeoPacket
{
  protected:
    int geoPacketType_var;
    NodeLocation_type nodeLocation_var;

  private:
    void copy(const GeoBeaconPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const GeoBeaconPacket&);

  public:
    GeoBeaconPacket(const char *name=NULL, int kind=0);
    GeoBeaconPacket(const GeoBeaconPacket& other);
    virtual ~GeoBeaconPacket();
    GeoBeaconPacket& operator=(const GeoBeaconPacket& other);
    virtual GeoBeaconPacket *dup() const {return new GeoBeaconPacket(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getGeoPacketType() const;
    virtual void setGeoPacketType(int geoPacketType);
    virtual NodeLocation_type& getNodeLocation();
    virtual const NodeLocation_type& getNodeLocation() const {return const_cast<GeoBeaconPacket*>(this)->getNodeLocation();}
    virtual void setNodeLocation(const NodeLocation_type& nodeLocation);
};

inline void doPacking(cCommBuffer *b, GeoBeaconPacket& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, GeoBeaconPacket& obj) {obj.parsimUnpack(b);}


#endif // ifndef _GEOBEACONPACKET_M_H_

