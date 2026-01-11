/** 
    @author: Mohamed Ashraf
    @email: mohamed.ashraf@coretech-innovations.com
    @date: Jan 2026
    @description: Standardized error codes for CTI Chat Application.
    @mohamedashraf-eng
*/

#ifndef ERROR_CODES_H
#   define ERROR_CODES_H

namespace CTI {
namespace Chat {
    
    /**
     * @brief Error Category definitions.
     * 1000-1999: Network/Connection Errors
     * 2000-2999: Authentication & Authorization
     * 3000-3999: Protocol & Framing Errors
     * 4000-4999: Chat Application Logic
     * 5000-5999: System & Server Errors
     */
    enum class ErrorCode : int {
        // Success
        SUCCESS                     = 0,

        // 1000: Network/Connection Errors
        ERR_CONNECTION_REFUSED      = 1001,
        ERR_CONNECTION_TIMEOUT      = 1002,
        ERR_CONNECTION_LOST         = 1003,
        ERR_SSL_HANDSHAKE_FAILED    = 1004,
        ERR_HOST_NOT_FOUND          = 1005,

        // 2000: Authentication & Authorization
        ERR_UNAUTHINTECATED          = 2001,
        ERR_UNAUTHORIZED             = 2002,
        ERR_INVALID_CREDENTIALS      = 2003,
        ERR_USER_ALREADY_LOGGED_IN   = 2004,
        ERR_SESSION_EXPIRED          = 2005,
        ERR_INSUFFICIENT_PERMISSIONS = 2006,

        // 3000: Protocol & Framing Errors (Security Layer)
        ERR_MALFORMED_PACKET         = 3001,
        ERR_PAYLOAD_TOO_LARGE        = 3002, // Protection against DoS/Buffer Overflow
        ERR_UNSUPPORTED_PROTOCOL_VER = 3003,
        ERR_DECRYPTION_FAILED        = 3004,

        // 4000: Chat Application Logic
        ERR_USER_NOT_FOUND          = 4001,
        ERR_RECIPIENT_OFFLINE       = 4002,
        ERR_MESSAGE_SEND_FAILED     = 4003,
        ERR_GROUP_NOT_FOUND         = 4004,
        ERR_NOT_IN_GROUP            = 4005,
        ERR_CHAT_NOT_FOUND          = 404,  // Mapping standard 404

        // 5000: System & Server Errors
        ERR_INTERNAL_SERVER_ERROR   = 5001,
        ERR_SERVER_BUSY             = 5002,
        ERR_DATABASE_FAILURE        = 5003,
        ERR_RESOURCE_LIMIT_REACHED  = 5004,
        ERR_UNKNOWN_ERROR           = 5999
    };

    /**
     * @brief Helper to convert ErrorCode to a readable string.
     */
    inline const char* error_code_to_string(ErrorCode code) {
        switch (code) {
            case ErrorCode::SUCCESS:                     return "Success";
            case ErrorCode::ERR_CONNECTION_REFUSED:      return "Connection Refused";
            case ErrorCode::ERR_SSL_HANDSHAKE_FAILED:    return "SSL Handshake Failed";
            case ErrorCode::ERR_PAYLOAD_TOO_LARGE:       return "Security Warning: Payload Too Large";
            case ErrorCode::ERR_USER_NOT_FOUND:          return "User Not Found";
            case ErrorCode::ERR_INTERNAL_SERVER_ERROR:   return "Internal Server Error";
            case ErrorCode::ERR_MALFORMED_PACKET:        return "Detected malformed packet";
            case ErrorCode::ERR_CHAT_NOT_FOUND:          return "Chat Not Found";
            default:                                     return "Unknown Error Code";
        }
    }

} /* namespace Chat */
} /* namespace CTI */

#endif /* ERROR_CODES_H */