/** 
 * @file IClientSession.hpp
 * @brief Definition of the IClientSession interface.
 * @author Mohamed Ashraf
 * @email mohamed.ashraf@coretech-innovations.com
 * @date Jan 2026
 * 
 * This file defines the abstract interface for client sessions, ensuring a 
 * decoupled communication bridge between the server logic and the network layer.
 */

#ifndef ICLIENTSESSION_HPP
#define ICLIENTSESSION_HPP

// Qt Depends
#include <QByteArray>

// Other
#include <vector>
#include "domain/ClientInfo.hpp"

namespace CTI {
namespace Chat {

class ClientInfo;

/**
 * @class IClientSession
 * @brief Abstract interface representing a single client connection.
 * 
 * IClientSession defines the mandatory behavior for any class handling a 
 * client connection. By using this interface, the SessionManager and 
 * ChatServer can interact with clients without being coupled to specific 
 * implementation details (like QTcpSocket or encryption wrappers).
 */
class IClientSession {
public:
    /**
     * @brief Virtual destructor to ensure proper cleanup of derived objects.
     */
    virtual ~IClientSession() = default;

    /**
     * @brief Sends data to the client.
     * 
     * This is a pure virtual function. Implementation classes must provide 
     * the logic to transmit the provided byte array through the established 
     * communication channel.
     * 
     * @param data The raw byte array to be sent to the client.
     */
    virtual void send(const QByteArray& data) = 0;
    
    /** @brief Returns the current clientInfo */
    virtual const ClientInfo* getClientInfo() = 0;
private:
    ClientInfo* clientInfo;
};

} /* namespace Chat */
} /* namespace CTI */

#endif /* ICLIENTSESSION_HPP */