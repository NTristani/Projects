#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include <time.h>
using namespace std;


#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_SIZE_WIDTH 700
#define WINDOW_SIZE_HEIGHT 700

int mouseX = 0, mouseY = 0; //global vars to save mouse x/y coord
bool selected = false;//Boolean that determines if a target has been clicked
int clickCount = 0;//Int that prevents program from registering multiple clicks in quick succession
int score = 0;//Player score
int highScore;//High score which is saved and loaded from a text file name "score.txt"
bool newHighScore = false;//If a new high score has been made

bool playing = false;//Boolean that determines if the game is currently being played
bool gameOver = false;//Boolean that is true whenever the player loses
bool clicking = false;//Boolean that is used to temporarily disable on screen text so that ray picking works properly

float playerPos[] = {0,-8.8,0};//Initial player position
//Player's current color: false = turquoise, true = ruby
bool playerCol = false;
bool jump = false;//Boolean that determines if the player is jumping/moving up
bool fall = false;//Boolean that determines if the player is falling/moving down
//Booleans that determine which way the player is currently moving
bool moveLeft = false;//Boolean that determines if the player is moving left
bool moveRight = false;//Boolean that determines if the player is moving right
//Which way the player is facing: 0 = right, 1 = left
int facing = 0;
//Player's current movement speed
float moveSpeed = 0.1;
//Int that determines when the player reaches the top of their jump
int jumpTime = 0;
//Boolean that determines if a bullet is currently moving
bool bulletFired = false;
//Int that determines if a bullet has reached its max travel distance
int bulletTime = 0;
float bulletPos[] = {0,0,0};//Bullet's current position

bool shotDown = false;//If the player shot downwards
bool snipe = true;//If the player is able to use the long-range shot
bool snipeShot = false;//If the long-range shot has been fired
float bulletDir = 0.4;//Used to update the bullet's postion after being fired

int currentTarget = 0;//Which target is current displayed
bool targetList[] = {true,false,false,false,false,false,false,false};//Array that determines which target is displayed
float targetX = 0.0;//Current target's x coordinate
float targetY = 0.0;//Current target's y coordinate
float targetAngle = 0.0;//Target's rotation angle
bool teapot = false;//If teapots are enabled or not

int sceneAngle = 0;//Scene rotation angle
float cloudSpot = 0;//Current location of the clouds


//an array for image data
GLubyte* image;
int width, height, max2;

GLuint myTex[2];

//Position of the light
float light_pos[] = {5,5, 0, 1};

//Ambient, diffuse, and specular values for the light
float amb0[4]  = {1, 1, 1, 1}; 
float diff0[4] = {1, 1, 1, 1}; 
float spec0[4] = {1, 1, 1, 1}; 

//Position of the light
float light_pos2[] = {1.0, 5.0, 1.0, 1};

//Camera values
float camPos[] = {0, 8, 25};
float camLook[] = {0, 0, 0};
float angle = 0.0f;

float lightCaseAngle = 0.0;
float lightAngle = 0.0;


//Values for material turquoise
float m_amb1[] = {0.1, 0.18725, 0.1745, 1.0};
float m_diff1[] = {0.396, 0.74151, 0.69102, 1.0};
float m_spec1[] = {0.297354, 0.30829, 0.306678, 1.0};
float shiny1 = 76.8;

//Values for material ruby
float m_amb3[] = {0.1745, 0.01175, 0.01175, 1.0};
float m_diff3[] = {0.61424, 0.04136, 0.04136, 1.0};
float m_spec3[] = {0.727811, 0.626959, 0.626959, 1.0};
float shiny3 = 76.8;

//Values for material gold
float m_amb4[] = {0.24725, 0.1995, 0.0745, 1.0};
float m_diff4[] = {0.75164, 0.60648, 0.22648, 1.0};
float m_spec4[] = {0.628281, 0.555802, 0.366065, 1.0};
float m_glow4[] = {0.628281, 0.555802, 0.366065, 1.0};
float shiny4 = 60;

float no_glow[] = {0,0,0,0};//Values for when an object has no glow

GLubyte* LoadPPM(char* file, int* width, int* height, int* max)
{
    GLubyte* img;
    FILE *fd;
    int n, m;
    int  k, nm;
    char c;
    int i;
    char b[100];
    float s;
    int red, green, blue;
    
    /* first open file and check if it's an ASCII PPM (indicated by P3 at the start) */
    fd = fopen(file, "r");
    fscanf(fd,"%[^\n] ",b);
    if(b[0]!='P'|| b[1] != '3')
    {
        printf("%s is not a PPM file!\n",file);
        exit(0);
    }
    printf("%s is a PPM file\n", file);
    fscanf(fd, "%c",&c);
    
    /* next, skip past the comments - any line starting with #*/
    while(c == '#')
    {
        fscanf(fd, "%[^\n] ", b);
        printf("%s\n",b);
        fscanf(fd, "%c",&c);
    }
    ungetc(c,fd);
    
    /* now get the dimensions and max colour value from the image */
    fscanf(fd, "%d %d %d", &n, &m, &k);
    
    printf("%d rows  %d columns  max value= %d\n",n,m,k);
    
    /* calculate number of pixels and allocate storage for this */
    nm = n*m;
    img = (GLubyte*)malloc(3*sizeof(GLuint)*nm);
    s=255.0/k;
    
    /* for every pixel, grab the read green and blue values, storing them in the image data array */
    for(i=0;i<nm;i++)
    {
        fscanf(fd,"%d %d %d",&red, &green, &blue );
        img[3*nm-3*i-3]=red*s;
        img[3*nm-3*i-2]=green*s;
        img[3*nm-3*i-1]=blue*s;
    }
    
    /* finally, set the "return parameters" (width, height, max) and return the image array */
    *width = n;
    *height = m;
    *max = k;
    
    return img;
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		//Jump
		case 'x':
		case 'X':
			if(jump == false && fall == false){
				jump = true;
			}
			break;

		//Normal shot
		//Long range shot if the player isn't moving
		case 'c':
		case 'C':
			if(bulletFired == false){
				bulletFired = true;
				shotDown = false;
				if(facing == 0){
					bulletDir = 0.4;
				}
				else{
					bulletDir = -0.4;
				}

				if(snipe==true){
					snipeShot=true;
				}
			}
			break;

		//Shoot downwards
		case 'z':
		case 'Z':
			if(bulletFired == false){
				bulletFired = true;
				shotDown = true;
				bulletDir = 0.4;
			}
			break;
		
		//Change player color/material to turquoise
		case 's':
		case 'S':
			playerCol = false;
			break;

		//Change player color/material to ruby
		case 'd':
		case 'D':
			playerCol = true;
			break;

		//Reset
		case 'r':
		case 'R':
			playerPos[0] = 0;
			playerPos[1] = -8.8;
			playerCol = false;
			moveRight = false;
			moveLeft = false;
			score = 0;
			break;

		//Start game
		case 'o':
		case 'O':
			if(playing == false){
				playing = true;
				gameOver = false;
				targetList[currentTarget] = false;
				currentTarget = 0;
				targetList[0] = true;
				playerPos[0] = 0;
				playerPos[1] = -8.8;
				playerCol = false;
				moveRight = false;
				moveLeft = false;
				score = 0;
			}
			break;


		//Exit game
		case 27:
			exit (0);
			break;

	}
	glutPostRedisplay();
}

void special(int key, int x, int y)
{
	//Arrow keys move the player
	switch(key)
	{
		case GLUT_KEY_LEFT:
			moveLeft = true;
			moveRight = false;
			snipe = false;
			facing = 1;
			break;

		case GLUT_KEY_RIGHT:
			moveRight = true;
			moveLeft = false;
			facing = 0;
			snipe = false;
			break;

		case GLUT_KEY_DOWN:
			moveRight = false;
			moveLeft = false;
			snipe = true;
			break;

		case GLUT_KEY_UP:
			if(jump == false && fall == false){
				jump = true;
			}
			break;
	}
	glutPostRedisplay();
}

void init(void)
{
	//Set the background color
	glClearColor(0, 0, 0.1, 0);
	glColor3f(1, 1, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 100);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	
}

//Draw a cube with normals and texture coordinates
void drawCube(){
	glBegin(GL_QUADS);
	glNormal3f(0,0,1);
	glTexCoord3f(1,1,1);
	glVertex3f(1,1,1);
	glTexCoord3f(-1,1,1);
	glVertex3f(-1,1,1);
	glTexCoord3f(-1,-1,1);
	glVertex3f(-1,-1,1);
	glTexCoord3f(1,-1,1);
	glVertex3f(1,-1,1);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0,0,-1);
	glTexCoord3f(1,1,-1);
	glVertex3f(1,1,-1);
	glTexCoord3f(1,-1,-1);
	glVertex3f(1,-1,-1);
	glTexCoord3f(-1,-1,-1);
	glVertex3f(-1,-1,-1);
	glTexCoord3f(-1,1,-1);
	glVertex3f(-1,1,-1);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glTexCoord3f(1,1,1);
	glVertex3f(1,1,1);
	glTexCoord3f(1,1,-1);
	glVertex3f(1,1,-1);
	glTexCoord3f(-1,1,-1);
	glVertex3f(-1,1,-1);
	glTexCoord3f(-1,1,1);
	glVertex3f(-1,1,1);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0,-1,0);
	glTexCoord3f(1,-1,1);
	glVertex3f(1,-1,1);
	glTexCoord3f(1,-1,-1);
	glVertex3f(1,-1,-1);
	glTexCoord3f(-1,-1,-1);
	glVertex3f(-1,-1,-1);
	glTexCoord3f(-1,-1,1);
	glVertex3f(-1,-1,1);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(1,0,0);
	glTexCoord3f(1,1,1);
	glVertex3f(1,1,1);
	glTexCoord3f(1,-1,1);
	glVertex3f(1,-1,1);
	glTexCoord3f(1,-1,-1);
	glVertex3f(1,-1,-1);
	glTexCoord3f(1,1,-1);
	glVertex3f(1,1,-1);
	glEnd();

	glFrontFace(GL_CW);
	glBegin(GL_QUADS);
	glNormal3f(-1,0,0);
	glTexCoord3f(-1,1,1);
	glVertex3f(-1,1,1);
	glTexCoord3f(-1,-1,1);
	glVertex3f(-1,-1,1);
	glTexCoord3f(-1,-1,-1);
	glVertex3f(-1,-1,-1);
	glTexCoord3f(-1,1,-1);
	glVertex3f(-1,1,-1);
	glEnd();
	glFrontFace(GL_CCW);
}

//Draw the platforms
//Platforms of the player's color are filled, while the others are wireframe
void drawPlatforms(){
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diff1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec1);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny1);
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glTranslatef(0,-10,0);
	
	if(playerCol==false){
		glScalef(4.9,0.5,0.5);
		drawCube();
	}
	else{
		glScalef(10,1,1);
		glutWireCube(1);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5,-7,0);
	
	if(playerCol==false){
		glScalef(2.4,0.5,0.5);
		drawCube();
	}
	else{
		glScalef(5,1,1);
		glutWireCube(1);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7,0,0);
	
	if(playerCol==false){
		glScalef(1.9,0.5,0.5);
		drawCube();
	}
	else{
		glScalef(4,1,1);
		glutWireCube(1);
	}
	glPopMatrix();	

	glPushMatrix();
	glTranslatef(4,-3,0);
	
	if(playerCol==false){
		glScalef(1.9,0.5,0.5);
		drawCube();
	}
	else{
		glScalef(4,1,1);
		glutWireCube(1);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,7,0);
	
	if(playerCol==false){
		glScalef(2.6,0.5,0.5);
		drawCube();
	}
	else{
		glScalef(5,1,1);
		glutWireCube(1);
	}
	glPopMatrix();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb3);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diff3);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec3);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny3);

	glPushMatrix();
	glTranslatef(7,-7,0);
	
	if(playerCol==true){
		glScalef(1,0.5,0.5);
		drawCube();
	}
	else{
		glScalef(2,1,1);
		glutWireCube(1);
	}
	glPopMatrix();

	

	glPushMatrix();
	glTranslatef(-8,-3,0);
	
	if(playerCol==true){
		glScalef(1.9,0.5,0.5);
		drawCube();
	}
	else{
		glScalef(4,1,1);
		glutWireCube(1);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7,3,0);
	
	if(playerCol==true){
		glScalef(1.9,0.5,0.5);
		drawCube();
	}
	else{
		glScalef(4,1,1);
		glutWireCube(1);
	}
	glPopMatrix();

	

	glPushMatrix();
	glTranslatef(-6,3,0);
	
	if(playerCol==true){
		glScalef(1.9,0.5,0.5);
		drawCube();
	}
	else{
		glScalef(4,1,1);
		glutWireCube(1);
	}
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

//Function that loads the high scroe from score.txt
void loadScore(){
	string line;
	ifstream myfile("score.txt");
	if(myfile.is_open()){
		while(getline(myfile,line)){
			stringstream(line) >> highScore;
		}
		myfile.close();
	}
}

//Function that saves a new high score to score.txt
void saveScore(){
	ofstream myfile("score.txt");
	if(myfile.is_open()){
		myfile<<score;
		myfile.close();
	}
}

void checkScore(){
	if(score > highScore){
		saveScore();
		newHighScore = true;
	}
	else{
		newHighScore = false;
	}
}

//Check the location of the player
//If they're not on a platform, they fall
//If the fall past a certain point, the lose
void checkLocation(){
	if(playerPos[1] <= -9 && playerPos[1] > -9.2 && playerPos[0] <= 5.0 && playerPos[0] >= -5.0 && playerCol == false){
		fall = false;
	}
	else if (playerPos[1] <= -6 && playerPos[1] > -6.2 && playerPos[0] <= -2.4 && playerPos[0] >= -7.6 && playerCol == false){
		fall = false;
	}
	else if (playerPos[1] <= -6 && playerPos[1] > -6.2 && playerPos[0] <= 8.0 && playerPos[0] >= 5.4 && playerCol == true){
		fall = false;
	}
	else if(playerPos[1] <= -2 && playerPos[1] > -2.2 && playerPos[0] <= 6.4 && playerPos[0] >= 1.6 && playerCol == false){
		fall = false;
	}
	else if(playerPos[1] <= 1 && playerPos[1] > 0.8 && playerPos[0] <= 9.4 && playerPos[0] >= 4.6 && playerCol == false){
		fall = false;
	}
	else if(playerPos[1] <= -2 && playerPos[1] > -2.2 && playerPos[0] <= -5.4 && playerPos[0] >= -10.6 && playerCol == true){
		fall = false;
	}
	else if(playerPos[1] <= 4 && playerPos[1] > 3.8 && playerPos[0] <= 9.4 && playerPos[0] >= 4.6 && playerCol == true){
		fall = false;
	}
	else if(playerPos[1] <= 8 && playerPos[1] > 7.8 && playerPos[0] <= 2.8 && playerPos[0] >= -3.0 && playerCol == false){
		fall = false;
	}
	else if(playerPos[1] <= 4 && playerPos[1] > 3.8 && playerPos[0] <= -3.6 && playerPos[0] >= -8.4 && playerCol == true){
		fall = false;
	}
	else if(playerPos[1] < -14){
		playing = false;
		gameOver = true;
	}
	
	else{
		fall = true;
		checkScore();//Check the playe's score and compare it to the high score
	}
}

//Draw the player
void drawPlayer(){
	if(playerCol == false){
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb1);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diff1);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec1);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny1);
	}
	else{
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb3);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diff3);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec3);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny3);
	}

	glPushMatrix();
	if(jump == true){
		playerPos[1] += 0.2;
		jumpTime++;
		if(jumpTime >= 25){
			jump = false;
			fall = true;
			jumpTime = 0;
		}
	}
	else if(jump == false){
		checkLocation();//Check the player's location to see if it should be falling
	}
	if(fall == true){
		playerPos[1] -= 0.2;
	}
	if(moveRight == true){ playerPos[0] += moveSpeed;}
	if(moveLeft == true){ playerPos[0] -= moveSpeed;}
	glTranslatef(playerPos[0],playerPos[1],playerPos[2]);
	glutSolidCube(1);
	glPopMatrix();
}

//Functino that randomly picks a new target to display
void newTarget(){
	bulletTime = 20;
	targetList[currentTarget] = false;
	int newTarget = rand() % 8;
	//pick a new target if the previous target was chosen again
	while(newTarget==currentTarget){
		newTarget = rand() % 8;
	}
	currentTarget = newTarget;
	targetList[newTarget] = true;
}

//Check bullet position to see if it hits a target
void checkBullet(){
	if((bulletPos[0] > -7.5 && bulletPos[0] < -6.5) && (bulletPos[1] <=8.5 && bulletPos[1] >= 7.5) && currentTarget == 0){
		score++;
		newTarget();
	}
	else if((bulletPos[0] > -4.5 && bulletPos[0] < -3.5) && (bulletPos[1] <1 && bulletPos[1] > -1) && currentTarget == 1){
		score++;
		newTarget();
	}
	else if((bulletPos[0] > 1.5 && bulletPos[0] < 2.5) && (bulletPos[1] <-4 && bulletPos[1] > -6) && currentTarget == 2){
		score++;
		newTarget();
	}
	else if((bulletPos[0] > 6.5 && bulletPos[0] < 8.5) && (bulletPos[1] <-8 && bulletPos[1] > -10) && currentTarget == 3){
		score++;
		newTarget();
	}
	else if((bulletPos[0] > 12.5 && bulletPos[0] < 13.5) && (bulletPos[1] < 2 && bulletPos[1] > 0) && currentTarget == 4){
		score++;
		newTarget();
	}
	else if((bulletPos[0] > 12.5 && bulletPos[0] < 13.5) && (bulletPos[1] < 6 && bulletPos[1] > 4) && currentTarget == 5){
		score++;
		newTarget();
	}
	else if((bulletPos[0] > -13.5 && bulletPos[0] < -12.5) && (bulletPos[1] < 6 && bulletPos[1] > 4) && currentTarget == 6){
		score++;
		newTarget();
	}
	else if((bulletPos[0] > -13.5 && bulletPos[0] < -12.5) && (bulletPos[1] < 1 && bulletPos[1] > -1) && currentTarget == 7){
		score++;
		newTarget();
	}

}

//Draw the bullet when it's fired
void drawBullet(){
	float bulletSpeed;
	int bulletDist;
	glPushMatrix();
	if(bulletFired == true){
		if(snipeShot==true){
			bulletSpeed = 2;
			bulletDist = 40;
		}
		else{
			bulletSpeed = 1;
			bulletDist = 20;
		}
		glTranslatef(bulletPos[0],bulletPos[1],bulletPos[2]);

		glutSolidSphere(0.3,10,10);
		if(shotDown==false){
			bulletPos[0] += bulletDir*bulletSpeed;
		}
		else{
			bulletPos[1] -= bulletDir*bulletSpeed;
		}
		bulletTime++;
		if(bulletTime >= bulletDist){
			bulletFired = false;
			bulletTime = 0;
			snipeShot = false;
		}
		checkBullet();
	}
	else{
		bulletPos[0] = playerPos[0];
		bulletPos[1] = playerPos[1];
	}
	glPopMatrix();
}

//Draw a laser sight if the player isn't moving
void drawLaser(){
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND); 
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1,0,0,0.5);
	glLineWidth(3);
	glPushMatrix();
	
	glBegin(GL_LINES);
	glVertex3f(playerPos[0],playerPos[1],0);
	if(facing==0){
		glVertex3f(playerPos[0] + 30, playerPos[1], 0);
	}
	else{
		glVertex3f(playerPos[0] - 30, playerPos[1], 0);
	}
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

//Draw the currently selected target
void drawTarget(){
	glPushMatrix();
	if(targetList[0] == true){
		glTranslatef(-7,8,0);
		if(sceneAngle > 0){
			sceneAngle -= 3;
		}
		else if(sceneAngle < 0){
			sceneAngle +=3;
		}
	}
	else if(targetList[1] == true){
		glTranslatef(-4,0,0);
		if(sceneAngle > 0){
			sceneAngle -= 3;
		}
		else if(sceneAngle < 0){
			sceneAngle +=3;
		}
	}
	else if(targetList[2] == true){
		glTranslatef(2,-5,0);
		if(sceneAngle > 0){
			sceneAngle -= 3;
		}
		else if(sceneAngle < 0){
			sceneAngle +=3;
		}
	}
	else if(targetList[3] == true){
		glTranslatef(7,-9,0);
		if(sceneAngle > 0){
			sceneAngle -= 3;
		}
		else if(sceneAngle < 0){
			sceneAngle +=3;
		}
	}
	else if(targetList[4] == true){
		glTranslatef(13,1,0);
		if(sceneAngle < 30){
			sceneAngle += 3;
		}
	}
	else if(targetList[5] == true){
		glTranslatef(13,5,0);
		if(sceneAngle < 30){
			sceneAngle += 3;
		}
	}
	else if(targetList[6] == true){
		glTranslatef(-13,5,0);
		if(sceneAngle > -30){
			sceneAngle -= 3;
		}
	}
	else if(targetList[7] == true){
		glTranslatef(-13,0,0);
		if(sceneAngle > -30){
			sceneAngle -= 3;
		}
	}
	glRotatef(targetAngle,0,1,0);
	glEnable(GL_TEXTURE_2D);
	if(teapot == false){
		glutSolidIcosahedron();
	}
	else{
		glFrontFace(GL_CW);
		glutSolidTeapot(1);
		glFrontFace(GL_CCW);
	}
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	targetAngle += 2;
}

//Draws the light source as a sphere
//The sphere is slightly behind the actual light so it doesn't block the player's view
void drawLightSource(){
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb4);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diff4);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec4);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, m_glow4);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny4);
	glPushMatrix();
	glTranslatef(light_pos[0],light_pos[1],light_pos[2]-5);
	glutSolidSphere(2,20,20);
	glPopMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, no_glow);

}

//Function that draws transparent cubes as clouds
void drawCloud(){
	glDisable(GL_LIGHTING);//Disable lighting for the clouds
	glEnable(GL_BLEND); //Enable blending
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1,1,1,0.5);

	glPushMatrix();
	glTranslatef(cos(cloudSpot)*10,0,0);
    glScalef(3,1,3);
    glutSolidCube(2);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-cos(cloudSpot)*10,-1,0.1);
    glScalef(7,1,3);
    glutSolidCube(2);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-cos(cloudSpot)*4,-9,0.1);
    glScalef(7,1,3);
    glutSolidCube(2);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-cos(cloudSpot)*6,-4,0.1);
    glScalef(4,1,3);
    glutSolidCube(2);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(cos(cloudSpot)*6,-6,0.2);
    glScalef(4,2,3);
    glutSolidCube(2);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-cos(cloudSpot)*6,3,0.1);
    glScalef(4,1,3);
    glutSolidCube(2);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(cos(cloudSpot)*6,4,0.3);
    glScalef(4,1,3);
    glutSolidCube(2);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(cos(cloudSpot)*3,6,0.2);
    glScalef(4,1,3);
    glutSolidCube(2);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-cos(cloudSpot)*8,7,0.1);
    glScalef(4,1,3);
    glutSolidCube(2);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-cos(cloudSpot)*4,8,0.3);
    glScalef(4,1,3);
    glutSolidCube(2);
    glPopMatrix();

    glEnable(GL_LIGHTING);//Re-enable lighting after we draw the clouds
    cloudSpot += 0.002;//Increment the cloud locations
}

//Intersetion calculation for targets
bool CalcIntersections(float tX, float tY, float tZ, float boundX, float boundY, float boundZ){
	//---Construct ray-----------------------------------------------------
	//construct Ray
	GLdouble R0[3], R1[3], Rd[3];
	GLdouble modelMat[16], projMat[16];
	GLint viewMat[4];

	//populate mpv matricies
	glGetDoublev(GL_MODELVIEW_MATRIX, modelMat);
	glGetDoublev(GL_PROJECTION_MATRIX, projMat);
	glGetIntegerv(GL_VIEWPORT, viewMat);

	//calculate near point
	gluUnProject(mouseX, mouseY, 0.0, modelMat, projMat, viewMat, &R0[0], &R0[1], &R0[2]);
	//calculate far point
	gluUnProject(mouseX, mouseY, 1.0, modelMat, projMat, viewMat, &R1[0], &R1[1], &R1[2]);

	//calcualte our ray from R0 and R1
	Rd[0] = R1[0] - R0[0];
	Rd[1] = R1[1] - R0[1];
	Rd[2] = R1[2] - R0[2];

	//turn ray Rd into unit ray 
	GLdouble m = sqrt(Rd[0]*Rd[0] + Rd[1]*Rd[1] + Rd[2]*Rd[2]);
	Rd[0] /= m;
	Rd[1] /= m;
	Rd[2] /= m;

	//calculate t value from z dir;
	double t = (((double)tZ) - R0[2])/Rd[2];

	//use t value to find x and y of our intersection point
	double pt[3];
	pt[0] = R0[0] + t * Rd[0];
	pt[1] = R0[1] + t * Rd[1];
	pt[2] = tZ;

	if(pt[0] > tX - boundX && pt[0] < tX + boundX &&
		pt[1] > tY - boundY && pt[1] < tY + boundY &&
		pt[2] > tZ - boundZ && pt[2] < tZ + boundZ){
		return true;
	}
	else{
		return false;
	}
		

}

//Function that checks for mouse clicks
void mouse(int btn, int state, int x, int y){
	mouseX = x;
	mouseY = WINDOW_SIZE_HEIGHT - y;
	

	//Left mouse button selects objects that you click on
	if(btn == GLUT_LEFT_BUTTON){
		clicking = true;
		//Check which target is currently on screen and calculate a ray intersection through it
		if(targetList[0] == true){
			selected = CalcIntersections(-7,8,0,1,1,1);
			cout<<"CLICKED\n";
		}
		else if(targetList[1] == true){
			selected = CalcIntersections(-4,0,0,1,1,1);
		}
		else if(targetList[2] == true){
			selected = CalcIntersections(2,-5,0,1,1,1);
		}
		else if(targetList[3] == true){
			selected = CalcIntersections(7,-9,0,1,1,1);
		}
		else if(targetList[4] == true){
			selected = CalcIntersections(13,1,0,1,1,1);
		}
		else if(targetList[5] == true){
			selected = CalcIntersections(13,5,0,1,1,1);
		}
		else if(targetList[6] == true){
			selected = CalcIntersections(-13,5,0,1,1,1);
		}
		else if(targetList[7] == true){
			selected = CalcIntersections(-13,5,0,1,1,1);
		}

		if(selected == true && clickCount == 0){
			teapot = !teapot;
			clickCount++;

		}

	}
}

//Function from the sample code that draws text on screen
void drawStrokeText(char* text, int x, int y)
{
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	gluOrtho2D(0, WINDOW_SIZE_WIDTH, 0, WINDOW_SIZE_HEIGHT);  
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
	glTranslatef(x, y, 0);
	glScalef(0.25, 0.25, 0.25);
	
	char* c;  //character iterator (ptr) 
	for(c = text; *c != '\0'; c++) //stop when we hit null character 
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *c); //print one char 
	}
}

//Function that draws the player's score on screen
void drawScore(float x, float y){
	stringstream ss;
	ss << score;
	string str = ss.str();
	char* char_type = (char*)str.c_str();
	drawStrokeText(char_type, x, y);
}

/* display function - GLUT display callback function
 *		clears the screen, sets the camera position, draws the ground plane and movable box
 */
void display(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 100);
	float origin[3] = {0,0,0};
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	

	//Set the camera
	gluLookAt(camPos[0], camPos[1], camPos[2], camLook[0], camLook[1], camLook[2], 0,1,0);

	glLightfv(GL_LIGHT0,GL_POSITION,light_pos);
	glLightfv(GL_LIGHT0,GL_AMBIENT,amb0);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diff0);
	glLightfv(GL_LIGHT0,GL_SPECULAR,spec0);	

	

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diff1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec1);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny1);

	//Draw the main screen
	if(playing == true){
		//Rotate the screen if a target spawns off screen
		glRotatef(sceneAngle,0,1,0);
		glPushMatrix();
		drawPlatforms();
		
		drawPlayer();
		drawBullet();
		if(moveLeft==false && moveRight==false){
			drawLaser();
		}
		drawTarget();
		drawLightSource();
		drawCloud();
		//Text seems to interfere with our ray-picking. So whenever we want to click on an object, we temporarily remove the on screen text
		if(clicking==false){
			drawScore(0,0);
		}
		
		glPopMatrix();

		//Prevent the game from registering multiple clicks in quick succession
		//Also re enables the score display after clicking on an object
		if(clickCount > 0 && clickCount < 20){
			clickCount++;
			clicking = false;
		}
		else{
			clickCount = 0;
			
		}

	}
	else{
		//Draw Text
		glLineWidth(3);
		glColor3f(1,1,1);
		if(gameOver==false){
			drawStrokeText("2.5D Classic Shooter", 200, 400);
			drawStrokeText("Press O to start", 225, 200);
			drawStrokeText("Press Esc to exit",225,100);
		}
		else{
			drawStrokeText("GAME OVER", 200, 600);
			drawStrokeText("Score: ",200,500);
			drawScore(300,500);
			drawStrokeText("High Score: ",200,400);
			stringstream ss;
			ss << highScore;
			string str = ss.str();
			char* char_type = (char*)str.c_str();
			drawStrokeText(char_type, 400, 400);
			if(score > highScore){
				drawStrokeText("New high score!",200,300);
			}
			drawStrokeText("Press O to play again",200,200);
			drawStrokeText("Press Esc to exit",200,100);
		}
		
	}
	
	glutSwapBuffers();
}

void FPS(int val){
	glutPostRedisplay();
	glutTimerFunc(17, FPS, 0);
}

void callBackInit(){
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutTimerFunc(0, FPS, 0);
}

/* main function - program entry point */
int main(int argc, char** argv)
{
	srand(time(NULL));//Initialise seed
	loadScore();//Load the high score
	glutInit(&argc, argv);		//starts up GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	

	glutInitWindowSize(700, 700);
	glutInitWindowPosition(50, 100);

	glutCreateWindow("Modeller");	//creates the window

	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	callBackInit();

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glEnable(GL_DEPTH_TEST);

	init();

	/* TEXTURES */
    glGenTextures(2, myTex);
    
    /* Set the image parameters*/
    glBindTexture(GL_TEXTURE_2D, myTex[0]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    
    /*Get and save image*/
    image = LoadPPM("marble.ppm",&width, &height,&max2);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, image);
	
	glutMainLoop();				//starts the event glutMainLoop
	return(0);					//return may not be necessary on all compilers
}
