#include "gamew.h"
#include "sqllib.h"
#include <QPixmap>
#include <QLabel>
#include<iostream>
#include<array>
#include<string>
#include<QPushButton>
#include <QString>
#include <QApplication>
#include <QScreen>
#include <QMessageBox>
#include <QLayout>
#include <string.h>
#include <QDate>

using namespace std;
QVector<QVector<QPushButton*>> arsaList;
QVector<QVector<QPushButton*>> arsaListDetail;


//int arsaID[5][5]{{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
/*arsaya sahip kimse yoksa id=0;
 * arsa emlak id ise=1;
 * arsa market id ise=2;
 * arsa mağaza id ise=3;
 * aarsa alınmış ve bina yoksa
 */
int k=0;
int l=2;
QLabel *buyGrassLabel;
QPushButton *market;
QPushButton *mall;
QPushButton *property;
QPushButton *buyLandClose;
QPushButton *detailClose;
int row,col;
int num;
QString userName;
QString userSurname;
QString numSt;
int day=0;

gameScreen::gameScreen(int personNum,QMainWindow *parent)
    : QMainWindow(parent)
{

    personNum1=personNum;
    //qDebug() <<"asdfs"<<num;
    //oyun alanının genişliği vve boyunu bulma
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int heightS = screenGeometry.height();
    int widthS = screenGeometry.width();

    height=heightS;
    width=widthS;

    //oyun alanının arsa boyutlarını tutma r=satir sayisi c=sütun sayısı
    QString gameSize=getGameSize(1);
    QString r=gameSize[0];
    QString c=gameSize[2];

    qDebug() <<r ;
    qDebug() <<c ;


    //boyutların atanması
    row=r.toInt();
    col=c.toInt();
    int y=0;
    int x=0;
    //oyun alanında kullanılacak görsellerin yollarını tutma
    //////////////////////
    QPixmap pixMarket("../main/Assets/market.png");
    QIcon ButtonMarket(pixMarket);
    QPixmap pixMall("../main/Assets/mall.png");
    QIcon ButtonMall(pixMall);
    QPixmap pixProperty("../main/Assets/property.png");
    QIcon ButtonProperty(pixProperty);
    QPixmap pixFarm("../main/Assets/farm.png");
    QIcon ButtonFarm(pixFarm);
    ////
    ///
    QPixmap pixFood("../main/Assets/food.png");
    QIcon ButtonFood(pixFood);
    QPixmap pixStuff("../main/Assets/stuff.png");
    QIcon ButtonStuff(pixStuff);
    QPixmap pixCoin("../main/Assets/coin.png");
    QIcon ButtonCoin(pixCoin);
    QPixmap pixUser("../main/Assets/user.png");
    QIcon ButtonUser(pixUser);


    //date button
    updateDateBtn= new QPushButton("",this);
    updateDateBtn->setGeometry(QRect(QPoint(widthS-150,heightS-200), QSize(100,50)));
    updateDateBtn->setText("gün artır");
    updateDateBtn->setStyleSheet("background-color:rgb(255, 171, 118);" "border-radius: 15px;");
    connect (updateDateBtn, & QPushButton :: clicked, this, [=] () -> void {
        updateDate(personNum1);
    });




    //user section
    userBtn= new QPushButton("",this);
    userBtn->setGeometry(QRect(QPoint(widthS-100,40), QSize(50,50)));
    userBtn->setIcon(ButtonUser);
    userBtn->setStyleSheet("background-color: rgba(255, 255, 255, 0)");
    userBtn->setIconSize(QSize(50,50));

    userName=getPersonName(personNum1);
    userSurname=getPersonSurname(personNum1);
    numSt=QString::number(personNum1);

    QString workingLandType="";
    qDebug() <<"numara:" <<userName;

    if(isPersonWorking(personNum1)){
        QString workingLandNum=getWorkingLand(personNum1);
        workingLandType=getLandType(workingLandNum);
    }

    userLabel= new QLabel("",this);
    userLabel->setGeometry(QRect(QPoint(widthS-260,45), QSize(150,100)));
    userLabel->setStyleSheet("background-color: rgb(247, 219, 106);" "border-radius: 15px");
    userLabel->setText("<big>İsim Soyisim:</big>"+userName+" "+userSurname+"<br>"
                        "<big>Numara:</big>"+ numSt+"<br>"
                       "<big>Çalıştığı İşletme:</big>"+workingLandType);


    //database'den para miktarını çeker
    int coinS=getMoney(personNum1);
    QString stCoin=QString::number(coinS);
    Lcoin= new QLabel(stCoin,this);
    Lcoin->setGeometry(QRect(QPoint(widthS-210,150), QSize(100,35)));
    Lcoin->setStyleSheet("background-color: rgb(247, 219, 106);" "border-radius: 15px");
    //database'den yemek miktarını çeker
    int foodS=getFood(personNum1);
    QString stFood=QString::number(foodS);
    Lfood= new QLabel(stFood,this);
    Lfood->setGeometry(QRect(QPoint(widthS-210,215), QSize(100,35)));
    Lfood->setStyleSheet("background-color: rgb(247, 219, 106);" "border-radius: 15px");

    //database'den eşya miktarını çeker
    int stuffS=getStuff(personNum1);
    QString stStuff=QString::number(stuffS);
    Lstuff= new QLabel(stStuff,this);
    Lstuff->setGeometry(QRect(QPoint(widthS-210,280), QSize(100,35)));
    Lstuff->setStyleSheet("background-color: rgb(247, 219, 106);" "border-radius: 15px");

    //coin label
    coin= new QLabel("",this);
    coin->setGeometry(QRect(QPoint(widthS-100,140), QSize(55,55)));
    coin->setPixmap(pixCoin.scaled(55,55));
    //yemek label
    food= new QLabel("",this);
    food->setGeometry(QRect(QPoint(widthS-100,205), QSize(55,55)));
    food->setPixmap(pixFood.scaled(55,55));
    //stuff label
    stuff= new QLabel("",this);
    stuff->setGeometry(QRect(QPoint(widthS-100,270), QSize(55,55)));
    stuff->setPixmap(pixStuff.scaled(55,55));


//////////////////////////////////////////////////////////////////////////////////////////

    y=(heightS/2)-(35*(row-1)/2)-100;
    x =(widthS/2)-(100*col/2)-(row/2*50);

    int xTemp=x;
    QPixmap pix("../main/Assets/grass.png");
    QIcon ButtonIcon(pix);

    //ARSALARI OLUŞTURAN VE OYUN ALANINA YERLEŞTİREN FONKSİYON
    for( auto i=0;i<row;i++)
    {
        QVector<QPushButton*> list2;
        QPushButton *a;

        for(auto j=0;j<col;j++)
        {
            a = new QPushButton(this);
            a->setGeometry(QRect(QPoint(x,y), QSize(100,100)));
            //butona resim eklenmesi
            a->setIcon(ButtonIcon);
            a->setIconSize(QSize(100,100));
            //buton arka planını saydamlaştırma
            a->setStyleSheet("background-color: rgba(255, 255, 255, 0)");
            list2.push_back(a);
            x+=100;
        }
        arsaList.push_back(list2);
        //basılacak arsaların konumları için
        xTemp+=50;
        x=xTemp;
        y+=35;
    }

    //arsalara tanımlanan işletmelerin atanması
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){

            QString rowNum=QString::number(i);
            QString colNum=QString::number(j);
            QString LandNum=rowNum+"x"+colNum;
            QString LandType=getLandType(LandNum);
            //setLandType(LandNum,"");
            setLandType("0x0","landAgent");
            setLandType("0x1","store");
            setLandType("0x2","market");
            newMarket("0x2",2,50,5,6);
            newStore("0x1",2,50,5,6);
            newBusiness("0x0","landAgent",1,-1,0);
            newBusiness("0x1","store",1,-1,0);
            newBusiness("0x2","market",1,-1,0);

            if(LandType=="store"){
                arsaList[i][j]->setIcon(ButtonMall);
                arsaList[i][j]->setIconSize(QSize(50,50));
                newBusiness(LandNum,"store",1,3,0);
            }else if(LandType=="market"){
                arsaList[i][j]->setIcon(ButtonMarket);
                arsaList[i][j]->setIconSize(QSize(50,50));
                newBusiness(LandNum,"market",1,3,0);

            }else if(LandType=="landAgent"){
                arsaList[i][j]->setIcon(ButtonProperty);
                arsaList[i][j]->setIconSize(QSize(50,50));
                newBusiness(LandNum,"landAgent",1,3,0);
            }else if(LandType=="empty"){
                arsaList[i][j]->setIcon(ButtonFarm);
                arsaList[i][j]->setIconSize(QSize(100,100));
            }
        }
    }


    //emlak için label oluşturulması
    buyGrassLabel= new QLabel("",this);
    buyGrassLabel->setGeometry(QRect(QPoint(widthS/2-350,heightS/2-350), QSize(700,700)));
    buyGrassLabel->setStyleSheet("background-color :rgb(248, 255, 219);" "border-radius: 5px");

    //arsa alma sekmesini kapatan buton
    buyLandClose =new QPushButton("",buyGrassLabel);
    buyLandClose->setGeometry(QRect(QPoint(640,10), QSize(50,50)));
    buyLandClose->setStyleSheet("background-color:rgb(255, 100, 100);" "border-radius: 5px");
    buyLandClose->setText("X");
    buyGrassLabel->setVisible(false);

    //çalışma detayı
    workDetail= new QLabel("",this);
    workDetail->setGeometry(QRect(QPoint(widthS/2-200,heightS/2-200), QSize(400,400)));
    workDetail->setStyleSheet("background-color :rgb(248, 255, 219);" "border-radius: 5px");
    workDetail->setVisible(false);
    /*
    QLabel *workerFeeLabel;
    QLabel *workingDaysCountL;
    QLabel *workingHoursL;
    */
    //çalışma detay sekmesini kapatan buton
    cancelWorkDetail=new QPushButton("",workDetail);
    cancelWorkDetail->setGeometry(QRect(QPoint(340,10), QSize(50,50)));
    cancelWorkDetail->setStyleSheet("background-color:rgb(255, 100, 100);" "border-radius: 5px");
    cancelWorkDetail->setText("X");

    workBtn=new QPushButton("",workDetail);
    workBtn->setGeometry(QRect(QPoint(150,250), QSize(100,50)));
    workBtn->setStyleSheet("background-color:rgb(255, 100, 100);" "border-radius: 5px");
    workBtn->setText("ÇALIŞ");


    workerFeeLabel=new QLabel("",workDetail);
    workerFeeLabel->setGeometry(QRect(QPoint(100,10), QSize(200,70)));
    workerFeeLabel->setStyleSheet("background-color :rgb(255, 180, 180);" "border-radius: 5px");

    workingDaysCountL=new QLabel("",workDetail);
    workingDaysCountL->setGeometry(QRect(QPoint(100,90), QSize(200,70)));
    workingDaysCountL->setStyleSheet("background-color :rgb(255, 180, 180);" "border-radius: 5px");

    workingHoursL=new QLabel("",workDetail);
    workingHoursL->setGeometry(QRect(QPoint(100,170), QSize(200,70)));
    workingHoursL->setStyleSheet("background-color :rgb(255, 180, 180);" "border-radius: 5px");



    //detay sekmesi
    detailLabel= new QLabel("",this);
    detailLabel->setGeometry(QRect(QPoint(widthS/2-200,heightS/2-200), QSize(400,400)));
    detailLabel->setStyleSheet("background-color :rgb(248, 255, 219);" "border-radius: 5px");
    detailLabel->setVisible(false);

    //detay sekmesini kapatan buton
    detailClose =new QPushButton("",detailLabel);
    detailClose->setGeometry(QRect(QPoint(340,10), QSize(50,50)));
    detailClose->setStyleSheet("background-color:rgb(255, 100, 100);" "border-radius: 5px");
    detailClose->setText("X");

    //alışveriş yapmak için yapılan sekme
    shoppingLabel=new QLabel("",this);
    shoppingLabel->setGeometry(QRect(QPoint(widthS/2-200,heightS/2-200), QSize(400,250)));
    shoppingLabel->setStyleSheet("background-color :rgb(248, 255, 219);" "border-radius: 5px");
    shoppingLabel->setVisible(false);

    //birim fiyat gösteren label
    priceLabel=new QLabel("",shoppingLabel);
    priceLabel->setGeometry(QRect(QPoint(100,10), QSize(200,70)));
    priceLabel->setText("birim fiyat:");
    priceLabel->setStyleSheet("background-color :rgb(255, 180, 180);" "border-radius: 5px");

    // `ne birim alışveriş yapmak istiyorsun` line editi
    shopAmount=new QLineEdit("",shoppingLabel);
    shopAmount->setGeometry(QRect(QPoint(100,90), QSize(200,70)));
    shopAmount->setStyleSheet("background-color :rgb(255, 180, 180);" "border-radius: 5px");
    shopAmount->setPlaceholderText("Almak istediğiniz miktar");

    shopClose=new QPushButton("",shoppingLabel);
    shopClose->setGeometry(QRect(QPoint(340,10), QSize(50,50)));
    shopClose->setStyleSheet("background-color:rgb(255, 100, 100);" "border-radius: 5px");
    shopClose->setText("X");



    //buy button
    buy= new QPushButton("",shoppingLabel);
    buy->setText("buy");
    buy->setGeometry(QRect(QPoint(170,170), QSize(60,40)));
    buy->setStyleSheet("background-color :rgb(255, 100, 100);" "border-radius: 5px");


    landTypeDetail=new QLabel("",detailLabel);
    landTypeDetail->setGeometry(QRect(QPoint(100,10), QSize(200,70)));
    landTypeDetail->setStyleSheet("background-color :rgb(255, 180, 180);" "border-radius: 5px");


    landOwnerDetail=new QLabel("",detailLabel);
    landOwnerDetail->setGeometry(QRect(QPoint(100,90), QSize(200,70)));
    landOwnerDetail->setStyleSheet("background-color :rgb(255, 180, 180);" "border-radius: 5px");


    workersCount=new QLabel("",detailLabel);
    workersCount->setGeometry(QRect(QPoint(100,170), QSize(200,70)));
    workersCount->setStyleSheet("background-color :rgb(255, 180, 180);" "border-radius: 5px");


    workerCapacityDetail=new QLabel("",detailLabel);
    workerCapacityDetail->setGeometry(QRect(QPoint(100,250), QSize(200,70)));
    workerCapacityDetail->setStyleSheet("background-color :rgb(255, 180, 180);" "border-radius: 5px");


    //detay tablosu için 2d vektor oluşturma
    int m=10;
    int p=10;


    for(int i=0;i<row;i++){
        QVector<QPushButton*> arsaDetail2;
        QPushButton *a2;
        for(int j=0;j<col;j++){
            //arsaListDetail[i][j] = new QPushButton(detailBox);
            a2 = new QPushButton(buyGrassLabel);
            a2->setGeometry(QRect(QPoint(m,p), QSize(50,50)));
            //buton arka planını saydamlaştırma
            arsaDetail2.push_back(a2);
            m+=55;
        }
        arsaListDetail.push_back(arsaDetail2);
        p+=55;
        m=10;
    }

    //tıklama işlemlerinin gerçekleştirilmesi
    upDate();
}

void gameScreen::LandDetail(int personNum)
{
    QPixmap pixMarket("../main/Assets/market.png");
    QIcon ButtonMarket(pixMarket);
    QPixmap pixMall("../main/Assets/mall.png");
    QIcon ButtonMall(pixMall);
    QPixmap pixProperty("../main/Assets/property.png");
    QIcon ButtonProperty(pixProperty);
    buyGrassLabel->setVisible(true);


    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            QString rowNum=QString::number(i);
            QString colNum=QString::number(j);
            QString LandNum=rowNum+"x"+colNum;
            QString LandType=getLandType(LandNum);
            QString LandOwnerNum =getLandOwnerNum(LandNum);

            int landOwner=LandOwnerNum.toInt();

            //arsa emlak ise
            if(LandType=="landAgent"){
                arsaListDetail[i][j]->setText("emlak");
                arsaListDetail[i][j]->setStyleSheet("background-color:rgb(255, 125, 125)");
            }
            //marketse
            else if(LandType=="market"){
                arsaListDetail[i][j]->setText("market");
                arsaListDetail[i][j]->setStyleSheet("background-color:rgb(255, 125, 125)");
            }
            //mall ise
            else if(LandType=="store"){
                arsaListDetail[i][j]->setText("mall");
                arsaListDetail[i][j]->setStyleSheet("background-color:rgb(255, 125, 125)");
            }
            //arsa satın alınacak ise
            else if(LandType=="land"){
                arsaListDetail[i][j]->setStyleSheet("background-color:rgb(93, 156, 89)");
                connect (arsaListDetail[i][j], & QPushButton :: clicked, this, [=] () -> void {
                    buyGrass(i,j);
                });
            }else if(LandType=="empty" && landOwner!=personNum){
                arsaListDetail[i][j]->setStyleSheet("background-color:rgb(255, 125, 125)");
            }
            //arsa kişiye ait ve boş ise
            if(landOwner==personNum && LandType=="empty"){
                arsaListDetail[i][j]->setStyleSheet("background-color:rgb(255, 171, 118)");
                connect (arsaListDetail[i][j], & QPushButton :: clicked, this, [=] () -> void {
                    QMessageBox msgBox;
                    msgBox.setText("hangi işletmeyi kurmak istersin?");
                    QPushButton* btnMarket = msgBox.addButton(tr("market"), QMessageBox::ActionRole);
                    QPushButton* btnMall = msgBox.addButton(tr("mağaza"), QMessageBox::ActionRole);
                    QPushButton* btnProperty = msgBox.addButton(tr("emlak"), QMessageBox::ActionRole);
                    QPushButton* btnCancel = msgBox.addButton(tr("çıkış"), QMessageBox::ActionRole);
                    msgBox.exec();
                        //market kurmak istiyorsa
                        if (msgBox.clickedButton() == btnMarket) {
                            arsaList[i][j]->setIcon(ButtonMarket);
                            arsaList[i][j]->setIconSize(QSize(50,50));
                            //setLandType(LandNum,"market");
                            buildMarket(i,j);
                            //update();
                        }else if (msgBox.clickedButton() == btnMall) {
                            arsaList[i][j]->setIcon(ButtonMall);
                            arsaList[i][j]->setIconSize(QSize(50,50));
                            //setLandType(LandNum,"store");
                            buildMall(i,j);
                            //update();

                        }else if (msgBox.clickedButton() == btnProperty) {
                            arsaList[i][j]->setIcon(ButtonProperty);
                            arsaList[i][j]->setIconSize(QSize(50,50));
                            //setLandType(LandNum,"landAgent");
                            buildProperty(i,j);

                        }
                        //msgBox-
                });
            }
            if(landOwner==personNum && LandType!="empty"){
                connect (arsaListDetail[i][j], & QPushButton :: clicked, this, [=] () -> void {
                    QMessageBox msgBox;
                    msgBox.setText("hangi işletmeyi kurmak istersin?");
                    QPushButton* btnBuy = msgBox.addButton(tr("işletmeyi sat"), QMessageBox::ActionRole);
                    QPushButton* btnRent = msgBox.addButton(tr("işletmeyi kirala"), QMessageBox::ActionRole);
                    msgBox.exec();
                    if(msgBox.clickedButton() == btnBuy){

                    }else if(msgBox.clickedButton() == btnRent){

                    }
                });
            }

        }
    }


    connect (buyLandClose, & QPushButton :: clicked, this, [=] () -> void {
        buyGrassLabel->setVisible(false);
    });

    update();
}

void gameScreen::buyGrass(int i,int j){

    QString rowNum=QString::number(i);
    QString colNum=QString::number(j);
    QString LandNum=rowNum+"x"+colNum;

    QPixmap pixFarm("../main/Assets/farm.png");
    QIcon ButtonFarm(pixFarm);

    QMessageBox msgBox;
    msgBox.setText("satın almak istediğine emin misin?");
    QPushButton* btn1 = msgBox.addButton(tr("Evet"), QMessageBox::ActionRole);
    QPushButton* btn2 = msgBox.addButton(tr("Hayır"), QMessageBox::ActionRole);
    msgBox.exec();
    //arsayı satın al
    if (msgBox.clickedButton() == btn1) {
        arsaListDetail[i][j]->setStyleSheet("background-color:rgb(255, 171, 118)");
        arsaList[i][j]->setIcon(ButtonFarm);
        arsaList[i][j]->setIconSize(QSize(100,100));
        setLandType(LandNum,"empty");
        setLandOwner(LandNum, personNum1);
    }//satın almayı iptal et
    else if(msgBox.clickedButton() == btn2) {

    }
    msgBox.close();
   // upDate();
}
void gameScreen::shopping(int i,int j){
    QString rowNum=QString::number(i);
    QString colNum=QString::number(j);
    QString landNum=rowNum+"x"+colNum;
    QString LandType=getLandType(landNum);

    shoppingLabel->setVisible(true);
    int price=getLandFoodPrice(landNum);
    QString priceSt=QString::number(price);

    priceLabel->setText("birim fiyat:"+priceSt);


    connect (buy, & QPushButton :: clicked, this, [=] () -> void {
        QString amount=shopAmount->text();

        QString rowNum=QString::number(i);
        QString colNum=QString::number(j);
        QString landNum=rowNum+"x"+colNum;
        QString LandType=getLandType(landNum);
        if(LandType=="market"){
            buyFood(personNum1,landNum,amount.toInt());
        }else if(LandType=="store"){
            buyStuff(personNum1,landNum,amount.toInt());
        }
        updateLabels(personNum1);
        qDebug() <<amount;
    });

    connect (shopClose, & QPushButton :: clicked, this, [=] () -> void {
        shoppingLabel->setVisible(false);
    });


}

void gameScreen::updateDate(int personNum){
    int * list = getEliminated();
    delEliminated();
    for(int i = 0;i<10;i++){
        if(list[i] != 0){
            if(list[i]==personNum1){
                this->close();
            }
        }
    }


    updateDailyExpense(personNum,&day);
    updateLabels(personNum);
    day++;
}
void gameScreen::updateLabels(int personNum){
    int coinS=getMoney(personNum);
    QString stCoin=QString::number(coinS);
    Lcoin->setText(stCoin);
    //database'den yemek miktarını çeker
    int foodS=getFood(personNum);
    QString stFood=QString::number(foodS);
    Lfood->setText(stFood);

    //database'den eşya miktarını çeker
    int stuffS=getStuff(personNum);
    QString stStuff=QString::number(stuffS);
    Lstuff->setText(stStuff);
}

void gameScreen::buildMarket(int x,int y)
{
    QString rowNum=QString::number(x);
    QString colNum=QString::number(y);
    QString LandNum=rowNum+"x"+colNum;
    QPixmap pixMarket("../main/Assets/market.png");
    QIcon ButtonMarket(pixMarket);
    newBusiness(LandNum,"market",1,3,0);
    newMarket(LandNum,2,100,5,2);
    arsaList[x][y]->setIcon(ButtonMarket);
    arsaList[x][y]->setIconSize(QSize(50,50));
    setLandType(LandNum,"market");
    update();
}
void gameScreen::buildMall(int x,int y)
{
    QString rowNum=QString::number(x);
    QString colNum=QString::number(y);
    QString LandNum=rowNum+"x"+colNum;
    QPixmap pixMall("../main/Assets/mall.png");
    QIcon ButtonMall(pixMall);
    newBusiness(LandNum,"store",1,3,0);
    newStore(LandNum,2,100,5,2);
    arsaList[x][y]->setIcon(ButtonMall);
    arsaList[x][y]->setIconSize(QSize(50,50));
    setLandType(LandNum,"store");
}
void gameScreen::buildProperty(int x,int y)
{
    QString rowNum=QString::number(x);
    QString colNum=QString::number(y);
    QString LandNum=rowNum+"x"+colNum;
    QPixmap pixProperty("../main/Assets/property.png");
    QIcon ButtonProperty(pixProperty);
    newBusiness(LandNum,"landAgent",1,3,0);
    arsaList[x][y]->setIcon(ButtonProperty);
    arsaList[x][y]->setIconSize(QSize(50,50));
    setLandType(LandNum,"landAgent");
}

void gameScreen::showDetail(int i,int j)
{
    QString rowNum=QString::number(i);
    QString colNum=QString::number(j);
    QString LandNum=rowNum+"x"+colNum;
    QString LandType=getLandType(LandNum);
    QString LandOwnerName=getLandOwnerName(LandNum);
    QString LandOwnerNum =getLandOwnerNum(LandNum);
    int workerCount=getBusinessWorkerCount(LandNum);
    QString workerNumSt=QString::number(workerCount);
    /*
    *   QLabel *landTypeDetail;
        QLabel *landOwnerDetail;
        QLabel *workersDetail;
        QLabel *workerCapacityDetail;
    */
    detailLabel->setVisible(true);
    landTypeDetail->setText("İşletme Türü:"+LandType);
    landOwnerDetail->setText("İşletme Sahibi:"+LandOwnerName+"/"+LandOwnerNum+" Numara");
    workersCount->setText("Çalışan Sayısı:"+workerNumSt);
    workerCapacityDetail->setText("Çalışan Kapasitesi:");
    //
    /*QString personNumSt=QString::number(personNum1);
    landOwnerDetail->setText(personNumSt);*/
    connect (detailClose, & QPushButton :: clicked, this, [=] () -> void {
        detailLabel->setVisible(false);
    });
}

void gameScreen::work(int i,int j)
{
    QString rowNum=QString::number(i);
    QString colNum=QString::number(j);
    QString LandNum=rowNum+"x"+colNum;
    int workerNum=getBusinessWorkerCount(LandNum);
    QString workerNumSt=QString::number(workerNum);
    QString landType=getLandType(LandNum);
    QDate Today = QDate::currentDate();
    QString startDate = Today.toString("");
    Today.addDays(3);
    QString finishDate=Today.toString("yyyy-MM-dd");

    /*
    QLabel *workerFeeLabel;
    QLabel *workingDaysCountL;
    QLabel *workingHoursL;
    */
    int workerFee=getLandWorkerFee(LandNum);
    QString workerFeeSt=QString::number(workerFee);
    int workerDaysCount=getLandNumberOfWorkingDays(LandNum);
    QString workerDaysCountSt=QString::number(workerDaysCount);
    int workingHour=getLandWorkingHours(LandNum);
    QString workingHourSt=QString::number(workingHour);

    workerFeeLabel->setText("maaş:"+workerFeeSt);
    workingDaysCountL->setText("çalışılacak gün sayısı:"+workerDaysCountSt);
    workingHoursL->setText("çalışılacak saat:"+workingHourSt);
    workDetail->setVisible(true);

    connect (cancelWorkDetail, & QPushButton :: clicked, this, [=] () -> void {
      workDetail->setVisible(false);
    });
    connect (workBtn, & QPushButton :: clicked, this, [=] () -> void {
        if(!isPersonWorking(personNum1)){
            newWorker(personNum1,LandNum,100,"1-1-1","1-1-1",3,3);
            userLabel->setText("<big>İsim Soyisim:</big>"+userName+" "+userSurname+"<br>"
                                "<big>Numara:</big>"+ numSt+"<br>"
                                "<big>Çalıştığı İşletme:</big>"+landType);
        }
    });
}



void gameScreen::upDate()
{
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){

            //arsaya tıklandığında çalışacak fonksiyonun çağırılması
            connect (arsaList[i][j], & QPushButton :: clicked, this, [=] () -> void {
                QString rowNum=QString::number(i);
                QString colNum=QString::number(j);
                QString LandNum=rowNum+"x"+colNum;
                QString LandType=getLandType(LandNum);
                //tıklanılan arsa emlak ise
                if(LandType=="landAgent"){
                    QMessageBox msgBox;
                    msgBox.setText("hangi işlemi yapmak istiyorsun?");
                    QPushButton* btnDetail = msgBox.addButton(tr("Detay"), QMessageBox::ActionRole);
                    QPushButton* btnBuyGrass = msgBox.addButton(tr("Arsa Satın Al"), QMessageBox::ActionRole);
                    QPushButton* btnWork = msgBox.addButton(tr("Çalış"), QMessageBox::ActionRole);
                    QPushButton* btnExit = msgBox.addButton(tr("Çıkış"), QMessageBox::ActionRole);

                    msgBox.exec();
                    if(msgBox.clickedButton() == btnBuyGrass){
                        LandDetail(personNum1);
                        msgBox.close();
                    }else if(msgBox.clickedButton() == btnDetail){
                        showDetail(i,j);
                    }else if(msgBox.clickedButton() == btnWork){
                        work(i,j);
                    }
                }
                //tıklanılan arsa market ise
                if(LandType=="market"){
                    QMessageBox msgBox;
                    msgBox.setText("hangi işlemi yapmak istiyorsun?");
                    QPushButton* btnDetail = msgBox.addButton(tr("Detay"), QMessageBox::ActionRole);
                    QPushButton* btnBuy = msgBox.addButton(tr("yiyecek Satın Al"), QMessageBox::ActionRole);
                    QPushButton* btnWork = msgBox.addButton(tr("Çalış"), QMessageBox::ActionRole);
                    QPushButton* btnExit = msgBox.addButton(tr("Çıkış"), QMessageBox::ActionRole);

                    msgBox.exec();
                    if(msgBox.clickedButton() == btnDetail){
                        showDetail(i,j);
                    }else if(msgBox.clickedButton() == btnWork){
                        work(i,j);

                    }else if(msgBox.clickedButton() == btnBuy){
                        shopping(i,j);
                    }
                }
                //tıklanılan arsa mağaza ise
                if(LandType=="store"){
                    QMessageBox msgBox;
                    msgBox.setText("hangi işlemi yapmak istiyorsun?");
                    QPushButton* btnDetail = msgBox.addButton(tr("Detay"), QMessageBox::ActionRole);
                    QPushButton* btnBuy = msgBox.addButton(tr("Eşya Satın Al"), QMessageBox::ActionRole);
                    QPushButton* btnWork = msgBox.addButton(tr("Çalış"), QMessageBox::ActionRole);
                    QPushButton* btnExit = msgBox.addButton(tr("Çıkış"), QMessageBox::ActionRole);
                    msgBox.exec();
                    if(msgBox.clickedButton() == btnDetail){
                        showDetail(i,j);
                    }else if(msgBox.clickedButton() == btnWork){
                        work(i,j);
                    }else if(msgBox.clickedButton() == btnBuy){
                        shopping(i,j);
                    }
                }
                //tıklanılan arsa alınmış ve bina yoksa
                if(LandType=="empty"){
                    QMessageBox msgBox;
                    msgBox.setText("hangi işlemi yapmak istersin?");
                    QPushButton* btnDetail = msgBox.addButton(tr("detay"), QMessageBox::ActionRole);
                    QPushButton* btnCancel = msgBox.addButton(tr("çıkış"), QMessageBox::ActionRole);
                    msgBox.exec();
                    if(msgBox.clickedButton() == btnDetail){
                        showDetail(i,j);
                    }
                }

            });
        }
    }

}

gameScreen::~gameScreen()
{
}


