/** 
 * @file SessionManager.cpp
 * @brief Implementation of the SessionManager class for client registry management.
 * @author Mohamed Ashraf
 * @email mohamed.ashraf@coretech-innovations.com
 * @date Jan 2026
 * 
 * This file handles the thread-safe storage and management of active client sessions,
 * allowing for safe addition, removal, and mass broadcasting of messages.
 */

// Qt Depends
#include <QMetaObject>
#include <QByteArray>
// Other
#include "SessionManager.hpp"
#include "error/error_emitter.hpp"
#include <algorithm>

namespace CTI {
namespace Chat {

/**
 * @brief Registers a new client session in the manager.
 * 
 * This method is thread-safe. It uses a QMutexLocker to prevent race conditions
 * when multiple clients attempt to connect or disconnect simultaneously.
 * 
 * @param session Pointer to the IClientSession instance to be added.
 */
void SessionManager::add(IClientSession* session) {
    // Step 1: Acquire lock to ensure thread-safe access to the sessions container
    QMutexLocker lock(&m_mutex);
    
    EMIT_DEBUG() << "Adding session.";
    
    // Step 2: Store the session pointer in the internal list
    m_sessions.push_back(session);
}

/**
 * @brief Removes and unregisters a client session.
 * 
 * Uses the erase-remove idiom to efficiently locate and remove the session 
 * pointer from the internal vector while maintaining thread safety.
 * 
 * @param session Pointer to the IClientSession instance to be removed.
 */
void SessionManager::remove(IClientSession* session) {
    // Step 1: Acquire lock to ensure thread-safe modification of the container
    QMutexLocker lock(&m_mutex);
    
    EMIT_DEBUG() << "Removing session.";
    
    // Step 2: Locate and remove the specific pointer using std::remove
    // remove takes start -> end and searches for element and delete it.
    // [A, B, X, C, X] -> [A, B, C, -, -] / and retruns pointer (iterator)
    // to the first deleted element.
    // erase takes start and end and erases a range.
    // erase[first delete element, end]
    // O(n)
    m_sessions.erase(
        std::remove(m_sessions.begin(), m_sessions.end(), session),
        m_sessions.end()
    );
}

/**
 * @brief Distributes a data packet to all currently registered sessions.
 * 
 * Iterates through the list of active sessions and triggers their send mechanism.
 * The method maintains a lock on the container throughout the iteration to 
 * prevent modification by other threads during the broadcast.
 * 
 * @param data The QByteArray containing the message to broadcast.
 */
void SessionManager::broadcast(const QByteArray& data, const std::string& clientId) {
    // Step 1: Acquire lock to protect the container during iteration
    QMutexLocker lock(&m_mutex);
    
    EMIT_DEBUG() << "Boradcasting to client: [`" << clientId.c_str() << "`].";
    
    // Step 2: Iterate through all active sessions
    for (auto* session : m_sessions) {
        if(session->getClientInfo()->id != clientId) {
            continue;
        }
        // Step 3: Send data to the individual session
        // session->send(data);
        
        /** 
         * @note Thread-Safe Alternative:
         * If the send method needs to be executed on the session's own thread,
         * QMetaObject::invokeMethod can be used with Qt::QueuedConnection.
         */
        /** @note This is a work around.
         * @todo Enhnace the method invoking.
         */
        QObject* obj = dynamic_cast<QObject*>(session);
        if (obj) {
            // QMetaObject::invokeMethod(obj, "send", Qt::QueuedConnection, Q_ARG(QByteArray, data));
            QMetaObject::invokeMethod(obj, [session, data]() {
                session->send(data);
            }, Qt::QueuedConnection);
        }
    }
}

} /* namespace Chat */
} /* namespace CTI */