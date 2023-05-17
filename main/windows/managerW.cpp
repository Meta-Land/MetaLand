#include "managerW.h"
#include "sqllib.h"

ManagerScreen::ManagerScreen(QMainWindow *parent)
    : QMainWindow(parent)
{
    //giriş bölümlerinin tanımlanması
    startFoodEntery = new QLineEdit(this);
    startMoneyEntery = new QLineEdit(this);
    startStuffEntery = new QLineEdit(this);
    dailyFoodExpenseEntery = new QLineEdit(this);
    dailyMoneyExpenseEntery = new QLineEdit(this);
    dailyStuffExpenseEntery = new QLineEdit(this);
    gameStartDateEntery = new QLineEdit(this);
    gameSizeEntery = new QLineEdit(this);
    placeOwnerFeeEntery = new QLineEdit(this);
    fixedIncomeEntery = new QLineEdit(this);
    fixedIncomeRateEntery = new QLineEdit(this);
    //giriş bölümlerine konum ve boyut atanması
    int y = 100;
    int x = 150;
    int x_minus = 115;
    startFoodEntery         ->setGeometry(QRect(QPoint(x, y+=40), QSize(200, 30)));
    startFoodLabel = new QLabel("startFood : ",this); startFoodLabel->move(x-x_minus,y);

    startMoneyEntery        ->setGeometry(QRect(QPoint(x, y+=40), QSize(200, 30)));
    startMoneyLabel = new QLabel("startMoney : ",this); startMoneyLabel->move(x-x_minus,y);

    startStuffEntery        ->setGeometry(QRect(QPoint(x, y+=40), QSize(200, 30)));
    startStuffLabel = new QLabel("startStuff : ",this); startStuffLabel->move(x-x_minus,y);

    dailyFoodExpenseEntery  ->setGeometry(QRect(QPoint(x, y+=40), QSize(200, 30)));
    dailyFoodExpenseLabel = new QLabel("dailyFoodExpense : ",this); dailyFoodExpenseLabel->move(x-x_minus,y);

    dailyMoneyExpenseEntery ->setGeometry(QRect(QPoint(x, y+=40), QSize(200, 30)));
    dailyMoneyExpenseLabel = new QLabel("dailyMoneyExpense : ",this); dailyMoneyExpenseLabel->move(x-x_minus,y);

    dailyStuffExpenseEntery ->setGeometry(QRect(QPoint(x, y+=40), QSize(200, 30)));
    dailyStuffExpenseLabel = new QLabel("dailyStuffExpense : ",this); dailyStuffExpenseLabel->move(x-x_minus,y);

    gameStartDateEntery     ->setGeometry(QRect(QPoint(x, y+=40), QSize(200, 30)));
    gameStartDateLabel = new QLabel("gameStartDate : ",this); gameStartDateLabel->move(x-x_minus,y);

    gameSizeEntery          ->setGeometry(QRect(QPoint(x, y+=40), QSize(200, 30)));
    gameSizeLabel = new QLabel("gameSize : ",this); gameSizeLabel->move(x-x_minus,y);

    placeOwnerFeeEntery     ->setGeometry(QRect(QPoint(x, y+=40), QSize(200, 30)));
    placeOwnerFeeLabel = new QLabel("placeOwnerFee : ",this); placeOwnerFeeLabel->move(x-x_minus,y);

    fixedIncomeEntery       ->setGeometry(QRect(QPoint(x, y+=40), QSize(200, 30)));
    fixedIncomeLabel = new QLabel("fixedIncome : ",this); fixedIncomeLabel->move(x-x_minus,y);

    fixedIncomeRateEntery   ->setGeometry(QRect(QPoint(x, y+=40), QSize(200, 30)));
    fixedIncomeRateLabel = new QLabel("fixedIncomeRate : ",this); fixedIncomeRateLabel->move(x-x_minus,y);

    // giriş bölmelerine yer tutucu eklenmesi (hiçbir giriş yokken kullanıcıya nereye ne gireceği hakkında bilgi verir)
    startFoodEntery->setPlaceholderText("start Food Entery");
    startMoneyEntery->setPlaceholderText("start Money Entery");
    startStuffEntery->setPlaceholderText("start Stuff Entery");

    dailyFoodExpenseEntery->setPlaceholderText("daily Food Expense Entery");
    dailyMoneyExpenseEntery->setPlaceholderText("daily Money Expense Entery");
    dailyStuffExpenseEntery->setPlaceholderText("daily Stuff Expense Entery");

    gameStartDateEntery->setPlaceholderText("game Start Date Entery");
    gameSizeEntery->setPlaceholderText("game Size Entery");
    placeOwnerFeeEntery->setPlaceholderText("place OwnerFee Entery");

    fixedIncomeEntery->setPlaceholderText("fixed Income Entery");
    fixedIncomeRateEntery->setPlaceholderText("fixed Income Rate Entery");

    startFoodEntery->setText(QString::number(getStartFood(1)));
    startMoneyEntery->setText(QString::number(getStartMoney(1)));
    startStuffEntery->setText(QString::number(getStartStuff(1)));

    dailyFoodExpenseEntery->setText(QString::number(getDailyFoodExpense(1)));
    dailyMoneyExpenseEntery->setText(QString::number(getDailyMoneyExpense(1)));
    dailyStuffExpenseEntery->setText(QString::number(getDailyStuffExpense(1)));

    gameStartDateEntery->setText(getGameStartDate(1));
    gameSizeEntery->setText(getGameSize(1));
    placeOwnerFeeEntery->setText(QString::number(getPlaceOwnerFee(1)));

    fixedIncomeEntery->setText(QString::number(getfixedIncome(1)));
    fixedIncomeRateEntery->setText(QString::number(getfixedIncomeRate(1)));


    startFoodEntery->setFocus();

    dataSetter = new QPushButton("Set Data", this);
    // butonlar için boyut ve konum atamaları yapılması
    dataSetter->setGeometry(QRect(QPoint(400, 220), QSize(300, 30)));

    // Connect button sinyalinin fonksiyonlara bağlanması
    connect(dataSetter, &QPushButton::released, this, &ManagerScreen::setData);

    picLabel= new QLabel("",this);
    picLabel->setGeometry(QRect(QPoint(50, 91), QSize(90, 90)));

    //label resim ekleme
}

void ManagerScreen::setData()
{
    int startFood=startFoodEntery->text().toInt();
    int startMoney=startMoneyEntery->text().toInt();
    int startStuff=startStuffEntery->text().toInt();

    int dailyFoodExpense=dailyFoodExpenseEntery->text().toInt();
    int dailyMoneyExpense=dailyMoneyExpenseEntery->text().toInt();
    int dailyStuffExpense=dailyStuffExpenseEntery->text().toInt();

    QString gameStartDate=gameStartDateEntery->text();
    QString gameSize=gameSizeEntery->text();
    int placeOwnerFee=placeOwnerFeeEntery->text().toInt();

    int fixedIncome=fixedIncomeEntery->text().toInt();
    int fixedIncomeRate=fixedIncomeRateEntery->text().toInt();
    qDebug() << "signUpClicked";
    initManager(startFood ,startMoney ,startStuff ,dailyFoodExpense ,
                dailyMoneyExpense ,dailyStuffExpense ,gameStartDate ,gameSize,
                placeOwnerFee , fixedIncome , fixedIncomeRate);
    qDebug() << "initManager ended";
}

ManagerScreen::~ManagerScreen()
{
}
