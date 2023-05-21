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
        int personNum1;


    private slots:
        void buildMarket(int x,int y);
        void buildMall(int x,int y);
        void buildProperty(int x,int y);
        void LandDetail();
        void showDetail(int, int);
        void buyGrass(int x,int y);
        void upDate();
    private:

        QLineEdit *satir;
        QLineEdit *sutun;
        QLabel *coin;
        QLabel *stuff;
        QLabel *food;
        QLabel *detailLabel;
        QLabel *landTypeDetail;
        QLabel *landOwnerDetail;
        QLabel *workersDetail;
        QLabel *workerCapacityDetail;


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

