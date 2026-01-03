/** 
 * @file IMessageParser.hpp
 * @brief Definition of the IMessageParser interface.
 * @author Mohamed Ashraf
 * @email mohamed.ashraf@coretech-innovations.com
 * @date Jan 2026
 * 
 * This file defines the abstract interface for the system's "Codec" (Coder-Decoder).
 * It is responsible for translating between the network-level byte stream 
 * and the application-level Message objects.
 */

#ifndef IMESSAGEPARSER_HPP
#define IMESSAGEPARSER_HPP

// Qt Depends
#include <QByteArray>

// Other
#include <vector>
#include "domain/Message.hpp"

namespace CTI {
namespace Chat {

/**
 * @class IMessageParser
 * @brief Abstract interface for data serialization and deserialization logic.
 * 
 * IMessageParser provides the bridge between the raw networking layer and 
 * the business logic layer. By abstracting this logic, the application can 
 * switch between different data formats (e.g., JSON, XML, Protobuf, or 
 * custom Binary) without changing the core server logic.
 */
class IMessageParser {
public:
    /**
     * @brief Virtual destructor for safe interface cleanup.
     */
    virtual ~IMessageParser() = default;

    /**
     * @brief Deserializes a raw byte array into a Message object.
     * 
     * This pure virtual function takes raw data received from a client 
     * and attempts to populate a Message structure based on the specific 
     * protocol implementation.
     * 
     * @param data The raw byte array extracted from the network buffer.
     * @return A Message object containing the interpreted fields.
     * 
     * @note If the data is malformed, the implementation should define 
     *       how to handle the error (e.g., returning an empty Message or 
     *       throwing an exception).
     */
    virtual Message parse(const QByteArray& data) = 0;

    /**
     * @brief Serializes a Message object into a raw byte array.
     * 
     * This pure virtual function prepares a Message object for network 
     * transmission by converting its fields into the protocol-specific 
     * byte format.
     * 
     * @param msg The Message object to be serialized.
     * @return A QByteArray containing the formatted data ready for transport.
     */
    virtual QByteArray serialize(const Message& msg) = 0;
};

} /* namespace Chat */
} /* namespace CTI */

#endif /* IMESSAGEPARSER_HPP */