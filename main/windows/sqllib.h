#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>

QSqlDatabase GenDb();
int IdPasswordControl(QString, QString);
int getMoney(int);
int getFood(int);
int getStuff(int);
void setMoney(int,int);
void setFood(int,int);
void setStuff(int,int);
void createTable();
void delTable();
