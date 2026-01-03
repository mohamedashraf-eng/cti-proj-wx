/** 
 * @file SessionThread.hpp
 * @brief Definition of the SessionThread class for multi-threaded client handling.
 * @author Mohamed Ashraf
 * @email mohamed.ashraf@coretech-innovations.com
 * @date Jan 2026
 * 
 * This file defines a QThread subclass designed to encapsulate a single 
 * client session, providing concurrency and preventing blocking of the 
 * main server listener.
 */

#ifndef SESSIONTHREAD_HPP
#define SESSIONTHREAD_HPP

// Qt Depends
#include <QThread>
// Other
#include <memory>

namespace CTI {
namespace Chat {

class ChatServer;
class SessionManager;

/**
 * @class SessionThread
 * @brief Manages the execution lifecycle of a ClientSession in a dedicated thread.
 * 
 * SessionThread is responsible for taking a raw socket descriptor and 
 * instantiating a ClientSession within its own event loop. This ensures that 
 * intensive I/O operations or message processing for one client do not 
 * affect the performance of other clients.
 * 
 * @note This class overrides QThread::run() to perform the setup and 
 * enter the event loop.
 */
class SessionThread : public QThread {
    Q_OBJECT
public:
    /**
     * @brief Constructs a SessionThread with necessary server components.
     * 
     * @param socketDescriptor The native handle for the TCP connection.
     * @param logic Shared pointer to the central ChatServer logic.
     * @param sessions Shared pointer to the SessionManager registry.
     * @param parent Optional QObject parent for memory management.
     */
    SessionThread(qintptr socketDescriptor,
                  std::shared_ptr<ChatServer> logic,
                  std::shared_ptr<SessionManager> sessions,
                  QObject* parent = nullptr);

protected:
    /**
     * @brief Entry point for the thread execution.
     * 
     * Overrides the base QThread::run method. This is where the ClientSession 
     * is created and the QEventLoop (exec()) is started.
     */
    void run() override;

private:
    /** @brief The native socket handle passed from the QTcpServer. */
    qintptr m_socketDescriptor;

    /** @brief Reference to the business logic for processing messages. */
    std::shared_ptr<ChatServer> m_logic;

    /** @brief Reference to the manager for tracking active sessions. */
    std::shared_ptr<SessionManager> m_sessions;
};

} /* namespace Chat */
} /* namespace CTI */

#endif /* SESSIONTHREAD_HPP */