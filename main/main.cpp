#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include "./windows/mainwindow.h"
#include "./windows/sqllib.h"
#include "./windows/managerW.h"
#include "./windows/dataBaseWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Screen w;
    w.resize(1920,1080);
    w.move(0, 0);
    w.show();
    // sql in init edilmesi
    DataBaseScreen w_3;
    int w_3_x = 800;
    int w_3_y = 500;
    w_3.move((1920-w_3_x)/2,(1080-w_3_y)/2);
    w_3.resize(w_3_x,w_3_y);
    w_3.show();
    //delTable("manager");
    //delTable("workers");
    delTable("persons");
    createPersonsTable();
    createManagerTable();
    createWorkersTable();
    int activeNum = signUp("emre","kaya","emre123");
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
