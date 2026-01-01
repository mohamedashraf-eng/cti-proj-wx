# Qt Project Configuration

!!! Author: Mohamed Ashraf (mohamed.ashraf@coretech-innovations.com)


This guide covers the creation and compilation of a **Qt Console Application** using Qt Creator and the terminal.

## Creating a Project via Qt Creator GUI

To begin, launch Qt Creator from your terminal:

```bash
qtcreator
```

Follow these steps within the GUI to initialize your project:

1.  **New Project**: Click on **Create Project**.
2.  **Project Type**: Select **Application (Qt)** → **Qt Console Application**.
3.  **Location**: Enter your **Project Name** and select the **Project Location**.
4.  **Build System**: Select **qmake** as the build tool.
5.  **Translation**: Select a translation file if needed (otherwise, click **Next**).
6.  **Kits**: Select the appropriate Desktop kits for your system.
7.  **Version Control**: Select **Git** as the version control framework.

Once finished, Qt Creator will generate the boilerplate code and a `.pro` file in your selected directory.

---

## Compiling and Running via Terminal

After generating the project, you can compile and run it manually using the terminal. It is best practice to use a "shadow build" directory to keep your source folder clean.

### 1. Generate the Makefile
Navigate to your project's source directory and create a build folder:

```bash
mkdir build && cd build
qmake ..
```

### 2. Compile the Code
Use the `make` command to compile. We use `-j$(nproc)` to utilize all available CPU cores for a faster build:

```bash
make -j$(nproc)
```

### 3. Run the Application
Once the build completes, an executable binary will be created in the build folder. Run it by referencing its name (usually the same as your project name):

```bash
./YourProjectName
```

!!! success "Success"
    If there are no compilation errors, your Qt Console application will now execute in the terminal.

## Folder structure explained

```bash
cti-chat-app/
├── cti-chat-app.pro        (Top-level project file)
├── .qmake.conf             (Top-level project configurations)
├── common/                 (Shared logic: Message types, Packet parsing)
│   ├── common.pri          (Shared include file)
├── cti_client/
│   ├── cti_client.pro      (Client-specific settings)
│   ├── main.cpp
└── cti_server/
    ├── cti_server.pro      (Server-specific settings)
    ├── main.cpp
```  

- `cti-chat-app/`: The root directory of the project and it contains the global files to the project and scripts.
- `common/`: Contains the shared logic and configuration between other sub - directories.
- `cti_client`: The client logic and configuration for the chat application.
- `cti_server`: The server logic and configuration for the chat application.

You can build the project from `build/`  

```bash
qmake ..
make
```  
  
! note that `-r` for recursive and it is required for debug mode.

This will build the project in debug mode and now you can access your available modules inside the project and `make` and run them separatly.
