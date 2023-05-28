#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include "./windows/mainwindow.h"
#include "./windows/sqllib.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Screen w;
    w.resize(1920,1080);
    w.move(0, 0);
    w.show();
    srand((unsigned) time(NULL));
    return a.exec();
}
