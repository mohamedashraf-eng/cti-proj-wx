/** 
    @author: Mohamed Ashraf
    @email: mohamed.ashraf@coretech-innovations.com
    @date: Jan 2026
    @description: A TCP based chat application using QT framework.

    @mohamedashraf-eng
*/
#ifndef ICOMMAND_HPP
#   define ICOMMAND_HPP

#include <QStringList>
#include <QDir>
#include "domain/Message.hpp"

namespace CTI {
namespace Chat {

/**
 * @brief Base interface for all executable commands.
 */
class ICommand {
public:
    virtual ~ICommand() = default;

    /**
     * @brief Executes the command logic.
     * @param args Arguments parsed from the client string.
     * @return Message object containing the protocol-compliant response.
     */
    virtual Message execute(const QStringList& args) = 0;

protected:
    /**
     * @brief Security utility to prevent path traversal and root access.
     */
    bool isValidPath(const QString& path) {
        if (path.isEmpty()) return false;
        if (path.contains("..") || path.startsWith("/") || path.contains(":/")) return false;
        return true;
    }
};

} // namespace Chat
} // namespace CTI

#endif