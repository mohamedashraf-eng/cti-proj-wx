### Qt project file for cti-chat-app

# ========================================
# Author: Mohamed Ashraf (mohamed.ashraf@coretech-innovations.com)
# Date: Jan 2026
# Description: A command-line chat application using Qt framework.
# ========================================

# common.pri
QT += network  # Both need TCP support

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

# HEADERS += $$PWD/chatmessage.h
# SOURCES += $$PWD/chatmessage.cpp