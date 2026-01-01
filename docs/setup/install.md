# 1. Installation Overview

!!! Author: Mohamed Ashraf (mohamed.ashraf@coretech-innovations.com)

## System Preparation
| Task | Command |
| :--- | :--- |
| **Update System** | `sudo apt update && sudo apt upgrade -y` |
| **Build Tools** | `sudo apt install -y build-essential libgl1-mesa-dev` |

## Qt 6 & Development Environment
| Component | Package / Purpose |
| :--- | :--- |
| **Core SDK** | `qt6-base-dev` (Includes QMake6 and core headers) |
| **Extra Tools** | `qt6-tools-dev` (Designer, Linguist, etc.) |
| **IDE** | `qtcreator` (Integrated Development Environment) |
| **Documentation** | `qtcreator-doc`, `qt6-documentation-tools` |

## Core Dependencies
These libraries are essential for networking, threading, and system integration.

| Category | Packages |
| :--- | :--- |
| **Networking** | `libssl-dev` (Required for SSL/TLS support in QtNetwork) |
| **System/Events** | `libglib2.0-0`, `libdbus-1-3` |
| **Display/XCB** | `libxcb-xinerama0`, `libxcb-icccm4`, `libxcb-image0`, `libxcb-keysyms1`, `libxcb-render-util0` |
| **Fonts** | `libfontconfig1`, `libfreetype6` |

---

# 2. Automated Installation Script
You can find the automation installing script at `scripts/setup_qt.sh`

### How to use:
1.  **Permit execution:** `chmod +x ./setup_qt.sh`
2.  **Run:** `sudo ./setup_qt.sh`  

```bash
cd ./scripts 
chmod +x ./setup_qt.sh 
sudo ./setup_qt.sh
```  
