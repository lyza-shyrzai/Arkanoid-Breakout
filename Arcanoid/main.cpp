#include <GL\glut.h>
#include <math.h>
#include "Ball.h"
#include "vars.h"
#include "Brick.h"

float r_x = 50.0, r_y = 290.0, r_w = 80, r_h = 8.0; //coordinates and dimensions of the racket

Ball ball(5);
Brick brick[10][15];

bool isCollision(Ball const& b, Brick const& br)
{
	float x = b.x, y = b.y, r = b.r, c = br.col, w = br.w, row = br.row, h = br.h;
	if (br.active)
	{
		//whether a ball or block near?
		if (fabs(x - c*w - w / 2 - 2) <= r + w / 2 && fabs(y - row*h - h / 2 - 2) <= r + h / 2)
		{
			// check angle collisions
			if (sqrt((c*w + w / 2 - x)*(c*w + w / 2 - x) + (row*h + h / 2 - y)*(row*h + h / 2 - y))
				- (w / 2 - 1)*sqrt(2.0) - r > r*(sqrt(2.0) - 1))
				return 0;
			else
				return 1;
		}
	}
	return 0;
}

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 0.0); //color of racket 
	glRectf(r_x, r_y, r_x + r_w, r_y + r_h);
	glColor3f(0.0, 0.0, 1.0); //color of ball
	//ball drawing
	glBegin(GL_POLYGON);
	for (float i = 0; i < 2 * 3.14; i += 3.14 / 4)
	{
		glVertex2f(ball.x + ball.r*sin(i), ball.y + ball.r*cos(i));
	}
	glEnd();
	//block drawing
	glColor3f(0.1, 0.2, 0.8);
	glBegin(GL_QUADS);
	for (int i = 0; i < 10; i++)
	{
		//changing color: gradient
		glColor3ub(i * 28, i*70, 50);
		for (int j = 0; j < 15; j++)
		{
			Brick &b = brick[i][j];
			if (b.active)
			{
				glVertex2f(b.col*b.w+1, b.row*b.h+1);
				glVertex2f(b.col*b.w + b.w-1, b.row*b.h+1);
				glVertex2f(b.col*b.w + b.w-1, b.row*b.h + b.h-1);
				glVertex2f(b.col*b.w+1, b.row*b.h + b.h-1);
			}
		}
	}
	glEnd();
	glutSwapBuffers();
}

void Timer(int)
{
	if (ball.active)
	{
		ball.move();
		//collision with a block
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				Brick &b = brick[i][j];
				if (isCollision(ball, b))
				{
					//if a ball is above or below
					if (fabs(ball.x - b.col*b.w - b.w / 2) < fabs(ball.y - b.row*b.h - b.h / 2))
					{
						ball.dy *= -1;
					}
					//if a ball is left or right
					else if (fabs(ball.x - b.col*b.w - b.w / 2) > fabs(ball.y - b.row*b.h - b.h / 2))
					{
						ball.dx *= -1;
					}
					//a ball is on the diagonal side of the block 
					else
					{
						if (ball.dx>0)
						{
							if (ball.x < b.col*b.w + 1) ball.dx *= -1;
						}
						else if (ball.x >(b.col + 1)*b.w - 1) ball.dx *= -1;
						if (ball.dy>0)
						{
							if (ball.y < b.row*b.h + 1) ball.dy *= -1;
						}
						else if (ball.y >(b.row + 1)*b.h - 1) ball.dy *= -1;
					}
					//If "life" block is equal to 0
					if (--b.hit == 0)
					{
						b.active = false;
					}
				}
			}
		}
	}
    Draw();
	glutTimerFunc(33, Timer, 0);
}

void MousePress(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && !ball.active)
	{
		ball.active = true;
		ball.dx = 4; //speed
		ball.dy = -4;
	}
}

//Tracking the movement of the racket with the mouse
void RacketMouse(int ax, int ay)
{
	r_x = ax - r_w / 2;
	if (!ball.active)
	{
		ball.x = r_x + r_w / 2; // a ball in the middle of the racket
		ball.y = r_y - ball.r;
	}	
}


void Init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0); //background color
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, 300, 300, 0, 1, 0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("Arkanoid ++i");
	glutDisplayFunc(Draw);
	glutTimerFunc(33, Timer, 0);
	glutPassiveMotionFunc(RacketMouse);
	glutMouseFunc(MousePress);
	Init();
	for (int i=0; i<10;i++)
		for (int j = 0; j < 15; j++)
		{
			brick[i][j].active = true;
			brick[i][j].col = j;
			brick[i][j].row = i;
		}
	glutMainLoop();
	return 0;
}