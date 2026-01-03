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

CONFIG(debug, debug|release) {
    TARGET = cti_client_d
} else {
    TARGET = cti_client
}

# QT += \
# 	core

TARGET = cti_client
# Standalone executable application.
TEMPLATE = app

SOURCES += \
	main.cpp \

# HEADERS += \
# 	chat_client.hpp \ 

message("Source files: " $$SOURCES)
message("Include paths: " $$INCLUDEPATH)
message("====================================================")