#ifndef SOCKET_H
#define SOCKET_H

#include <array>
#include <chrono>

template<class SocketImpl>
class SocketTemplate  {

    SocketImpl impl;

    public:

    /**
     * Move constructor.
     */
    SocketTemplate(SocketTemplate&& other);

    /**
     * Constructor.
     */
    template<class... Args>
    SocketTemplate(Args&&... args);

    /**
     * Opens the socket.
     */
    void Open();

    /**
     * Closes the socket.
     */
    void Close();

    /**
     * Sends data over the socket.
     *
     * @param buffer
     *        Array containing the data to send.
     */
    template<size_t n>
    void Send(const std::array<char, n>& buffer, size_t toSend = n) const;
 
    /** 
     * Receives data on the socket.
     *
     * @param buffer
     *        Data is stored in this parameter.s
     */
    template<size_t n>
    size_t Receive(std::array<char, n>& buffer, size_t readSize = n) const;

    /**
     * Sets the receive timeout for this socket.
     *
     * @param seconds
     *        Amount of seconds to set as timeout.
     */
    void SetReceiveTimeout(unsigned seconds);

    /**
     * Set most seconds to wait when sending using this socket.
     *
     * @param seconds
     *        Timeout in seconds.
     */
    void SetSendTimeout(unsigned seconds);
};

template<class SocketImpl>
template<class... Args>
SocketTemplate<SocketImpl>::SocketTemplate(Args&&... args)
: impl(std::forward<Args>(args)...) {
}

template<class SocketImpl>
SocketTemplate<SocketImpl>::SocketTemplate(SocketTemplate<SocketImpl>&& other)
: impl(std::move(other.impl)) {
}

template<class SocketImpl>
void SocketTemplate<SocketImpl>::Open() {
    impl.Open();
}

template <class SocketImpl>
void SocketTemplate<SocketImpl>::Close() {
    impl.Close();
}

template<class SocketImpl>
template<size_t n>
void SocketTemplate<SocketImpl>::Send(const std::array<char, n>& buffer, size_t toSend) const {
    impl.Send(buffer, toSend);
}

template<class SocketImpl>
template<size_t n>
size_t SocketTemplate<SocketImpl>::Receive(std::array<char, n>& buffer, size_t readSize) const {
    return impl.Receive(buffer, readSize);
}

template<class SocketImpl>
void SocketTemplate<SocketImpl>::SetReceiveTimeout(unsigned seconds)
{
    impl.SetReceiveTimeout(seconds);
}

template<class SocketImpl>
void SocketTemplate<SocketImpl>::SetSendTimeout(unsigned seconds)
{
    impl.SetSendTimeout(seconds);
}

#if defined __unix__ || (defined (__APPLE__) && defined (__MACH__))
#include "unix/BSDSocket.h"
typedef SocketTemplate<BSDSocket> Socket;
#endif

#endif 