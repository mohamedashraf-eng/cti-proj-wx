/** 
 * @file Message.hpp
 * @brief Definition of the Message structure used across the chat system.
 * @author Mohamed Ashraf
 * @email mohamed.ashraf@coretech-innovations.com
 * @date Jan 2026
 */

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include <utility>

namespace CTI {
namespace Chat {

/**
 * @class Message
 * @brief A lightweight data container for chat protocol units.
 * 
 * Optimized to use move semantics for efficient data transfer between 
 * the parser, security engine, and message handler.
 */
class Message {
public:
    /**
     * @brief Default constructor. 
     * Creates an empty message with "System" as the default sender.
     */
    Message() : senderId("System"), payload("") {}

    /**
     * @brief Parameterized constructor with move optimization.
     * @param payload The content or command string.
     * @param senderId Unique identifier of the sender.
     */
    Message(std::string payload, std::string senderId) 
        : senderId(std::move(senderId)), 
          payload(std::move(payload)) {}

    /**
     * @brief Equality operator for unit testing and logic comparison.
     */
    bool operator==(const Message& other) const {
        return (senderId == other.senderId && payload == other.payload);
    }

    /** 
     * @brief Unique identifier of the message sender (e.g., UUID or Username).
     */
    std::string senderId;

    /** 
     * @brief The actual content or command data of the message. 
     */
    std::string payload;    
};

} /* namespace Chat */
} /* namespace CTI */

#endif /* MESSAGE_HPP */