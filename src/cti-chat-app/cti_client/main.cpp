/** 
    @author: Mohamed Ashraf
    @email: mohamed.ashraf@coretech-innovations.com
    @date: Jan 2026
    @description: A TCP based chat application using QT framework.

    @mohamedashraf-eng
*/
// Qt Depends
#include <QCoreApplication>
// Std Depends
#include <iostream>
#include <memory>
// Other Depends
#include "error_emitter.hpp"
#include "constants.hpp" 
#include "Client.hpp"

using namespace CTI::Chat; 

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    std::shared_ptr<Client> client = std::make_shared<Client>();

    client->startConnection(
        Constants::DEFAULT_HOST, 
        Constants::DEFAULT_PORT);
    
    // client->startMessageListener();

    return a.exec();    
}