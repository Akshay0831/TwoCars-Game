#include<GL/glut.h>
#include<string.h>
#include<ctime>
#include<fstream>

#define MAINMENU 0
#define RUNNING 1
#define PAUSED 2
#define GAMEOVER 3
#define HEIGHT 40
#define WIDTH 40
#define FPS 30
#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2

using namespace std;

int gameState = MAINMENU;
int highscore;

int width=WIDTH,height=HEIGHT-3;
int posX1=3,posY1=2,posX2=23,posY2=2;
int Direction;
int flagL=0,flagR=0,flagU=0,flagD=0;
int SquareX1,SquareY1,SquareX2,SquareY2;
bool Square1 = true,Square2 = true;
int score = 0,i;
char buffer[10],bufferHS[10];

void drawLanes(){
	glLineWidth(10.0);
	glColor3f(0.5,0.0,0.8);
	glBegin(GL_LINES);
		glVertex2f(width/2.0,0.0);
		glVertex2f(width/2.0,height);
	glEnd();

	glLineWidth(4.0);
	glColor3f(0.5,0.0,1.0);
	glBegin(GL_LINES);
		glVertex2f(width/4.0,0.0);
		glVertex2f(width/4.0,height);
	glEnd();
	glBegin(GL_LINES);
		glVertex2f(3*(width/4.0),0.0);
		glVertex2f(3*(width/4.0),height);
	glEnd();
}

void drawCar(int posX1, int posY1, float R, float G, float B){
	glColor3f(R, G, B);
	glBegin(GL_POLYGON);
		glVertex2f(posX1+3.9, posY1+4.8);
		glVertex2f(posX1+3.88, posY1+4.88);
		glVertex2f(posX1+3.8, posY1+4.9);
		glVertex2f(posX1+3.7, posY1+5);
		glVertex2f(posX1+0.3, posY1+5);
		glVertex2f(posX1+0.2, posY1+4.9);
		glVertex2f(posX1+0.12, posY1+4.88);
		glVertex2f(posX1+0.1, posY1+4.8);
		glVertex2f(posX1, posY1+4.6);
		glVertex2f(posX1, posY1+0.4);
		glVertex2f(posX1+0.1, posY1+0.2);
		glVertex2f(posX1+0.12, posY1+0.12);
		glVertex2f(posX1+0.2, posY1+0.1);
		glVertex2f(posX1+0.3, posY1);
		glVertex2f(posX1+3.7, posY1);
		glVertex2f(posX1+3.8, posY1+0.1);
		glVertex2f(posX1+3.88, posY1+0.12);
		glVertex2f(posX1+3.9, posY1+0.2);
		glVertex2f(posX1+4, posY1+0.4);
		glVertex2f(posX1+4, posY1+4.6);
	glEnd();
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
		glVertex2f(posX1+3.6, posY1+4.5);
		glVertex2f(posX1+3.58, posY1+4.58);
		glVertex2f(posX1+3.5, posY1+4.6);
		glVertex2f(posX1+3.4, posY1+4.7);
		glVertex2f(posX1+0.6, posY1+4.7);
		glVertex2f(posX1+0.4, posY1+4.6);
		glVertex2f(posX1+0.42, posY1+4.58);
		glVertex2f(posX1+0.4, posY1+4.5);
		glVertex2f(posX1+0.3, posY1+4.3);
		glVertex2f(posX1+0.3, posY1+0.7);
		glVertex2f(posX1+0.4, posY1+0.5);
		glVertex2f(posX1+0.42, posY1+0.42);
		glVertex2f(posX1+0.5, posY1+0.4);
		glVertex2f(posX1+0.6, posY1+0.3);
		glVertex2f(posX1+3.4, posY1+0.3);
		glVertex2f(posX1+3.5, posY1+0.4);
		glVertex2f(posX1+3.58, posY1+0.42);
		glVertex2f(posX1+3.6, posY1+0.5);
		glVertex2f(posX1+3.7, posY1+0.7);
		glVertex2f(posX1+3.7, posY1+4.3);
	glEnd();
	glColor3f(R, G, B);
	glBegin(GL_POLYGON);
		glVertex2f(posX1+1, posY1+2);
		glVertex2f(posX1+1, posY1+3);
		glVertex2f(posX1+0.6, posY1+4);
		glVertex2f(posX1+0.8, posY1+4.2);
		glVertex2f(posX1+3.2, posY1+4.2);
		glVertex2f(posX1+3.4, posY1+4);
		glVertex2f(posX1+3, posY1+3);
		glVertex2f(posX1+3, posY1+2);
		glVertex2f(posX1+3.4, posY1+1);
		glVertex2f(posX1+3.2, posY1+0.8);
		glVertex2f(posX1+0.8, posY1+0.8);
		glVertex2f(posX1+0.6, posY1+1);
		glVertex2f(posX1+1, posY1+2);
	glEnd();
	glColor3f(0.0,0.0,0.0);
	glRectd(posX1+1,posY1+2,posX1+3, posY1+3);
}

void drawCars(){
	if(Direction==UP && flagU==0 && posX1>0 && posX1<10){
		posX1+=10;
		flagU = 1;
	}
	else if(Direction==DOWN && flagD==0 && posX1>10 && posX1<20){
		posX1-=10;
		flagD = 1;
	}
	else if(Direction==RIGHT && flagR==0 && posX2>20 && posX2<30){
		posX2+=10;
		flagR = 1;
	}
	else if(Direction==LEFT && flagL==0 && posX2>30 && posX2<40){
		posX2-=10;
		flagL = 1;
	}
	
	drawCar(posX1, posY1, 1.0, 0.0, 0.0);
	drawCar(posX2, posY2, 0.0, 0.2, 1.0);
	
	if((posX1+4==SquareX1+4 && posY1+5>=SquareY1 && posY1<SquareY1) || (posX2+4==SquareX2+4 && posY2+5>=SquareY2 && posY2<SquareY2))
		gameState = GAMEOVER;
	
}

void random1(int &x,int &y){
	int _maxY = height,_min = 25;
	srand(time(NULL));
	
	x = posX1;
	y = _min + rand() % (_maxY - _min);
}

void drawSquare(int squareX, int squareY, float R, float G, float B) {
	glColor3f(R, G, B);
	glBegin(GL_POLYGON);
		glVertex2f(squareX,squareY+0.2);
		glVertex2f(squareX+0.2,squareY);
		glVertex2f(squareX+3.8,squareY);
		glVertex2f(squareX+4,squareY+0.2);
		glVertex2f(squareX+4,squareY+2.8);
		glVertex2f(squareX+3.8,squareY+3);
		glVertex2f(squareX+0.2,squareY+3);
		glVertex2f(squareX,squareY+2.8);
		glVertex2f(squareX,squareY+0.2);
	glEnd();
	
	glColor3f(1.0,1.0,1.0);
	glRectf(squareX+0.5,squareY+0.5,squareX+3.5,squareY+2.5);
	
	glColor3f(R, G, B);
	glRectf(squareX+1,squareY+1,squareX+3,squareY+2);
}

void drawSquares(){
	if(Square1){
		random1(SquareX1,SquareY1);
		score++;
	}
	Square1 = false;
	drawSquare(SquareX1, SquareY1, 0.0, 0.2, 1.0);

	if(Square2){
		SquareX2=posX2;SquareY2=25+(SquareY1+10)%10;
		score++;
	}
	Square2 = false;	
	drawSquare(SquareX2, SquareY2, 1.0, 0.0, 0.0);
}

void drawText(const char* ch,int xpos, int ypos, void *font){
	int numofchar = strlen(ch);
	glLoadIdentity();
	glRasterPos2f( xpos , ypos);
	for (i = 0; i <= numofchar - 1; i++){
		glutBitmapCharacter(font, ch[i]);
	}
}

void drawTextNum(const char* ch,int numtext,int xpos, int ypos){
	int len, k = 0;
	len = numtext - strlen (ch);
	glLoadIdentity ();
	glRasterPos2f( xpos , ypos);
	for (i = 0; i <=numtext - 1; i++)
	{
	if ( i < len )
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'0');
	else
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch[k]);
		k++;
	}
	}
}
void utoa(int dataIn, char* bffr, int radix){
	int temp_dataIn;
	temp_dataIn = dataIn;
	int stringLen=1;

	while ((int)temp_dataIn/radix != 0){
		temp_dataIn = (int)temp_dataIn/radix;
		stringLen++;
	}
	temp_dataIn = dataIn;
	do{
		*(bffr+stringLen-1) = (temp_dataIn%radix)+'0';
		temp_dataIn = (int) temp_dataIn / radix;
	}while(stringLen--);
}



void reshapeFunc(int w,int h){
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,HEIGHT,0.0,WIDTH,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
}

void timerFunc(int){
	glutPostRedisplay();
	glutTimerFunc(1000/FPS,timerFunc,0);

	if(score<=20){
		if(SquareY1>0)
			SquareY1 -= 0.15;
		if(SquareY1==0)
			Square1 = true;

		if(SquareY2>0)
			SquareY2 -= 0.15;
		if(SquareY2==0)
			Square2 = true;
	}else if(score>20 && score<=50){
		if(SquareY1>0)
			SquareY1 -= 0.25;
		if(SquareY1==0)
			Square1 = true;

		if(SquareY2>0)
			SquareY2 -= 0.25;
		if(SquareY2==0)
			Square2 = true;
	}else{
		if(SquareY1>0)
			SquareY1 -= 0.35;
		if(SquareY1==0)
			Square1 = true;

		if(SquareY2>0)
			SquareY2 -= 0.35;
		if(SquareY2==0)
			Square2 = true;
	}
}

void SpecialKeyHandler(int key,int x,int y){
	switch(key){
		case GLUT_KEY_RIGHT:
			if(Direction!=RIGHT){
				Direction=RIGHT;
				flagR=0;
			}
			break;

		case GLUT_KEY_LEFT:
			if(Direction!=LEFT){
				Direction=LEFT;
				flagL=0;
			}
			break;
	}
}

void NormalKeyHandler(unsigned char key,int x,int y){
	switch(key){
		 case 'd':
			if(Direction!=UP ){
				Direction=UP;
				flagU=0;
			}
			break;
		case 'a':
			if(Direction!=DOWN){
				Direction=DOWN;
				flagD=0;
			}
			break;
		case 040:
			if(gameState == MAINMENU) gameState=RUNNING;
		 	break;
		case 033:
		 	if(gameState == RUNNING) gameState = PAUSED;
		 	else if(gameState == PAUSED) gameState = RUNNING;
			else if(gameState == GAMEOVER) gameState = MAINMENU;
	 		break;
		case 'q': 
			exit(0);	 
	}
}

void init(){
	glClearColor(0.0,0.1,0.3,1.0);
	gluOrtho2D(0, 500, 0, 500);
	glMatrixMode(GL_MODELVIEW);
}

void displayFunc(){
	if(gameState == MAINMENU)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0,0,0);
		glRectd(0, 34, WIDTH, 37);
		glRectd(0, 21, 17, 26);
		glRectd(22, 19, WIDTH, 24);
		glColor3f(1,1,1);
		drawText("Press Space to Play", 14, 11,GLUT_BITMAP_HELVETICA_18);
		drawText("T W O    C A R S", 12,35,GLUT_BITMAP_TIMES_ROMAN_24);
		glColor3f(1,0,0);
		drawText("A to Move Left" , 3, 24,GLUT_BITMAP_HELVETICA_18);
		drawText("D to  Move Right", 2, 22,GLUT_BITMAP_HELVETICA_18);
		glColor3f(0,0.3,1);
		drawText("<- to Move Left" , 26, 22,GLUT_BITMAP_HELVETICA_18);
		drawText("-> to Move Right", 26, 20,GLUT_BITMAP_HELVETICA_18);
		drawCar(14, 21, 1, 0, 0);
		drawCar(21, 19, 0, 0.2, 1.0);
		glutSwapBuffers();
	}
	else if(gameState==RUNNING){
		glClear(GL_COLOR_BUFFER_BIT);
		drawLanes();
		drawCars();
		drawSquares();
		glColor3f(1,1,1);
		drawText("Score:", 3,38,GLUT_BITMAP_HELVETICA_18);
		utoa(score, buffer, 10);
		drawTextNum(buffer, 6, 8,38);

		drawText("HighScore:", 23,38,GLUT_BITMAP_HELVETICA_18);
		utoa(highscore, bufferHS, 10);
		drawTextNum(bufferHS, 6, 31,38);	
		glutSwapBuffers();
		for(int q = 0; q<= 10000000; q++);
	}
	else if(gameState == PAUSED){
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0,0,0);
		glRectd(0, 34, WIDTH, 37);
		glRectd(0, 21, 17, 26);
		glRectd(22, 19, WIDTH, 24);
		glColor3f(1.0,0.6,0.2);
		drawText("|| PAUSED", 15,35,GLUT_BITMAP_TIMES_ROMAN_24);
		glColor3f(1,0,0);
		drawText("A to Move Left" , 3, 24,GLUT_BITMAP_HELVETICA_18);
		drawText("D to  Move Right", 2, 22,GLUT_BITMAP_HELVETICA_18);
		glColor3f(0,0.3,1);
		drawText("<- to Move Left" , 26, 22,GLUT_BITMAP_HELVETICA_18);
		drawText("-> to Move Right", 26, 20,GLUT_BITMAP_HELVETICA_18);
		glColor3f(1,1,1);
		drawText("Press Esc to Resume", 12, 11,GLUT_BITMAP_HELVETICA_18);
		drawCar(14, 21, 1, 0, 0);
		drawCar(21, 19, 0, 0.2, 1.0);
		glutSwapBuffers();
	
	}
	else if(gameState==GAMEOVER){
		glColor3f(0,0,0);
		glRectd(0, 34, WIDTH, 37);
		fstream File;
		if(highscore<score){
			highscore = score;
			File.open("game.save",ios::out | ios::trunc);
			File<<highscore;
			File.close();
		}
		glColor3f(1,0,0);
		drawText("GAME OVER", 14,35,GLUT_BITMAP_TIMES_ROMAN_24);
		glColor3f(1,1,1);
		drawText("Press Q to quit", 14,20,GLUT_BITMAP_HELVETICA_18);
		drawText("Press Esc for Main Menu", 12, 18,GLUT_BITMAP_HELVETICA_18);
		glutSwapBuffers();
	}
}

int main(int argc,char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	ifstream hsFile;
	hsFile.open("game.save");
	hsFile >> highscore;
	hsFile.close();

	glutInitWindowSize(500,800);
	glutCreateWindow("Two Cars");
	init();
	glutDisplayFunc(displayFunc);
	glutReshapeFunc(reshapeFunc);
	glutTimerFunc(0,timerFunc,0);
	glutSpecialFunc(SpecialKeyHandler);
	glutKeyboardFunc(NormalKeyHandler);
	glutIdleFunc(displayFunc);
	glutMainLoop();
	return 0;
}
