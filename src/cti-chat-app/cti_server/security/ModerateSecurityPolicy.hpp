/** 
    @author: Mohamed Ashraf
    @email: mohamed.ashraf@coretech-innovations.com
    @date: Jan 2026
    @description: A TCP based chat application using QT framework.

    @mohamedashraf-eng
*/
#ifndef MODERATESECURITYPOLICY_HPP
#   define MODERATESECURITYPOLICY_HPP

// Qt Depends

// Other
#include "domain/Message.hpp"
#include "error/error_codes.hpp"
#include "error/error_emitter.hpp"
#include "constants.hpp"

namespace CTI {
namespace Chat {

class ModerateSecurityPolicy : public ISecurityPolicy {
public:
    ErrorCode validate(const Message& msg) override {
        // Check against DDOS attacks.
        if(msg.payload.size() > Constants::MAX_PAYLOAD_SIZE) {
            EMIT_ERROR() << error_code_to_string(ErrorCode::ERR_PAYLOAD_TOO_LARGE);
            return ErrorCode::ERR_PAYLOAD_TOO_LARGE;
        }

        return ErrorCode::SUCCESS;
    }

};

} /* namespace Chat */
} /* namespace CTI */

#endif /* MODERATESECURITYPOLICY_HPP */