#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include "Socket.h"

template <class ServerSocketImpl>
class ServerSocketTemplate {

    ServerSocketImpl impl;

    public:

    /**
     * Constructor.
     *
     * @param port
     *        Port this server socket should be listening to.
     */
    ServerSocketTemplate(unsigned port);

    /**
     * Move constructor.
     */
    ServerSocketTemplate(ServerSocketTemplate&& other);

    /**
     * Destructor.
     */
    ~ServerSocketTemplate();

    /**
     * Opens the server socket.
     */
    void Open();

    /**
     * Closes the server socket.
     */
    void Close();

    /**
     * Start listening on this port for incoming connections.
     */
    void Listen(int maxConnections);

    /**
     * @return
     *          Whether the server socket is ready to accept
     *          a connection or not.
     */
    bool IsReady() const;

    /**
     * Accepts an incoming connection.
     *
     * @return 
     *          Client's socket
     */
    typename ServerSocketImpl::AcceptedSocketType Accept() const;

    /**
     * @return
     *          The port the server socket is listening to.
     *
     */
    unsigned short GetPort() const;

};


template<class ServerSocketImpl>
ServerSocketTemplate<ServerSocketImpl>::ServerSocketTemplate(unsigned port) 
: impl(port) {
}

template<class ServerSocketImpl>
ServerSocketTemplate<ServerSocketImpl>::ServerSocketTemplate(ServerSocketTemplate<ServerSocketImpl>&& other)
: impl(std::move(other.impl)) {
}

template<class ServerSocketImpl>
ServerSocketTemplate<ServerSocketImpl>::~ServerSocketTemplate() {
    Close();
}

template<class ServerSocketImpl>
void ServerSocketTemplate<ServerSocketImpl>::Open() {
    impl.Open();
}

template<class ServerSocketImpl>
void ServerSocketTemplate<ServerSocketImpl>::Close() {
    impl.Close();
}

template<class ServerSocketImpl>
void ServerSocketTemplate<ServerSocketImpl>::Listen(int maxConnections) {
    impl.Listen(maxConnections);
}

template<class ServerSocketImpl>
bool ServerSocketTemplate<ServerSocketImpl>::IsReady() const {
    return impl.IsReady();
}


template<class ServerSocketImpl>
typename ServerSocketImpl::AcceptedSocketType ServerSocketTemplate<ServerSocketImpl>::Accept() const {
    return impl.Accept();
}

template<class ServerSocketImpl>
unsigned short ServerSocketTemplate<ServerSocketImpl>::GetPort() const {
    return impl.GetPort();
}


#if defined __unix__ || (defined (__APPLE__) && defined (__MACH__))
#include "unix/BSDServerSocket.h"
typedef ServerSocketTemplate<BSDServerSocket> ServerSocket;
#endif

#endif 