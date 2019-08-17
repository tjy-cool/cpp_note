#ifndef _NONCOPYABLE_H_
#define _NONCOPYABLE_H_

class NonCopyable
{
public:
    NonCopyable(){ };
    ~NonCopyable(){ };
private:
    NonCopyable(const NonCopyable&);        // no copy
    void operator=(const NonCopyable&);     // no assignment
};

#endif /* NONCOPYABLE_H_ */