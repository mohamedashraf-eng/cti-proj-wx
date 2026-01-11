/** 
 * @file TcpServer.hpp
 * @brief Definition of the TcpServer class, the entry point for network connections.
 * @author Mohamed Ashraf
 * @email mohamed.ashraf@coretech-innovations.com
 * @date Jan 2026
 * 
 * This file defines the server listener that accepts incoming TCP connections
 * and orchestrates the creation of threaded client sessions.
 */

#ifndef TCPSERVER_HPP
#define TCPSERVER_HPP

// Qt Depends
#include <QTcpServer>
// Other
#include <memory>

namespace CTI {
namespace Chat {

class ChatServer;
class SessionManager;

/**
 * @class TcpServer
 * @brief A multi-threaded TCP server implementation for the chat system.
 * 
 * TcpServer extends QTcpServer to override the connection handling mechanism.
 * Instead of processing data in the main thread, it acts as a dispatcher that
 * wraps every new socket descriptor into a SessionThread, ensuring high
 * responsiveness and scalability.
 */
class TcpServer : public QTcpServer {
    Q_OBJECT
public:
    /**
     * @brief Constructs the TcpServer with shared application components.
     * 
     * @param logic Shared pointer to the business logic (parsing/handling).
     * @param sessions Shared pointer to the thread-safe session registry.
     * @param parent Optional QObject parent for the Qt object hierarchy.
     */
    TcpServer(std::shared_ptr<ChatServer> logic,
              std::shared_ptr<SessionManager> sessions,
              QObject* parent = nullptr);

protected:
    /**
     * @brief Reimplementation of the low-level connection handler.
     * 
     * This method is triggered by the Qt event loop whenever a new client 
     * connects. It receives the raw socket descriptor and delegates it to 
     * a worker thread.
     * 
     * @param socketDescriptor The platform-specific handle for the new connection.
     */
    void incomingConnection(qintptr socketDescriptor) override;

private:
    /** @brief Shared reference to the core message processing logic. */
    std::shared_ptr<ChatServer> m_logic;

    /** @brief Shared reference to the central connection registry. */
    std::shared_ptr<SessionManager> m_sessions;
};

} /* namespace Chat */
} /* namespace CTI */

#endif /* TCPSERVER_HPP */