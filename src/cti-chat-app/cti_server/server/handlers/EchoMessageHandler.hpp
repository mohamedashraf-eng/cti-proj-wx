/** 
    @author: Mohamed Ashraf
    @email: mohamed.ashraf@coretech-innovations.com
    @date: Jan 2026
    @description: A TCP based chat application using QT framework.

    @mohamedashraf-eng
*/
#ifndef ECHOMESSAGERHANDLER_HPP
#   define ECHOMESSAGERHANDLER_HPP

// Qt Depends

// Other
#include "domain/Message.hpp"
#include "error/error_codes.hpp"
#include "core/IMessageHandler.hpp"

namespace CTI {
namespace Chat {

class EchoMessageHandler : public IMessageHandler {
public:
    Message handle(const Message& msg) override {
        Message updatedMsg = msg;
        updatedMsg.payload += " from server.";
        return updatedMsg;
    }
};

} /* namespace Chat */
} /* namespace CTI */

#endif /* ECHOMESSAGERHANDLER_HPP */