### Qt project file for cti-chat-app

# ========================================
# Author: Mohamed Ashraf (mohamed.ashraf@coretech-innovations.com)
# Date: Jan 2026
# Description: A command-line chat application using Qt framework.
# ========================================

# Add the 'common' directory itself
INCLUDEPATH += $$PWD

# Add subdirectories if your headers are nested
INCLUDEPATH += \
        $$PWD/error \
        $$PWD/core \
        $$PWD/network_layer \
        $$PWD/protocol_layer \

QT += core network

# Check Build Mode and define a C++ macro
CONFIG(debug, debug|release) {
    message("Shared: Building in DEBUG mode")
    DEFINES += CTI_CHAT_VERBOSE_MODE
} else {
    message("Shared: Building in RELEASE mode")
}

# This puts the .exe files in a 'debug' or 'release' folder inside your build path
CONFIG(debug, debug|release) {
    DESTDIR = $$OUT_PWD/../bin/debug
} else {
    DESTDIR = $$OUT_PWD/../bin/release
}

HEADERS += \
           $$PWD/constants.hpp \
           $$PWD/error/error_codes.hpp \
           $$PWD/error/error_emitter.hpp \
           $$PWD/network_layer/iconnect.hpp \
           $$PWD/protocol_layer/imessage.hpp \

# HEADERS += $$PWD/chatmessage.h
# SOURCES += $$PWD/chatmessage.cpp