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
        void grassClicked(int x,int y);
        void showDetails();
    private:

        QLineEdit *satir;
        QLineEdit *sutun;
        QLabel *detail;
        QPushButton *market;
        QPushButton *property;
        QPushButton *mall;

        int height;
        int width;

};

