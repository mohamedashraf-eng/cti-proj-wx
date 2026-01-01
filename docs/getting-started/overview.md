# Client-Server Chat & File Management System

!!! Author: Mohamed Ashraf (mohamed.ashraf@coretech-innovations.com)

## 1. Project Overview
A robust TCP-based system for remote file management and administrative communication. The system follows a strict request-response protocol over a multithreaded, event-driven architecture.

---

## 2. Technical Specifications

### Architecture & Design
*   **Protocol:** Strict TCP Sockets (UDP is prohibited).
*   **Principles:** Adherence to **SOLID** principles.
*   **Patterns:** Must implement at least one Design Pattern (e.g., Command, Factory, or Singleton) and an **Event-based** architecture.
*   **Concurrency:** Full multithreading support for handling multiple concurrent clients.
*   **Build System:** Use **QMake** with `.pro` and `.pri` file structures for modularity.

### Communication Rules
*   **Format:** Plain text, one command per line.
*   **Delimiters:** Arguments are separated by semicolons (`;`) where specified.
*   **Optional:** Support for converting string commands to JSON before server-side parsing.
*   **Success Response:** `OK` or `OK <metadata>`
*   **Error Response:** `ERROR <code> <message>` (e.g., `ERROR 404 FILE_NOT_FOUND`).

### Security Constraints
*   **Scope:** Operations are restricted to the server's designated working directory.
*   **Root Protection:** Reject all operations targeting the server root.
*   **Traversal Prevention:** Block all directory traversal attempts (e.g., `..`, `./`, or absolute paths).

---

## 3. Command Reference

| Command | Format | Behavior | Success Response |
| :--- | :--- | :--- | :--- |
| **AUTH** | `AUTH <user>,<pass>` | Authenticates admin to start session. | `OK` |
| **CREATE** | `CREATE <file>` | Creates an empty file in the working directory. | `OK` |
| **WRITE** | `WRITE <file>;<data>` | Overwrites file content with provided data. | `OK` |
| **APPEND** | `APPEND <file>;<data>` | Adds data to the end of an existing file. | `OK` |
| **READ** | `READ <file>` | Retrieves the entire content of a file. | `OK <len>` \n `<content>` |
| **DELETE** | `DELETE <file>` | Removes the specified file from the server. | `OK` |
| **RENAME** | `RENAME <old>;<new>` | Renames an existing file. | `OK` |
| **LIST** | `LIST` | Lists all files in the working directory. | `OK <count>` \n `<files...>` |
| **INFO** | `INFO <file>` | Returns file size and last modified timestamp. | `OK size=<B> modified=<T>` |

---

## 4. Error Handling
The server must return standardized error codes. Common examples include:

| Code | Message | Description |
| :--- | :--- | :--- |
| **401** | `UNAUTHORIZED` | Authentication failed or required. |
| **403** | `FORBIDDEN` | Security violation (traversal attempt). |
| **404** | `FILE_NOT_FOUND` | Target file does not exist. |
| **409** | `CONFLICT` | File already exists (on Create/Rename). |
| **500** | `INTERNAL_ERROR` | Server-side read/write failure. |

---

## 5. Interaction Examples

### File Creation & Writing
**Client:** `CREATE notes.txt`  
**Server:** `OK`  

**Client:** `WRITE notes.txt;Hello World`  
**Server:** `OK`

### File Retrieval
**Client:** `READ notes.txt`  
**Server:**  
`OK 11`  
`Hello World`

### Directory Listing
**Client:** `LIST`  
**Server:**  
`OK 2`  
`notes.txt`  
`config.cfg`

---

## 6. Testing Requirements
*   **Unit Tests:** Mandatory implementation for core logic, command parsing, and security validation layers.
*   **Path Validation:** Specific tests to ensure `../../etc/passwd` or similar paths are rejected.