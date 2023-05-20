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

using namespace std;
QVector<QVector<QPushButton*>> arsaList;
QVector<QVector<QPushButton*>> arsaListDetail;

int arsaID[5][5]{{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
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
QPushButton *detailClose;


gameScreen::gameScreen(QMainWindow *parent)
    : QMainWindow(parent)
{


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
    int row=r.toInt();
    int col=c.toInt();
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
    ////
    ///
    QPixmap pixFood("../main/Assets/food.png");
    QIcon ButtonFood(pixFood);
    QPixmap pixStuff("../main/Assets/stuff.png");
    QIcon ButtonStuff(pixStuff);
    QPixmap pixCoin("../main/Assets/coin.png");
    QIcon ButtonCoin(pixCoin);

    //database'den para miktarını çeker
    int coinS=getMoney(1);
    QString stCoin=QString::number(coinS);
    Lcoin= new QLabel(stCoin,this);
    Lcoin->setGeometry(QRect(QPoint(widthS-210,110), QSize(150,60)));
    Lcoin->setStyleSheet("background-color: rgb(247, 219, 106);" "border-radius: 30px");
    //database'den yemek miktarını çeker
    int foodS=getMoney(1);
    QString stFood=QString::number(foodS);
    Lcoin= new QLabel(stFood,this);
    Lfood= new QLabel(stFood,this);
    Lfood->setGeometry(QRect(QPoint(widthS-210,210), QSize(150,60)));
    Lfood->setStyleSheet("background-color: rgb(247, 219, 106);" "border-radius: 30px");

    //database'den eşya miktarını çeker
    int stuffS=getMoney(1);
    QString stStuff=QString::number(stuffS);
    Lcoin= new QLabel(stCoin,this);
    Lstuff= new QLabel(stCoin,this);
    Lstuff->setGeometry(QRect(QPoint(widthS-210,310), QSize(150,60)));
    Lstuff->setStyleSheet("background-color: rgb(247, 219, 106);" "border-radius: 30px");

    //coin label
    coin= new QLabel("",this);
    coin->setGeometry(QRect(QPoint(widthS-100,100), QSize(80,80)));
    coin->setPixmap(pixCoin.scaled(80,80));
    //yemek label
    food= new QLabel("",this);
    food->setGeometry(QRect(QPoint(widthS-100,200), QSize(80,80)));
    food->setPixmap(pixFood.scaled(80,80));
    //stuff label
    stuff= new QLabel("",this);
    stuff->setGeometry(QRect(QPoint(widthS-100,300), QSize(80,80)));
    stuff->setPixmap(pixStuff.scaled(80,80));


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
            QString stI=QString::number(i);
            QString stJ=QString::number(j);
            QString text=stI+stJ;
            a = new QPushButton(this);
            a->setGeometry(QRect(QPoint(x,y), QSize(100,100)));
            //butona resim eklenmesi
            a->setIcon(ButtonIcon);
            a->setIconSize(QSize(100,100));
            a->setText(text);
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
            if(LandType=="store"){
                arsaList[i][j]->setIcon(ButtonMall);
                arsaList[i][j]->setIconSize(QSize(50,50));
            }else if(LandType=="market"){
                arsaList[i][j]->setIcon(ButtonMarket);
                arsaList[i][j]->setIconSize(QSize(50,50));
            }else if(LandType=="landAgent"){
                arsaList[i][j]->setIcon(ButtonProperty);
                arsaList[i][j]->setIconSize(QSize(50,50));
            }
            qDebug() <<LandType;
        }
    }



    //yöneticiye ait olan emlak, mağaza ve marketin rastgele atanması
     /*
    //arsaya emlak etanması
    arsaList[0][0]->setIcon(ButtonProperty);
    arsaList[0][0]->setIconSize(QSize(50,50));
    arsaID[0][0]=1;

    //arsaya market aranması
    arsaList[0][1]->setIcon(ButtonMarket);
    arsaList[0][1]->setIconSize(QSize(50,50));
    arsaID[0][1]=2;

    //alışveriş merkezi atanması
    arsaList[0][2]->setIcon(ButtonMall);
    arsaList[0][2]->setIconSize(QSize(50,50));
    arsaID[0][2]=3;
   */

    //emlak için label oluşturulması
    buyGrassLabel= new QLabel("",this);
    buyGrassLabel->setGeometry(QRect(QPoint(widthS/2-200,heightS/2-200), QSize(400,400)));
    buyGrassLabel->setStyleSheet("background-color :rgb(248, 255, 219);" "border-radius: 5px");

    //detay sekmesini kapatan buton
    detailClose =new QPushButton("",buyGrassLabel);
    detailClose->setGeometry(QRect(QPoint(340,10), QSize(50,50)));
    detailClose->setStyleSheet("background-color:rgb(255, 100, 100);" "border-radius: 5px");
    detailClose->setText("X");
    buyGrassLabel->setVisible(false);

    //detay tablosu için 2d vektor oluşturma
    int m=10;
    int p=10;


    for(int i=0;i<5;i++){
        QVector<QPushButton*> arsaDetail2;
        QPushButton *a2;
        for(int j=0;j<5;j++){
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




    //arsaya tıklandığında gerçekleştirilecek fonksiyonlar
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            QString rowNum=QString::number(i);
            QString colNum=QString::number(j);
            QString LandNum=rowNum+"x"+colNum;
            QString LandType=getLandType(LandNum);
            //arsaya tıklandığında çalışacak fonksiyonun çağırılması
            connect (arsaList[i][j], & QPushButton :: clicked, this, [=] () -> void {
                //tıklanılan arsa emlak ise
                if(LandType=="landAgent"){
                    QMessageBox msgBox;
                    msgBox.setText("hangi işlemi yapmak istiyorsun?");
                    QPushButton* btnDetail = msgBox.addButton(tr("Detay"), QMessageBox::ActionRole);
                    QPushButton* btnBuyGrass = msgBox.addButton(tr("Arsa Satın Al"), QMessageBox::ActionRole);
                    QPushButton* btnWork = msgBox.addButton(tr("Çalış"), QMessageBox::ActionRole);
                    msgBox.exec();
                    if(msgBox.clickedButton() == btnBuyGrass){
                        showDetails();
                    }
                }
                //tıklanılan arsa market ise
                if(LandType=="market"){
                    QMessageBox msgBox;
                    msgBox.setText("hangi işlemi yapmak istiyorsun?");
                    QPushButton* btnDetail = msgBox.addButton(tr("Detay"), QMessageBox::ActionRole);
                    QPushButton* btnBuyGrass = msgBox.addButton(tr("yiyecek Satın Al"), QMessageBox::ActionRole);
                    QPushButton* btnWork = msgBox.addButton(tr("Çalış"), QMessageBox::ActionRole);
                    msgBox.exec();

                }
                //tıklanılan arsa mağaza ise
                if(LandType=="store"){
                    QMessageBox msgBox;
                    msgBox.setText("hangi işlemi yapmak istiyorsun?");
                    QPushButton* btnDetail = msgBox.addButton(tr("Detay"), QMessageBox::ActionRole);
                    QPushButton* btnBuyGrass = msgBox.addButton(tr("Eşya Satın Al"), QMessageBox::ActionRole);
                    QPushButton* btnWork = msgBox.addButton(tr("Çalış"), QMessageBox::ActionRole);
                    msgBox.exec();

                }
                //tıklanılan arsa alınmış ve bina yoksa
                if(arsaID[i][j]==4){
                    QMessageBox msgBox;
                    msgBox.setText("hangi işletmeyi kurmak istersin?");
                    QPushButton* btnMarket = msgBox.addButton(tr("market"), QMessageBox::ActionRole);
                    QPushButton* btnMall = msgBox.addButton(tr("mağaza"), QMessageBox::ActionRole);
                    QPushButton* btnProperty = msgBox.addButton(tr("emlak"), QMessageBox::ActionRole);
                    msgBox.exec();
                    //market kurmak istiyorsa
                    if (msgBox.clickedButton() == btnMarket) {
                        arsaList[i][j]->setIcon(ButtonMarket);
                        arsaList[i][j]->setIconSize(QSize(50,50));
                        arsaID[i][j]=2;
                    }else if (msgBox.clickedButton() == btnMall) {
                        arsaList[i][j]->setIcon(ButtonMall);
                        arsaList[i][j]->setIconSize(QSize(50,50));
                        arsaID[i][j]=3;
                    }else if (msgBox.clickedButton() == btnProperty) {
                        arsaList[i][j]->setIcon(ButtonProperty);
                        arsaList[i][j]->setIconSize(QSize(50,50));
                        arsaID[i][j]=1;
                    }

                }

            });
        }
    }
}



void gameScreen::showDetails()
{
    buyGrassLabel->setVisible(true);
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            //arsa emlak ise
            if(arsaID[i][j]==1){
                arsaListDetail[i][j]->setText("emlak");
                arsaListDetail[i][j]->setStyleSheet("background-color:rgb(255, 125, 125)");
            }
            //marketse
            if(arsaID[i][j]==2){
                arsaListDetail[i][j]->setText("market");
                arsaListDetail[i][j]->setStyleSheet("background-color:rgb(255, 125, 125)");

            }
            //mall ise
            if(arsaID[i][j]==3){
                arsaListDetail[i][j]->setText("mall");
                arsaListDetail[i][j]->setStyleSheet("background-color:rgb(255, 125, 125)");
            }
            //arsa satın alınacak ise
            if(arsaID[i][j]==0){
                arsaListDetail[i][j]->setStyleSheet("background-color:rgb(93, 156, 89)");
                connect (arsaListDetail[i][j], & QPushButton :: clicked, this, [=] () -> void {
                    buyGrass(i,j);
                });
            }
        }
    }
    connect (detailClose, & QPushButton :: clicked, this, [=] () -> void {
        buyGrassLabel->setVisible(false);
    });
}

void gameScreen::buyGrass(int i,int j){
    QPixmap pixFarm("../main/Assets/farm.png");
    QIcon ButtonFarm(pixFarm);

    QMessageBox msgBox;
    msgBox.setText("satın almak istediğine emin misin?");
    QPushButton* btn1 = msgBox.addButton(tr("Evet"), QMessageBox::ActionRole);
    QPushButton* btn2 = msgBox.addButton(tr("Hayır"), QMessageBox::ActionRole);
    msgBox.exec();
    //arsayı satın al
    if (msgBox.clickedButton() == btn1) {
        arsaListDetail[i][j]->setStyleSheet("background-color:rgb(255, 125, 125)");
        arsaList[i][j]->setIcon(ButtonFarm);
        arsaList[i][j]->setIconSize(QSize(100,100));
        arsaID[i][j]=4;
    }//satın almayı iptal et
    else if(msgBox.clickedButton() == btn2) {

    }
}


void gameScreen::buildMarket(int x,int y)
{
    QPixmap pixMarket("../main/Assets/market.png");
    QIcon ButtonMarket(pixMarket);
    arsaList[x][y]->setIcon(ButtonMarket);
    arsaList[x][y]->setIconSize(QSize(80,80));
    arsaID[x][y]=2;
}
void gameScreen::buildMall(int x,int y)
{
    QPixmap pixMall("../main/Assets/mall.png");
    QIcon ButtonMall(pixMall);
    arsaList[x][y]->setIcon(ButtonMall);
    arsaList[x][y]->setIconSize(QSize(80,80));
    arsaID[x][y]=3;
}
void gameScreen::buildProperty(int x,int y)
{
    QPixmap pixProperty("../main/Assets/property.png");
    QIcon ButtonProperty(pixProperty);
    arsaList[x][y]->setIcon(ButtonProperty);
    arsaList[x][y]->setIconSize(QSize(80,80));
    arsaID[x][y]=1;
}
gameScreen::~gameScreen()
{
}


