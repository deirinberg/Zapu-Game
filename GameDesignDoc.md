# Game Design Document

## Objective

A side scroller in which a character needs to continually avoid obstacles and enemies with. The speed of the game and frequency of enemies will increase over time.

## Characters
### Main Character

The main character is a blue Yoshi with an orb on it's head called Zapu. It's image will change when the character running, jumping and crouching.
It can emit electricity from the orb on it's head which can kill enemies. ![alt text](/Pictures/YW1.png "Yoshi")

### Obstacle #1

Extra life egg. Randomly appears giving character an extra life once they pass a certain score and run over it. ![alt text](/Pictures/extraEgg.png "Extra Egg")

### Obstacle #2

Baby Bowser. Can't be jumped on due to spike shell. Can only be electrocuted.
![alt text](/Pictures/bWalk1.png "Baby Bowser")

### Obstacle #3

Regular Bullet- a blue bullet can be double jumped over or crouched to avoid. If jumped over and landed on will fall/disappear. Unaffected by bolts.
![alt text](/Pictures/BlueBullet.png "Regular Bullet")

### Obstacle #4

Flying witch. Hovers over character and drops sharp object (spike). Can only be killed by spike bouncing back and hitting it. Zapu loses a life if it hits it.
![alt text](/Pictures/Kamek1.png "Witch")

### Obstacle #5

Spike. Can be avoided by turning into an egg which will bounce back the spike and kill the witch. Failure to become an egg results in Zapu losing a life.
![alt text](/Pictures/SpikeBall.png "Spike")

### Obstacle #6 (AI)

Heat Bullet. A red bullet's y position changes to zapu's up to until it gets close. It otherwise acts like a regular bullet (obstacle #3).
![alt text](/Pictures/BulletBill.png "Heat Bullet")

### Obstacle #7 (AI)

Fire Bowser. A red bowser shoots fire balls and matches zapu's y position the whole time. Can killed by zaps and acts like baby bowser (obstacle #2) with additional powers.
![alt text](/Pictures/FBWalk1.png "Fire Baby Bowser")

## Controls

![alt text](/Pictures/Help.png "Controls and Enemies")

## Score

Increases with the distance zapu covers. 
Once the score hits certain amounts the speed of the game will increase even more leading to higher scores.
Higher scores also increase the frequency of the enemies.

## Levels

There are 3 different levels in the game. When the user has 100 points the background changes to level 2 (snowy background).
In level 2 both the speed of the game and the frequency of enemies increase. When the user has 250 points the background changes to level 3 (dark background).
In level 3 the frequency of enemies increases. At 500 points the speed and frequency increase but no background screen.

## Lives

Players will start with 3 lives. If one of the obstacles comes in contact with the character (as detailed above) it will lose a life. If Zapu however hits a green egg it will gain a life.

## Menus

#### Main Menu
![alt text](/Pictures/Menu1.png "Main Menu")

#### Name Menu
![alt text](/Pictures/NameMenu.png "Name Menu")

#### Pause Menu
![alt text](/Pictures/Menu2.png "Pause Menu")

#### Score Menu
![alt text](/Pictures/Menu3.png "Score Menu")

#### Game Window
![alt text](/Pictures/fullView.png "Main Window")

