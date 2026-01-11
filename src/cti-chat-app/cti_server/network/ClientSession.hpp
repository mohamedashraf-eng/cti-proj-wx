/** 
 * @file ClientSession.hpp
 * @brief Definition of the ClientSession class for the CTI Chat System.
 * @author Mohamed Ashraf
 * @email mohamed.ashraf@coretech-innovations.com
 * @date Jan 2026
 * 
 * This file contains the declaration of the ClientSession class, which handles
 * the lifecycle of a single TCP client connection.
 */

#ifndef CLIENTSESSION_HPP
#define CLIENTSESSION_HPP

// Qt Depends
#include <QTcpSocket>
// Other
#include "core/IClientSession.hpp"
#include "domain/ClientInfo.hpp"
#include <memory>
#include <vector>

namespace CTI {
/**
 * @namespace CTI::Chat
 * @brief Contains the core communication and server logic for the chat application.
 */
namespace Chat {

class ChatServer;
class SessionManager;

/**
 * @class ClientSession
 * @brief Handles individual client connections, data reception, and transmission.
 * 
 * ClientSession implements the IClientSession interface and inherits from QObject
 * to utilize the Qt Signal/Slot mechanism. It manages its own QTcpSocket and
 * handles incoming stream fragmentation using a delimiter-based protocol.
 * 
 * @note This class is marked as 'final' to prevent further inheritance.
 */
class ClientSession final : public QObject, public IClientSession {
    Q_OBJECT
public:
    /**
     * @brief Constructs a ClientSession with a specific socket descriptor.
     * 
     * @param socketDescriptor The native handle for the incoming connection.
     * @param logic Shared pointer to the central server logic for processing messages.
     * @param sessions Pointer to the manager responsible for tracking all active sessions.
     * @param parent Optional QObject parent (defaults to nullptr).
     */
    explicit ClientSession(qintptr socketDescriptor,
                           std::shared_ptr<ChatServer> logic,
                           SessionManager* sessions,
                           QObject* parent = nullptr);

    /**
     * @brief Sends a data packet to the connected client.
     * 
     * Implements the IClientSession interface. This method appends the 
     * protocol delimiter automatically.
     * 
     * @param data The byte array to be transmitted.
     */
    void send(const QByteArray& data) override;
    
    /** @brief Returns the current clientInfo */
    const ClientInfo* getClientInfo() override {
        return m_clientInfo;
    }

private slots:
    /**
     * @brief Triggered when the underlying QTcpSocket has data available.
     */
    void onReadyRead();

    /**
     * @brief Triggered when the client connection is closed.
     * 
     * Handles self-cleanup and unregistration from the SessionManager.
     */
    void onDisconnected();
    
private:
    /**
     * @brief Internal helper to parse the raw buffer into discrete messages.
     * 
     * Scans for the ';' delimiter and forwards complete packets to the logic layer.
     */
    void processBuffer();

    /** @brief The actual network socket for this client. */
    QTcpSocket* m_socket;

    /** @brief Internal storage for incoming data fragments. */
    QByteArray m_buffer;

    /** @brief Reference to the business logic layer. */
    std::shared_ptr<ChatServer> m_logic;

    /** @brief Reference to the session registry. */
    SessionManager* m_sessions;

    /** @brief Client information. */        
    ClientInfo* m_clientInfo;
};

} /* namespace Chat */
} /* namespace CTI */

#endif /* CLIENTSESSION_HPP */