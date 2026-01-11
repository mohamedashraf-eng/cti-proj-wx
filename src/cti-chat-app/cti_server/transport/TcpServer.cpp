/** 
 * @file TcpServer.cpp
 * @brief Implementation of the TcpServer class for handling incoming network connections.
 * @author Mohamed Ashraf
 * @email mohamed.ashraf@coretech-innovations.com
 * @date Jan 2026
 * 
 * This file implements the listener logic that detects new client connections
 * and offloads them to dedicated worker threads.
 */

// Qt Depends

// Other
#include "TcpServer.hpp"
#include "server/SessionManager.hpp"
#include "threading/SessionThread.hpp"
#include "error/error_codes.hpp"
#include "error/error_emitter.hpp"
#include "constants.hpp"

namespace CTI {
namespace Chat {

/**
 * @brief Constructs the TcpServer and initializes core dependencies.
 * 
 * @param logic Shared pointer to the central ChatServer business logic.
 * @param sessions Shared pointer to the SessionManager for client tracking.
 * @param parent Optional QObject parent for the internal Qt tree.
 */
TcpServer::TcpServer(std::shared_ptr<ChatServer> logic,
                     std::shared_ptr<SessionManager> sessions,
                     QObject* parent)
    : QTcpServer(parent),
      m_logic(logic),
      m_sessions(sessions) {
    EMIT_INFO() << "TCP Server initiated.";
}

/**
 * @brief Overridden handler for new native socket connections.
 * 
 * This method is automatically called by the QTcpServer whenever a client 
 * connects. It implements the "Thread-per-Connection" model by:
 * 1. Creating a new SessionThread.
 * 2. Configuring automatic memory cleanup for the thread.
 * 3. Starting the thread execution.
 * 
 * @param socketDescriptor The native platform-dependent socket handle.
 */
void TcpServer::incomingConnection(qintptr socketDescriptor) {
    EMIT_INFO() << "Server recieved incoming connection.";
    
    // Check if the current connected clients are max.
    if(m_sessions->getNumberOfSessions() >= Constants::MAX_CONNECTED_CLIENTS - 1u) {
        EMIT_WARN() << 
            "Failed to add new client. Max connected clients reached.";
        EMIT_WARN() << error_code_to_string(ErrorCode::ERR_CONNECTION_REFUSED);
        return;
    }

    // Step 1: Create a new thread to handle this specific client
    // We pass the socket descriptor and the shared server dependencies.
    auto* thread = new SessionThread(
        socketDescriptor,
        m_logic,
        m_sessions
    );

    // Step 2: Set up automatic cleanup
    // Connect the finished signal to deleteLater to ensure the thread 
    // object is deleted from memory once the client disconnects and the loop ends.
    connect(thread, &QThread::finished, 
            thread, &QObject::deleteLater);

    // Step 3: Launch the thread
    // This calls SessionThread::run() in a new execution context.
    thread->start();
}

} /* namespace Chat */
} /* namespace CTI */