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
	main.cpp

# HEADERS += \
# 	clientwindow.h


message("Source files: " $$SOURCES)
message("Include paths: " $$INCLUDEPATH)
message("====================================================")