#ifndef _SOCKETIO_H
#define _SOCKETIO_H

namespace wxt{
class SocketIO{
public:
    SocketIO(int fd);
    ~SocketIO(){}
    int recvn(char *,int);
    int sendn(const char *,int);
    int recvPeek(char * ,int) const;
    int recvLine(char *,int);
private:
    int _fd;
};
}
#endif //!_SOCKETIO_H

