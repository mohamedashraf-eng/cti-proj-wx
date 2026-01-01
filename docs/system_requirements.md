# Client Server Chat System

## Overview
This project implements a TCP based client server chat and file management system

## Requirements
- TCP sockets only not UDP
- Follow SOLID principles
- At least one design pattern must be used
- Event based architecture
- Multithreading support
- One command per line
- Commands are plain text
- Arguments separated by semicolon where specified
- Optional conversion from string command to JSON before parsing
- Responses are plain text
- Use QMake with pro and pri files
- Server replies with
  - `OK`
  - `ERROR <code> <message>`

### Error Code Examples
- `404 FILE_NOT_FOUND`
- `500 INTERNAL_ERROR`

## Security Basics
- Reject all operations targeting the server root directory
- Reject directory traversal attempts including `..` or absolute paths

## Testing
- Unit tests must be implemented

## Commands

### AUTH
**Format**
```
AUTH <username>,<password>
```

**Behavior**
Authenticate admin user and start communication

**Responses**
- `OK` Authenticated
- `ERROR <code> <message>` Invalid username or password

---

### CREATE
**Format**
```
CREATE <filename>
```

**Behavior**
Create an empty file in the server working directory

**Responses**
- `OK` file created successfully
- `ERROR <code> <message>` file already exists or cannot be created

---

### WRITE
**Format**
```
WRITE <filename>;<data>
```

**Behavior**
Overwrite file content with provided data  
Everything after the first semicolon is treated as file content

**Example**
```
WRITE hi.txt;Hello World
```

**Responses**
- `OK` data written successfully
- `ERROR <code> <message>` file does not exist or cannot be written

---

### APPEND
**Format**
```
APPEND <filename>;<data>
```

**Behavior**
Append data to the end of the file

**Responses**
- `OK` data appended successfully
- `ERROR <code> <message>` file does not exist or cannot be written

---

### READ
**Format**
```
READ <filename>
```

**Behavior**
Return file content

**Responses**
On success
```
OK <length>
<file content>
```

On failure
- `ERROR <code> <message>` file does not exist or cannot be read

---

### DELETE
**Format**
```
DELETE <filename>
```

**Behavior**
Delete specified file

**Responses**
- `OK` file deleted
- `ERROR <code> <message>` file does not exist or cannot be deleted

---

### RENAME
**Format**
```
RENAME <oldname>;<newname>
```

**Behavior**
Rename an existing file

**Responses**
- `OK` file renamed
- `ERROR <code> <message>` file does not exist or rename failed

---

### LIST
**Format**
```
LIST
```

**Behavior**
List files in the server working directory

**Responses**
On success
```
OK <count>
<filename>
...
```

On failure
- `ERROR <code> <message>`

---

### INFO
**Format**
```
INFO <filename>
```

**Behavior**
Return file metadata such as size and last modified time

**Responses**
```
OK size=<bytes> modified=<timestamp>
```
- `ERROR <code> <message>`

## Examples

Client
```
CREATE hi.txt
```

Server
```
OK <path>
```

Client
```
WRITE hi.txt;Hello World
```

Server
```
OK
```

Client
```
READ hi.txt
```

Server
```
OK 12
Hello World
```

Client
```
LIST
```

Server
```
OK 1
hi.txt
```
