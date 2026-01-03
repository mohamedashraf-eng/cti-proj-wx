/** 
 * @file SessionThread.cpp
 * @brief Implementation of the SessionThread class for isolated client execution.
 * @author Mohamed Ashraf
 * @email mohamed.ashraf@coretech-innovations.com
 * @date Jan 2026
 * 
 * This file manages the dedicated thread lifecycle for a single client connection,
 * ensuring that network I/O and message processing for one client do not block 
 * others or the main server thread.
 */

// Qt Depends
// Other
#include "SessionThread.hpp"
#include "network/ClientSession.hpp"
#include "error/error_emitter.hpp"

namespace CTI {
namespace Chat {

/**
 * @brief Constructs a SessionThread object.
 * 
 * Stores the necessary dependencies and the socket handle required to 
 * instantiate the session once the thread starts execution.
 * 
 * @param socketDescriptor The native handle for the TCP connection.
 * @param logic Shared pointer to the central business logic.
 * @param sessions Shared pointer to the session manager.
 * @param parent Optional QObject parent.
 */
SessionThread::SessionThread(qintptr socketDescriptor,
                             std::shared_ptr<ChatServer> logic,
                             std::shared_ptr<SessionManager> sessions,
                             QObject* parent)
    : QThread(parent),
      m_socketDescriptor(socketDescriptor),
      m_logic(logic),
      m_sessions(sessions) {
    EMIT_DEBUG() << "Creating a new session thread.";
}

/**
 * @brief The main execution logic for the dedicated client thread.
 * 
 * This method is called when the thread starts. It performs the following steps:
 * 1. Instantiates the ClientSession on the current thread's stack/heap.
 * 2. Ensures the session's event handling is tied to this thread.
 * 3. Links the session's lifecycle to the thread's execution.
 * 4. Starts the Qt Event Loop.
 */
void SessionThread::run() {
    EMIT_DEBUG() << "Running a session thread.";

    // Step 1: Create the ClientSession instance.
    // Note: It is created here (inside run()) so its constructor runs in this thread.
    ClientSession* session = new ClientSession(
        m_socketDescriptor,
        m_logic,
        m_sessions.get()
    );

    // Step 2: Explicitly move the session object to this thread.
    // This ensures all slots (like onReadyRead) are executed in this worker thread.
    session->moveToThread(this);

    // Step 3: Lifecycle management.
    // When the ClientSession is deleted (via deleteLater in its own onDisconnected slot),
    // it will trigger the thread to exit its event loop.
    connect(session, &QObject::destroyed,
            this, &QThread::quit);
            
    // Step 4: Start the thread's event loop.
    // This blocks until quit() is called.
    exec();
}

} /* namespace Chat */
} /* namespace CTI */