#ifndef _SOCKETIO_H
#define _SOCKETIO_H

namespace wxt{
class SocketIO{
public:
    SocketIO(int fd);
    int recvn(char *,int);
    int sendn(const char *,int);
    int recvLine(char *,int);
    int recvPeek(char *,int);
private:
    int _fd;
};
}

#endif

