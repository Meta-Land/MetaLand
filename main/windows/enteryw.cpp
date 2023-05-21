#include "enteryw.h"
#include "sqllib.h"

EnteryScreen::EnteryScreen(QString managerPlayer,QMainWindow *parent)
    : QMainWindow(parent)
{
    //giriş bölümlerinin tanımlanması
    nameEntery = new QLineEdit(this);
    surnameEntery = new QLineEdit(this);
    PasswordEntery = new QLineEdit(this);
    //giriş bölümlerine konum ve boyut atanması
    nameEntery->setGeometry(QRect(QPoint(150, 100), QSize(200, 30)));
    surnameEntery->setGeometry(QRect(QPoint(150, 140), QSize(200, 30)));
    PasswordEntery->setGeometry(QRect(QPoint(150, 180), QSize(200, 30)));
    // giriş bölmelerine yer tutucu eklenmesi (hiçbir giriş yokken kullanıcıya nereye ne gireceği hakkında bilgi verir)
    nameEntery->setPlaceholderText("Id Entery");
    surnameEntery->setPlaceholderText("Surname Entery");
    PasswordEntery->setPlaceholderText("Password Entery");
    nameEntery->setFocus();

    db = new QSqlDatabase();
    *db = connectDataBase();
    schemaBox = new QComboBox(this);
    updatecombo();

    gameLabel = new QLabel("Game Select",this);
    gameLabel->setGeometry(QRect(QPoint(470, 70), QSize(200, 30)));

    schemaBox->setCurrentIndex(0);
    schemaBox->setGeometry(QRect(QPoint(400, 100), QSize(200, 30)));
    connect(schemaBox,&QComboBox::currentIndexChanged,
            this,&EnteryScreen::dbConnect);
    dbConnect();

    gameSelectButton = new QPushButton("Start Game", this);
    gameSelectButton->setGeometry(QRect(QPoint(50, 220), QSize(300, 60)));
    connect(gameSelectButton, &QPushButton::released, this, std::bind(&EnteryScreen::gameSelectClicked, this,managerPlayer));

    if(managerPlayer == "player"){
        signUpButton = new QPushButton("Singup", this);
        signUpButton->setGeometry(QRect(QPoint(50, 285), QSize(300, 30)));
        connect(signUpButton, &QPushButton::released, this, &EnteryScreen::signUpClicked);

    }else{
        newGameLabel = new QLabel("New Game",this);
        newGameLabel->setGeometry(QRect(QPoint(770, 70), QSize(200, 30)));

        gameNameEntery = new QLineEdit(this);
        gameNameEntery->setGeometry(QRect(QPoint(700, 100), QSize(200, 30)));
        gameNameEntery->setPlaceholderText("Game Name");

        newGameButton = new QPushButton("Create New Game", this);
        newGameButton->setGeometry(QRect(QPoint(700, 140), QSize(200, 30)));
        connect(newGameButton, &QPushButton::released, this, &EnteryScreen::newGameClicked);
    }

    picLabel= new QLabel("",this);
    picLabel->setGeometry(QRect(QPoint(50, 91), QSize(90, 90)));

    //label resim ekleme
    QPixmap pic("../main/Assets/user.jpg");
    picLabel->setPixmap(pic);
}

bool EnteryScreen::signIn(QString managerPlayer)
{
    //Kullanıcı giriş yapmak istemektedir ve datalar okunarak bir sonraki adıma ilerlenmelidir
    QString name=nameEntery->text();
    QString surname=surnameEntery->text();
    QString password=PasswordEntery->text();
    QMessageBox msgBox;
    if(name == ""){
        msgBox.setText("isim Bölümü Boş Geçilemez!");
        msgBox.exec();
    }if(surname == ""){
        msgBox.setText("soyisim Bölümü Boş Geçilemez!");
        msgBox.exec();
    }else if(password == ""){
        msgBox.setText("Password Bölümü Boş Geçilemez!");
        msgBox.exec();
    }else{
        // verilen id ve password bulundu ise eşsiz datasını döndürür. bulunamadıysa -1
        personNum = IdPasswordControl(name,surname,password,managerPlayer);
        qDebug() <<"numara" <<personNum;
        if(personNum != -1){
            //id password bulunmuştur.
            qDebug() << "id password bulunmuştur.";
                return 1;
        }else{
            //id ve password bulunamamıştır.
            qDebug() << "id ve password bulunamamıştır.";
            msgBox.setText("ID Ve Password Bulunamamıştır.");
            msgBox.exec();
            return 0;
            //yeni sayfa
        }
    }
    return 0;
}

void EnteryScreen::dbConnect(){
    QString schema = schemaBox->currentText();
    connectDataBaseSchema(schema);
}

void EnteryScreen::signUpClicked()
{
    //kullanıcı kayıt olmak istemektedir yeni bir ekrana yönlendirilmelidir.
    secW = new SignUpScreen();
    secW->resize(400,350);
    secW->move((1920-400)/2, (1080-350)/2);
    secW->show();
}

void EnteryScreen::gameSelectClicked(QString managerPlayer){
    qDebug() << managerPlayer;
    QString schema = schemaBox->currentText();
    if(connectDataBaseSchema(schema)){
        if(signIn(managerPlayer)){
            //this->close();
            if(managerPlayer == "manager"){
                qDebug() << schema;
                managerScreen = new ManagerScreen();
                managerScreen->resize(1920,1080);
                managerScreen->move(0, 0);
                managerScreen->show();
                this->close();
            }else{
                thirdS= new gameScreen(personNum);
                thirdS->resize(1920,1080);
                thirdS->setStyleSheet("background:rgb(152,208,182);");
                qDebug() << "selam "<<thirdS->personNum1;
                thirdS->move(0,0);
                thirdS->show();
                this->close();
            }
        }
    }
}

void EnteryScreen::newGameClicked(){
    QString schemaName=gameNameEntery->text();
    createSchema(schemaName);
    updatecombo();
}

void EnteryScreen::updatecombo(){
    QString schemas[50];
    getSchemas(schemas);
    for(int i=0;i<50;i++){
        schemaBox->removeItem(i);
        if(schemas[i] != ""){
            schemaBox->insertItem(i,schemas[i]);
            qDebug() <<schemas[i];
        }
    }
}

EnteryScreen::~EnteryScreen()
{
}

