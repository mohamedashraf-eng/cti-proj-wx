/** 
 * @file main.cpp
 * @brief Entry point for the CTI TCP Chat Server application.
 * @author Mohamed Ashraf
 * @email mohamed.ashraf@coretech-innovations.com
 * @date Jan 2026
 * 
 * This file orchestrates the dependency injection and bootstrapping of the 
 * server components, including the network transport, business logic, 
 * security, and parsing layers.
 */

// Qt Depends
#include <QCoreApplication>
#include <QByteArray>

// Other
#include "transport/TcpServer.hpp"
#include "server/ChatServer.hpp"
#include "constants.hpp"

#include "security/ModerateSecurityPolicy.hpp"
#include "server/parsers/RawMessageParser.hpp"
#include "server/handlers/CmdMessageHandler.hpp"

using namespace CTI::Chat;

/**
 * @brief Main function of the application.
 * 
 * Performs the following logical steps:
 * 1. Initializes the Qt Event Loop.
 * 2. Instantiates concrete implementations of the system's core interfaces.
 * 3. Aggregates dependencies into the ChatServer logic.
 * 4. Starts the TCP network listener on the configured port.
 * 
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return int Status code (0 for success).
 */
int main(int argc, char *argv[]) {
    // Step 1: Initialize the Qt Core Application to manage the event loop
    QCoreApplication app(argc, argv);

    // Step 2: Component Instantiation (Dependency Injection setup)
    // Here we choose the specific behaviors for parsing, handling, and security.
    
    /** @brief Concrete implementation for raw message parsing. */
    auto parser   = std::make_shared<RawMessageParser>();
    
    /** @brief Concrete implementation for handling messages (Cmd strategy). */
    auto handler  = std::make_shared<CmdMessageHandler>();
    
    /** @brief Concrete implementation of the security policy (Moderate level). */
    auto security = std::make_shared<ModerateSecurityPolicy>();
    
    /** @brief The central session registry for tracking connected users. */
    auto sessions = std::make_shared<SessionManager>();

    // Step 3: Initialize the ChatServer logic
    // We inject the components created above into the central logic orchestrator.
    auto logic = std::make_shared<ChatServer>(
                                    parser, 
                                    handler, 
                                    security, 
                                    sessions);

    // Step 4: Configure and start the Network Transport layer
    // Instantiate the TCP server and bind it to the default port.
    TcpServer server(logic, sessions);
    
    bool isListening = server.listen(
        QHostAddress::Any,
        Constants::DEFAULT_PORT
    );

    if (!isListening) {
        // Port might be occupied or permission denied
        return -1;
    }

    // Step 5: Start the blocking event loop
    // This allows the server to process signals/slots for networking and threading.
    return app.exec();
}