/** 
 * @file Client.hpp
 * @brief Definition of the TcpServer class, the entry point for network connections.
 * @author Mohamed Ashraf
 * @email mohamed.ashraf@coretech-innovations.com
 * @date Jan 2026
 * 
 */

#ifndef CLIENT_HPP
#define CLIENT_HPP

// Qt Depends
#include <QSocketNotifier>
#include <QTextStream>
#include <QTcpSocket>
#include <QTextStream>
#include <QObject>

// Other
#include <iostream>
#include <string>
#include <cstdio>
#include "error_emitter.hpp"

namespace CTI {
namespace Chat {

class ConsoleInputHandler : public QObject {
    Q_OBJECT
public:
    ConsoleInputHandler(QObject* parent = nullptr) : QObject(parent) {
        m_cin = new QTextStream(stdin);
        
        m_notifier = new QSocketNotifier(fileno(stdin), QSocketNotifier::Read, this);
        connect(m_notifier, &QSocketNotifier::activated, this, &ConsoleInputHandler::handleInput);
		EMIT_DEBUG() << "ConsoleInputHandler initialized.";
    }

signals:
    void inputReceived(const QString& input);

private slots:
    void handleInput() {
		EMIT_DEBUG() << "Console input received.";

		m_notifier->setEnabled(false);

		std::string line;
		auto& res = std::getline(std::cin, line);
		if(res) {
			QString input = QString::fromStdString(line);
			if(!input.isEmpty()) {
				emit inputReceived(input);
			}
		}

		m_notifier->setEnabled(true);
    }

private:
    QSocketNotifier* m_notifier;
    QTextStream* m_cin;
};

class Client : public QObject {
    Q_OBJECT
public:
    // Use a constructor to initialize pointers to nullptr
    Client(QObject* parent = nullptr) : QObject(parent), m_socket(nullptr), m_inputHandler(nullptr) {}

    void startConnection(QString ip, quint16 port) {
        if (!m_socket) m_socket = new QTcpSocket(this);
        if (!m_inputHandler) m_inputHandler = new ConsoleInputHandler(this);

        connect(m_socket, &QTcpSocket::connected, this, &Client::onConnected);
        connect(m_socket, &QTcpSocket::errorOccurred, this, &Client::onError);
        connect(m_socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
        
        // Connect input handler to sendMessage
        connect(m_inputHandler, &ConsoleInputHandler::inputReceived, this, &Client::sendMessage);

        EMIT_DEBUG() << "Connecting to host [" << ip << ", " << port << "]...";
        m_socket->connectToHost(ip, port);
    }

public slots:
    void sendMessage(const QString& message) {
		EMIT_DEBUG() << "Sending message:" << message;
        if(m_socket && m_socket->state() == QAbstractSocket::ConnectedState) {
            m_socket->write(message.toUtf8() + ";");
            m_socket->flush();
        }
    }

private slots:
    void onConnected() { EMIT_DEBUG() << "Connected to server."; }
    void onReadyRead() {
        EMIT_DEBUG() << "Received:" << m_socket->readAll();
    }
    void onError(QAbstractSocket::SocketError) {
        EMIT_DEBUG() << "Socket Error:" << m_socket->errorString();
    }

private:
    QTcpSocket* m_socket;
    ConsoleInputHandler* m_inputHandler;
};

} /* namespace Chat */
} /* namespace CTI */

#endif /* CLIENT_HPP */