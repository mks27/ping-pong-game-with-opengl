# ping-pong-game-with-opengl

# Introduction

Game development is really interesting work, actually when you look at a computer game and the AI implemented in it and its graphics and complexity, you then feel it is impossible to build such type of games. But if you know that all these games are depending on graphics libraries which made developing games very easy task, you will be interested in designing and developing games. We are going to prove that here by developing a simple 2D game depending on OpenGL library, we will introduce the concept of scene rendering and object collision, and also we will show how to write a text on the screen to get the score of the player. Finally we will show how to use the keyboard and mouse to interact with the game.

# The game basics:

When you develop a game you have to fully understand how the game is played, so you can implement its logic. Our game is a simple ball with bat game known as Ping-Pong game. The bat will be moved according to the movement of the mouse. And the ball will move randomly in the created window. When the ball hits the right, left, or top wall – we will refer to the window border as a wall – it will return back. When it hits the bottom wall it will not only return back but it will increase the score of the computer, but if the player can hold it by the bat, his score will be increased. Let us take a look at the interface of the game.
The window contains two counters, the first is PC: it is for the computer, it increases only if the ball hits the bottom border of the window (bottom wall). Player: it is a counter increases only if the ball hits your bat (the bat is represented by the rectangle at the bottom of the screen).

# The game implementation
We will show step by step how to implement the game. First of all the concept of motion in OpenGL should be clear, the motion is done by drawing and looping. In every loop, the position of the object is adjusted so you fell it is moving. Motion in OpenGL has the same concept as the Cartoon films, every cycle the drawing is adjusted little bit and then all the images are displayed together which results in “moving” characters.


# Drawing the window
The window in OpenGL is implemented simply by the following code segment
   glutInit(&argc, argv);
   glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (795, 500); 
   glutInitWindowPosition (0, 0);
   glutCreateWindow ("GAME");

 # Drawing the Ball and the Bat and Displaying the Score Text
As we said the ball will be represented by a rectangle. For that we will define a new structure called RECTA, which is implemented by defining the left, top, right, and bottom coordinates. We are going to define three variables of this structure to be used as Ball, Wall, and Bat respectively
struct RECTA
{ 
        float left,top,right,bottom; 
};

RECTA ball={100,100,120,120};
RECTA wall ;
RECTA player_1 ={0,490,40,500}; 

Then we will use the DrawRectangle function to draw the RECTA instances on OpenGL window.
void DrawRectangle(RECTA  rect) 
{ 
        glBegin(GL_QUADS); 
        glVertex2f(rect.left,rect.bottom);      //Left - Bottom 
        glVertex2f(rect.right,rect.bottom); 
        glVertex2f(rect.right,rect.top); 
        glVertex2f(rect.left,rect.top); 
        glEnd(); 
}



# Moving the Ball and the Bat
As we said before, the motion of the Ball (the square) is done by adjusting the square position in each loop. The Ball has a speed (this will be defined by a Timer Function together with the length of the Ball movement steps- in our program we call this steps “delta”). For the timer function it always contains a code that will be executed in a regular basis every specified period of time (every 1 millisecond in our program). Our timer function is depicted in the following code segment


static float Xspeed=4,Yspeed=4; 
static float delta=4; 
void Timer(int v) 
{ 
        ball.left+=Xspeed; 
        ball.right+=Xspeed; 
        ball.top+=Yspeed; 
        ball.bottom+=Yspeed; 
 
        glutTimerFunc(1,Timer,1); 
}


We have defined two global variables Xspeed and Yspeed, which has the value of delta=1. This can be shown graphically in Fig. 2. The value of delta will be changed (+1/-1) according to the collision of the ball with the walls. If the ball hits the right wall Xspeed will be –delta (this will make the ball return back), if the ball hits the left wall the Xspeed will be changed to delta and so on. For Yspeed also if the ball hits the top wall it will be equal delta, however if it hits the bottom wall or the bat, it will be –delta. The most important point here is that the Xspeed, Yspead will be used to increase the position of the ball, which was clearly done in the Timer function (refer to the above code segment). For changing the values of Xspeed and Yspeed, it is shown in the following code segment
CThreeMaxLoader contains the following function which responsible for loading the 3DS file:


	if(Test_Ball_Wall(ball,wall)== FROM_RIGHT) 
    Xspeed=-delta; 

    if(Test_Ball_Wall(ball,wall)== FROM_LEFT) 
    Xspeed=delta; 

    if(Test_Ball_Wall(ball,wall)== FROM_TOP) 
    Yspeed=delta; 

    if(Test_Ball_Wall(ball,wall)== FROM_BOTTOM) 
	{
		Yspeed=-delta; 
		pcResult +=1;
	}


In the above code segment, the variable pcResult holds the counter of the computer score. Also we noticed the existence of a new function called Test_Ball_Wall(ball,wall). This function is used to detect the collision between the ball and the walls. 
Moving the bat will be done by moving the mouse cursor, when the mouse cursor is moved, only the x coordinate of the bat will be changed, the movement of the bat is shown in the following code segment

static int mouse_x=0; 
void MouseMotion(int x,int y)
{
 
	mouse_x=x;
}

We have defined a global variable called mouse_x. it will be used in drawing the bat when we render the whole scene. You can stop the game by pressing the Esc. key from the keyboard this is programmed as follow
void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}

# Ball collision detection
As we described in the previous section, when the ball hits the wall it will reflect back. The detection of the collision between the ball and wall (taking an example the right wall) is done simply by comparing the right coordinate of the wall with the ball’s right coordinate, the collision will occur if they are the same or the ball’s right is greater. For the bat/ball collision is done by comparing the top of the bat with the bottom of the ball. A collision occurs if they are the same or the balls bottom is greater and the x-coordinate lie inside the bat’s x coordinates. The following code shows the above procedure

int Test_Ball_Wall(RECTA  ball , RECTA wall) 
{ 
        if(ball.right >=wall.right) 
        return FROM_RIGHT;  
        if(ball.left <=wall.left) 
        return FROM_LEFT;  
        if(ball.top <=wall.top) 
        return FROM_TOP;  
        if(ball.bottom >=wall.bottom) 
          stop();
        //return FROM_BOTTOM;  
 
        else return 0 ; 
}

bool Test_Ball_Player(RECTA ball,RECTA player) 
{ 
     
		if(ball.bottom >= player.top && ball.left>= player.left && ball.right <=player.right ) 
                {
			playerResult++;
		
                  return true;  
		}
 
            return false;  
}
As we can expect playerResult is a global variable holds the score of the player.

# Putting all things together
We are going to show how the above code will be used in rendering the whole scene of the game. First take a look at the Render function

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT );
	glLoadIdentity();
 
	sprintf(string,"PC : %d ",pcResult); // ÊÍæíá ÑÞã Çáì äÕ
	drawText(string,10,80); // ØÈÇÚÉ ÇáäÕ
	sprintf(string,"Player : %d ",playerResult);
	drawText(string,10,120);

	wall.left=wall.top=0;
	wall.right=WINDOW_WIDTH;
	wall.bottom=WINDOW_HEIGHT;

	DrawRectangle(ball);

	if(Test_Ball_Wall(ball,wall)== FROM_RIGHT) 
    Xspeed=-delta; 

    if(Test_Ball_Wall(ball,wall)== FROM_LEFT) 
    Xspeed=delta; 

    if(Test_Ball_Wall(ball,wall)== FROM_TOP) 
    Yspeed=delta; 

    if(Test_Ball_Wall(ball,wall)== FROM_BOTTOM) 
	{
		Yspeed=-delta; 
		pcResult +=1;
	}
 
	DrawRectangle(player_1); 
    player_1.left=mouse_x-20; 
    player_1.right=mouse_x+40; 


    if(Test_Ball_Player(ball,player_1)==true) 
            Yspeed=-delta; 

	glutSwapBuffers();
}

As we mentioned before the Render function will run every OpenGL loop. So, first we need to clear and load the identity matrix to the window, and then we will use the drawText function to draw the text for the PC and Player scores. Then we define the walls coordinates (it will have the same size as the created OpenGL window) and then draw the ball. Then we detect the collision between the ball and the wall and between the ball and the bat, and accordingly increase the scores of the PC and the player. Finally we move the player according to the movement of the mouse.


# Conclusion

That's all for this project.  Ping- Pong are very familiar and interesting game, so there really wasn't a  lot of new stuff to cover. The most important thing we did here was set up our game which is user friendly and the game will gets over when ball strikes the surface  and user have to prevent the ball with the lower boundary which is not a easy task with this speed provided to the ball. So i think most of the user like it and will definitely enjoy the game.
