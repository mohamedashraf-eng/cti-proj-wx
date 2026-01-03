/** 
 * @file FileCommands.hpp
 * @brief Concrete implementations of the file management and security protocol.
 * @author Mohamed Ashraf
 * @company CoreTech Innovations
 * @date Jan 2026
 * 
 * This file implements the Command Pattern for a multi-threaded TCP server.
 * It includes a thread-safe circular buffer for session management and 
 * mandatory authorization checks for every file operation.
 */

#ifndef FILECOMMANDS_HPP
#define FILECOMMANDS_HPP

#include "ICommand.hpp"
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QDateTime>
#include <QMap>
#include <QQueue>
#include <QMutex>
#include <QRegularExpression>
#include "error/error_emitter.hpp"
#include "constants.hpp"

namespace CTI {
namespace Chat {

/**
 * @class SecurityState
 * @brief Manages global authentication state and session lifecycle.
 * 
 * Uses a FIFO (Circular Buffer) logic to limit active sessions.
 * Provides thread-safe methods to authorize requests across multiple handler threads.
 */
class SecurityState {
public:
    /** @brief Map of active sessions: <SenderID (Socket GUID), Username> */
    inline static QMap<QString, QString> m_authUsers;
    
    /** @brief Queue to maintain the order of logins for circular buffer eviction. */
    inline static QQueue<QString> m_sessionQueue;
    
    /** @brief Mutex to protect shared session maps. */
    inline static QMutex m_mutex;
    
    /** @brief Maximum concurrent sessions allowed before evicting the oldest. */
    static constexpr int MAX_SESSIONS = Constants::MAX_CONNECTED_CLIENTS;

    /** @brief Mock user database for authentication. */
    inline static const QMap<QString, QString> m_usersDb = {
        {"admin", "password123"},
        {"user1", "securePass"},
        {"guest", "12345"}
    };

    /**
     * @brief Verifies if a sender has an active authenticated session.
     * @param senderId The unique ID of the connection.
     * @return true if authorized, false otherwise.
     */
    static bool isAuthorized(const QString& senderId) {
        QMutexLocker locker(&m_mutex);
        bool authorized = m_authUsers.contains(senderId);
        if (!authorized) {
            EMIT_WARN() << "Unauthorized access attempt blocked from SenderID:" << senderId;
        }
        return authorized;
    }

    /**
     * @brief Registers a new session. Evicts oldest session if buffer is full.
     * @param senderId The connection identifier.
     * @param username The authenticated username.
     */
    static void addSession(const QString& senderId, const QString& username) {
        QMutexLocker locker(&m_mutex);

        if (!m_authUsers.contains(senderId)) {
            if (m_sessionQueue.size() >= MAX_SESSIONS) {
                QString oldest = m_sessionQueue.dequeue();
                m_authUsers.remove(oldest);
                EMIT_INFO() << "Circular buffer full. Evicted oldest session:" << oldest;
            }
            m_sessionQueue.enqueue(senderId);
        }
        m_authUsers[senderId] = username;
    }
};

/**
 * @class AuthCommand
 * @brief Authenticates a client and generates a session.
 * @details args: [0] senderId, [1] username, [2] password
 */
class AuthCommand : public ICommand {
public:
    Message execute(const QStringList& args) override {
        EMIT_DEBUG() << "Processing AUTH request...";
        
        if (args.size() < 3) {
            EMIT_WARN() << "AUTH attempt failed: Missing arguments.";
            return Message{"ERROR 401 MISSING_CREDENTIALS", "Server"};
        }

        QString senderId = args[0];
        QString username = args[1];
        QString password = args[2];

        auto it = SecurityState::m_usersDb.find(username);
        if (it != SecurityState::m_usersDb.end() && it.value() == password) {
            SecurityState::addSession(senderId, username);
            EMIT_INFO() << "User [" << username << "] successfully authenticated from Sender:" << senderId;
            return Message{"OK AUTHORIZED", "Server"};
        }

        EMIT_WARN() << "Authentication failed for user [" << username << "] from Sender:" << senderId;
        return Message{"ERROR 401 UNAUTHORIZED", "Server"};
    }
};

/**
 * @class CreateCommand
 * @brief Creates a new empty file.
 * @details args: [0] senderId, [1] filename
 */
class CreateCommand : public ICommand {
public:
    Message execute(const QStringList& args) override {
        if (args.isEmpty() || !SecurityState::isAuthorized(args[0])) 
            return Message{"ERROR 401 UNAUTHORIZED", "Server"};

        if (args.size() < 2 || !isValidPath(args[1])) {
            EMIT_WARN() << "CREATE rejected: Invalid path traversal or missing name. Requested by:" << args[0];
            return Message{"ERROR 403 FORBIDDEN", "Server"};
        }

        QFile file(args[1]);
        if (file.exists()) {
            EMIT_WARN() << "CREATE conflict: File already exists:" << args[1];
            return Message{"ERROR 409 CONFLICT", "Server"};
        }

        if (file.open(QIODevice::WriteOnly)) {
            file.close();
            EMIT_INFO() << "File created successfully:" << args[1] << "by" << args[0];
            return Message{"OK", "Server"};
        }
        
        EMIT_ERROR() << "File creation failed (I/O Error):" << args[1];
        return Message{"ERROR 500 INTERNAL_ERROR", "Server"};
    }
};

/**
 * @class WriteCommand
 * @brief Overwrites an existing file.
 * @details args: [0] senderId, [1] filename, [2] content
 */
class WriteCommand : public ICommand {
public:
    Message execute(const QStringList& args) override {
        if (args.isEmpty() || !SecurityState::isAuthorized(args[0])) 
            return Message{"ERROR 401 UNAUTHORIZED", "Server"};

        if (args.size() < 3 || !isValidPath(args[1])) {
            EMIT_WARN() << "WRITE rejected: Invalid path or missing content. Sender:" << args[0];
            return Message{"ERROR 403 FORBIDDEN", "Server"};
        }

        QFile file(args[1]);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            file.write(args[2].toUtf8());
            EMIT_INFO() << "WRITE success:" << args[1] << "Size:" << args[2].size();
            return Message{"OK", "Server"};
        }

        EMIT_ERROR() << "WRITE failed: File not accessible:" << args[1];
        return Message{"ERROR 404 FILE_NOT_FOUND", "Server"};
    }
};

/**
 * @class AppendCommand
 * @brief Appends data to an existing file.
 * @details args: [0] senderId, [1] filename, [2] data
 */
class AppendCommand : public ICommand {
public:
    Message execute(const QStringList& args) override {
        if (args.isEmpty() || !SecurityState::isAuthorized(args[0])) 
            return Message{"ERROR 401 UNAUTHORIZED", "Server"};

        if (args.size() < 3 || !isValidPath(args[1])) 
            return Message{"ERROR 403 FORBIDDEN", "Server"};

        QFile file(args[1]);
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            file.write(args[2].toUtf8());
            EMIT_INFO() << "APPEND success to:" << args[1];
            return Message{"OK", "Server"};
        }
        return Message{"ERROR 500 INTERNAL_ERROR", "Server"};
    }
};

/**
 * @class ReadCommand
 * @brief Retrieves the content of a file.
 * @details args: [0] senderId, [1] filename
 */
class ReadCommand : public ICommand {
public:
    Message execute(const QStringList& args) override {
        if (args.isEmpty() || !SecurityState::isAuthorized(args[0])) 
            return Message{"ERROR 401 UNAUTHORIZED", "Server"};

        if (args.size() < 2 || !isValidPath(args[1])) 
            return Message{"ERROR 403 FORBIDDEN", "Server"};

        QFile file(args[1]);
        if (file.open(QIODevice::ReadOnly)) {
            QByteArray content = file.readAll();
            EMIT_INFO() << "READ success:" << args[1] << "Bytes sent:" << content.size();
            std::string res = "OK " + std::to_string(content.size()) + "\n" + content.toStdString();
            return Message{res, "Server"};
        }

        EMIT_WARN() << "READ failed: File not found:" << args[1];
        return Message{"ERROR 404 FILE_NOT_FOUND", "Server"};
    }
};

/**
 * @class ListCommand
 * @brief Lists all files in the server directory.
 * @details args: [0] senderId
 */
class ListCommand : public ICommand {
public:
    Message execute(const QStringList& args) override {
        if (args.isEmpty() || !SecurityState::isAuthorized(args[0])) 
            return Message{"ERROR 401 UNAUTHORIZED", "Server"};

        QDir dir(".");
        QStringList files = dir.entryList(QDir::Files | QDir::NoDotAndDotDot);
        EMIT_INFO() << "LIST command executed. Files found:" << files.size();

        QString response = QString("OK %1\n%2").arg(files.size()).arg(files.join("\n"));
        return Message{response.toStdString(), "Server"};
    }
};

/**
 * @class DeleteCommand
 * @brief Permanently removes a file.
 * @details args: [0] senderId, [1] filename
 */
class DeleteCommand : public ICommand {
public:
    Message execute(const QStringList& args) override {
        if (args.isEmpty() || !SecurityState::isAuthorized(args[0])) 
            return Message{"ERROR 401 UNAUTHORIZED", "Server"};

        if (args.size() < 2 || !isValidPath(args[1])) 
            return Message{"ERROR 403 FORBIDDEN", "Server"};

        if (QFile::remove(args[1])) {
            EMIT_INFO() << "DELETE success: File removed:" << args[1] << "by" << args[0];
            return Message{"OK", "Server"};
        }

        EMIT_WARN() << "DELETE failed: File missing or locked:" << args[1];
        return Message{"ERROR 404 FILE_NOT_FOUND", "Server"};
    }
};

/**
 * @class RenameCommand
 * @brief Renames a file from source to destination.
 * @details args: [0] senderId, [1] oldName, [2] newName
 */
class RenameCommand : public ICommand {
public:
    Message execute(const QStringList& args) override {
        if (args.isEmpty() || !SecurityState::isAuthorized(args[0])) 
            return Message{"ERROR 401 UNAUTHORIZED", "Server"};

        if (args.size() < 3 || !isValidPath(args[1]) || !isValidPath(args[2])) 
            return Message{"ERROR 403 FORBIDDEN", "Server"};

        if (QFile::rename(args[1], args[2])) {
            EMIT_INFO() << "RENAME success:" << args[1] << "->" << args[2];
            return Message{"OK", "Server"};
        }

        EMIT_ERROR() << "RENAME failed for path:" << args[1];
        return Message{"ERROR 500 INTERNAL_ERROR", "Server"};
    }
};

/**
 * @class InfoCommand
 * @brief Retrieves metadata (size and timestamp).
 * @details args: [0] senderId, [1] filename
 */
class InfoCommand : public ICommand {
public:
    Message execute(const QStringList& args) override {
        if (args.isEmpty() || !SecurityState::isAuthorized(args[0])) 
            return Message{"ERROR 401 UNAUTHORIZED", "Server"};

        if (args.size() < 2 || !isValidPath(args[1])) 
            return Message{"ERROR 403 FORBIDDEN", "Server"};

        QFileInfo info(args[1]);
        if (!info.exists()) {
            EMIT_WARN() << "INFO failed: File not found:" << args[1];
            return Message{"ERROR 404 FILE_NOT_FOUND", "Server"};
        }

        EMIT_DEBUG() << "INFO retrieved for:" << args[1];
        QString res = QString("OK size=%1 modified=%2")
                      .arg(info.size())
                      .arg(info.lastModified().toString(Qt::ISODate));
                      
        return Message{res.toStdString(), "Server"};
    }
};

} // namespace Chat
} // namespace CTI

#endif // FILECOMMANDS_HPP