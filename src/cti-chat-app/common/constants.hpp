/** 
    @author: Mohamed Ashraf
    @email: mohamed.ashraf@coretech-innovations.com
    @date: Jan 2026
    @description: Global constants for CTI Chat Application.
    @mohamedashraf-eng
*/

#ifndef CONSTANTS_HPP
#   define CONSTANTS_HPP

#include <cstdint>
#include <QString>

namespace CTI {
namespace Chat {
namespace Constants {

    // --- Networking Configuration ---
    static constexpr uint16_t DEFAULT_PORT            = 12345;
    inline const QString      DEFAULT_HOST            = "127.0.0.1";
    static constexpr int      MAX_PENDING_CONNECTIONS = 50; // Max queue for listen()
    /** @brief Character used to identify the end of a message frame. */
    static constexpr char DELIMITER = ';';
    
    // --- Security & Resource Limits ---
    /** 
     * @brief MAX_PAYLOAD_SIZE
     * Limits the total size of a single incoming packet (5 MB).
     * Prevents malicious clients from exhausting server RAM.
     */
    static constexpr uint32_t MAX_PAYLOAD_SIZE        = 1024 * 1024 * 5; 

    /** 
     * @brief MAX_MESSAGE_LENGTH
     * Max characters allowed in a single chat message.
     */
    static constexpr uint32_t MAX_MESSAGE_LENGTH       = 4096;
    
    static constexpr uint8_t  MAX_USERNAME_LENGTH      = 32;
    static constexpr uint16_t MAX_CONNECTED_CLIENTS    = 1000;

    // --- Timeouts (Milliseconds) ---
    static constexpr int      CONNECTION_TIMEOUT_MS    = 10000; // 10s
    static constexpr int      SSL_HANDSHAKE_TIMEOUT_MS = 5000;  // 5s
    static constexpr int      KEEP_ALIVE_INTERVAL_MS   = 30000; // 30s Heartbeat
    static constexpr int      IDLE_CLIENT_TIMEOUT_MS   = 60000; // Disconnect after 1 min inactivity

    // --- Protocol Details ---
    /**
     * @brief PACKET_HEADER_SIZE
     * Size of the integer prepended to packets to indicate payload length.
     * uint32_t = 4 bytes.
     */
    static constexpr uint8_t  PACKET_HEADER_SIZE       = sizeof(uint32_t);

    // --- Security / SSL Paths ---
    inline const QString      SERVER_CERT_PATH         = "configs/certs/server.crt";
    inline const QString      SERVER_KEY_PATH          = "configs/certs/server.key";

    // --- Application Info ---
    inline const QString      APP_NAME                 = "CTI Chat Server - Wx";
    inline const QString      APP_VERSION              = "1.0.0";

} /* namespace Constants */

} /* namespace Chat */
} /* namespace CTI */

#endif /* CONSTANTS_HPP */