/** 
 * @file SessionManager.hpp
 * @brief Definition of the SessionManager class for managing active chat sessions.
 * @author Mohamed Ashraf
 * @email mohamed.ashraf@coretech-innovations.com
 * @date Jan 2026
 * 
 * This file defines the registry for all active client connections, providing
 * thread-safe methods to manage the session lifecycle and facilitate broadcasting.
 */

#ifndef SESSIONMANAGER_HPP
#define SESSIONMANAGER_HPP

// Qt Depends
#include <QVector>
#include <QMutex>
#include <QMetaObject>
#include <QByteArray>
// Other
#include "core/IClientSession.hpp"

namespace CTI {
namespace Chat {

class IClientSession;
class ClientInfo;

/**
 * @class SessionManager
 * @brief A thread-safe registry for managing multiple client sessions.
 * 
 * The SessionManager maintains a list of all currently connected clients. 
 * Since client connections and disconnections can occur on different threads 
 * (asynchronous socket handling), this class uses a mutex to ensure that the 
 * internal session list remains consistent during concurrent access.
 */
class SessionManager {
public:
    /**
     * @brief Adds a new session to the registry.
     * 
     * This method is thread-safe and should be called whenever a new 
     * ClientSession is instantiated.
     * 
     * @param session Pointer to the session interface to be registered.
     */
    void add(IClientSession* session);

    /**
     * @brief Removes a session from the registry.
     * 
     * This method is thread-safe and should be called when a client 
     * disconnects to prevent the manager from holding dangling pointers.
     * 
     * @param session Pointer to the session interface to be removed.
     */
    void remove(IClientSession* session);

    /**
     * @brief Sends data to all currently registered sessions.
     * 
     * Iterates through the session list and calls the send method on each.
     * A lock is held during the entire duration of the broadcast to ensure 
     * no sessions are added or removed while sending.
     * 
     * @param data The data packet to be transmitted to every client.
     */
    void broadcast(const QByteArray& data, const std::string& clientId);

    /**
     * @brief Returns the current active sessions.
     *
     */
    uint16_t getNumberOfSessions() {
        return m_sessions.length();
    }

private:
    /** 
     * @brief Mutex to synchronize access to the sessions container. 
     * Ensures that add/remove/broadcast operations do not overlap.
     */
    QMutex m_mutex;

    /** 
     * @brief Internal list of registered client session interfaces. 
     * Used for iterating during broadcasts.
     */
    QVector<IClientSession*> m_sessions;
};

} /* namespace Chat */
} /* namespace CTI */

#endif /* SESSIONMANAGER_HPP */