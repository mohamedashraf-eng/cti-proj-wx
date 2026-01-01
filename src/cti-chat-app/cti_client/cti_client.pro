### Qt project file for cti-chat-app

# ========================================
# Author: Mohamed Ashraf (mohamed.ashraf@coretech-innovations.com)
# Date: Jan 2026
# Description: A command-line chat application using Qt framework.
# ========================================

message("====================================================")
message("Current directory: " $$PWD)

QT += \
	network

TARGET = cti_client
TEMPLATE = app

# Include the shared logic
include(../common/common.pri)

SOURCES += \
	main.cpp

# HEADERS += \
# 	clientwindow.h

message("Source files: " $$SOURCES)
message("Include paths: " $$INCLUDEPATH)
message("====================================================")