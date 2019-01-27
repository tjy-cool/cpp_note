#ifndef __CLINK_H
#define __CLINK_H

#include <iostream>

struct LinkNode{
    int _data;
    LinkNode *_next;
    LinkNode(const int& data)
    :_data(data)
    ,_next(NULL)
    {}
};

class CLink
{
public:
    CLink();
    ~CLink();

    void PushBack(const int& data);
    void PopBack();
    LinkNode * FindNode(const int& data);
    bool Delete(int data);
    void Destroy();
private:
    LinkNode *pHead;
};

#endif