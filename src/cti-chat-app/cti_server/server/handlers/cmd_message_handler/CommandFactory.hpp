/** 
 * @file CommandFactory.hpp
 * @brief Factory for creating and retrieving command objects for the Chat Server.
 * @author Mohamed Ashraf
 * @email mohamed.ashraf@coretech-innovations.com
 * @date Jan 2026
 * 
 * This file implements a registry-based factory that maps protocol keywords 
 * to their respective functional logic, supporting the Command Design Pattern.
 */

#ifndef COMMANDFACTORY_HPP
#define COMMANDFACTORY_HPP

#include <map>
#include <memory>
#include <QString>
#include "FileCommands.hpp"

namespace CTI {
namespace Chat {

/**
 * @class CommandFactory
 * @brief Manages the creation and lookup of command implementations.
 * 
 * The CommandFactory serves as the central repository for all operations 
 * supported by the server. It eliminates the need for complex switch-case 
 * or if-else chains in the message handler by providing a clean mapping 
 * between string-based protocol commands and their logic classes.
 */
class CommandFactory {
public:
    /**
     * @brief Constructs the factory and registers all supported commands.
     * 
     * The constructor pre-allocates and stores shared instances of every 
     * command defined in the protocol (AUTH, CREATE, WRITE, etc.) into 
     * an internal registry.
     */
    CommandFactory() {
        m_registry["AUTH"]   = std::make_shared<AuthCommand>();
        m_registry["CREATE"] = std::make_shared<CreateCommand>();
        m_registry["WRITE"]  = std::make_shared<WriteCommand>();
        m_registry["APPEND"] = std::make_shared<AppendCommand>();
        m_registry["READ"]   = std::make_shared<ReadCommand>();
        m_registry["DELETE"] = std::make_shared<DeleteCommand>();
        m_registry["RENAME"] = std::make_shared<RenameCommand>();
        m_registry["LIST"]   = std::make_shared<ListCommand>();
        m_registry["INFO"]   = std::make_shared<InfoCommand>();
    }

    /**
     * @brief Retrieves a command object based on its protocol name.
     * 
     * Performs a case-insensitive lookup in the registry.
     * 
     * @param name The command keyword received from the client (e.g., "auth", "CREATE").
     * @return std::shared_ptr<ICommand> A shared pointer to the command object if found; 
     *         otherwise, @c nullptr.
     */
    std::shared_ptr<ICommand> create(const QString& name) {
        auto it = m_registry.find(name.toUpper());
        return (it != m_registry.end()) ? it->second : nullptr;
    }

private:
    /** 
     * @brief Internal registry mapping command keywords to their implementations. 
     */
    std::map<QString, std::shared_ptr<ICommand>> m_registry;
};

} // namespace Chat
} // namespace CTI

#endif // COMMANDFACTORY_HPP