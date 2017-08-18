
#include <GL/glut.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
using namespace std;
#define FROM_RIGHT      1 
#define FROM_LEFT       2 
#define FROM_TOP        3 
#define FROM_BOTTOM     4 
 
static int WINDOW_WIDTH ,WINDOW_HEIGHT;

int playerResult=0;
static float Xspeed=4,Yspeed=4; 
static float delta=4; 

char string [100];

struct RECTA
{ 
        float left,top,right,bottom; 
};

RECTA ball={100,100,120,120};
RECTA wall ;
RECTA player_1 ={0,490,40,500}; 

void DrawRectangle(RECTA  rect) 
{ 
        glBegin(GL_QUADS); 
        glVertex2f(rect.left,rect.bottom);      //Left - Bottom 
        glVertex2f(rect.right,rect.bottom); 
        glVertex2f(rect.right,rect.top); 
        glVertex2f(rect.left,rect.top); 
        glEnd(); 
}

void Timer(int v) 
{ 
        ball.left+=Xspeed; 
        ball.right+=Xspeed; 
        ball.top+=Yspeed; 
        ball.bottom+=Yspeed; 
 
        glutTimerFunc(1,Timer,1); 
}
void drawText(char*string,int x,int y)
{
	  char *c;
	  glPushMatrix();
	  glTranslatef(x, y,0);
	  glScalef(0.1,-0.1,1);
  
	  for (c=string; *c != '\0'; c++)
	  {
    		glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
	  }
	  glPopMatrix();

}

void stop()
{
   printf("game over");
    exit(0);
}
 
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
 

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}

static int mouse_x=0; 
void MouseMotion(int x,int y)
{
 
	mouse_x=x;
}


// OpenGL Setting
void Setting(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

}

 
// OnWindowResize 
void reshape (int w, int h)
{
	WINDOW_WIDTH =w ;
	WINDOW_HEIGHT =h ;

   glViewport (0, 0, (GLsizei) w, (GLsizei) h);

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluOrtho2D (0, w, h, 0);


   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity ();

}

int pcResult =0;/* äÊíÌÉ ÇáßãÈíæÊÑ äÎÒäåÇ åäÇ  */

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


int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (795, 500); 
   glutInitWindowPosition (0, 0);
   glutCreateWindow ("GAME");
    Setting ();
   glutDisplayFunc(Render); 
   glutIdleFunc(Render);
   glutTimerFunc(1,Timer,1);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   //glutSpecialFunc(inputKey);
   //glutSpecialUpFunc(upkey);
   glutPassiveMotionFunc(MouseMotion);
   glutMainLoop();
   return 0;
}
