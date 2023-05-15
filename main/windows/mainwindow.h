#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include "enteryw.h"
#include <QLabel>
#include "./windows/analog_w.h"

class Screen : public QMainWindow

{
    Q_OBJECT
    public:
        Screen(QMainWindow *parent = nullptr);
        ~Screen();

    // Fonksiyon ön tanımlamaları slots bölümünde yapılıyor.
    private slots:
        void manager_clicked();
        void player_clicked();

    private:
        QLabel *label;
        QLabel *label_2;
        AnalogClock *clock;
        QPushButton *manager;
        QPushButton *player;
        EnteryScreen *secW;
};
