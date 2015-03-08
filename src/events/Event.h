#ifndef _EVENT_H_
#define _EVENT_H_

class Event
{
public:
    explicit Event(const char* type):m_Type(type) {}
    virtual ~Event() {}

    const char* GetType() const { return m_Type; }

private:
    const char* m_Type;
};

#endif