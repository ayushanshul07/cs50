//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3
#define PADLENGTH 60
#define PADHEIGHT 6

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    double velocity_x = (drand48() * 2 + 1 ) ;
    double velocity_y = 2 ;
    waitForClick();
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    { 
        move(ball, velocity_x , velocity_y);

        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            velocity_x = -velocity_x;
        }
        else if (getX(ball) <= 0)
        {
            velocity_x = -velocity_x;
        }
        else if(getY(ball) <= 0)
        {
            velocity_y = -velocity_y;
        }
        else if(getY(ball) + 2 * RADIUS >= (HEIGHT - 10))
        {
            lives--;
            waitForClick();
            setLocation( ball , (WIDTH / 2) - RADIUS , (HEIGHT / 2) - RADIUS );
        }

        GEvent event = getNextEvent(MOUSE_EVENT);

        if (event != NULL)
        {
            if (getEventType(event) == MOUSE_MOVED)
            {
                double xcordinate = getX(event);
                double ycordinate = HEIGHT - 75 - (PADHEIGHT / 2);

                if (xcordinate >= ((WIDTH) - (PADLENGTH / 2)) )
                    setLocation( paddle , WIDTH - PADLENGTH , ycordinate );
                else if(xcordinate <= (PADLENGTH / 2))
                    setLocation( paddle , 0 , ycordinate );
                else  
                    setLocation( paddle , xcordinate - (PADLENGTH / 2) , ycordinate );
            }

        }

        GObject object = detectCollision(window, ball);
        if (object == paddle)
        {
            velocity_y = -velocity_y;
        }

        if (object != NULL)
        {
            if (strcmp(getType(object), "GRect") == 0 && object != paddle && object != label)
            {
                velocity_y = -velocity_y;
                removeGWindow(window , object);
                bricks--;
                points += lives;
                updateScoreboard(window,label, points );
            }

        }
        pause(11);
    }

    if (lives > 0 )
    {
        removeGWindow(window , ball);
        GLabel label = newGLabel("You won!!!");
        setFont(label,"SansSerif-25");
        setColor(label,"GREEN");
        double x = (getWidth(window) - getWidth(label)) / 2;
        double y = (getHeight(window) - getHeight(label)) / 2 + 20;
        setLocation(label,x,y);
        add(window,label);      
    }
    else
    {
        removeGWindow(window , ball);
        GLabel label = newGLabel("Game Over");
        setFont(label,"SansSerif-25");
        setColor(label,"RED");
        double x = (getWidth(window) - getWidth(label)) / 2;
        double y = (getHeight(window) - getHeight(label)) / 2 + 20;
        setLocation(label,x,y);
        add(window,label); 

    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    for(int i = 0 ; i < ROWS ;++i)
    {
        string colors[5] = {"RED","ORANGE","YELLOW","GREEN","CYAN"};
        for(int j = 0 ; j < COLS ;++j)
        {
            GRect block = newGRect(0 + (34.5) * j + 5 * (j + 1) , 46 + 10 * i + 5 * (i + 1) , 34.5 ,10);
            setFilled(block,true);
            setColor(block , colors[i]);
            add(window,block);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval((WIDTH / 2) - RADIUS , (HEIGHT / 2) - RADIUS , 2 * RADIUS , 2 * RADIUS);
    setFilled(ball,true);
    setColor(ball,"BLACK");
    add(window,ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect( (WIDTH - PADLENGTH) / 2 ,HEIGHT - 75 - (PADHEIGHT / 2) ,PADLENGTH , PADHEIGHT);
    setFilled(paddle,true);
    setColor(paddle,"BLACK");
    add(window,paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{   
    GLabel label = newGLabel("0");
    setFont(label,"SansSerif-50");
    setColor(label,"GRAY");
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label,x,y);
    add(window,label);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
