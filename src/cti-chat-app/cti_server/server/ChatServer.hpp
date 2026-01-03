/** 
 * @file ChatServer.hpp
 * @brief Definition of the ChatServer class, the central engine of the application.
 * @author Mohamed Ashraf
 * @email mohamed.ashraf@coretech-innovations.com
 * @date Jan 2026
 * 
 * This class orchestrates the message lifecycle by coordinating between parsing,
 * security validation, business logic, and broadcasting.
 */

#ifndef CHATSERVER_HPP
#define CHATSERVER_HPP

// Qt Depends
#include <QByteArray>
#include <memory>
#include <string>

// Other
#include "core/IMessageHandler.hpp"
#include "core/IMessageParser.hpp"
#include "security/ISecurityPolicy.hpp"
#include "server/SessionManager.hpp"

namespace CTI {
namespace Chat {

/**
 * @class ChatServer
 * @brief The central coordinator for message processing and distribution.
 * 
 * ChatServer acts as a mediator. It delegates specific tasks to injected 
 * components (Parser, Handler, Security) and uses the SessionManager to 
 * distribute the results.
 */
class ChatServer {
public:
    /**
     * @brief Constructs the ChatServer with its functional dependencies.
     * 
     * @param parser Logic for converting between raw bytes and Message objects.
     * @param handler Logic for executing commands contained within messages.
     * @param security Policy engine for validating incoming messages.
     * @param session Registry and distributor for all active client connections.
     */
    ChatServer(std::shared_ptr<IMessageParser> parser,
               std::shared_ptr<IMessageHandler> handler,
               std::shared_ptr<ISecurityPolicy> security,
               std::shared_ptr<SessionManager> session);

    /**
     * @brief High-level entry point to process incoming data from any client.
     * 
     * Orchestrates the internal pipeline: Parse -> Validate -> Handle -> Serialize -> Broadcast.
     * 
     * @param data The raw byte array received from the network.
     */
    void processAndBroadcast(const QByteArray& data, const std::string& clientId);

private:
    /**
     * @brief Internal method to run the message through the parsing and logic pipeline.
     * @param data Raw byte array.
     * @return QByteArray Serialized result message.
     */
    QByteArray process(const QByteArray& data, const std::string& clientId);

    /**
     * @brief Internal method to distribute data to all connected clients.
     * @param data The serialized byte array to broadcast.
     */
    void broadcast(const QByteArray& data, const std::string& clientId);

    /**
     * @brief Internal method to send data to a specific client.
     * @param data The serialized byte array.
     * @param clientId The unique identifier for the target session.
     */
    void sendTo(const QByteArray& data, const std::string& clientId);

private:
    /** @brief Component responsible for data transformation. */
    std::shared_ptr<IMessageParser> m_parser;

    /** @brief Component responsible for executing business logic. */
    std::shared_ptr<IMessageHandler> m_handler;

    /** @brief Component responsible for ensuring messages meet security criteria. */
    std::shared_ptr<ISecurityPolicy> m_security;

    /** @brief Component responsible for managing and communicating with client sessions. */
    std::shared_ptr<SessionManager> m_sessions;
};

} /* namespace Chat */
} /* namespace CTI */

#endif /* CHATSERVER_HPP */