#!/bin/bash

# =================================================================
# Qt 6 Development Environment Setup for Ubuntu 22.04
# Author: AI Assistant
# Description: Installs build tools, Qt6 SDK, and dependencies.
# Author: Mohamed Ashraf (mohamed.ashraf@coretech-innovations.com)
# =================================================================

# Color codes for logging
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

LOG_FILE="qt_install_$(date +%Y%m%d_%H%M%S).log"

log() {
    echo -e "${BLUE}[INFO]${NC} $1" | tee -a "$LOG_FILE"
}

success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1" | tee -a "$LOG_FILE"
}

error() {
    echo -e "${RED}[ERROR]${NC} $1" | tee -a "$LOG_FILE"
}

# Ensure script is run as root
if [ "$EUID" -ne 0 ]; then 
  error "Please run as root (use sudo)"
fi

log "Starting Installation. Detailed logs: $LOG_FILE"

# 1. Update System
log "Updating package lists and upgrading system..."
apt update && apt upgrade -y >> "$LOG_FILE" 2>&1
if [ $? -eq 0 ]; then success "System updated."; else error "System update failed."; fi

# 2. Install Build Essentials
log "Installing Build Essentials and Mesa OpenGL..."
apt install -y build-essential libgl1-mesa-dev >> "$LOG_FILE" 2>&1
success "Build tools installed."

# 3. Install Qt 6 SDK and Creator
log "Installing Qt6 Base, Tools, and Qt Creator..."
apt install -y qt6-base-dev qt6-tools-dev qt6-tools-dev-tools \
    qtcreator qtcreator-data qtcreator-doc >> "$LOG_FILE" 2>&1
success "Qt6 SDK and Creator installed."

# 4. Install Dependencies (Network, Security, XCB)
log "Installing system dependencies (SSL, DBus, XCB)..."
apt install -y \
    libssl-dev \
    libglib2.0-0 \
    libdbus-1-3 \
    libxcb-xinerama0 \
    libxcb-icccm4 \
    libxcb-image0 \
    libxcb-keysyms1 \
    libxcb-render-util0 \
    libfontconfig1 \
    libfreetype6 >> "$LOG_FILE" 2>&1
success "Dependencies installed."

# 5. Fix QMake Path (Symlink qmake to qmake6)
log "Configuring qmake symlink..."
if [ -f /usr/bin/qmake6 ] && [ ! -f /usr/bin/qmake ]; then
    ln -s /usr/bin/qmake6 /usr/bin/qmake
    success "Symlinked qmake6 to qmake."
fi

# Summary
echo -e "\n--------------------------------------------"
success "Installation Complete!"
log "Environment Summary:"
echo -e "  - QMake Version: $(qmake --version | grep 'Using Qt version' || echo 'Check manually')"
echo -e "  - Compiler: $(g++ --version | head -n 1)"
echo -e "  - Log stored in: $LOG_FILE"
echo -e "--------------------------------------------"
echo -e "You can now open Qt Creator and start your project."