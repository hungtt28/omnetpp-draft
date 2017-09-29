//
// Generated file, do not edit! Created by nedtool 5.1 from GPSR.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include "GPSR_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(GPSR)

GPSR::GPSR(const char *name, short kind) : ::omnetpp::cMessage(name,kind)
{
    this->Mode = 0;
    this->Dx = 0;
    this->Dy = 0;
    this->Lpx = 0;
    this->Lpy = 0;
    this->Lfx = 0;
    this->Lfy = 0;
    this->FirstSenderAddress = -1;
    this->FirstReceiverAddress = -1;
}

GPSR::GPSR(const GPSR& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

GPSR::~GPSR()
{
}

GPSR& GPSR::operator=(const GPSR& other)
{
    if (this==&other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void GPSR::copy(const GPSR& other)
{
    this->Mode = other.Mode;
    this->Dx = other.Dx;
    this->Dy = other.Dy;
    this->Lpx = other.Lpx;
    this->Lpy = other.Lpy;
    this->Lfx = other.Lfx;
    this->Lfy = other.Lfy;
    this->FirstSenderAddress = other.FirstSenderAddress;
    this->FirstReceiverAddress = other.FirstReceiverAddress;
}

void GPSR::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->Mode);
    doParsimPacking(b,this->Dx);
    doParsimPacking(b,this->Dy);
    doParsimPacking(b,this->Lpx);
    doParsimPacking(b,this->Lpy);
    doParsimPacking(b,this->Lfx);
    doParsimPacking(b,this->Lfy);
    doParsimPacking(b,this->FirstSenderAddress);
    doParsimPacking(b,this->FirstReceiverAddress);
}

void GPSR::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->Mode);
    doParsimUnpacking(b,this->Dx);
    doParsimUnpacking(b,this->Dy);
    doParsimUnpacking(b,this->Lpx);
    doParsimUnpacking(b,this->Lpy);
    doParsimUnpacking(b,this->Lfx);
    doParsimUnpacking(b,this->Lfy);
    doParsimUnpacking(b,this->FirstSenderAddress);
    doParsimUnpacking(b,this->FirstReceiverAddress);
}

int GPSR::getMode() const
{
    return this->Mode;
}

void GPSR::setMode(int Mode)
{
    this->Mode = Mode;
}

double GPSR::getDx() const
{
    return this->Dx;
}

void GPSR::setDx(double Dx)
{
    this->Dx = Dx;
}

double GPSR::getDy() const
{
    return this->Dy;
}

void GPSR::setDy(double Dy)
{
    this->Dy = Dy;
}

double GPSR::getLpx() const
{
    return this->Lpx;
}

void GPSR::setLpx(double Lpx)
{
    this->Lpx = Lpx;
}

double GPSR::getLpy() const
{
    return this->Lpy;
}

void GPSR::setLpy(double Lpy)
{
    this->Lpy = Lpy;
}

double GPSR::getLfx() const
{
    return this->Lfx;
}

void GPSR::setLfx(double Lfx)
{
    this->Lfx = Lfx;
}

double GPSR::getLfy() const
{
    return this->Lfy;
}

void GPSR::setLfy(double Lfy)
{
    this->Lfy = Lfy;
}

int GPSR::getFirstSenderAddress() const
{
    return this->FirstSenderAddress;
}

void GPSR::setFirstSenderAddress(int FirstSenderAddress)
{
    this->FirstSenderAddress = FirstSenderAddress;
}

int GPSR::getFirstReceiverAddress() const
{
    return this->FirstReceiverAddress;
}

void GPSR::setFirstReceiverAddress(int FirstReceiverAddress)
{
    this->FirstReceiverAddress = FirstReceiverAddress;
}

class GPSRDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    GPSRDescriptor();
    virtual ~GPSRDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(GPSRDescriptor)

GPSRDescriptor::GPSRDescriptor() : omnetpp::cClassDescriptor("GPSR", "omnetpp::cMessage")
{
    propertynames = nullptr;
}

GPSRDescriptor::~GPSRDescriptor()
{
    delete[] propertynames;
}

bool GPSRDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GPSR *>(obj)!=nullptr;
}

const char **GPSRDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *GPSRDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int GPSRDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 9+basedesc->getFieldCount() : 9;
}

unsigned int GPSRDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<9) ? fieldTypeFlags[field] : 0;
}

const char *GPSRDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "Mode",
        "Dx",
        "Dy",
        "Lpx",
        "Lpy",
        "Lfx",
        "Lfy",
        "FirstSenderAddress",
        "FirstReceiverAddress",
    };
    return (field>=0 && field<9) ? fieldNames[field] : nullptr;
}

int GPSRDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='M' && strcmp(fieldName, "Mode")==0) return base+0;
    if (fieldName[0]=='D' && strcmp(fieldName, "Dx")==0) return base+1;
    if (fieldName[0]=='D' && strcmp(fieldName, "Dy")==0) return base+2;
    if (fieldName[0]=='L' && strcmp(fieldName, "Lpx")==0) return base+3;
    if (fieldName[0]=='L' && strcmp(fieldName, "Lpy")==0) return base+4;
    if (fieldName[0]=='L' && strcmp(fieldName, "Lfx")==0) return base+5;
    if (fieldName[0]=='L' && strcmp(fieldName, "Lfy")==0) return base+6;
    if (fieldName[0]=='F' && strcmp(fieldName, "FirstSenderAddress")==0) return base+7;
    if (fieldName[0]=='F' && strcmp(fieldName, "FirstReceiverAddress")==0) return base+8;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *GPSRDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "double",
        "double",
        "double",
        "double",
        "double",
        "double",
        "int",
        "int",
    };
    return (field>=0 && field<9) ? fieldTypeStrings[field] : nullptr;
}

const char **GPSRDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *GPSRDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int GPSRDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    GPSR *pp = (GPSR *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *GPSRDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GPSR *pp = (GPSR *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GPSRDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GPSR *pp = (GPSR *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getMode());
        case 1: return double2string(pp->getDx());
        case 2: return double2string(pp->getDy());
        case 3: return double2string(pp->getLpx());
        case 4: return double2string(pp->getLpy());
        case 5: return double2string(pp->getLfx());
        case 6: return double2string(pp->getLfy());
        case 7: return long2string(pp->getFirstSenderAddress());
        case 8: return long2string(pp->getFirstReceiverAddress());
        default: return "";
    }
}

bool GPSRDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    GPSR *pp = (GPSR *)object; (void)pp;
    switch (field) {
        case 0: pp->setMode(string2long(value)); return true;
        case 1: pp->setDx(string2double(value)); return true;
        case 2: pp->setDy(string2double(value)); return true;
        case 3: pp->setLpx(string2double(value)); return true;
        case 4: pp->setLpy(string2double(value)); return true;
        case 5: pp->setLfx(string2double(value)); return true;
        case 6: pp->setLfy(string2double(value)); return true;
        case 7: pp->setFirstSenderAddress(string2long(value)); return true;
        case 8: pp->setFirstReceiverAddress(string2long(value)); return true;
        default: return false;
    }
}

const char *GPSRDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *GPSRDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    GPSR *pp = (GPSR *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


