#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include "./windows/mainwindow.h"
#include "./windows/sqllib.h"
#include "./windows/managerW.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Screen w;
    w.resize(1920,1080);
    w.move(0, 0);
    w.show();
    // sql in init edilmesi
    QSqlDatabase db = GenDb();
    //delTable("manager");
    //delTable("workers");
    createPersonsTable();
    createManagerTable();
    createWorkersTable();
    int activeNum = signUp("emre","emre123");
    qDebug() << activeNum;
    updateWorker(activeNum,"4x4",100,"1-1-1","3-3-3",5,5);
    qDebug() << isPersonWorking(activeNum);



    getStartFood(1);
    getFood(1);
    updateDailyExpense(1);
    getFood(1);
    QString list[400];
    getOwnedLandNums(-1,list);

    createLandTable();
    genGameTable(5,5);
    srand((unsigned) time(NULL));
    ManagerScreen w_2;
    w_2.show();
    return a.exec();
}
