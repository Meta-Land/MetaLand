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
        gameScreen(int personNum,QMainWindow *parent = nullptr);
        ~gameScreen();
        int personNum1;


    private slots:
        void buildMarket(int x,int y);
        void buildMall(int x,int y);
        void buildProperty(int x,int y);
        void LandDetail(int);
        void showDetail(int, int);
        void buyGrass(int x,int y);
        void shopping(int i, int j);
        void upDate();
        void work(int i,int j);
        void updateDate(int);
        void updateLabels(int);
    private:

        QLineEdit *shopAmount;
        QLineEdit *sutun;
        QLabel *coin;
        QLabel *stuff;
        QLabel *food;
        QLabel *detailLabel;
        QLabel *landTypeDetail;
        QLabel *landOwnerDetail;
        QLabel *workersCount;
        QLabel *workerCapacityDetail;
        QLabel *shoppingLabel;
        QLabel *priceLabel;
        QLabel *Lcoin;
        QLabel *Lstuff;
        QLabel *Lfood;
        QLabel *workDetail;
        QLabel *workerFeeLabel;
        QLabel *workingDaysCountL;
        QLabel *workingHoursL;
        QPushButton *cancelWorkDetail;
        QPushButton *workBtn;
        QPushButton *buy;
        QPushButton *userBtn;
        QPushButton *updateDateBtn;
        QLabel *userLabel;
        QPushButton *shopClose;


        /*QPushButton *market;
        QPushButton *property;
        QPushButton *mall;*/
        //QLabel *detailBox;
        //QPushButton *detailClose;
        int height;
        int width;

};

