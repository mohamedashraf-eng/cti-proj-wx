### Qt project file for cti-chat-app

# ========================================
# Author: Mohamed Ashraf (mohamed.ashraf@coretech-innovations.com)
# Date: Jan 2026
# Description: A command-line chat application using Qt framework.
# ========================================

AUTHOR = "Mohamed Ashraf"
EMAIL = "mohamed.ashraf@coretech-innovations.com"

message("====================================================")
message("Author: " $$AUTHOR)
message("Email: " $$EMAIL)
message("====================================================")
message("Current directory: " $$PWD)
message("The active configuration is: " $$CONFIG)
message("====================================================")

CONFIG += \
        c++17 \
        warn_on \
        ordered 

# This project contains a subdirectories projects.
TEMPLATE = subdirs

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# The sub-directories to include
SUBDIRS += \
    cti_client \
    cti_server 
#     common

# OTHER SETTINGS
TRANSLATIONS += \
    cti-chat-app_en_CA.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
