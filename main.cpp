#include "EmbedExe.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EmbedExe w;
    w.show();

    return a.exec();
}
