#ifndef _EVENT_H_
#define _EVENT_H_

class Event
{
private:
    const char* m_Type;

public:
    const char* GetType() const { return m_Type; }

public:
    explicit Event(const char* type):m_Type(type) {};
    virtual ~Event() {};
};

#endif