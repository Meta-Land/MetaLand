#include <QDate>
#include "sqllib.h"
#include "mainwindow.h"

void createSchema(QString Schema){
    QSqlQuery create;
    create.prepare("CREATE SCHEMA `"+Schema+"` ;");
    create.exec();
    connectDataBaseSchema(Schema);
    //create tables
    createLandTable();
    createPersonsTable();
    createManagerTable();
    createBusinessTable();
    createWorkersTable();
    createMarketTable();
    createStoreTable();
    createLandagentTable();
    signUpRoot("root","root","root");
    initManager();
}

QSqlDatabase connectDataBase()
{
    //sql part
    QMessageBox msgBox;
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("EandE");
    //db.setDatabaseName("first_sql");
    if(db.open()){
        msgBox.setText("SQL Database Connection Done!");
    }else{
        msgBox.setText("SQL Database Connection Error!");
    }
    //msgBox.exec();
    return db;
}

bool connectDataBaseSchema(QString schema)
{
    //sql part
    QMessageBox msgBox;
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("EandE");
    db.setDatabaseName(schema);
    //db.setDatabaseName("first_sql");
    if(db.open()){
        msgBox.setText("SQL Database Connection Done!");
        //msgBox.exec();
        return true;
    }else{
        msgBox.setText("SQL Database Connection Error!");
        //msgBox.exec();
        return false;
    }
}

void delTable(QString table){
    QSqlQuery drop;
    drop.prepare("DROP TABLE "+table+"");
    drop.exec();
}

void createLandTable(){
    QSqlQuery create;
    create.prepare( "CREATE TABLE IF NOT EXISTS land (landNum VARCHAR(30) UNIQUE PRIMARY KEY,"
                   "landOwner INTEGER,"
                   "landType VARCHAR(30))");
    if(create.exec()){
        qDebug() << "land table created";
    }else{
        qDebug() << "land table not created";
    }
}

void createPersonsTable(){
    QSqlQuery create;
    create.prepare( "CREATE TABLE IF NOT EXISTS persons (num INTEGER UNIQUE PRIMARY KEY,"
                   "name VARCHAR(30),"
                   "surname VARCHAR(30),"
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

void createManagerTable(){
    QSqlQuery create;
    create.prepare( "CREATE TABLE IF NOT EXISTS manager (num INTEGER UNIQUE PRIMARY KEY,"
                   "startFood INTEGER,"
                   "startMoney INTEGER,"
                   "startStuff INTEGER,"
                   "dailyFoodExpense INTEGER,"
                   "dailyMoneyExpense INTEGER,"
                   "dailyStuffExpense INTEGER,"
                   "gameStartDate DATE,"
                   "gameSize VARCHAR(30),"
                   "placeOwnerFee INTEGER,"
                   "fixedIncome INTEGER,"
                   "fixedIncomeRate INTEGER)");
    if(create.exec()){
        qDebug() << "manager table created";
    }else{
        qDebug() << "manager table not created";
    }
    //initManager();
}

void createBusinessTable(){
    QSqlQuery create;
    create.prepare( "CREATE TABLE IF NOT EXISTS business (landNum VARCHAR(30) UNIQUE PRIMARY KEY,"
                   "businessType VARCHAR(30),"
                   "businessLevel INTEGER,"
                   "businessCapacity INTEGER,"
                   "businessWorkerCount INTEGER)");
    if(create.exec()){
        qDebug() << "business table created";
    }else{
        qDebug() << "business table not created";
    }
}

void createWorkersTable(){
    QSqlQuery create;
    create.prepare("CREATE TABLE IF NOT EXISTS workers (workerNo INTEGER UNIQUE PRIMARY KEY,"
                   "workinglandNum VARCHAR(30),"
                   "workerFee INTEGER,"
                   "startToWorkDate DATE,"
                   "stopToWorkDate DATE,"
                   "numberOfWorkingDays INTEGER,"
                   "workingHours INTEGER)");
    if(create.exec()){
        qDebug() << "workers table created";
    }else{
        qDebug() << "workers table not created";
    }
}

void createMarketTable(){
    QSqlQuery create;
    create.prepare("CREATE TABLE IF NOT EXISTS markets (landNum VARCHAR(30) UNIQUE PRIMARY KEY,"
                   "foodPrice INTEGER,"
                   "workerFee INTEGER,"
                   "numberOfWorkingDays INTEGER,"
                   "workingHours INTEGER)");
    if(create.exec()){
        qDebug() << "markets table created";
    }else{
        qDebug() << "markets table not created";
    }
}

void createStoreTable(){
    QSqlQuery create;
    create.prepare("CREATE TABLE IF NOT EXISTS stores (landNum VARCHAR(30) UNIQUE PRIMARY KEY,"
                   "stuffPrice INTEGER,"
                   "workerFee INTEGER,"
                   "numberOfWorkingDays INTEGER,"
                   "workingHours INTEGER)");
    if(create.exec()){
        qDebug() << "stores table created";
    }else{
        qDebug() << "stores table not created";
    }
}

void createLandagentTable(){
    QSqlQuery create;
    create.prepare("CREATE TABLE IF NOT EXISTS landagents (landNum VARCHAR(30) UNIQUE PRIMARY KEY,"
                   "stuffPrice INTEGER)");
    if(create.exec()){
        qDebug() << "landagents table created";
    }else{
        qDebug() << "landagents table not created";
    }
}

void getSchemas(QString *Schemas){
    QSqlQuery query;
    query.prepare("SHOW schemas;");
    query.exec();
    int x = 0;
    while (query.next()) {
        QString schemaName = query.value(0).toString();
        Schemas[x] = schemaName;
        x++;
    }
}

//eğer aranan isim ev parolada kişi bulunur ise o kişinin eşsiz verisi olan numarayı döndürür.
//bulunamazsa -1 döndürür
int IdPasswordControl(QString name,QString surname,QString password,QString managerPlayer){
    QSqlQuery query;
    query.prepare("SELECT * FROM persons WHERE name = '"+name+"' and surname = '"+surname+"' and passwd = '"+password+"'");
    query.exec();
    //query ilerliyorsa eşleşen bir data vardır yani id password eşleşmesi olumuştur.
    while (query.next()) {
        int num_get = query.value(0).toInt();
        qDebug() << num_get;
        if(managerPlayer == "player"){
            if(num_get == 0){
                return -1;
            }
            return num_get;
        }else{
            qDebug() <<"here" << num_get;
            if(num_get == 0){
                qDebug() <<"here";
                return num_get;
            }
        }
    }
    qDebug() << name << surname << password;
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

int IdControl(QString name, QString surname){
    QSqlQuery query;
    query.prepare("SELECT * FROM persons WHERE name = '"+name+"' and surname = '"+surname+"'");
    query.exec();
    //query ilerliyorsa eşleşen bir data vardır yani id password eşleşmesi olumuştur.
    while (query.next()) {
        int num_get = query.value(0).toInt();
        qDebug() << num_get;
        return num_get;
    }
    qDebug() << name;
    return -1;
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

QString getPersonName(int num){
    QSqlQuery query;
    query.prepare("SELECT name FROM persons WHERE num = '"+QString::number(num)+"'");
    query.exec();
    query.next();
    QString gMoney = query.value(0).toString();
    qDebug() << gMoney;
    return gMoney;
}

QString getPersonSurname(int num){
    QSqlQuery query;
    query.prepare("SELECT surname FROM persons WHERE num = '"+QString::number(num)+"'");
    query.exec();
    query.next();
    QString gMoney = query.value(0).toString();
    qDebug() << gMoney;
    return gMoney;
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


int initManager(){
    QDate cd = QDate::currentDate();
    QString value = cd.toString("yyyy-MM-dd");
    QSqlQuery query;
    query.prepare("INSERT INTO `manager`  VALUES (:num, :startFood, :startMoney,:startStuff,"
                  ":dailyFoodExpense, :dailyMoneyExpense, :dailyStuffExpense, :gameStartDate, :gameSize, :placeOwnerFee,"
                  ":fixedIncome, :fixedIncomeRate);");
    query.bindValue(":num", 1);
    query.bindValue(":startFood", 50);
    query.bindValue(":startMoney", 50);
    query.bindValue(":startStuff", 50);
    query.bindValue(":dailyFoodExpense", 10);
    query.bindValue(":dailyMoneyExpense", 10);
    query.bindValue(":dailyStuffExpense", 10);
    query.bindValue(":gameStartDate", value);
    query.bindValue(":gameSize", "5x5");
    query.bindValue(":placeOwnerFee", 20);
    query.bindValue(":fixedIncome", 20);
    query.bindValue(":fixedIncomeRate", 20);
    if(query.exec()){
        genGameTable(5,5);
        return 1;
    }else{
        return 0;
    }
}

int initManager(int startFood,int startMoney,int startStuff,int dailyFoodExpense,
                int dailyMoneyExpense,int dailyStuffExpense,QString gameStartDate,QString gameSize,
                int placeOwnerFee, int fixedIncome, int fixedIncomeRate){
    delTable("manager");
    createManagerTable();
    QSqlQuery query;
    query.prepare("INSERT INTO `manager`  VALUES (:num, :startFood, :startMoney, :startStuff,"
                  " :dailyFoodExpense, :dailyMoneyExpense, :dailyStuffExpense, :gameStartDate, :gameSize, :placeOwnerFee,"
                  " :fixedIncome, :fixedIncomeRate);");
    query.bindValue(":num", 1);
    query.bindValue(":startFood", startFood);
    query.bindValue(":startMoney", startMoney);
    query.bindValue(":startStuff", startStuff);
    query.bindValue(":dailyFoodExpense", dailyFoodExpense);
    query.bindValue(":dailyMoneyExpense", dailyMoneyExpense);
    query.bindValue(":dailyStuffExpense", dailyStuffExpense);
    query.bindValue(":gameStartDate", gameStartDate);
    query.bindValue(":gameSize", gameSize);
    query.bindValue(":placeOwnerFee", placeOwnerFee);
    query.bindValue(":fixedIncome", fixedIncome);
    query.bindValue(":fixedIncomeRate", fixedIncomeRate);
    if(query.exec()){
        QString gameSize=getGameSize(1);
        QString r=gameSize[0];
        QString c=gameSize[2];
        genGameTable(r.toInt(),c.toInt());
        qDebug() << "okey";
        return 1;
    }else{
        return 0;
    }
}


int getStartFood(int numberOfManager = 1)
{
    QSqlQuery query;
    query.prepare("SELECT startFood FROM manager WHERE num = '"+QString::number(numberOfManager)+"'");
    query.exec();
    query.next();
    int gMoney = query.value(0).toInt();
    qDebug() << gMoney;
    return gMoney;
}

int getStartMoney(int numberOfManager = 1)
{
    QSqlQuery query;
    query.prepare("SELECT startMoney FROM manager WHERE num = '"+QString::number(numberOfManager)+"'");
    query.exec();
    query.next();
    int gMoney = query.value(0).toInt();
    qDebug() << gMoney;
    return gMoney;
}

int getStartStuff(int numberOfManager = 1)
{
    QSqlQuery query;
    query.prepare("SELECT startStuff FROM manager WHERE num = '"+QString::number(numberOfManager)+"'");
    query.exec();
    query.next();
    int gMoney = query.value(0).toInt();
    qDebug() << gMoney;
    return gMoney;
}

int getDailyFoodExpense(int numberOfManager = 1)
{
    QSqlQuery query;
    query.prepare("SELECT dailyFoodExpense FROM manager WHERE num = '"+QString::number(numberOfManager)+"'");
    query.exec();
    query.next();
    int gMoney = query.value(0).toInt();
    qDebug() << gMoney;
    return gMoney;
}

int getDailyMoneyExpense(int numberOfManager = 1)
{
    QSqlQuery query;
    query.prepare("SELECT dailyMoneyExpense FROM manager WHERE num = '"+QString::number(numberOfManager)+"'");
    query.exec();
    query.next();
    int gMoney = query.value(0).toInt();
    qDebug() << gMoney;
    return gMoney;
}

int getDailyStuffExpense(int numberOfManager = 1)
{
    QSqlQuery query;
    query.prepare("SELECT dailyStuffExpense FROM manager WHERE num = '"+QString::number(numberOfManager)+"'");
    query.exec();
    query.next();
    int gMoney = query.value(0).toInt();
    qDebug() << gMoney;
    return gMoney;
}

QString getGameStartDate(int numberOfManager = 1)
{
    QSqlQuery query;
    query.prepare("SELECT gameStartDate FROM manager WHERE num = '"+QString::number(numberOfManager)+"'");
    query.exec();
    query.next();
    QString gameStartDate = query.value(0).toString();
    qDebug() << gameStartDate;
    return gameStartDate;
}

QString getGameSize(int numberOfManager = 1)
{
    QSqlQuery query;
    query.prepare("SELECT gameSize FROM manager WHERE num = '"+QString::number(numberOfManager)+"'");
    query.exec();
    query.next();
    QString gameSize = query.value(0).toString();
    qDebug() << gameSize;
    return gameSize;
}

int getPlaceOwnerFee(int numberOfManager = 1)
{
    QSqlQuery query;
    query.prepare("SELECT placeOwnerFee FROM manager WHERE num = '"+QString::number(numberOfManager)+"'");
    query.exec();
    query.next();
    int placeOwnerFee = query.value(0).toInt();
    qDebug() << placeOwnerFee;
    return placeOwnerFee;
}

int getfixedIncome(int numberOfManager = 1)
{
    QSqlQuery query;
    query.prepare("SELECT fixedIncome FROM manager WHERE num = '"+QString::number(numberOfManager)+"'");
    query.exec();
    query.next();
    int fixedIncome = query.value(0).toInt();
    qDebug() << fixedIncome;
    return fixedIncome;
}

int getfixedIncomeRate(int numberOfManager = 1)
{
    QSqlQuery query;
    query.prepare("SELECT fixedIncomeRate FROM manager WHERE num = '"+QString::number(numberOfManager)+"'");
    query.exec();
    query.next();
    int fixedIncomeRate = query.value(0).toInt();
    qDebug() << fixedIncomeRate;
    return fixedIncomeRate;
}

void setStartFood(int numberOfManager, int startFood)
{
    QSqlQuery query;
    query.prepare("UPDATE manager SET startFood = '"+ QString::number(startFood) +"' WHERE num = '"+QString::number(numberOfManager)+"'");
    query.exec();
}

void setStartMoney(int numberOfManager, int startMoney)
{
    QSqlQuery query;
    query.prepare("UPDATE manager SET startMoney = '"+ QString::number(startMoney) +"' WHERE num = '"+QString::number(numberOfManager)+"'");
    query.exec();
}

void setStartStuff(int numberOfManager, int startStuff)
{
    QSqlQuery query;
    query.prepare("UPDATE manager SET startStuff = '"+ QString::number(startStuff) +"' WHERE num = '"+QString::number(numberOfManager)+"'");
    query.exec();
}

int signUp(QString name,QString surname,QString password){
    //eğer bu isimde birisi bulunmadıysa
    int num = getBigestNum()+1;
    if(IdControl(name, surname) == -1){
        QSqlQuery query;
        query.prepare("INSERT INTO `persons`  VALUES "
                            "("+QString::number(num)+",'"+name+"','"+surname+"','"+password+"',"+QString::number(getStartFood())+","
                            ""+QString::number(getStartMoney())+","+QString::number(getStartStuff())+");");
    if(query.exec()){}
    }else{
        QMessageBox msgBox;
        msgBox.setText("Bu Kullanıcı Adı Zaten Kullanımda!");
        msgBox.exec();
    }
    return num;
}

void signUpRoot(QString name,QString surname,QString password){
    //eğer bu isimde birisi bulunmadıysa
    if(IdControl(name, surname) == -1){
        QSqlQuery query;
        query.prepare("INSERT INTO `persons`  VALUES "
                      "("+QString::number(0)+",'"+name+"','"+surname+"','"+password+"',"+QString::number(getStartFood())+","
                                                                                                                                           ""+QString::number(getStartMoney())+","+QString::number(getStartStuff())+");");
        if(query.exec()){}
    }else{
        QMessageBox msgBox;
        msgBox.setText("Bu Kullanıcı Adı Zaten Kullanımda!");
        msgBox.exec();
    }
}

void updateDailyExpense(int personNum){
    int food = getFood(personNum);
    int money = getMoney(personNum);
    int stuff = getStuff(personNum);
    food -= getDailyFoodExpense();
    money -= getDailyMoneyExpense();
    stuff -= getDailyStuffExpense();
    setFood(personNum,food);
    setMoney(personNum,money);
    setStuff(personNum,stuff);
}

int getBigestLandNum(){
    QSqlQuery query;
    query.prepare("SELECT MAX(landNum) From land");
    if(query.exec()){
        while (query.next()) {
            int num_get = query.value(0).toInt();
            qDebug() << num_get;
            return num_get;
        }
    }
    return -1;
}

void initLand(QString landNum, int landOwner, QString landType){
    QSqlQuery query;
    query.prepare("INSERT INTO `land`  VALUES (:landNum, :landOwner, :landType)");
    query.bindValue(":landNum", landNum);
    query.bindValue(":landOwner", landOwner);
    query.bindValue(":landType", landType);
    query.exec();
}

void genLands(int x, int y){
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            initLand(QString::number(i)+"x"+QString::number(j),-1,"land");
        }
    }
}

void setLandType(QString landNum, QString landType)
{
    QSqlQuery query;
    query.prepare("UPDATE land SET landType = '"+landType+"' WHERE landNum = '"+landNum+"'");
    query.exec();
}

QString getLandType(QString landNum)
{
    QSqlQuery query;
    query.prepare("SELECT LandType FROM land WHERE landNum = '"+landNum+"'");
    query.exec();
    query.next();
    QString LandType = query.value(0).toString();
    qDebug() << LandType;
    return LandType;
}
//////////////////
QString getLandOwnerName(QString landNum)
{
    QSqlQuery query;
    query.prepare("SELECT persons.name FROM land, persons WHERE land.landNum = '"+landNum+"' AND land.landOwner=persons.num");
    query.exec();
    query.next();
    QString LandOwnerName = query.value(0).toString();
    qDebug() << LandOwnerName;
    return LandOwnerName;
}

QString getLandOwnerNum(QString landNum)
{
    QSqlQuery query;
    query.prepare("SELECT landOwner FROM land WHERE landNum = '"+landNum+"'");
    query.exec();
    query.next();
    QString LandOwnerNum = query.value(0).toString();
    qDebug() << LandOwnerNum;
    return LandOwnerNum;
}

void setLandOwner(QString landNum, int landOwner)
{
    QSqlQuery query;
    query.prepare("UPDATE land SET landOwner = '"+QString::number(landOwner)+"' WHERE landNum = '"+landNum+"'");
    query.exec();
}

void genGameTable(int x, int y){
    genLands(x,y);
    int marketX = rand()%x;
    int marketY = rand()%y;
    setLandType(QString::number(marketX)+"x"+QString::number(marketY),"market");
    int storeX = rand()%x;
    int storeY = rand()%y;
    //aynı noktayı hem market hem store emlakçı atanmaması için döngüler
    while(marketX == storeX and marketY == storeY){
        storeX = rand()%x;
        storeY = rand()%y;
    }
    setLandType(QString::number(storeX)+"x"+QString::number(storeY),"store");
    int landAgentX = rand()%x;
    int landAgentY = rand()%y;
    while((marketX == landAgentX and marketY == landAgentY)and(storeX == landAgentX and storeY == landAgentY)){
        landAgentX = rand()%x;
        landAgentY = rand()%y;
    }
    setLandType(QString::number(landAgentX)+"x"+QString::number(landAgentY),"landAgent");
}

void setBussinessType(QString landNum, QString businessType)
{
    QSqlQuery query;
    query.prepare("UPDATE business SET businessType = '"+businessType+"' WHERE landNum = '"+landNum+"'");
    query.exec();
}

void setBussinessLevel(QString landNum, int businessLevel)
{
    QSqlQuery query;
    query.prepare("UPDATE business SET businessType = '"+QString::number(businessLevel)+"' WHERE landNum = '"+landNum+"'");
    query.exec();
}

void setBussinessCapacity(QString landNum, int businessCapacity)
{
    QSqlQuery query;
    query.prepare("UPDATE business SET businessType = '"+QString::number(businessCapacity)+"' WHERE landNum = '"+landNum+"'");
    query.exec();
}

void setBussinessWorkerCount(QString landNum, int businessWorkerCount)
{
    QSqlQuery query;
    query.prepare("UPDATE business SET workerCount = '"+QString::number(businessWorkerCount)+"' WHERE landNum = '"+landNum+"'");
    query.exec();
}

QString getBussinessType(QString landNum)
{
    QSqlQuery query;
    query.prepare("SELECT businessType FROM business WHERE landNum = '"+landNum+"'");
    query.exec();
    query.next();
    QString businessType = query.value(0).toString();
    qDebug() << businessType;
    return businessType;
}


int getBussinessLevel(QString landNum)
{
    QSqlQuery query;
    query.prepare("SELECT businessType FROM business WHERE landNum = '"+landNum+"'");
    query.exec();
    query.next();
    int bussinessLevel = query.value(0).toInt();
    qDebug() << bussinessLevel;
    return bussinessLevel;
}

int getBussinessCapacity(QString landNum)
{
    QSqlQuery query;
    query.prepare("SELECT businessType FROM business WHERE landNum = '"+landNum+"'");
    query.exec();
    query.next();
    int bussinessCapacity = query.value(0).toInt();
    qDebug() << bussinessCapacity;
    return bussinessCapacity;
}

int getBussinessWorkerCount(QString landNum)
{
    QSqlQuery query;
    query.prepare("SELECT workerCount FROM business WHERE landNum = '"+landNum+"'");
    query.exec();
    query.next();
    int bussinessWorkerCount = query.value(0).toInt();
    qDebug() << bussinessWorkerCount;
    return bussinessWorkerCount;
}


int getOwnedLandNums(int landOwner, QString *landNumList){
    QSqlQuery query;
    query.prepare("SELECT landNum FROM land WHERE landOwner = '"+QString::number(landOwner)+"'");
    query.exec();
    int x = 0;
    while (query.next()) {
        QString landNum = query.value(0).toString();
        qDebug() << landNum;
        landNumList[x] = landNum;
        x += 1;
    }
    return x;
}

void bussinessLevelUp(QString landNum){
    int level = getBussinessLevel(landNum);
    int capacity = getBussinessCapacity(landNum);
    //level 3 ten fazla ise arttırmaz
    //(1. seviye - 3 oyuncu; 2. seviye-6 oyuncu; 3. seviye 12 oyuncu)
    if(level<3){
        setBussinessLevel(landNum,level+1);
        setBussinessCapacity(landNum,capacity*2);
    }
}

void newWorker(int workerNo, QString workinglandNum, int workerFee,QString startToWorkDate,
               QString stopToWorkDate, int numberOfWorkingDays, int workingHours){
    QSqlQuery query;
    query.prepare("INSERT INTO `workers` VALUES (:workerNo, :workinglandNum, :workerFee, :startToWorkDate,"
                  ":stopToWorkDate, :numberOfWorkingDays, :workingHours);");
    query.bindValue(":workerNo", workerNo);
    query.bindValue(":workinglandNum", workinglandNum);
    query.bindValue(":workerFee", workerFee);
    query.bindValue(":startToWorkDate", startToWorkDate);
    query.bindValue(":stopToWorkDate", stopToWorkDate);
    query.bindValue(":numberOfWorkingDays", numberOfWorkingDays);
    query.bindValue(":workingHours", workingHours);
    if(query.exec()){

    }else{
        qDebug()<<"new Worker error";
    }
    int workerC = getBussinessWorkerCount(workinglandNum);
    setBussinessWorkerCount(workinglandNum,workerC+1);
}

void newMarket(QString landNum, int foodPrice,int workerFee, int numberOfWorkingDays, int workingHours){
    QSqlQuery query;
    query.prepare("INSERT INTO `markets` VALUES (:landNum, :foodPrice, :workerFee,"
                  " :numberOfWorkingDays, :workingHours);");
    query.bindValue(":landNum", landNum);
    query.bindValue(":foodPrice", foodPrice);
    query.bindValue(":workerFee", workerFee);
    query.bindValue(":numberOfWorkingDays", numberOfWorkingDays);
    query.bindValue(":workingHours", workingHours);
}

void newStore(QString landNum, int stuffPrice,int workerFee, int numberOfWorkingDays, int workingHours){
    QSqlQuery query;
    query.prepare("INSERT INTO `stores` VALUES (:landNum, :stuffPrice, :workerFee,"
                  " :numberOfWorkingDays, :workingHours););");
    query.bindValue(":landNum", landNum);
    query.bindValue(":stuffPrice", stuffPrice);
    query.bindValue(":workerFee", workerFee);
    query.bindValue(":numberOfWorkingDays", numberOfWorkingDays);
    query.bindValue(":workingHours", workingHours);
}

int getMarketWorkerFee(QString landNum){
    QSqlQuery query;
    query.prepare("SELECT workerFee FROM markets WHERE landNum = '"+landNum+"'");
    query.exec();
    query.next();
    int workerFee = query.value(0).toInt();
    qDebug() << workerFee;
    return workerFee;
}

int getMarketStuffPrice(QString landNum){
    QSqlQuery query;
    query.prepare("SELECT stuffPrice FROM markets WHERE landNum = '"+landNum+"'");
    query.exec();
    query.next();
    int stuffPrice = query.value(0).toInt();
    qDebug() << stuffPrice;
    return stuffPrice;
}

int getMarketNumberOfWorkingDays(QString landNum){
    QSqlQuery query;
    query.prepare("SELECT numberOfWorkingDays FROM markets WHERE landNum = '"+landNum+"'");
    query.exec();
    query.next();
    int numberOfWorkingDays = query.value(0).toInt();
    qDebug() << numberOfWorkingDays;
    return numberOfWorkingDays;
}

int getMarketWorkingHours(QString landNum){
    QSqlQuery query;
    query.prepare("SELECT workingHours FROM markets WHERE landNum = '"+landNum+"'");
    query.exec();
    query.next();
    int workingHours = query.value(0).toInt();
    qDebug() << workingHours;
    return workingHours;
}

void updateWorker(int workerNo, QString workinglandNum, int workerFee,QString startToWorkDate,
               QString stopToWorkDate, int numberOfWorkingDays, int workingHours){
    QSqlQuery query;
    query.prepare("UPDATE `workers` SET  workinglandNum = :workinglandNum, workerFee = :workerFee, startToWorkDate =  :startToWorkDate,"
                  " stopToWorkDate = :stopToWorkDate, numberOfWorkingDays = :numberOfWorkingDays, workingHours = :workingHours WHERE workerNo = :workerNo");
    query.bindValue(":workerNo", workerNo);
    query.bindValue(":workinglandNum", workinglandNum);
    query.bindValue(":workerFee", workerFee);
    query.bindValue(":startToWorkDate", startToWorkDate);
    query.bindValue(":stopToWorkDate", stopToWorkDate);
    query.bindValue(":numberOfWorkingDays", numberOfWorkingDays);
    query.bindValue(":workingHours", workingHours);
    if(query.exec()){

    }else{
        qDebug()<<"update Worker error";
    }
}

int getWorkerFee(int workerNo){
    {
        QSqlQuery query;
        query.prepare("SELECT workerFee FROM workers WHERE workerNo = '"+QString::number(workerNo)+"'");
        query.exec();
        query.next();
        int workerFee = query.value(0).toInt();
        qDebug() << workerFee;
        return workerFee;
    }
}

int* getContractEndedWorkers(QString date){
    QSqlQuery query;
    query.prepare("SELECT workerNo FROM workers WHERE stopToWorkDate < "+ date +";");
    query.exec();
    static int contractEndedList[50];
    int counter = 0;
    while (query.next()) {
        int num_get = query.value(0).toInt();
        qDebug() << num_get;
        contractEndedList[counter] = num_get;
        counter +=1;
    }
    qDebug() << "data";
    return contractEndedList;
}

void delContractEndedWorkers(QString date){
    int * list = getContractEndedWorkers(date);
    for(int i = 0;i<50;i++){
        if(list[i] != 0){
            QSqlQuery query;
            query.prepare("DELETE FROM persons WHERE (`workerNo`='"+ QString::number(list[i]) +"');");
            query.exec();
        }
    }
}

int * getWorkers(){
    QSqlQuery query;
    query.prepare("SELECT workerNo FROM workers;");
    query.exec();
    static int workerList[100];
    int counter = 0;
    while (query.next()) {
        int num_get = query.value(0).toInt();
        qDebug() << num_get;
        workerList[counter] = num_get;
        counter +=1;
    }
    qDebug() << "data";
    return workerList;
}

int * getWorkersAtBussiness(QString workinglandNum){
    QSqlQuery query;
    query.prepare("SELECT workerNo FROM workers WHERE workinglandNum = "+ workinglandNum +";");
    query.exec();
    static int workerList[12];
    int counter = 0;
    while (query.next()) {
        int num_get = query.value(0).toInt();
        qDebug() << num_get;
        workerList[counter] = num_get;
        counter +=1;
    }
    qDebug() << "data";
    return workerList;
}

QString getWorkingLand(int num){
    QSqlQuery query;
    query.prepare("SELECT workinglandNum FROM workers WHERE workerNo = "+ QString::number(num) +";");
    query.exec();
    while (query.next()) {
        return query.value(0).toString();
    }
}

int * getWorkersAtMarket(){
    int* worker = getWorkers();
    static int marketWorkers[50];
    int markettercount = 0;
    for(int i =0;i<100;i++){
        if(worker[i] != 0){
            QString land = getWorkingLand(worker[i]);
            QString landType = getLandType(land);
            if(landType == "market"){
                marketWorkers[markettercount] = worker[i];
                qDebug() << worker[i];
            }
        }
    }
    return marketWorkers;
}

int * getWorkersAtStore(){
    int* worker = getWorkers();
    static int marketWorkers[50];
    int markettercount = 0;
    for(int i =0;i<100;i++){
        if(worker[i] != 0){
            QString land = getWorkingLand(worker[i]);
            QString landType = getLandType(land);
            if(landType == "market"){
                marketWorkers[markettercount] = worker[i];
                qDebug() << worker[i];
            }
        }
    }
    return marketWorkers;
}

int * getWorkersAtLandAgent(){
    int* worker = getWorkers();
    static int landAgentWorkers[50];
    int agentercount = 0;
    for(int i =0;i<100;i++){
        if(worker[i] != 0){
            QString land = getWorkingLand(worker[i]);
            QString landType = getLandType(land);
            if(landType == "landAgent"){
                landAgentWorkers[agentercount] = worker[i];
                qDebug() << worker[i];
            }
        }
    }
    return landAgentWorkers;
}


bool isPersonWorking(int num){
    QSqlQuery query;
    query.prepare("SELECT * FROM workers WHERE workerNo = "+ QString::number(num) +";");
    query.exec();
    while (query.next()) {
        return true;
    }
    return false;
}

/*
    KULLANICI TABLOSU GEREKLİLİKLER
    "Kullanıcı no"
    "kullanıcı adı"
    "kullanıcı soyadı"
    "kullanıcı şifresi"
    "kullanıcı yemek miktarı,"
    "kullanıcı eşyamiktarı,"
    "kullanıcı para miktarı,"

    YÖNETİCİ TABLOSUNDA BULUNACAK OLANLAR
    "başlangıç yemek miktarı,"
    "başlangıç eşya miktarı,"
    "başlangıç para miktarı,"
    "günlük yiyecek gideri,"
    "günlük eşya gideri,"
    "günlük para gideri,"
    "oyun başlangıç tarihi"
    "oyun alan boyutu (karesel alan 3x4 gibi)"
    //bir işletme yöneticisinin alacağı yönetici tarafından belirlenen değer
    "yönetici işletme ücreti,"
    "işletme sabit gelir miktarı,"
    "işletme sabit gelir oranı,"

    ALAN TABLOSUNDA BULUNACAK OLANLAR
    "(karesel) alan no,"
    "alan türü (arsa veyaişletme),"
    "alan sahibi," // user no

    İŞLETME TABLOSUNDA BULUNACAK OLANLAR
    "(karesel) alan no,"
    "işletme türü(market,mağaza,emlak),"
    "işletme seviyesi,"
    "işletme kapasitesi,"
    "işletme çalışan sayısı,"

    //işletmede kullanıcıya bağlı değişen veriler
    WORKERS TABLOSUNDA BULUNACAK OLANLAR
    "(karesel) çalışılan alan no,"
    "Kullanıcı no"
    "kullanıcı işletme ücreti,"
    "kullanıcı çalışma başlangıç tarihi,"
    "kullanıcı çalışma bitiş tarihi,"
    "kullanıcı çalışma gün sayısı,"
    "kullanıcı çalışma saatleri,"

    MARKET TABLOSU BULUNACAK OLANLAR
    "market yiyecek ücreti,"

    MAĞAZA TABLOSU BULUNACAK OLANLAR
    "mağaza eşya ücreti,"
    EMLAK TABLOSU BULUNACAK OLANLAR
    "işletme fiyatı,"
    "kiralık işletme fiyatı,"
    "emlak komisyonu,"
    "emlak işlemi (kira-satış),"

    "kira süresi,"
    "satış tarihi,"
    "kiralama tarihi,"
    "kira bitiş tarihi,"
    "işlemin yapıldığı emlak,"
    "işletme mevcut seviye"
*/
