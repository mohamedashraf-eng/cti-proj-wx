/** 
    @author: Mohamed Ashraf
    @email: mohamed.ashraf@coretech-innovations.com
    @date: Jan 2026
    @description: A TCP based chat application using QT framework.

    @mohamedashraf-eng
*/

#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>

#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::cout << "Hello QT\n";

    return a.exec();
}
