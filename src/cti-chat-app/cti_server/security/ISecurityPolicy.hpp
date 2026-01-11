/** 
    @author: Mohamed Ashraf
    @email: mohamed.ashraf@coretech-innovations.com
    @date: Jan 2026
    @description: A TCP based chat application using QT framework.

    @mohamedashraf-eng
*/
#ifndef ISECURITYPOLICY_HPP
#   define ISECURITYPOLICY_HPP

// Qt Depends

// Other
#include "domain/Message.hpp"
#include "error/error_codes.hpp"

namespace CTI {
namespace Chat {

class ISecurityPolicy {
public:
    virtual ~ISecurityPolicy() = default;
    virtual ErrorCode validate(const Message& msg) = 0;
};

} /* namespace Chat */
} /* namespace CTI */

#endif /* ISECURITYPOLICY_HPP */