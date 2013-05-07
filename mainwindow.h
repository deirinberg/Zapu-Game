#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>
#include <QFormLayout>
#include <QStringList>
#include <QStringListModel>
#include <QLineEdit>
#include <QRadioButton>
#include <QPushButton>
#include <QTextEdit>
#include <QListView>
#include <QRadioButton>
#include <QTimer>
#include <QGraphicsItemAnimation>
#include <QPushButton>
#include <vector>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPixmap>
#include "foreground.h"
#include "background.h"
#include "highscores.h"

/** Forward declaration to avoid importing the same thing */
class UI;
/** Forward declaration to avoid importing the same thing */
class MainChar;

#define WINDOW_MAX_X 506
#define WINDOW_MAX_Y 466
using namespace std;
class MainWindow : public QWidget {
    Q_OBJECT
    
public:
    /** MainWindow constructor */
    explicit MainWindow();
    /** MainWindow destructor */
    ~MainWindow();
    /** Count of how much time has elapsed */
    int count;
    /** Y position of current ground */
    int floor;
    /** Score of game */
    int points;
    /** Number of lives left */
    int numLives;
    /** Number of floors without gaps generated */
    int genCount;
    /** Frequency of enemies */
    double freq;
    /** Shows all items which are added to the QWidget */
    void show();
    /** Starts a new game when selected */
    void newGame();
    /** Indicates during animation if player just lost or not */
    bool resetting;
    /** Whether spike ball has been dropped or not */
    bool spiked;
    /** Returns if the spikeBall should bounce up or not */
    bool bounceBack;
    /** Returns if there are more jumps or not */
    bool moreGaps;
    /** Resets main character if a life is lost */
    void reset();
    /** Updates the score of the game */
    void updateScore();
    /** Adds an egg (life) to the status bar */
    void addEgg();
    /** Holds the name of the user */
    QString name;
    /** Returns the numerical image used for generating the score */
    QPixmap* scoreImage(int num);
private:
    /** Where all objects are added to */
    QGraphicsScene *scene;
    /** Holds/displays the scene which contains the objects */
    QGraphicsView *view;
    /** Text box where user types in his or her name */
    QLineEdit *nameBox;
    /** Displays score after all lives are lost */
    QLabel *scoreTxt;
    /** Displays name after all lives are lost */
    QLabel *nameTxt;
    /** Master layout for determining position of all QWidgets */
    QGridLayout *layout;
    /** Holds initial zapu image */
    QPixmap *yoshi;
    /** Holds initial ground image */
    QPixmap *ground1;
    /** Holds end piece ground image */
    QPixmap *ground16;
    /** Holds extra life egg image */
    QPixmap *eEgg;
    /** Holds bullet image */
    QPixmap *bulletBill;
    /** Holds witch image */
    QPixmap *witch;
    /** Holds initial bowser image */
    QPixmap *bWalk;
    /** Holds spike image */
    QPixmap *spikeBall;
    /** Holds bolt image */
    QPixmap *elec;
    /** Holds 0 image */
    QPixmap *zero;
    /** Holds 1 image */
    QPixmap *one;
    /** Holds 2 image */
    QPixmap *two;
    /** Holds 3 image */
    QPixmap *three;
    /** Holds 4 image */
    QPixmap *four;
    /** Holds 5 image */
    QPixmap *five;
    /** Holds 6 image */
    QPixmap *six;
    /** Holds 7 image */
    QPixmap *seven;
    /** Holds 8 image */
    QPixmap *eight;
    /** Holds 9 image */
    QPixmap *nine;
    
    /** Holds beginning menu */
    QPixmap *bMenu;
    /** Holds pause menu */
    QPixmap *pMenu;
    /** Holds score menu */
    QPixmap *sMenu;
    /** Holds name menu */
    QPixmap *nMenu;
    /** Holds name error message */
    QPixmap *error;
    /** Holds help menu */
    QPixmap *help;
    
    HighScores *hs;
    
    /** Pointer to main character */
    MainChar *zapu;
    /** Vector of pointers to things */
    vector<Foreground*> fObjects;
    /** Vector of pointers to bolts */
    vector<Foreground*> zObjects;
    /** Vector of pointers to ground objects */
    vector<Background*> bObjects;
    /** Vector of pointers to menus */
    vector<UI*>menus;
    /** Vector of pointers to eggs in status bar */
    vector<UI*>eggs;
    /** Vector of pointers to score in status bar */
    vector<UI*>score;
    
    /** Timer to animate the game */
    QTimer *timer;
    
protected:
/** Sends signals to main character when key is pressed */
 void keyPressEvent(QKeyEvent *e);
/** Sends signals to main character when key is released */
 void keyReleaseEvent(QKeyEvent *r);
/** Used to navigate the menus */
 void mousePressEvent(QMouseEvent *event);

public slots:
    /** Determines all of the movements of the game */
    void animate();
};

#endif // MAINWINDOW_H

