//
// Generated file, do not edit! Created by nedtool 5.1 from GPSR.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __GPSR_M_H
#define __GPSR_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0501
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
#include "Coord.h"
// }}

/**
 * Class generated from <tt>GPSR.msg:21</tt> by nedtool.
 * <pre>
 * message GPSR
 * {
 *     int Mode = 0;				// M
 *     double Dx = 0;               	// D
 *     double Dy = 0;
 *     double Lpx = 0;     			// Lp
 *     double Lpy = 0;
 *     double Lfx = 0;   				// Lf
 *     double Lfy = 0;
 *     int FirstSenderAddress = -1;   	// e0
 *     int FirstReceiverAddress = -1; 	// e0
 * }
 * </pre>
 */
class GPSR : public ::omnetpp::cMessage
{
  protected:
    int Mode;
    double Dx;
    double Dy;
    double Lpx;
    double Lpy;
    double Lfx;
    double Lfy;
    int FirstSenderAddress;
    int FirstReceiverAddress;

  private:
    void copy(const GPSR& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const GPSR&);

  public:
    GPSR(const char *name=nullptr, short kind=0);
    GPSR(const GPSR& other);
    virtual ~GPSR();
    GPSR& operator=(const GPSR& other);
    virtual GPSR *dup() const override {return new GPSR(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getMode() const;
    virtual void setMode(int Mode);
    virtual double getDx() const;
    virtual void setDx(double Dx);
    virtual double getDy() const;
    virtual void setDy(double Dy);
    virtual double getLpx() const;
    virtual void setLpx(double Lpx);
    virtual double getLpy() const;
    virtual void setLpy(double Lpy);
    virtual double getLfx() const;
    virtual void setLfx(double Lfx);
    virtual double getLfy() const;
    virtual void setLfy(double Lfy);
    virtual int getFirstSenderAddress() const;
    virtual void setFirstSenderAddress(int FirstSenderAddress);
    virtual int getFirstReceiverAddress() const;
    virtual void setFirstReceiverAddress(int FirstReceiverAddress);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const GPSR& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, GPSR& obj) {obj.parsimUnpack(b);}


#endif // ifndef __GPSR_M_H

