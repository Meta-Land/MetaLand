#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>

void createSchema(QString Schema);
QSqlDatabase connectDataBase();
bool connectDataBaseSchema(QString schema);
void getSchemas(QString *Schemas);
int IdPasswordControl(QString,QString, QString,QString);
int IdControl(QString name,QString surname);
int getMoney(int);
int getFood(int);
int getStuff(int);
void setMoney(int,int);
void setFood(int,int);
void setStuff(int,int);
void createPersonsTable();
void delTable(QString);

QString getPersonName(int num);
QString getPersonSurname(int num);
QString getWorkingLand(int);

//isim ve şifreyi, başlangıç değerleriyle data base a yazan fonksiyon
int signUp(QString,QString,QString);
void signUpRoot(QString name,QString surname,QString password);
int getBigestNum();
//elenen kullanıcıları(en fazla 10 adet) döndüren fonksiyon
int * getEliminated();
//getEliminated i kullanarak elenen kullanıcıları database den silen fonksiyon
void delEliminated();
//yönetici tablosunun oluşturulma sql kodu
void createManagerTable();
//başlangıç değerlerinin get fonksaiyonları
int getStartFood(int);
int getStartMoney(int);
int getStartStuff(int);
// başlangıç değerlerinin set etme fonksiyonları
void setStartFood(int, int);
void setStartMoney(int, int);
void setStartStuff(int, int);

int getDailyFoodExpense(int);
int getDailyMoneyExpense(int);
int getDailyStuffExpense(int);
QString getGameStartDate(int );
QString getGameSize(int );
QString getLandType(QString );
QString getLandOwnerName(QString);
QString getLandOwnerNum(QString);
int getPlaceOwnerFee(int );
int getfixedIncome(int );
int getfixedIncomeRate(int);

//yönetici tablosunun boş init edilmesi
int initManager();
int initManager(int ,int ,int ,int ,int ,int ,QString ,QString ,int , int, int);
// gün bitimi yemek eşya ve paranın data baste bulunan değere göre güncellenmesi
void updateDailyExpense(int,int*);
//set edilmiş günlük düşüşlerin get fonksiyonları

int * getWorkersAtMarket();
int * getWorkersAtStore();
int * getWorkersAtLandAgent();

bool isWorkingAtMarket(int personNum);
bool isWorkingAtStore(int personNum);
bool isWorkingAtLandAgent(int personNum);

void createLandTable();
void createBusinessTable();
void createWorkersTable();

//for lands
void genLands(int, int);
void initLand(QString, int, QString);
void setLandType(QString, QString);
void setLandOwner(QString, int);
//en temel oyun oynama alanı oyuşturan fonksiyon girilen x,y değerlerine göre
//alanı oluşturur ve yöneticiye ait olması gereken market emlak mağazayı oluşturur
void genGameTable(int, int);

//sahip olunan arazilerin x,y lerini verilen string liste yazar
//kaç adet olduğunu geri döndürür
int getOwnedLandNums(int, QString*);

//busines setters
void setBusinessType(QString, QString);
void setBusinessLevel(QString, int);
void setBusinessCapacity(QString, int);
void setBusinessWorkerCount(QString, int);

//busines getters
QString getBusinessType(QString);
int getBusinessLevel(QString);
int getBusinessCapacity(QString);
int getBusinessWorkerCount(QString);

void businessLevelUp(QString);

void newWorker(int, QString, int,QString, QString , int , int );
void updateWorker(int, QString, int,QString, QString , int , int );

int* getContractEndedWorkers(QString date);
void delContractEndedWorkers(QString date);

void createMarketTable();
void createStoreTable();
void createLandagentTable();

void buyFood(int buyer, QString landNum, int buyedCount);
void buyStuff(int buyer, QString landNum, int buyedCount);

int * getWorkersAtBusiness(QString workinglandNum);
bool isPersonWorking(int num);

int getWorkerFee(QString landNum);
int getWorkerFee(int workernum);

int getLandFoodPrice(QString landNum);
int getLandStuffPrice(QString landNum);
int getLandWorkerFee(QString landNum);
int getLandNumberOfWorkingDays(QString landNum);
int getLandWorkingHours(QString landNum);


void newStore(QString landNum, int foodPrice,int workerFee,
              int numberOfWorkingDays, int workingHours);
void newMarket(QString landNum, int stuffPrice,int workerFee,
               int numberOfWorkingDays, int workingHours);

void newBusiness(QString landNum, QString businessType, int businessLevel,
                 int businessCapacity, int businessWorkerCount);
