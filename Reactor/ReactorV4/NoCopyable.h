#ifndef _NOCOPYABLE_H
#define _NOCOPYABLE_H

namespace wxt{
class NoCopyable{
protected:
    NoCopyable(){}
    ~NoCopyable(){}

    NoCopyable(const NoCopyable &)=delete;
    NoCopyable &operator=(const NoCopyable &)=delete;
};
}

#endif

