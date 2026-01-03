/** 
    @author: Mohamed Ashraf
    @email: mohamed.ashraf@coretech-innovations.com
    @date: Jan 2026
    @description: Standardized error emitter for CTI Chat Application.
                  Wraps Qt logging with context-aware metadata.
    @mohamedashraf-eng
*/

#ifndef ERROR_EMITTER_H
#   define ERROR_EMITTER_H

// Qt Depends
#   include <QDebug>
#   include <QDateTime>

// Std Depends
#   include <iostream>

/**
 * @brief Formatting helpers for the console output
 */
#   define CTI_LOG_FORMAT(level) \
        qUtf8Printable(QString("[%1][%2][%3]: ") \
            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz")) \
            .arg(__LINE__) \
            .arg(level))

/**
 * @section Log Levels Abstraction
 * 
 * CRITICAL and ERROR are always enabled for safety and security tracking.
 * INFO and WARN are toggled via the CTI_CHAT_VERBOSE_MODE flag.
 */

// 1. Critical Errors (System failure, Security Breach)
#   define EMIT_CRITICAL() qCritical().noquote() << CTI_LOG_FORMAT("CRITICAL")

// 2. Standard Errors (Recoverable errors, Socket drops)
#   define EMIT_ERROR()    qCritical().noquote() << CTI_LOG_FORMAT("ERROR")

#   if defined(CTI_CHAT_VERBOSE_MODE)

        // 3. Warnings (Potential issues, suspicious activity)
#       define EMIT_WARN() qWarning().noquote() << CTI_LOG_FORMAT("WARN")

        // 4. Info (Flow tracking, connection heartbeats)
#       define EMIT_INFO() qInfo().noquote() << CTI_LOG_FORMAT("INFO")

        // 5. Debug (Only for development-heavy logic)
#       define EMIT_DEBUG() qDebug().noquote() << CTI_LOG_FORMAT("DEBUG")

#   else
        // If Verbose is OFF, these macros expand to a no-op "Nothing Stream"
        // This ensures zero CPU/Memory overhead for logging in production.
#       define EMIT_WARN()  while(false) QMessageLogger().noDebug()
#       define EMIT_INFO()  while(false) QMessageLogger().noDebug()
#       define EMIT_DEBUG() while(false) QMessageLogger().noDebug()

#   endif /* defined(CTI_CHAT_VERBOSE_MODE) */

#endif /* ERROR_EMITTER_H */