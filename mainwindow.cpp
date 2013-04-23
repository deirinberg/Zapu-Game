#include "mainwindow.h"
#include "math.h"
#include <iostream>
#include <QApplication>
#include <QtAlgorithms>
#include <QFile>
#include "mainchar.h"
#include "background.h"
#include "ground.h"

using namespace std;

void MainWindow::findSol(){

}

void MainWindow::clearSol(){

}

void MainWindow::animate(){
  view->setFocus();
  QWidget::setFocus();
  int last = objects.size()-1;
  bool gen = false;
  objects[last]->move(count); 
  if(objects[last]->vX == 1){
   for(int i = 1; i<last; i++){
    objects[i]->move(count);
     if(i == (last-1) && (objects[last-1]->pos().x() - objects[last-2]->pos().x())>64){
      QPixmap *ground = new QPixmap("/home/cs102/game_eirinber/Pictures/Ground16.png");
      objects[i-1]->setPixmap(*ground);
     }
     else if(objects[i]->pos().x() == -64){
      cout<<i<<" "<<objects[i]->pos().x()<<endl;
      scene->removeItem(objects.at(i));
      objects.erase(objects.begin()+i);
      gen = true;
     }
   }
   if(gen == true){
    int index = objects.size()-2;
    int shift = objects[index]->pos().x();
    cout<<"LAST: "<<objects[index]->pos().x()<<" "<<shift+64<<endl;
    QPixmap *ground = new QPixmap("/home/cs102/game_eirinber/Pictures/Ground1.png");
    Ground *g  = new Ground(ground, shift+64, objects[index]->pos().y()); 
    objects.insert(objects.end()-1, g);
    scene->removeItem(objects.at(objects.size()-1));
    scene->addItem(objects.at(objects.size()-2));
    scene->addItem(objects.at(objects.size()-1));
   }
 }
  count++;
}

void MainWindow::startGame(){

}

void MainWindow::keyPressEvent(QKeyEvent *e){
 objects[objects.size()-1]->keySignal(e);
}

void MainWindow::keyReleaseEvent(QKeyEvent *r){
 if(r->isAutoRepeat()){
  r->ignore();
 }
 else{
  objects[objects.size()-1]->keyRelease(r);
 }
}

void MainWindow::mouseEvent(QMouseEvent *m){
 m->ignore();
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
    scene = new QGraphicsScene();
    view = new QGraphicsView( scene );
    layout = new QGridLayout(); 
    QFormLayout *viewLayout = new QFormLayout();
    
    QFormLayout *messageLayout = new QFormLayout();
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
    
    count = 0;
    
    updateCheat = false;
    
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
    timer->setInterval(4);
    timer->start();
    
    scene->setSceneRect(0, -3*WINDOW_MAX_Y/2+50, 3*WINDOW_MAX_X/2+96, 3*WINDOW_MAX_Y/2-4);
    view->setFixedSize(3*WINDOW_MAX_X/2+100, 3*WINDOW_MAX_Y/2);
    viewLayout->addRow(view);
    view->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //view->setFocusPolicy(Qt::NoFocus);
    QWidget::setFocus();
    layout->addLayout(viewLayout, 1, 0, 9, 9);
    QPixmap *background = new QPixmap("/home/cs102/game_eirinber/Pictures/Background.png");
    Background *b  = new Background(background, 0, -341); // Let’s pretend a default constructor
    objects.push_back(b);
    QPixmap *ground = new QPixmap("/home/cs102/game_eirinber/Pictures/Ground1.png");
   for(int i = 1; i<=12; i++){
    Ground *g  = new Ground(ground, (i-1)*64, 20); 
    objects.push_back(g);
    }
    QPixmap *yoshi = new QPixmap("/home/cs102/game_eirinber/Pictures/YW1.png");
    MainChar* m = new MainChar(yoshi, 10, -55); // Let’s pretend a default constructor
    objects.push_back(m);
    for (unsigned int i=0; i<objects.size(); i++ ) {
     scene->addItem(objects.at(i));
    }
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
    delete message;
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
    delete layout;
    delete scene;
    delete view;
}

