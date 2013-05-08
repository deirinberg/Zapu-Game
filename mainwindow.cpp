#include "mainwindow.h"
#include "math.h"
#include <iostream>
#include <QApplication>
#include <QtAlgorithms>
#include <QFile>
#include <string>
#include <fstream>
#include <sstream>
#include "mainchar.h"
#include "bolt.h"
#include "background.h"
#include "bullet.h"
#include "fireball.h"
#include "heatBullet.h"
#include "extraEgg.h"
#include "kamek.h"
#include "spike.h"
#include "bowser.h"
#include "fireBowser.h"
#include "ground.h"
#include "ui.h"

using namespace std;

/** Controls all of the movements of the game. If the player lost (vx is -2
 *  vy is 0 and player's state is -2 it will call the reset function). If
 *  the game isn't resetting the player will move. If the player is moving or
 *  the game is resetting the ground will move in the left direction to look 
 *  like the player is moving in the right direction. If there is a gap the ground
 *  image will be set to an end piece. If ground pieces go off screen they will be
 *  cleared and removed from the scene. If the player loses all of their lives the
 *  game will display their name and score with the option of starting a new game or
 *  quitting. If they lose only a life the ground will move past the gap and the 
 *  main character will reappear. Once a tile goes off the screen a ground piece will
 *  replace it offscreen (randomly generated). If the game isn't resetting a thing
 *  will be randomly selected and added to the view. Bowser needs 5 pieces of ground
 *  ahead of him so he doesn't typically float. Animate will then test the collisons 
 *  (which can only occur between two visible objects). Zapu can bounce off the top
 *  of bullets (but not their tip) but loses a life hitting them in other places.
 *  Zapu dies when hitting the witch. If Zapu is in an egg (VX=-2) it can bounce
 *  back spike balls which will make it lose a life in any other state. Electricity
 *  bolts are tested to collide with Bowser whose health goes down after each hit.
 *  Zapu will lose a life by colliding with any part of bowser. Extra life eggs
 *  can only be generated when the user has 3 lifes or less and are added to the
 *  status bar when run over. If bad collisions occur zapu's vx is set to -2 and its
 *  vy is set to 0 so the game can reset. If zapu falls through a gap the game is reset.
 *  Finally the score is incremented and updated depending on the count duration.
 *  
 *  @return nothing
 */
void MainWindow::animate(){
  QWidget::setFocus();
  bool gen = false;
  if(zapu->getVX() == -2 && zapu->getVY()==0 && zapu->getState()!=-2){
   zapu->setState(-2);
   zapu->setVisible(false);
   resetting = true;
   reset();
  }
  if(resetting == false && zapu->getState()!=-2){
   zapu->move(count); 
    if(zapu->pos().y() > 36){
     resetting = true;
     reset();
    }
  }
  if(zapu->getVX() == 1 || resetting == true){
   for(unsigned int i = 0; i<bObjects.size(); i++){
    bObjects[i]->move(count);
    if(resetting == false){
      floor = bObjects[0]->pos().y();
      if(bObjects[0]->pos().x()>=90 || (bObjects[0]->pos().x()<=-54 && bObjects[1]->pos().x()>=90)){
        floor = 500;
       }
      if(zapu->pos().y() < 36){
       zapu->setGround(floor);
      }
     }
     int last = 0;
     if(i == bObjects.size()-1){
      last = bObjects.size()-1;
     }
     if(last!=0 && (bObjects[last]->pos().x() - bObjects[last-1]->pos().x())>64){
      bObjects[i-1]->setPixmap(*ground16);
     }
     else if(bObjects[i]->pos().x() == -64){
      scene->removeItem(bObjects.at(i));
      bObjects.erase(bObjects.begin()+i);
      gen = true;
     }
     else if(bObjects[i]->pos().x() == 0 && resetting == true && timer->isActive()){
        if(numLives==0){
        timer->stop();
        hs->update(name.toStdString(), points);
        menus[2]->setVisible(true);
        QFormLayout *scoreLayout = new QFormLayout();
        scoreTxt = new QLabel("", this);
        QString qscore = QString::number(points);
        QFont font("Futura", 28, QFont::Bold, true);
        QFont font2("Futura", 21, QFont::Bold, true);
        font.setItalic(false);
        font2.setItalic(false);
        scoreTxt->setText(qscore);
        scoreTxt->setFixedHeight(44);
        scoreTxt->setFont(font);
        scoreLayout->addRow(scoreTxt);
        layout->addLayout(scoreLayout, 162, 228, 1, 100);
        
        QFormLayout *nameLayout = new QFormLayout();
        nameTxt = new QLabel("", this);
        nameTxt->setFixedHeight(32);
        nameTxt->setText(name);
        nameTxt->setFont(font2);
        nameLayout->addRow(nameTxt);
        layout->addLayout(nameLayout, 161, 122, 1, 100);
        setLayout(layout);
        }
        else{
        zapu->setVX(0);
        zapu->setVisible(true);
        zapu->setPixmap(*yoshi);
        zapu->setPos(10, bObjects[0]->pos().y()-75);
        zapu->setGround(floor);
        resetting = false;
        }
      }
   }
   if(gen == true){
    int shift = bObjects[bObjects.size()-1]->pos().x();
    Ground *g  = new Ground(ground1, shift+64, bObjects[bObjects.size()-1]->pos().y()); 
    if((genCount == -1 && fObjects.size() == 0) || moreGaps == true){
      g->setLimit(18);
    }
    else{
     g->setLimit(12);
    }
    if(genCount != -1){
     genCount++;
    }
    bObjects.push_back(g);
    scene->addItem(bObjects.at(bObjects.size()-1));
   }
 }
if(resetting == false){
 if(genCount == 5){
   int ground = bObjects[bObjects.size()-1]->pos().y();
    if(fireB == false){
     Bowser *b  = new Bowser(bWalk, bObjects[bObjects.size()-1]->pos().x(), ground); 
     fObjects.push_back(b);
     scene->addItem(fObjects[fObjects.size()-1]);
    }
    else{
     FireBowser *fb  = new FireBowser(bWalk, bObjects[bObjects.size()-1]->pos().x(), ground); 
     fObjects.push_back(fb);
     scene->addItem(fObjects[fObjects.size()-1]);
    }
   genCount = -1;
 }
  int div = 2000*freq;
  if(spiked == false && genCount == -1 && count!= 0 && count%div==0){
    srand(time(NULL));
    int rn = rand()%6;
    moreGaps = false;
    if(rn == 0){
    Bullet *b  = new Bullet(bulletBill, bObjects[bObjects.size()-1]->pos().x(), 0); 
    fObjects.push_back(b);
    scene->addItem(fObjects[fObjects.size()-1]);
    }
    else if(rn == 1){
    HeatBullet *hb  = new HeatBullet(heatBB, bObjects[bObjects.size()-1]->pos().x(), zapu->pos().y()); 
    fObjects.push_back(hb);
    scene->addItem(fObjects[fObjects.size()-1]);
    }
    else if(rn == 2){
    Kamek *k  = new Kamek(witch, bObjects[bObjects.size()-1]->pos().x(), 0); 
    fObjects.push_back(k);
    spiked = false;
    scene->addItem(fObjects[fObjects.size()-1]);
    }
    else if(rn == 3){
    genCount = 0;
    fireB = false;
    }
    else if(rn == 4){
    genCount = 0;
    fireB = true; 
    }
    else if(rn == 5){
    if(numLives <= 3 && points>=150 && count%3==0){
    int ground = bObjects[bObjects.size()-1]->pos().y();
    ExtraEgg *e  = new ExtraEgg(eEgg, bObjects[bObjects.size()-1]->pos().x(), ground-18); 
    fObjects.push_back(e);
    scene->addItem(fObjects[fObjects.size()-1]);
    }
    else{
     moreGaps = true;
    }
   }
  }
  for(unsigned int i = 0; i<fObjects.size(); i++){
     int state = fObjects[i]->getState();
     if(state!=4 && state!=7){
      fObjects[i]->move(count);
     }
     else if((state == 4 || state == 7) && zapu->getVX()==1){
      fObjects[i]->move(count);
     }
   if(state == -2 && fObjects[i]->pos().x()>250){
      fObjects[i]->setPos(fObjects[i]->pos().x(), zapu->pos().y());
   }
   if(state == 5){
     fObjects[i]->setPos(fObjects[i]->pos().x(), zapu->pos().y());
    if(count%800==0 && fObjects[i]->pos().y()<500){
     FireBall *f  = new FireBall(fire, fObjects[0]->pos().x(), fObjects[0]->pos().y()+5); 
     fObjects.push_back(f);
     scene->addItem(fObjects[fObjects.size()-1]);
    }
   }
   if(spiked == false && state == 1){
      spiked = true;
      Spike *s  = new Spike(spikeBall, 35, -236); 
      fObjects.push_back(s);
      scene->addItem(fObjects[fObjects.size()-1]);
   }
   if(fObjects[i]->isVisible() && zapu->isVisible()){
     if(zapu->collidesWithItem(fObjects[i])){
       if(zapu->getVX() != -2 && (zapu->pos().x() > fObjects[i]->pos().x()) && (zapu->pos().y()-10) < fObjects[i]->pos().y()){
        if(state!=3 && state!=4 && state!=5 && state!=7){ 
          zapu->collideUp(0);
          fObjects[i]->collideDown(0);
          if(state==3){
           fObjects[i-1]->collideDown(0);
          }
         }
         else if(state!=4){
          zapu->setVX(-2);
          zapu->collideDown(0);
          fObjects[i]->collideUp(0);
          zapu->setState(1);
         }
         else if(state==7){
           scene->removeItem(fObjects.at(i));
	   fObjects.erase(fObjects.begin()+i);
           addEgg();
         }
        }
        else if(state!=4){
         if(zapu->getState()==-1 && state==-1){
          bounceBack = true;
          zapu->collideUp(1);
          fObjects[i]->collideDown(1);
         }
         else if(state==7){
          scene->removeItem(fObjects.at(i));
	  fObjects.erase(fObjects.begin()+i);
          addEgg();
         }
         else{
          zapu->setVX(-2);
          zapu->collideDown(0);
          zapu->setState(1);
          fObjects[i]->collideUp(0);
          }
        }
      }
     if(bounceBack == true){
      for(unsigned int j = 1; j<fObjects.size(); j++){
       if(state==1 && fObjects[j]->getState()==-1){
       if(fObjects[i]->collidesWithItem(fObjects[j])){
          spiked = false;
          bounceBack = false;
  	  scene->removeItem(fObjects.at(i));
   	  scene->removeItem(fObjects.at(j));
	  fObjects.erase(fObjects.begin()+i);
	  fObjects.erase(fObjects.begin()+j-1);
        }
       }}
      }
     else if(state==3 || state == 5){
       for(unsigned int j = 1; j<zObjects.size(); j++){
         if(fObjects[i]->collidesWithItem(zObjects[j])){
           scene->removeItem(zObjects[j]);
           zObjects.erase(zObjects.begin()+j);
           fObjects[i]->collideDown(3);
        }
       }
     }
     else if(state==4 && zapu->collidesWithItem(fObjects[i])){
         scene->removeItem(fObjects[i]);
         fObjects.erase(fObjects.begin()+i);
     }
     if(fObjects[i]->pos().x()<-125 || fObjects[i]->pos().y()>110){
      scene->removeItem(fObjects[i]);
      fObjects.erase(fObjects.begin()+i);
     }
    }
   }
   for(unsigned int i = 0; i<zObjects.size(); i++){
    zObjects[i]->move(count);
    if(zObjects[i]->pos().x()>500){
     scene->removeItem(zObjects[i]);
     zObjects.erase(zObjects.begin()+i);
    }
   }
  if(zapu->getVX() == 1 && count%50 == 0){
    points++;
    updateScore();
   }
 }
  count++;
}

/** Adds a life then makes the added life an additional
 *  visible egg.
 *
 *  @return nothing
 */
void MainWindow::addEgg(){
  numLives++;
  switch(numLives){
  case 2: eggs[1]->setVisible(true); break;
  case 3: eggs[2]->setVisible(true); break;
  case 4: eggs[3]->setVisible(true); break;
 }
}


/** Called when key is pressed. If the game is going on and
 *  and the character can move it'll send the signal to the
 *  class. Each time the key is pressed (not counting duration)
 *  held down a new electricity bolt will be created and added
 *  to the screen.
 *
 *  @param  QKeyEvent pointer that stores key pressed
 *  @return nothing
 */
void MainWindow::keyPressEvent(QKeyEvent *e){
if(resetting == false && timer->isActive()){
 if(zapu->getState()!=-2){
  zapu->keySignal(e);
  if(!e->isAutoRepeat() && e->key() == Qt::Key_Space && zapu->getState()!=-1){
    Bolt *b  = new Bolt(elec, 77, zapu->pos().y()+3);
    zObjects.push_back(b);
    scene->addItem(b);
  }
 }
}
}

/** Called when key is released. If the game is going on and
 *  and the character can move it'll send the signal to the
 *  class. Held down releases are ignored.
 *
 *  @param  QKeyEvent pointer that stores key released
 *  @return nothing
 */
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

/** Called when mouse is pressed. If the click is inside of a
 *  button the menu will hide and direct to the right place 
 *  (sometimes another menu, other times starting a new game,
 *  also quitting the game). Also stops game if pause button
 *  pressed 
 *
 *  @param  QMouseEvent pointer that stores mouse clicks
 *  @return nothing
 */
void MainWindow::mousePressEvent(QMouseEvent *event){
 if(menus[5]->isVisible() || menus[6]->isVisible()){
  menus[0]->setVisible(true);
  menus[5]->setVisible(false);
  menus[6]->setVisible(false);
  scoresList->setVisible(false);
 }
else if(event->pos().x() >= ((WINDOW_MAX_X/2)-141) && event->pos().x()<= (WINDOW_MAX_X/2)+141){
  if(menus[0]->isVisible()){
   if(event->pos().y()>= 146 && event->pos().y() <= 202){
     menus[0]->setVisible(false);
     menus[3]->setVisible(true);
     nameBox = new QLineEdit();
     QFont font("Futura", 19, QFont::Bold, true);
     font.setItalic(false);
     nameBox->setFixedHeight(44);
     nameBox->setFont(font);
     layout->addWidget(nameBox, 182, 168, 100, 250);
     setLayout(layout);
   }
   else if(event->pos().y()>= 211 && event->pos().y() <= 267){
     menus[0]->setVisible(false);
     menus[5]->setVisible(true);
   }
   else if(event->pos().y()>= 276 && event->pos().y() <= 332){
     menus[0]->setVisible(false);
     menus[6]->setVisible(true);
     scoresList->setVisible(true);
     QStringList scores;
     ifstream fin;
     fin.open("HSList.txt");
     if(fin.good()){
      string line;
      while(!fin.eof()){
       getline(fin, line);
       QString qline = QString::fromStdString(line);
       scores<<qline;
      }
     }
      model = new QStringListModel(scoresList);
      model->setStringList(scores);
      scoresList->setModel(model);
      fin.close();
   }
   else if(event->pos().y()>= 341 && event->pos().y() <= 397){
      qApp->quit();
   }
  }
   if(event->pos().y()>= 152 && event->pos().y() <= 216){
    if(menus[1]->isVisible()){
      menus[1]->setVisible(false);
      menus[0]->setVisible(false);
      zapu->setVX(0);
      timer->start();
     }
  }
  else if(event->pos().y()>= 242 && event->pos().y() <= 306){
      if(menus[1]->isVisible() || menus[2]->isVisible()){
      if(menus[2]->isVisible()){
         delete nameTxt;
         delete scoreTxt;
        }
       newGame();
       menus[0]->setVisible(false);
       menus[1]->setVisible(false);
       menus[2]->setVisible(false);
      }
  }
  else if(event->pos().y()>= 332 && event->pos().y() <= 396){
   if(menus[1]->isVisible() || menus[2]->isVisible()){
    qApp->quit();
    }
  }
}
if(menus[3]->isVisible()){
 if(event->pos().x() >= ((WINDOW_MAX_X/2)-68) && event->pos().x()<= (WINDOW_MAX_X/2)+214){
   if(event->pos().y()>= 257 && event->pos().y() <= 321){
   if(nameBox->text().isEmpty()){
    menus[4]->setVisible(true);
   }
   else{
    string fullName = nameBox->text().toStdString();
    stringstream ss(fullName);
    string firstName;
    getline(ss, firstName, ' ');
    name = QString::fromStdString(firstName);
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
    timer->stop();
    menus[0]->setVisible(true);
    menus[1]->setVisible(true);
  }}
}
}

/** Called when player loses a life. Reset is set to true and
 *  necessary default values are set as well. Things and bolts
 *  are cleared and removed from the scene. The number of lives
 *  is then decreased by one and an egg on the status bar 
 *  disappears. 
 *
 *  @return nothing
 */
void MainWindow::reset(){
 resetting = true;
 spiked = false;
 genCount = -1;
 bounceBack = false;
 while(!fObjects.empty()){
   scene->removeItem(fObjects.at(0));
   fObjects.erase(fObjects.begin());
 }
 while(!zObjects.empty()){
   scene->removeItem(zObjects.at(0));
   zObjects.erase(zObjects.begin());
 }
 numLives--;
 switch(numLives){
  case 0: eggs[0]->setVisible(false); 
  case 1: eggs[1]->setVisible(false); break;
  case 2: eggs[2]->setVisible(false); break;
  case 3: eggs[3]->setVisible(false); break;
 }
}

/** Speeds up game and increases frequency of enemies depending
 *  on score. The score is then translated into images (custom
 *  font) that is displayed on the status bar. These images are
 *  returned from another class as pointers and then set as 
 *  qpixmaps.
 *
 *  @return nothing
 */
void MainWindow::updateScore(){
   int thous, hunds, tens, ones;
   if(points == 100){
    timer->setInterval(5);
    world.load(qApp->applicationDirPath()+"/Pictures/SnowBackground.png");
    updateWorld();
    freq = 0.60;
   }
   else if(points == 250){
    world.load(qApp->applicationDirPath()+"/Pictures/DarkBackground.png");
    updateWorld();
    freq = 0.40;
   }
   else if(points == 500){
    timer->setInterval(4);
    freq = 0.25;
   }
   else if(points == 750){
    freq = 0.10;
   }
   else if(points == 1000){
    freq = 0.05;
   }
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

/** Returns corresponding image depending on number.
 *
 *  @return pointer to numerical qpixmap
 */
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

/** Clears all objects and resets variables to default values. 
 *  The status bar (score and eggs are reset to default images).
 *  A new main character will be generated if it hasn't been 
 *  deleted. The timer (linked to animate()) will start again.
 *
 *  @return nothing
 */
void MainWindow::newGame(){
 while(!fObjects.empty()){
   scene->removeItem(fObjects.at(0));
   fObjects.erase(fObjects.begin());
 }
 while(!zObjects.empty()){
   scene->removeItem(zObjects.at(0));
   zObjects.erase(zObjects.begin());
 }
 while(!bObjects.empty()){
   scene->removeItem(bObjects.at(0));
   bObjects.erase(bObjects.begin());
 }
 while(!eggs.empty()){
  scene->removeItem(eggs.at(0));
  eggs.erase(eggs.begin());
 }
 while(!score.empty()){
   scene->removeItem(score.at(0));
   score.erase(score.begin());
 }
  world.load(qApp->applicationDirPath()+"/Pictures/fullView.png");
  updateWorld();
  
  count = 0;
  points = 0;    
  numLives = 3;
  freq = 1;
  resetting = false;
  spiked = false;
  bounceBack = false;
  moreGaps = false;
  genCount = -1;
 QPixmap *ground = new QPixmap(qApp->applicationDirPath()+"/Pictures/Ground1.png");
  for(int i = 0; i<12; i++){
   Ground *g  = new Ground(ground, (i-1)*64, 20); 
   g->setLimit(12);
   bObjects.push_back(g); 
   scene->addItem(bObjects.at(i));  
  }
 if(zapu == NULL){
  yoshi = new QPixmap(qApp->applicationDirPath()+"/Pictures/YW1.png");
  zapu = new MainChar(yoshi, 10, bObjects.at(0)->pos().y()-75); 
  scene->addItem(zapu);
 }
 else{
  zapu->setPixmap(*yoshi);
  zapu->setPos(zapu->pos().x(), bObjects.at(0)->pos().y()-75);
 }
  zapu->setVX(0);
  zapu->setGround(bObjects.at(0)->pos().y()-50);
  zapu->setVisible(true);
 QPixmap *bwEgg;   
 UI *uiItem, *num;    
  for(int i = 0; i<4; i++){
   bwEgg = new QPixmap(qApp->applicationDirPath()+"/Pictures/bwEgg.png");
   uiItem = new UI(bwEgg, i*34+90, -397, true);
   eggs.push_back(uiItem);
   scene->addItem(uiItem);
  }
  eggs[3]->setVisible(false);
  for(int j = 0; j<5; j++){
   num = new UI(zero, j*15+309, -394, false);
   score.push_back(num);
   scene->addItem(num);
  }
 score[0]->setVisible(true);
if(!timer->isActive()){
  timer->setInterval(6);
  timer->start();
  freq = 1.0;
 }
}

void MainWindow::updateWorld() {
  QPalette palette;  
  palette.setBrush(view->backgroundRole(), world);
  view->setPalette(palette);
}

/** MainWindow default constructor. A new scene is created a view is set to
 *  it with it's parent as scene. A new grid layout and form layout (for
 *  the view are created. New form layouts are created for each QLabel (text)
 *  and are added to the grid layouts in the appropriate locations. Many QPixmaps
 *  are initialized with selected images. Variables are set to their default values.
 *  All items are then added to the scene in their initial states.
 *
 *  @return nothing
 */
MainWindow::MainWindow()  {
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    layout = new QGridLayout(); 
    QFormLayout *viewLayout = new QFormLayout();
  
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
    timer->setInterval(6);

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
    help = new QPixmap(qApp->applicationDirPath()+"/Pictures/Help.png");
    hsMenu = new QPixmap(qApp->applicationDirPath()+"/Pictures/Scores.png");
        
    ground1 = new QPixmap(qApp->applicationDirPath() + "/Pictures/Ground1.png");
    ground16 = new QPixmap(qApp->applicationDirPath() + "/Pictures/Ground16.png");
    eEgg = new QPixmap(qApp->applicationDirPath() + "/Pictures/extraEgg.png");
    bulletBill = new QPixmap(qApp->applicationDirPath() + "/Pictures/BlueBullet.png");
    heatBB = new QPixmap(qApp->applicationDirPath() + "/Pictures/BulletBill.png");
    fire = new QPixmap(qApp->applicationDirPath() + "/Pictures/FireBall.png");
    witch = new QPixmap(qApp->applicationDirPath() + "/Pictures/Kamek1.png");
    spikeBall = new QPixmap(qApp->applicationDirPath() + "/Pictures/SpikeBall.png");
    bWalk = new QPixmap(qApp->applicationDirPath() + "/Pictures/bWalk1.png");
    elec = new QPixmap(qApp->applicationDirPath() + "/Pictures/Bolt.png");
    world.load(qApp->applicationDirPath()+"/Pictures/fullView.png");
    updateWorld();
    
    count = 0;
    points = 0;
    numLives = 3;
    freq = 1;
    resetting = false;
    spiked = false;
    bounceBack = false;
    moreGaps = false;
    genCount = -1;
    
    hs = new HighScores();
  
    scene->setSceneRect(0, -WINDOW_MAX_Y+50, WINDOW_MAX_X-4, WINDOW_MAX_Y-4);
    view->setFixedSize(WINDOW_MAX_X, WINDOW_MAX_Y);
    viewLayout->addRow(view);
    view->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QWidget::setFocus();
    layout->addLayout(viewLayout, 0, 0, 506, 466);
    
    scoresList = new QListView();
    scoresList->setMaximumWidth(150);
    scoresList->setMaximumHeight(350);
    scoresList->setVisible(false);
    layout->addWidget(scoresList, 62, 164, 350, 150);

    QPixmap *ground = new QPixmap(qApp->applicationDirPath()+"/Pictures/Ground1.png");
   for(int i = 1; i<=12; i++){
    Ground *g  = new Ground(ground, (i-1)*64, 20); 
    g->setLimit(12);
    bObjects.push_back(g);
    }
    yoshi = new QPixmap(qApp->applicationDirPath()+"/Pictures/YW1.png");
    zapu = new MainChar(yoshi, 10, -55); 
    scene->addItem(zapu);
    for (unsigned int i=0; i<bObjects.size(); i++ ) {
     scene->addItem(bObjects.at(i));
    }
    
    UI *menu1 = new UI(bMenu, 0, -418, true);
    menus.push_back(menu1);
    UI *menu2 = new UI(pMenu, 0, -418, false);
    menus.push_back(menu2);
    UI *menu3 = new UI(sMenu, 0, -418, false);
    menus.push_back(menu3);
    UI *menu4 = new UI(nMenu, 0, -418, false);
    menus.push_back(menu4);
    UI *nError = new UI(error, 50, -281, false);
    menus.push_back(nError);
    UI *hMenu = new UI(help, 0, -418, false);
    menus.push_back(hMenu);
    UI *menu5 = new UI(hsMenu, 0, -418, false);
    menus.push_back(menu5);
    
    QPixmap *bwEgg;
    UI *uiItem, *num;
    for(int i = 0; i<4; i++){
     bwEgg = new QPixmap(qApp->applicationDirPath()+"/Pictures/bwEgg.png");
     uiItem = new UI(bwEgg, i*34+90, -397, true);
     eggs.push_back(uiItem);
     scene->addItem(uiItem);
    }
    eggs[3]->setVisible(false);
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
 *  their hierarchy (qpixmaps then scene then view).
 *  
 *  @return nothing
 */
MainWindow::~MainWindow(){
    delete timer;

    delete zero;
    delete one;
    delete two;
    delete three;
    delete four;
    delete five;
    delete six;
    delete seven;
    delete eight;
    delete nine;
    
    delete bMenu;
    delete pMenu;
    delete sMenu;
    delete nMenu;
    delete error;
    delete help;
        
    delete ground1;
    delete ground16;
    delete eEgg;
    delete bulletBill;
    delete witch;
    delete spikeBall;
    delete bWalk;
    delete elec;
    delete scene;
    delete view;
}

