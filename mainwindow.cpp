#include "mainwindow.h"
#include "math.h"
#include <iostream>
#include <QApplication>
#include <QtAlgorithms>
#include <QFile>
#include <string>
#include "mainchar.h"
#include "bolt.h"
#include "background.h"
#include "bullet.h"
#include "kamek.h"
#include "spike.h"
#include "ground.h"
#include "ui.h"

using namespace std;

void MainWindow::findSol(){

}

void MainWindow::clearSol(){

}

void MainWindow::animate(){
  //view->setFocus();
  QWidget::setFocus();
  bool gen = false;
  if(zapu->getVX() == -2 && rCount == 0){
   //cout<<"VX: "<<zapu->getVX()<<endl;
   rCount = count;
   resetting = true;
  }
  else if(zapu->getVX() == -2 && (rCount+400) == count){
   rCount = 0;
   cout<<"BEFORE RESET\n";
   reset();
  } 
  
  if(resetting == false){
  zapu->move(count); 
  }
  if(zapu->getVX() == 1 || resetting == true){
  //cout<<"IN DISSS\n";
   for(unsigned int i = 0; i<bObjects.size(); i++){
    bObjects[i]->move(count);
    if(i == 0){
      floor = bObjects[i]->pos().y();
      if(bObjects[i]->pos().x() <-24 && (bObjects[i+1]->pos().x()>82)){
        floor = 500;
       }
       zapu->setGround(floor);
     }
     int last = bObjects.size()-1;
     //cout<<bObjects[last]->pos().x()<<endl;
     if(i == last && (bObjects[last]->pos().x() - bObjects[last-1]->pos().x())>64){
      bObjects[i-1]->setPixmap(*ground16);
     }
     else if(bObjects[i]->pos().x() == -64){
      //cout<<i<<" "<<bObjects[i]->pos().x()<<endl;
      scene->removeItem(bObjects.at(i));
      bObjects.erase(bObjects.begin()+i);
      gen = true;
     }
     else if(bObjects[i]->pos().x() == 0 && resetting == true && timer->isActive()){
        if(numLives==0){
        timer->stop();
        menus[2]->setVisible(true);
        QFormLayout *scoreLayout = new QFormLayout();
        scoreTxt = new QLabel("", this);
        QString qscore = QString::number(points);
        QFont font("Futura", 28, QFont::Bold, true);
        QFont font2("Futura", 21, QFont::Bold, true);
        font.setItalic(false);
        font2.setItalic(false);
        //nameBox->setFixedWidth(22);
        scoreTxt->setText(qscore);
        scoreTxt->setFixedHeight(44);
        //scoreTxt->setFixedWidth(300);
        scoreTxt->setFont(font);
        scoreLayout->addRow(scoreTxt);
        layout->addLayout(scoreLayout, 162, 228, 1, 100);
        
        QFormLayout *nameLayout = new QFormLayout();
        nameTxt = new QLabel("", this);
        nameTxt->setFixedHeight(32);
        nameTxt->setText(name);
        //cout<<"NAME: "<<name.toStdString()<<endl;
        nameTxt->setFont(font2);
        nameLayout->addRow(nameTxt);
        layout->addLayout(nameLayout, 161, 122, 1, 100);
       
        setLayout(layout);
        }
        else{
        cout<<i<<" "<<bObjects[i]->pos().x()<<" "<<floor<<endl;
        cout<<"STOPPING\n";
        resetting = false;
        zapu->setVX(0);
        zapu->setPixmap(*yoshi);
        zapu->setPos(10, floor-75);
        //zapu = new MainChar(yoshi, 10, floor-75); // Let’s pretend a default constructor
        zapu->setGround(floor);
        }
      }
   } //end for loop for ground items
    
   if(gen == true){
    int shift = bObjects[bObjects.size()-1]->pos().x();
    Ground *g  = new Ground(ground1, shift+64, bObjects[bObjects.size()-1]->pos().y()); 
    if(fObjects.size() == 0){
     g->setLimit(18);
    }
    else{
     g->setLimit(12);
     cout<<"DECREASED LIMIT\n";
    }
    bObjects.push_back(g);
    scene->addItem(bObjects.at(bObjects.size()-1));
   }//end ground items
 }
if(resetting == false){
  if(spiked == false && count!= 0 && count%4000==0){
    cout<<"NEW ENEMY\n";
    srand(time(NULL));
    int rn = rand()%2;
   if(rn == 0){
    Bullet *b  = new Bullet(bulletBill, bObjects[bObjects.size()-1]->pos().x(), 0); 
    fObjects.push_back(b);
    scene->addItem(fObjects[fObjects.size()-1]);
    }
    else if(rn == 1){
    Kamek *k  = new Kamek(witch, bObjects[bObjects.size()-1]->pos().x(), 0); 
    fObjects.push_back(k);
    spiked = false;
    scene->addItem(fObjects[fObjects.size()-1]);
    }
  }
   for(unsigned int i = 0; i<fObjects.size(); i++){
     fObjects[i]->move(count);
     if(spiked == false && fObjects[i]->getState() == 1){
      cout<<"SPIKE BALL\n";
       spiked = true;
       Spike *s  = new Spike(spikeBall, 35, -236); 
       fObjects.push_back(s);
       scene->addItem(fObjects[fObjects.size()-1]);
     }
     if(zapu->collidesWithItem(fObjects[i])){
        //cout<<"YOSHI HIT A BULLET\n";
        //cout<<"VX: "<<fObjects[0]->vX<<endl;
        //cout<<"Diff: "<<fObjects[0]->pos().x()-fObjects[1]->pos().x()<<endl;
       if(zapu->getVX() != -2 && (zapu->pos().x() > fObjects[i]->pos().x()) && (zapu->pos().y()-10) < fObjects[i]->pos().y()){
          zapu->collideUp(0);
          fObjects[i]->collideDown(0);
        }
        else {
         if(zapu->getState()==-1 && fObjects[i]->getState()==-1){
          bounceBack = true;
          zapu->collideUp(1);
          fObjects[i]->collideDown(1);
         }
         else{
          zapu->collideDown(0);
          fObjects[i]->collideUp(0);
          }
        }
      }
     if(bounceBack == true){
      for(unsigned int j = 1; j<fObjects.size(); j++){
       if(fObjects[i]->getState()==1 && fObjects[j]->getState()==-1){
       if(fObjects[i]->collidesWithItem(fObjects[j])){
          spiked = false;
          bounceBack = false;
          cout<<"CASE 1\n";
  	  scene->removeItem(fObjects.at(i));
  	  cout<<"CASE 2\n";
   	  scene->removeItem(fObjects.at(j));
   	  cout<<"CASE 3\n";
	  fObjects.erase(fObjects.begin()+i);
	  cout<<"CASE 4\n";
	  fObjects.erase(fObjects.begin()+j-1);
	  cout<<"CASE 5\n";
        }
       }}
      }
     if(fObjects[i]->pos().x()<-100 || fObjects[i]->pos().y()>110){
      cout<<"REMOVE BULLET\n";
      scene->removeItem(fObjects[i]);
      fObjects.erase(fObjects.begin()+i);
     }
    }
   for(unsigned int i = 0; i<zObjects.size(); i++){
    zObjects[i]->move(count);
    if(zObjects[i]->pos().x()>500){
     scene->removeItem(zObjects[i]);
     zObjects.erase(zObjects.begin()+i);
    }
   }
  if(zapu->pos().y() > 35){
    reset();
   }
  if(zapu->getVX() == 1 && count%100 == 0){
    points++;
    updateScore();
   }
}
  count++;
}

void MainWindow::startGame(){

}


void MainWindow::keyPressEvent(QKeyEvent *e){
if(resetting == false && timer->isActive()){
 if(zapu->getState()!=-2){
  zapu->keySignal(e);
  if(!e->isAutoRepeat() && e->key() == Qt::Key_Space){
    Bolt *b  = new Bolt(elec, 77, zapu->pos().y()+3);
    zObjects.push_back(b);
    scene->addItem(b);
  }
 }
}
}

void MainWindow::keyReleaseEvent(QKeyEvent *r){
if(resetting == false && timer->isActive()){
 if(zapu->getState()!=-2){
  if(r->isAutoRepeat()){
   r->ignore();
  }
  else{
   zapu->keyRelease(r);
  }
 }
}
}

void MainWindow::mousePressEvent(QMouseEvent *event){
 // cout<<"HERE\n";
if(menus[0]->isVisible() || menus[1]->isVisible()){
if(event->pos().x() >= ((WINDOW_MAX_X/2)-141) && event->pos().x()<= (WINDOW_MAX_X/2)+141){
   if(event->pos().y()>= 160 && event->pos().y() <= 224){
    if(menus[1]->isVisible()){
      menus[1]->setVisible(false);
     }
     else {
     menus[0]->setVisible(false);
     menus[3]->setVisible(true);
     nameBox = new QLineEdit();
     QFont font("Futura", 19, QFont::Bold, true);
     font.setItalic(false);
     //nameBox->setFixedWidth(22);
     nameBox->setFixedHeight(44);
     nameBox->setFont(font);
     layout->addWidget(nameBox, 182, 168, 100, 250);
     setLayout(layout);
     //scene->addItem(&nameBox);
     //timer->start();
   }
 }}
 if(event->pos().x() >= ((WINDOW_MAX_X/2)-141) && event->pos().x()<= (WINDOW_MAX_X/2)+141){
   if(event->pos().y()>= 340 && event->pos().y() <= 404){
   qApp->quit();
 }}
}
else if(menus[2]->isVisible()){
 if(event->pos().x() >= ((WINDOW_MAX_X/2)-141) && event->pos().x()<= (WINDOW_MAX_X/2)+141){
   if(event->pos().y()>= 340 && event->pos().y() <= 404){
     qApp->quit();
 }}
}
else if(menus[3]->isVisible()){
 if(event->pos().x() >= ((WINDOW_MAX_X/2)-68) && event->pos().x()<= (WINDOW_MAX_X/2)+214){
   if(event->pos().y()>= 265 && event->pos().y() <= 329){
   //bool isString;
   //QString nameTxt = nameBox->text();
   if(nameBox->text().isEmpty()){
    menus[4]->setVisible(true);
   }
   else{
    name = nameBox->text();
    delete nameBox;
    menus[3]->setVisible(false);
    menus[4]->setVisible(false);
    timer->start();
   }
 }}
}
else if(timer->isActive()){
 if(event->pos().x() >= (WINDOW_MAX_X-66) && event->pos().x()<= WINDOW_MAX_X){
   if(event->pos().y()>= 0 && event->pos().y() <= 55){
    cout<<"PAUSE"<<endl;
    timer->stop();
    menus[0]->setVisible(true);
    menus[1]->setVisible(true);
  }}
}
}

void MainWindow::reset(){
 resetting = true;
 spiked = false;
 bounceBack = false;
 while(!fObjects.empty()){
   scene->removeItem(fObjects.at(0));
   cout<<"BEFORE SIZE: "<<fObjects.size()<<endl;
   //delete fObjects.back();
   fObjects.erase(fObjects.begin());
   cout<<"AFTER SIZE: "<<fObjects.size()<<endl;
 }
 while(!zObjects.empty()){
   scene->removeItem(zObjects.at(0));
   //delete fObjects.back();
   zObjects.erase(zObjects.begin());
 }
 numLives--;
 switch(numLives){
  case 0: eggs[0]->setVisible(false); /* reset */
  case 1: eggs[1]->setVisible(false);
  case 2: eggs[2]->setVisible(false); break;
  case 3: eggs[3]->setVisible(false); break;
 }
}

void MainWindow::updateScore(){
   int thous, hunds, tens, ones;
 if(points < 10){
   score[0]->setPixmap(*scoreImage(points));
 }
 else if(points < 100){
   tens = points/10;
   ones = points%10;
   score[0]->setPixmap(*scoreImage(tens));
   score[1]->setVisible(true);
   score[1]->setPixmap(*scoreImage(ones));
 }
 else if(points < 1000){
   hunds = points/100;
   tens = (points/10)%10;
   ones = points%10;
   score[0]->setPixmap(*scoreImage(hunds));
   score[1]->setVisible(true);
   score[1]->setPixmap(*scoreImage(tens));
   score[2]->setVisible(true);
   score[2]->setPixmap(*scoreImage(ones));
 }
 else if(points < 10000){
   thous = points/1000;
   hunds =  (points/100)%10;
   tens = (points/10)%10;
   ones = points%10;
   score[0]->setPixmap(*scoreImage(thous));
   score[1]->setPixmap(*scoreImage(hunds));
   score[1]->setVisible(true);
   score[2]->setPixmap(*scoreImage(tens));
   score[2]->setVisible(true);
   score[3]->setPixmap(*scoreImage(ones));
   score[3]->setVisible(true);
 }
}

QPixmap* MainWindow::scoreImage(int num){
 QPixmap *p = zero;
 switch(num){
  case 1: p = one; break;
  case 2: p = two; break;
  case 3: p = three; break;
  case 4: p = four; break;
  case 5: p = five; break;
  case 6: p = six; break;
  case 7: p = seven; break;
  case 8: p = eight; break;
  case 9: p = nine; break;
 }
  return p;
}

/** MainWindow default constructor. A new scene is created a view is set to
 *  it with it's parent as scene. A new grid layout and form layout (for
 *  the view are created. New form layouts are created for each QLabel (text)
 *  and are added to the grid layouts in the appropriate locations. A view
 *  is created with the appropriate size, added to a form layout and then
 *  placed in the grid layout. QWidgets (QLineEdits, QRadioButtons, QPushButtons
 *  and QListView) are added to the grid layout without the need of form 
 *  layouts. QPushButtons are linked to the appropriate functions (called when
 *  clicked). QListView is set a maximum width and maximum height to improve
 *  the UI. The timer is set to the slot animate with a duration of 4. Count
 *  is set to 0 and updateCheat is set to false (default values). Finally
 *  the layout is set to the grid layout.
 *  
 *  @return nothing
 */
MainWindow::MainWindow()  {
    statusBar = new QGraphicsView();
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    layout = new QGridLayout(); 
    QFormLayout *viewLayout = new QFormLayout();
    //viewLayout = new QFormLayout();
    
 /* QFormLayout *messageLayout = new QFormLayout();
    message = new QLabel("", this);
    messageLayout->addRow(message);
    layout->addLayout(messageLayout, 0, 0, 1, 9);
    
    QFormLayout *sizeLayout = new QFormLayout();
    QLabel *sizeTxt = new QLabel("Size", this);
    sizeLayout->addRow(sizeTxt);
    layout->addLayout(sizeLayout, 1, 9, 1, 1);
    
    QFormLayout *initLayout = new QFormLayout();
    QLabel *initTxt = new QLabel("Initial Moves", this);
    initLayout->addRow(initTxt);
    layout->addLayout(initLayout, 2, 9, 1, 1);
    
    QFormLayout *randomLayout = new QFormLayout();
    QLabel *randomTxt = new QLabel("Random Seed #", this);
    randomLayout->addRow(randomTxt);
    layout->addLayout(randomLayout, 3, 9, 1, 1);
    
    QFormLayout *heurLayout = new QFormLayout();
    QLabel *heurTxt = new QLabel("Heuristic: ", this);
    heurLayout->addRow(heurTxt);
    layout->addLayout(heurLayout, 4, 9, 1, 1);
    
    sizeEdit = new QLineEdit(); 
    layout->addWidget(sizeEdit, 1, 10, 1, 1);
    
    startMovesEdit = new QLineEdit(); 
    layout->addWidget(startMovesEdit, 2, 10, 1, 1);
    
    randomSeedEdit = new QLineEdit(); 
    layout->addWidget(randomSeedEdit, 3, 10, 1, 1);
    
    mHeur = new QRadioButton("Manhattan");
    layout->addWidget(mHeur, 4, 10, 1, 1);

    oHeur = new QRadioButton(("Out Of Place"));
    layout->addWidget(oHeur, 5, 10, 1, 1);
    
    start = new QPushButton("Start");
    connect( start, SIGNAL(clicked()), SLOT(startGame()) );
    layout->addWidget(start, 6, 9, 1, 1); 
    
    ///// You'll need this later ///////
    quit = new QPushButton("Quit", this );
    connect( quit, SIGNAL(clicked()), qApp, SLOT(quit()) );
    layout->addWidget(quit, 6, 10, 1, 1);

    cheat = new QPushButton("Cheat");
    connect(cheat, SIGNAL(clicked()), SLOT(findSol()) );
    layout->addWidget(cheat, 7, 9, 1, 1);
    
    clear = new QPushButton("Hide Cheat", this );
    connect(clear, SIGNAL(clicked()), SLOT(clearSol()));
    layout->addWidget(clear, 7, 10, 1, 1);
    
    cheatList = new QListView();
    cheatList->setMaximumWidth(127);
    cheatList->setMaximumHeight(153);
    layout->addWidget(cheatList, 8, 10, 1, 1);
    */
    count = 0;
    points = 0;
    numLives = 3;
    rCount = 0;
    resetting = false;
    spiked = false;
    bounceBack = false;
 // updateCheat = false;
    
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
    timer->setInterval(3);
    //timer->start();
    
    zero = new QPixmap(qApp->applicationDirPath()+"/Pictures/0.png");
    one = new QPixmap(qApp->applicationDirPath()+"/Pictures/1.png");
    two = new QPixmap(qApp->applicationDirPath()+"/Pictures/2.png");
    three = new QPixmap(qApp->applicationDirPath()+"/Pictures/3.png");
    four = new QPixmap(qApp->applicationDirPath()+"/Pictures/4.png");
    five = new QPixmap(qApp->applicationDirPath()+"/Pictures/5.png");
    six = new QPixmap(qApp->applicationDirPath()+"/Pictures/6.png");
    seven = new QPixmap(qApp->applicationDirPath()+"/Pictures/7.png");
    eight = new QPixmap(qApp->applicationDirPath()+"/Pictures/8.png");
    nine = new QPixmap(qApp->applicationDirPath()+"/Pictures/9.png");
    
    bMenu = new QPixmap(qApp->applicationDirPath()+"/Pictures/Menu1.png");
    pMenu = new QPixmap(qApp->applicationDirPath()+"/Pictures/Menu2.png");
    sMenu = new QPixmap(qApp->applicationDirPath()+"/Pictures/Menu3.png");
    nMenu = new QPixmap(qApp->applicationDirPath()+"/Pictures/NameMenu.png");
    error = new QPixmap(qApp->applicationDirPath()+"/Pictures/NameError.png");
        
    ground1 = new QPixmap(qApp->applicationDirPath() + "/Pictures/Ground1.png");
    ground16 = new QPixmap(qApp->applicationDirPath() + "/Pictures/Ground16.png");
    bulletBill = new QPixmap(qApp->applicationDirPath() + "/Pictures/BulletBill.png");
    witch = new QPixmap(qApp->applicationDirPath() + "/Pictures/Kamek1.png");
    spikeBall = new QPixmap(qApp->applicationDirPath() + "/Pictures/SpikeBall.png");
    elec = new QPixmap(qApp->applicationDirPath() + "/Pictures/Bolt.png");
    QPalette palette;
    QPixmap world, status;
    world.load(qApp->applicationDirPath()+"/Pictures/fullView.png");
    
   /* status.load(qApp->applicationDirPath()+"/Pictures/StatusBarPause.png");  
    statusBar->setFixedSize(WINDOW_MAX_X, 61);
    palette.setBrush(statusBar->backgroundRole(), status);
    statusBar->setPalette(palette);
    viewLayout->addRow(statusBar);
    viewLayout->setVerticalSpacing(0);*/
    
    scene->setSceneRect(0, -WINDOW_MAX_Y+50, WINDOW_MAX_X-4, WINDOW_MAX_Y-4);
    view->setFixedSize(WINDOW_MAX_X, WINDOW_MAX_Y);
    viewLayout->addRow(view);
    view->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    palette.setBrush(view->backgroundRole(), world);
    view->setPalette(palette);
    QWidget::setFocus();
    layout->addLayout(viewLayout, 0, 0, 506, 466);

    //World *w  = new World(world, 0, -341); // Let’s pretend a default constructor
    //bObjects.push_back(w);
    QPixmap *ground = new QPixmap(qApp->applicationDirPath()+"/Pictures/Ground1.png");
   for(int i = 1; i<=12; i++){
    Ground *g  = new Ground(ground, (i-1)*64, 20); 
    g->setLimit(12);
    bObjects.push_back(g);
    }
    yoshi = new QPixmap(qApp->applicationDirPath()+"/Pictures/YW1.png");
    zapu = new MainChar(yoshi, 10, -55); // Let’s pretend a default constructor
    scene->addItem(zapu);
    for (unsigned int i=0; i<bObjects.size(); i++ ) {
     scene->addItem(bObjects.at(i));
    }
    
    UI *menu1 = new UI(bMenu, 0, -410, true);
    menus.push_back(menu1);
    UI *menu2 = new UI(pMenu, 0, -410, false);
    menus.push_back(menu2);
    UI *menu3 = new UI(sMenu, 0, -410, false);
    menus.push_back(menu3);
    UI *menu4 = new UI(nMenu, 0, -410, false);
    menus.push_back(menu4);
    UI *nError = new UI(error, 50, -275, false);
    menus.push_back(nError);
    
    QPixmap *bwEgg;
    UI *uiItem, *num;
    for(int i = 0; i<3; i++){
     bwEgg = new QPixmap(qApp->applicationDirPath()+"/Pictures/bwEgg.png");
     uiItem = new UI(bwEgg, i*34+92, -397, true);
     eggs.push_back(uiItem);
     scene->addItem(uiItem);
    }
    for(int j = 0; j<5; j++){
     num = new UI(zero, j*15+309, -394, false);
     score.push_back(num);
     scene->addItem(num);
    }
    for(unsigned int i = 0; i<menus.size(); i++){
      menus[i]->setZValue(5);
      scene->addItem(menus[i]);
    }
    
    score[0]->setVisible(true);
    setLayout(layout);
    
}

/** QWidget shows all that has been added to it (the grid layout).
 *
 *  @return nothing
 */
void MainWindow::show() {
    QWidget::show();
}

/** Destructor for MainWindow. Clears and deletes all items in order of
 *  their hierarchy (buttons then layouts then main layout).
 *  
 *  @return nothing
 */
MainWindow::~MainWindow(){
    delete timer;
 /* delete message;
    delete sizeEdit;
    delete startMovesEdit;
    delete randomSeedEdit;
    delete mHeur;
    delete oHeur;
    delete start;
    delete cheat;
    delete quit;
    delete clear;
    delete cheatList;
    delete layout;*/
    delete scene;
    delete view;
}

