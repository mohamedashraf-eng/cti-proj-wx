/** 
 * @file IMessageHandler.hpp
 * @brief Definition of the IMessageHandler interface.
 * @author Mohamed Ashraf
 * @email mohamed.ashraf@coretech-innovations.com
 * @date Jan 2026
 * 
 * This file defines the abstract interface for processing chat messages. It 
 * allows for different business logic implementations (e.g., Echo, AI Bot, 
 * Group Chat) to be swapped easily.
 */

#ifndef IMESSAGEHANDLER_HPP
#define IMESSAGEHANDLER_HPP

// Qt Depends

// Other
#include "domain/Message.hpp"

namespace CTI {
namespace Chat {

/**
 * @class IMessageHandler
 * @brief Abstract interface for handling business logic of processed messages.
 * 
 * IMessageHandler acts as the functional engine of the chat server. Once a 
 * message has been parsed and validated, it is passed to an implementation of 
 * this interface to determine the appropriate response or action.
 */
class IMessageHandler {
public:
    /**
     * @brief Virtual destructor for safe interface cleanup.
     */
    virtual ~IMessageHandler() = default;

    /**
     * @brief Processes a message and generates a response.
     * 
     * This pure virtual function is responsible for executing the core 
     * application logic (such as routing a private message or updating a 
     * user's status).
     * 
     * @param msg The incoming Message object (already parsed and validated).
     * @return A Message object representing the response to be sent back 
     *         or broadcasted.
     * 
     * @note Implementation classes should ensure that the returned Message 
     *       is properly formatted for the subsequent serialization step.
     */
    virtual Message handle(const Message& msg) = 0;
};

} /* namespace Chat */
} /* namespace CTI */

#endif /* IMESSAGEHANDLER_HPP */