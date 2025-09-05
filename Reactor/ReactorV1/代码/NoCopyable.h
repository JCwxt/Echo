#ifndef NOCOPYABLE_H
#define NOCOPYABLE_H

namespace wxt{
class NoCopyable{
protected :
    NoCopyable();
    ~NoCopyable();
    NoCopyable(const NoCopyable &)=delete;
    NoCopyable &operator= (const NoCopyable &)=delete;
};
}

#endif

