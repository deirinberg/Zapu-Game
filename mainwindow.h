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

class UI;
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
    /** Counter for animating tiles */
    int count;
    /** Location of the tile to animate */
    int index;
    /** Location of blank tile */
    int blankLoc;
    /** X distance tile needs to move during animation */
    int dx;
    /** Y distance tile needs to move during animation */
    int dy;
    int floor;
    int points;
    int numLives;
    int rCount;
    /** True or false based on if cheat can be cleared or not */
    bool updateCheat;
    /** Shows all items which are added to the QWidget */
    void show();
    /** Clears the cheat in the text box if it exists */
    bool resetting;
    bool spiked;
    bool bounceBack;
    void clearCheat();
    void reset();
    void updateScore();
    QString name;
    QPixmap* scoreImage(int num);
private:
    /** Where all tiles are added to */
    QGraphicsScene *scene;
    /** Holds/displays the scene which contains the tiles */
    QGraphicsView *view;
    QGraphicsView *statusBar;
    /** Positions all of the buttons/text/text boxes in the window */
    //QGridLayout *layout;
    /** Textbox for user to enter the size of the board */
    QLineEdit *sizeEdit;
    /** Textbox for user to enter the number of initial moves of the board */
    QLineEdit *startMovesEdit;
    /** Textbox for user to enter the random seed number for the initial moves of the board */
    QLineEdit *randomSeedEdit;
    /** Button to select the manhattan heuristic for the cheat */
    QRadioButton *mHeur;
    /** Button to select the out of place heuristic for the cheat */
    QRadioButton *oHeur;
    /** Button to start the game */
    QPushButton *start;
    /** Button to display the solution of the board */
    QPushButton *cheat;
    /** Button to quit the game */
    QPushButton *quit;
    /** Button to clear the solution of the board */
    QPushButton *clear;
    /** List displaying the solution of the board */
    QListView *cheatList;
    /** Model that contains the solutions of the board, set to ListView */
    QStringListModel *model;
    /** Displays errors or messages to user */
    QLabel *message;
    
    QLineEdit *nameBox;
    QLabel *scoreTxt;
    QLabel *nameTxt;
    QGridLayout *layout;
    
    QPixmap *yoshi;
    QPixmap *ground1;
    QPixmap *ground16;
    QPixmap *bulletBill;
    QPixmap *witch;
    QPixmap *spikeBall;
    QPixmap *elec;
    QPixmap *zero;
    QPixmap *one;
    QPixmap *two;
    QPixmap *three;
    QPixmap *four;
    QPixmap *five;
    QPixmap *six;
    QPixmap *seven;
    QPixmap *eight;
    QPixmap *nine;
    
    QPixmap *bMenu;
    QPixmap *pMenu;
    QPixmap *sMenu;
    QPixmap *nMenu;
    QPixmap *error;
    
    MainChar *zapu;
    
    vector<Foreground*> fObjects;
    vector<Foreground*> zObjects;
    vector<Background*> bObjects;
    vector<UI*>menus;
    vector<UI*>eggs;
    vector<UI*>score;
    
    /** Timer to animate the movement of tiles */
    QTimer *timer;
    
protected:
 void keyPressEvent(QKeyEvent *e);
 void keyReleaseEvent(QKeyEvent *r);
 void mousePressEvent(QMouseEvent *event);

public slots:
    /** Starts the game when the appropriate button is pressed */
    void startGame();
    void findSol();
    /** Clears the solution when the appropriate button is pressed */
    void clearSol();
    /** Animates the tiles after a valid move is requested */
    void animate();
};

#endif // MAINWINDOW_H

