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