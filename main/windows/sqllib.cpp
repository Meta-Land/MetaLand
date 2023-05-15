#include "sqllib.h"
#include "mainwindow.h"

//eğer aranan isim ev parolada kişi bulunur ise o kişinin eşsiz verisi olan numarayı döndürür.
//bulunamazsa -1 döndürür
int IdPasswordControl(QString id,QString password)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM persons WHERE id = '"+id+"' and passwd = '"+password+"'");
    query.exec();
    //query ilerliyorsa eşleşen bir data vardır yani id password eşleşmesi olumuştur.
    while (query.next()) {
        int num_get = query.value(0).toInt();
        qDebug() << num_get;
        return num_get;
    }
    qDebug() << id << password;
    return -1;
}

// değerleri 0 ve ya altında olanları döndürür
int * getEliminated(){
    QSqlQuery query;
    query.prepare("SELECT * FROM persons WHERE money <= 0 OR food <= 0 OR stuff <= 0;");
    query.exec();
    static int eliminatedList[10];
    int counter = 0;
    while (query.next()) {
        int num_get = query.value(0).toInt();
        qDebug() << num_get;
        eliminatedList[counter] = num_get;
        counter +=1;
    }
    qDebug() << "data";
    return eliminatedList;
}

void delEliminated(){
    int * list = getEliminated();
    for(int i = 0;i<10;i++){
        if(list[i] != 0){
            QSqlQuery query;
            query.prepare("DELETE FROM persons WHERE (`num`='"+ QString::number(list[i]) +"');");
            query.exec();
        }
    }
}

int IdControl(QString id){
    QSqlQuery query;
    query.prepare("SELECT * FROM persons WHERE id = '"+id+"'");
    query.exec();
    //query ilerliyorsa eşleşen bir data vardır yani id password eşleşmesi olumuştur.
    while (query.next()) {
        int num_get = query.value(0).toInt();
        qDebug() << num_get;
        return num_get;
    }
    qDebug() << id;
    return -1;
}

int signUp(QString id,QString password){
    if(IdControl(id) == -1){
        int num = getBigestNum()+1;
        QSqlQuery query;
        query.prepare("INSERT INTO `persons`  VALUES ("+QString::number(num)+",'"+id+"','"+password+"',0,0,0);");
        if(query.exec()){
            return 1;
        }else{
            return 0;
        }
    }else{
        QMessageBox msgBox;
        msgBox.setText("Bu Kullanıcı Adı Zaten Kullanımda!");
        msgBox.exec();
        return 0;
    }
}

int getBigestNum(){
    QSqlQuery query;
    query.prepare("SELECT MAX(num) From persons");
    if(query.exec()){
        while (query.next()) {
            int num_get = query.value(0).toInt();
            qDebug() << num_get;
            return num_get;
        }
    }
    return -1;
}

int getMoney(int numberOfPerson)
{
    QSqlQuery query;
    query.prepare("SELECT money FROM persons WHERE num = '"+QString::number(numberOfPerson)+"'");
    query.exec();
    query.next();
    int gMoney = query.value(0).toInt();
    qDebug() << gMoney;
    return gMoney;
}

int getFood(int numberOfPerson)
{
    QSqlQuery query;
    query.prepare("SELECT food FROM persons WHERE num = '"+QString::number(numberOfPerson)+"'");
    query.exec();
    query.next();
    int gFood = query.value(0).toInt();
    qDebug() << gFood;
    return gFood;
}

int getStuff(int numberOfPerson)
{
    QSqlQuery query;
    query.prepare("SELECT stuff FROM persons WHERE num = '"+QString::number(numberOfPerson)+"'");
    query.exec();
    query.next();
    int gStuff = query.value(0).toInt();
    qDebug() << gStuff;
    return gStuff;
}

void setMoney(int numberOfPerson, int money)
{
    QSqlQuery query;
    query.prepare("UPDATE persons SET money = '"+ QString::number(money) +"' WHERE num = '"+QString::number(numberOfPerson)+"'");
    query.exec();
}

void setFood(int numberOfPerson, int food)
{
    QSqlQuery query;
    query.prepare("UPDATE persons SET food = '"+ QString::number(food) +"' WHERE num = '"+QString::number(numberOfPerson)+"'");
    query.exec();
}

void setStuff(int numberOfPerson, int stuff)
{
    QSqlQuery query;
    query.prepare("UPDATE persons SET stuff = '"+ QString::number(stuff) +"' WHERE num = '"+QString::number(numberOfPerson)+"'");
    query.exec();
}

void createTable(){
    QSqlQuery create;
    create.prepare( "CREATE TABLE IF NOT EXISTS persons (num INTEGER UNIQUE PRIMARY KEY,"
                   "id VARCHAR(30),"
                   "passwd VARCHAR(30),"
                   "money INTEGER,"
                   "food INTEGER,"
                   "stuff INTEGER)");
    if(create.exec()){
        qDebug() << "table created";
    }else{
        qDebug() << "table not created";
    }
}

void delTable(){
    QSqlQuery drop;
    drop.prepare("DROP TABLE persons");
    drop.exec();
}

QSqlDatabase GenDb()
{
    //sql part
    QMessageBox msgBox;
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("EandE");
    db.setDatabaseName("first_sql");
    if(db.open()){
        msgBox.setText("SQL Database Connection Done!");
    }else{
        msgBox.setText("SQL Database Connection Error!");
    }
    msgBox.exec();
    return db;
}
