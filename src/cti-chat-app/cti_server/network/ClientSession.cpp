/**
 * @file ClientSession.cpp
 * @brief Implementation of the ClientSession class for handling individual TCP connections.
 * @author Mohamed Ashraf
 * @email mohamed.ashraf@coretech-innovations.com
 * @date Jan 2026
 * 
 * @copyright © 2026 CTI Chat Project. All rights reserved.
 */

#include "ClientSession.hpp"
#include <QUuid>
#include "server/ChatServer.hpp"
#include "server/SessionManager.hpp"
#include "error/error_emitter.hpp"
#include "constants.hpp"

/**
 * @namespace CTI::Chat
 * @brief Root namespace for the CoreTech Innovations Chat Application components.
 */
namespace CTI {
namespace Chat {

/**
 * @brief Constructs a new Client Session object.
 * 
 * This constructor initializes the network socket using the provided descriptor,
 * registers the session within the SessionManager, and establishes signal-slot 
 * connections for asynchronous data handling.
 * 
 * @param socketDescriptor The native socket handle provided by the QTcpServer.
 * @param logic Shared pointer to the ChatServer logic for message processing.
 * @param sessions Pointer to the SessionManager to track active clients.
 * @param parent Optional QObject parent for memory management.
 */
ClientSession::ClientSession(qintptr socketDescriptor,
                             std::shared_ptr<ChatServer> logic,
                             SessionManager* sessions,
                             QObject* parent)
    : QObject(parent),
      m_logic(std::move(logic)),
      m_sessions(sessions) {

    // Step 1: Initialize and configure the TCP Socket
    EMIT_INFO() << "Creating new TCP Scoket for client session.";
    m_socket = new QTcpSocket(this);
    m_socket->setSocketDescriptor(socketDescriptor);
    
    // Step 2: Create a client uuid.
    m_clientInfo = new ClientInfo();
    QUuid id = QUuid::createUuid();
    m_clientInfo->id = id.toString(QUuid::WithoutBraces).toStdString();
    EMIT_INFO() << "Added new client with uuid: " << m_clientInfo->id.c_str();

    // Step 3: Register this session with the manager
    EMIT_DEBUG() << "Adding the session to session manager.";
    m_sessions->add(this);

    // Step 4: Connect socket signals to session slots
    connect(m_socket, &QTcpSocket::readyRead,
            this, &ClientSession::onReadyRead);

    connect(m_socket, &QTcpSocket::disconnected,
            this, &ClientSession::onDisconnected);
}

/**
 * @brief Sends a raw data packet to the connected client.
 * 
 * Appends a delimiter (;) to the end of the byte array to ensure the 
 * client can distinguish between consecutive frames.
 * 
 * @param data The QByteArray containing the message or data to be sent.
 */
void ClientSession::send(const QByteArray& data) {
    // Step 1: Validate socket state
    if (!m_socket || !m_socket->isOpen()) {
        EMIT_DEBUG() << "Invalid socket.";
        return;
    }

    // Step 2: Write data followed by the protocol delimiter
    EMIT_DEBUG() << "Writing to socket.";
    m_socket->write(data);
    m_socket->write(";");
}

/**
 * @brief Processes the internal buffer to extract and handle complete frames.
 * 
 * This method searches for the DELIMITER in the accumulated buffer. If a full
 * frame is found, it is extracted and passed to the ChatServer logic for broadcasting.
 * It continues processing until no more complete frames are found in the buffer.
 */
void ClientSession::processBuffer() {
    EMIT_DEBUG() << "Processing buffer";
    
    while (true) {
        // Step 1: Look for the delimiter index
        int index = m_buffer.indexOf(Constants::DELIMITER);
        if (index < 0) {
            break;
        }

        // Step 2: Extract the frame and remove it (including delimiter) from the buffer
        QByteArray frame = m_buffer.left(index);
        m_buffer.remove(0, index + 1); 

        // Step 3: Pass non-empty frames to the server logic for processing
        if (!frame.isEmpty()) {
            EMIT_DEBUG() << "Processing message in bussiness logic.";
            m_logic->processAndBroadcast(frame, m_clientInfo->id);
        }
    }
}

/**
 * @brief Slot triggered when the socket has new data available to read.
 * 
 * Reads all available bytes from the socket, appends them to the internal 
 * buffer, and triggers the buffer processing logic.
 */
void ClientSession::onReadyRead() {
    EMIT_DEBUG() << "Data ready to read.";
    EMIT_INFO() << "Client[`" << m_clientInfo->id.c_str() << "`] sent message.";
    // Step 1: Read incoming bytes and append to existing buffer
    m_buffer.append(m_socket->readAll());
    
    // Step 2: Attempt to parse frames from the updated buffer
    processBuffer();
}

/**
 * @brief Slot triggered when the client disconnects from the socket.
 * 
 * Handles the cleanup process by removing the session from the manager 
 * and scheduling the deletion of the socket and the session object itself.
 */
void ClientSession::onDisconnected() {
    EMIT_INFO() << "Client`["<< m_clientInfo->id.c_str() << "]` disconnected."; 
    
    // Delete the client info.
    if(m_clientInfo) {
        delete m_clientInfo;
        m_clientInfo = nullptr;
    }

    // Step 1: Unregister from the session manager
    m_sessions->remove(this);
    
    // Step 2: Schedule object deletion to ensure safe cleanup after the event loop
    m_socket->deleteLater();
    deleteLater();
}

} /* namespace Chat */
} /* namespace CTI */