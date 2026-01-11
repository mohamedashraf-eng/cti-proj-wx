### Qt project file for cti-chat-app

# ========================================
# Author: Mohamed Ashraf (mohamed.ashraf@coretech-innovations.com)
# Date: Jan 2026
# Description: A command-line chat application using Qt framework.
# ========================================

message("====================================================")
message("Current directory: " $$PWD)

# Include the shared logic
include(../common/common.pri)

# Add subdirectories if your headers are nested
INCLUDEPATH += \
        $$PWD/core \
        $$PWD/domain \
        $$PWD/network \
        $$PWD/security \
        $$PWD/server \
        $$PWD/threading \
        $$PWD/transport \

CONFIG(debug, debug|release) {
    TARGET = cti_server_d
# 	QT += console
} else {
    TARGET = cti_server
}

# QT += \
# 	core

TARGET = cti_server
TEMPLATE = app

SOURCES += \
	main.cpp \
    network/ClientSession.cpp \
    server/ChatServer.cpp \
    threading/SessionThread.cpp \
    transport/TcpServer.cpp \
    server/SessionManager.cpp \

HEADERS += \
    core/IMessageHandler.hpp \
    core/IMessageParser.hpp \
    core/IServer.hpp \
    domain/ClientInfo.hpp \
    domain/Message.hpp \
    network/ClientSession.hpp \
    server/ChatServer.hpp \
    threading/SessionThread.hpp \
    transport/TcpServer.hpp \
    server/SessionManager.hpp \
    core/IClientSession.hpp \
    security/ModerateSecurityPolicy.hpp \
    server/handlers/EchoMessageHandler.hpp \
    server/handlers/CmdMessageHandler.hpp \
    security/ISecurityPolicy.hpp \
    server/parsers/RawMessageParser.hpp \
    


message("Source files: " $$SOURCES)
message("Include paths: " $$INCLUDEPATH)
message("====================================================")