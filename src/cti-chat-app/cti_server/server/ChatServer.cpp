/** 
 * @file ChatServer.cpp
 * @brief Implementation of the ChatServer core logic.
 * @author Mohamed Ashraf
 * @email mohamed.ashraf@coretech-innovations.com
 * @date Jan 2026
 */

#include "ChatServer.hpp"
#include "error/error_codes.hpp"
#include "error/error_emitter.hpp"

namespace CTI {
namespace Chat {

/**
 * @brief Constructs the ChatServer with required dependencies.
 * @param parser Shared pointer to serialization logic.
 * @param handler Shared pointer to business logic.
 * @param security Shared pointer to integrity validation.
 * @param sessions Shared pointer to session management.
 */
ChatServer::ChatServer(std::shared_ptr<IMessageParser> parser,
                       std::shared_ptr<IMessageHandler> handler,
                       std::shared_ptr<ISecurityPolicy> security,
                       std::shared_ptr<SessionManager> sessions)
    : m_parser(parser),
      m_handler(handler),
      m_security(security),
      m_sessions(sessions) { 
    EMIT_DEBUG() << "Initiated Chat Server core logic."; 
}

/**
 * @brief Internal pipeline to transform raw input into a processed response.
 * @param data Raw byte array from a client.
 * @return QByteArray The serialized response. Returns empty array on security failure.
 */
QByteArray ChatServer::process(const QByteArray& data, const std::string& clientId) {
    EMIT_DEBUG() << "Processing incoming data bundle.";

    // 1. Parsing
    Message msg = m_parser->parse(data);
    msg.senderId = clientId;

    // 2. Security Validation
    if (ErrorCode::SUCCESS != m_security->validate(msg)) {
        EMIT_ERROR() << "Security validation failed. Dropping packet.";
        return QByteArray(); 
    }

    // 3. Business Logic Handling
    EMIT_DEBUG() << "Executing message command handler.";
    Message out = m_handler->handle(msg);

    // 4. Serialization
    return m_parser->serialize(out);
}

/**
 * @brief Sends a specific data packet to a single client.
 * @param data Serialized message bytes.
 * @param clientId Unique identifier for the target session.
 */
void ChatServer::sendTo(const QByteArray& data, const std::string& clientId) {
    if (data.isEmpty()) return;
    m_sessions->broadcast(data, clientId);
}

/**
 * @brief Broadcasts a data packet to all currently connected clients.
 * @param data Serialized message bytes.
 */
void ChatServer::broadcast(const QByteArray& data, const std::string& clientId) {
    if (data.isEmpty()) {
        EMIT_DEBUG() << "Broadcast skipped: Data is empty.";
        return;
    }
    
    EMIT_INFO() << "Broadcasting message to specific client.";
    m_sessions->broadcast(data, clientId);
}

/**
 * @brief Orchestrates the complete message processing pipeline and broadcasts the result.
 * 
 * Pipeline: Parse -> Security Check -> Handle Logic -> Serialize -> Broadcast.
 * 
 * @param data The raw byte array received from a ClientSession.
 */
void ChatServer::processAndBroadcast(const QByteArray& data, const std::string& clientId) {
    QByteArray processedData = process(data, clientId);
    
    if (!processedData.isEmpty()) {
        broadcast(processedData, clientId);
    }
}

} // namespace Chat
} // namespace CTI