#include "mainwindow.h"
#include "math.h"
#include <iostream>
#include <QApplication>
#include <QtAlgorithms>
#include <QFile>
#include "mainchar.h"
#include "bolt.h"
#include "background.h"
#include "bullet.h"
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
  //int last = objects.size()-1;
  bool gen = false;
  fObjects[0]->move(count); 
  if(fObjects[0]->vX == 1){
   for(unsigned int i = 0; i<bObjects.size(); i++){
    bObjects[i]->move(count);
    if(i == 0){
     int floor = bObjects[i]->pos().y();
      if(bObjects[i]->pos().x() <-24 && (bObjects[i+1]->pos().x()>82)){
        floor = 500;
       }
       fObjects[0]->setGround(floor);
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
   } //end for loop for ground items
    
   if(gen == true){
    int shift = bObjects[bObjects.size()-1]->pos().x();
    Ground *g  = new Ground(ground1, shift+64, bObjects[bObjects.size()-1]->pos().y()); 
    if(fObjects.size() == 1){
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
 if(count!= 0 && count%4000==0){
    cout<<"NEW ENEMY\n";
    Bullet *b  = new Bullet(bulletBill, bObjects[bObjects.size()-1]->pos().x(), 0); 
    fObjects.push_back(b);
    scene->addItem(fObjects[fObjects.size()-1]);
 }
  for(unsigned int i = 1; i<fObjects.size(); i++){
    fObjects[i]->move(count);
    if(fObjects[0]->collidesWithItem(fObjects[1])){
       //cout<<"YOSHI HIT A BULLET\n";
       //cout<<"VX: "<<fObjects[0]->vX<<endl;
       //cout<<"Diff: "<<fObjects[0]->pos().x()-fObjects[1]->pos().x()<<endl;
      if(fObjects[0]->vX == 1 && (fObjects[0]->pos().x() > fObjects[1]->pos().x()) && (fObjects[0]->pos().y()-10) < fObjects[1]->pos().y()){
         fObjects[0]->collideUp(0);
         fObjects[1]->collideDown(0);
       }
       else {
         fObjects[0]->collideDown(0);
         fObjects[1]->collideUp(0);
       }
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
  count++;
}

void MainWindow::startGame(){

}

void MainWindow::keyPressEvent(QKeyEvent *e){
 fObjects[0]->keySignal(e);
 if(!e->isAutoRepeat() && e->key() == Qt::Key_Space){
   Bolt *b  = new Bolt(elec, 77, fObjects[0]->pos().y()+3);
   zObjects.push_back(b);
   scene->addItem(b);
 }
}

void MainWindow::keyReleaseEvent(QKeyEvent *r){
 if(r->isAutoRepeat()){
  r->ignore();
 }
 else{
  fObjects[0]->keyRelease(r);
 }
}

void MainWindow::mousePressEvent(QMouseEvent *event){
  cout<<"HERE\n";
 if(event->pos().x() >= (WINDOW_MAX_X-66) && event->pos().x()<= WINDOW_MAX_X){
   if(event->pos().y()>= 0 && event->pos().y() <= 55){
    cout<<"PAUSE"<<endl;
    }
  }
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
    //layout = new QGridLayout(); 
    QFormLayout *viewLayout = new QFormLayout();
    
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
    
 // updateCheat = false;
    
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
    timer->setInterval(3);
    timer->start();
    
    
    ground1 = new QPixmap(qApp->applicationDirPath() + "/Pictures/Ground1.png");
    ground16 = new QPixmap(qApp->applicationDirPath() + "/Pictures/Ground16.png");
    bulletBill = new QPixmap(qApp->applicationDirPath() + "/Pictures/BulletBill.png");
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
    //layout->addLayout(viewLayout, 1, 0, 9, 9);

    //World *w  = new World(world, 0, -341); // Let’s pretend a default constructor
    //bObjects.push_back(w);
    QPixmap *ground = new QPixmap(qApp->applicationDirPath()+"/Pictures/Ground1.png");
   for(int i = 1; i<=12; i++){
    Ground *g  = new Ground(ground, (i-1)*64, 20); 
    g->setLimit(12);
    bObjects.push_back(g);
    }
    QPixmap *yoshi = new QPixmap(qApp->applicationDirPath()+"/Pictures/YW1.png");
    MainChar* m = new MainChar(yoshi, 10, -55); // Let’s pretend a default constructor
    fObjects.push_back(m);
    for (unsigned int i=0; i<bObjects.size(); i++ ) {
     scene->addItem(bObjects.at(i));
    }
    scene->addItem(fObjects.at(0));
    QPixmap *eggs;
    UI *uiItem;
    for(int i = 0; i<3; i++){
     eggs = new QPixmap(qApp->applicationDirPath()+"/Pictures/bwEgg.png");
     uiItem = new UI(eggs, i*34+92, -396, true);
     scene->addItem(uiItem);
    }
    setLayout(viewLayout);
    
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

