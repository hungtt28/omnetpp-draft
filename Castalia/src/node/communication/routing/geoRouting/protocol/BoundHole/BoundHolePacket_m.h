//
// Generated file, do not edit! Created by nedtool 4.6 from src/node/communication/routing/geoRouting/protocol/BoundHole/BoundHolePacket.msg.
//

#ifndef _BOUNDHOLEPACKET_M_H_
#define _BOUNDHOLEPACKET_M_H_

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0406
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
#include "GeoControlPacket_m.h"
#include "VirtualMobilityManager.h"

struct Node {
	int nodeId;
	NodeLocation_type nodeLocation;
	
	Node(){};
	Node(int id, NodeLocation_type nodeLocation): nodeId(id), nodeLocation(nodeLocation) {};
};

typedef std::vector<Node> Nodes;
// }}

/**
 * Enum generated from <tt>src/node/communication/routing/geoRouting/protocol/BoundHole/BoundHolePacket.msg:37</tt> by nedtool.
 * <pre>
 * enum BoundHoleMode
 * {
 * 
 *     BOUNDHOLE_SUPPRESSED_START_MODE = 0;
 *     BOUNDHOLE_REFRESH_MODE = 1;
 * }
 * </pre>
 */
enum BoundHoleMode {
    BOUNDHOLE_SUPPRESSED_START_MODE = 0,
    BOUNDHOLE_REFRESH_MODE = 1
};

/**
 * Class generated from <tt>src/node/communication/routing/geoRouting/protocol/BoundHole/BoundHolePacket.msg:42</tt> by nedtool.
 * <pre>
 * packet BoundHolePacket extends GeoControlPacket
 * {
 *     int boundHoleMode = BOUNDHOLE_SUPPRESSED_START_MODE;
 *     int originalId = -1;
 *     int holeId = -1;
 *     bool bForce = false;
 *     int iNode = -1;
 *     Nodes boundHoleNodes;
 * }
 * </pre>
 */
class BoundHolePacket : public ::GeoControlPacket
{
  protected:
    int boundHoleMode_var;
    int originalId_var;
    int holeId_var;
    bool bForce_var;
    int iNode_var;
    Nodes boundHoleNodes_var;

  private:
    void copy(const BoundHolePacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const BoundHolePacket&);

  public:
    BoundHolePacket(const char *name=NULL, int kind=0);
    BoundHolePacket(const BoundHolePacket& other);
    virtual ~BoundHolePacket();
    BoundHolePacket& operator=(const BoundHolePacket& other);
    virtual BoundHolePacket *dup() const {return new BoundHolePacket(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getBoundHoleMode() const;
    virtual void setBoundHoleMode(int boundHoleMode);
    virtual int getOriginalId() const;
    virtual void setOriginalId(int originalId);
    virtual int getHoleId() const;
    virtual void setHoleId(int holeId);
    virtual bool getBForce() const;
    virtual void setBForce(bool bForce);
    virtual int getINode() const;
    virtual void setINode(int iNode);
    virtual Nodes& getBoundHoleNodes();
    virtual const Nodes& getBoundHoleNodes() const {return const_cast<BoundHolePacket*>(this)->getBoundHoleNodes();}
    virtual void setBoundHoleNodes(const Nodes& boundHoleNodes);
};

inline void doPacking(cCommBuffer *b, BoundHolePacket& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, BoundHolePacket& obj) {obj.parsimUnpack(b);}


#endif // ifndef _BOUNDHOLEPACKET_M_H_
