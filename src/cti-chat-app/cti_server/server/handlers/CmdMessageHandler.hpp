/** 
 * @file CmdMessageHandler.hpp
 * @brief Implementation of the Command Pattern Invoker for the Chat Server.
 * @author Mohamed Ashraf
 * @email mohamed.ashraf@coretech-innovations.com
 * @date Jan 2026
 * 
 * This file contains the CmdMessageHandler class, which acts as the bridge between 
 * raw network messages and specific business logic commands.
 */

#ifndef CMDMESSAGERHANDLER_HPP
#define CMDMESSAGERHANDLER_HPP

#include <QString>
#include <QStringList>
#include <QRegularExpression>
#include <memory>

#include "core/IMessageHandler.hpp"
#include "cmd_message_handler/CommandFactory.hpp"

namespace CTI {
namespace Chat {

/**
 * @class CmdMessageHandler
 * @brief The Invoker class in the Command Design Pattern.
 * 
 * CmdMessageHandler is responsible for the first stage of message processing 
 * after parsing. It tokenizes the message payload into a command name and 
 * arguments, then uses the CommandFactory to execute the appropriate logic.
 * 
 * This class ensures that the ChatServer remains decoupled from the specific 
 * implementation of file operations, authentication, or administrative tasks.
 */
class CmdMessageHandler : public IMessageHandler {
public:
    /**
     * @brief Constructs the handler and initializes the command registry factory.
     */
    CmdMessageHandler() : m_factory(std::make_unique<CommandFactory>()) {}

    /**
     * @brief Orchestrates the command execution lifecycle.
     * 
     * This method performs the following steps:
     * 1. Converts the std::string payload to QString for advanced manipulation.
     * 2. Identifies the command verb (the first word in the string).
     * 3. Splits the remaining string into tokens based on ';' or ',' delimiters.
     * 4. Requests a command object from the Factory.
     * 5. Executes the command and returns the resulting Message.
     * 
     * @param msg The incoming Message object containing raw payload and sender info.
     * @return Message A response message containing either the success result 
     *         or a protocol-compliant ERROR code.
     * 
     * @note Supports formats: 
     *       - "CREATE file.txt"
     *       - "WRITE file.txt;Hello World"
     *       - "AUTH user,pass"
     */
    Message handle(const Message& msg) override {
        // Prepare payload for processing
        QString payload = QString::fromStdString(msg.payload).trimmed();
        
        // 1. Tokenize Command Verb
        /**
         * payload: AUTH admin,password
         * cmdName = AUTH (from index 0 to space)
         * argString = admin,password (from space+1 to end)
         */
        int firstSpace = payload.indexOf(' ');
        QString cmdName = (firstSpace == -1) ? payload : payload.left(firstSpace);
        QString argString = (firstSpace == -1) ? "" : payload.mid(firstSpace + 1);

        // 2. Tokenize Arguments
        /** Separated by delimeter with no whitespace.
         *          0   d    1
         * args: [admin],;[password]
         */
        QStringList args = argString.split(QRegularExpression("[;,]"), Qt::SkipEmptyParts);

        // 3. Inject Sender Identity
        // We prepend it so the command always knows args[0] is the SenderID
        args.prepend(QString::fromStdString(msg.senderId)); 

        // 4. Command Resolution and Execution
        auto command = m_factory->create(cmdName);
        if (command) {
            return command->execute(args);
        }

        // 5. Fallback for Unrecognized Commands
        return Message("ERROR 404 COMMAND_NOT_FOUND", "Server");
    }
private:
    /** 
     * @brief The factory used to resolve string-based verbs into command objects. 
     */
    std::unique_ptr<CommandFactory> m_factory;
};

} /* namespace Chat */
} /* namespace CTI */

#endif /* CMDMESSAGERHANDLER_HPP */