#include <QMainWindow>
#include <QPixmap>
#include <QLabel>
#include <QGraphicsPixmapItem>
#include <QLineEdit>

class gameScreen:  public QMainWindow

{
    Q_OBJECT
    public:
        gameScreen(QMainWindow *parent = nullptr);
        ~gameScreen();
    private:
       // QPixmap *l;
        QLabel *l1;
        QLabel *l2;
        QLabel *l3;
        QLabel *l4;
        QLabel *l5;
        QLabel *l6;
        QLabel *l7;
        QLineEdit *satir;
        QLineEdit *sutun;

};

