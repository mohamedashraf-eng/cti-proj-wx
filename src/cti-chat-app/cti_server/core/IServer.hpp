/** 
 * @file IServer.hpp
 * @brief Definition of the IServer interface for server lifecycle control.
 * @author Mohamed Ashraf
 * @email mohamed.ashraf@coretech-innovations.com
 * @date Jan 2026
 * 
 * This file defines the standard interface for controlling the operational 
 * state of the chat server.
 */

#ifndef ISERVER_HPP
#define ISERVER_HPP

// Qt Depends

// Other

namespace CTI {
namespace Chat {

/**
 * @class IServer
 * @brief Abstract interface defining core server control operations.
 * 
 * IServer provides a unified way to manage the lifecycle of a server instance.
 * By using this interface, the application's entry point (main) can start and 
 * stop the server without needing to know whether it's a TCP, UDP, or 
 * Mock implementation.
 */
class IServer {
public:
    /**
     * @brief Virtual destructor to ensure proper cleanup of derived server implementations.
     */
    virtual ~IServer() = default;

    /**
     * @brief Initiates the server's listening or processing state.
     * 
     * Implementation classes should use this method to bind to ports, 
     * start event loops, or begin accepting incoming network traffic.
     */
    virtual void start() = 0;

    /**
     * @brief Gracefully shuts down the server.
     * 
     * Implementation classes should use this method to close active sockets,
     * disconnect clients, and release occupied resources.
     */
    virtual void stop() = 0;
};

} /* namespace Chat */
} /* namespace CTI */

#endif /* ISERVER_HPP */