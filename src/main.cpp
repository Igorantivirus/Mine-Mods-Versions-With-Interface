#include "MinecraftVersionsInterface.hpp"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MinecraftVersionsInterface w;
    w.show();
    return a.exec();
}
