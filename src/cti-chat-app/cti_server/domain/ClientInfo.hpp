/** 
 * @file ClientInfo.hpp
 * @brief Definition of the ClientInfo class for client metadata.
 * @author Mohamed Ashraf
 * @email mohamed.ashraf@coretech-innovations.com
 * @date Jan 2026
 * 
 * This file contains the data structure used to store basic identification 
 * information for connected clients.
 */

#ifndef CLIENTINFO_HPP
#define CLIENTINFO_HPP

// Qt Depends

// Other
#include <string>

namespace CTI {
namespace Chat {

/**
 * @class ClientInfo
 * @brief A simple container for client-specific metadata.
 * 
 * This class is used to maintain the identity of a client throughout their 
 * session. It can be extended in the future to include additional 
 * information such as connection time, IP address, or user permissions.
 */
class ClientInfo {
public:
    /** 
     * @brief The unique identifier for the client. 
     * This ID is used by the server to route messages and track user sessions.
     */
    std::string id;
};

} /* namespace Chat */
} /* namespace CTI */

#endif /* CLIENTINFO_HPP */