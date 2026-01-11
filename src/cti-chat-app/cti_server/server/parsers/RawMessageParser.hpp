/** 
 * @file RawMessageParser.hpp
 * @brief Implementation of a 1:1 raw data parser for the Chat System.
 * @author Mohamed Ashraf
 * @email mohamed.ashraf@coretech-innovations.com
 * @date Jan 2026
 * 
 * This parser performs no structural transformation, treating the entire 
 * incoming byte stream as the message payload.
 */

#ifndef RAWMESSAGEPARSER_HPP
#define RAWMESSAGEPARSER_HPP

// Qt Depends
#include <QByteArray>

// Other
#include "domain/Message.hpp"
#include "core/IMessageParser.hpp"

namespace CTI {
namespace Chat {

/**
 * @class RawMessageParser
 * @brief A basic implementation of IMessageParser for raw byte-to-string mapping.
 * 
 * Use this parser when the protocol does not define a specific header/footer 
 * structure and the application logic expects the full buffer content.
 * It maps QByteArray directly to the Message payload.
 */
class RawMessageParser : public IMessageParser {
public:
    /**
     * @brief Converts raw bytes into a Message object.
     * 
     * Optimization: Uses QByteArray::toStdString() which is highly optimized 
     * in Qt 6 to minimize intermediate allocations.
     * 
     * @param data The raw bytes received from the socket.
     * @return Message object with the payload populated and senderId set to "Client".
     */
    Message parse(const QByteArray& data) override {
        // We set senderId to "Client" as the default for incoming raw data.
        // The specific Session ID is typically injected later in the pipeline.
        return Message(data.toStdString(), "Client");
    }

    /**
     * @brief Serializes a Message object back into a raw byte array.
     * 
     * Optimization: Uses QByteArray::fromStdString to leverage move-aware 
     * construction if the compiler supports it.
     * 
     * @param msg The Message object to be sent over the wire.
     * @return QByteArray containing the message payload.
     */
    QByteArray serialize(const Message& msg) override {
        return QByteArray::fromStdString(msg.payload);
    }
};

} /* namespace Chat */
} /* namespace CTI */

#endif /* RAWMESSAGEPARSER_HPP */