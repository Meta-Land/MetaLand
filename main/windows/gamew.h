#include <QMainWindow>
#include <QPixmap>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsPixmapItem>
#include <QLineEdit>

class gameScreen:  public QMainWindow

{
    Q_OBJECT
    public:
        gameScreen(QMainWindow *parent = nullptr);
        ~gameScreen();

    private slots:
        void buildMarket(int x,int y);
        void buildMall(int x,int y);
        void buildProperty(int x,int y);
        void showDetails();
        void buyGrass(int x,int y);
    private:

        QLineEdit *satir;
        QLineEdit *sutun;
        QLabel *coin;
        QLabel *stuff;
        QLabel *food;

        QLabel *Lcoin;
        QLabel *Lstuff;
        QLabel *Lfood;

        /*QPushButton *market;
        QPushButton *property;
        QPushButton *mall;*/
        //QLabel *detailBox;
        //QPushButton *detailClose;
        int height;
        int width;

};

