/** 
    @author: Mohamed Ashraf
    @email: mohamed.ashraf@coretech-innovations.com
    @date: Jan 2026
    @description: A TCP based chat application using QT framework.

    @mohamedashraf-eng
*/
// Qt Depends
#include <QCoreApplication>
#include <QSocketNotifier>
// Std Depends
#include <iostream>
// Other Depends
#include "error_emitter.hpp"

// using namespace CTI::Chat; 

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    return a.exec();
}
