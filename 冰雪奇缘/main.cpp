#include"snow.h"
#include"people.h"
#include<stdio.h>

float times = -1; 
/*float eyex = 0;
float eyey = 0;
float eyez = 10;
float pointx = 0;
float pointy = 0;
float pointz = 0;
float upx = 0;
float upy = 1;
float upz = 0;*/
snow x;
people me;
GLsizei winWidth = 600;
GLsizei winHeight = 600;
GLfloat xComplexMin = -600; 
GLfloat xComplexMax = 600;
GLfloat yComplexMin = -600;
GLfloat yComplexMax = 600;
GLfloat znear = -600;
GLfloat zfar = 600;


void init()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(370, 80);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("冰雪奇缘");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);  

	glOrtho(xComplexMin, xComplexMax, yComplexMin, yComplexMax, znear, zfar);
	/*glMatrixMode(GL_PROJECTION);  
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();  //将当前的用户坐标系的原点移到了屏幕中心
	gluPerspective(120, 1, 100, 600); ;
	glMatrixMode(GL_MODELVIEW);  
	glLoadIdentity();
	gluLookAt(20, 20, 20, 0, 0, 0, 0, 0 ,1);*/
	me.pos();
}

void winReshapeFun(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(xComplexMin, xComplexMax, yComplexMin, yComplexMax, znear, zfar);
	glClear(GL_COLOR_BUFFER_BIT);
	//times = 0;
}

void cycle(double r, double xr, double yr)
{
	int x;
	int y;
	double pie = 6.28;
	double add = 0.01;
	double weizhi = 0;
	glColor3f(1, 0, 1);
	while(weizhi <= pie)
	{
		x = xr + r * cos(weizhi);
		y = yr + r * sin(weizhi);
		glBegin(GL_POINTS);
		glVertex3f(x, y, 0);
		glEnd();
		weizhi += add;
	}
	//glFlush();
}

void zfensan()//雪花散开
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
	me.pos();
	//glMatrixMode(GL_PROJECTION);  
	//glLoadIdentity();  //将当前的用户坐标系的原点移到了屏幕中心
	//gluPerspective(180, 1, -100, 100);  //观察的视景体在世界坐标系中的具体大小(角度,视景体的宽高比,沿z轴方向的两裁面之间的距离的近处,沿z轴方向的两裁面之间的距离的远处)
	//glMatrixMode(GL_MODELVIEW);  
	//glLoadIdentity();
	//glPushMatrix();
	//gluLookAt(70, 0, 0, 0, 0, 0, 0, 0, 1);
	//gluLookAt(20, 20, 20, 0, 0, 0, 0, 0, 1);

	//glFlush();
	//glFlush();
	
	//delete [] str;


	//重点雪
	//static float times = -1;
	x.drawsnow();
	//x.origintriangle();
	if((int)times % 2 == 0)
	{
		times ++;
	}
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3d(0, 0, -40);
	glVertex3d(0, 0, 40);
	glVertex3d(10, 0, 10);
	glVertex3d(0, 0, 40);
	glVertex3d(-10, 0, 10);
	glVertex3d(0, 0, 40);

	glVertex3d(-40, 0, 0);
	glVertex3d(40, 0, 0);
	glVertex3d(10, 0, 10);
	glVertex3d(40, 0, 0);
	glVertex3d(-10, 0, 10);
	glVertex3d(40, 0, 0);

	glVertex3d(0, -40, 0);
	glVertex3d(0, 40, 0);
	glVertex3d(10, 0, 10);
	glVertex3d(0, 40, 0);
	glVertex3d(-10, 0, 10);
	glVertex3d(0, 40, 0);
	glEnd();
	/*glColor3f(1, 1, 1);
	glutSolidSphere(10, 20, 20);*/
	cycle(43, 0, 0);
	cycle(280, 200, 200);
	glFlush();
	glutSwapBuffers();
	//glPopMatrix();
	//glutPostRedisplay();
}

void myIdle()
{
	_sleep(500);
	//x.origintriangle();
	if(times <= 4)
	{
		//gluLookAt(eyex, 0, 10, 0, 0, 0, 0, 1, 0);
		//glColor3f(0.94, 0.94, 1);
		//eyez -= times * 20;
		++times;
		zfensan();
		_sleep(500);
	}
	/*else
	{
	eyex ++;
	glEnable(GL_DEPTH_TEST);  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
	zfensan();
	}*/
}

void mouse(GLint button, GLint action, GLint xmouse, GLint ymouse)//鼠标输入
{
	if(button == GLUT_WHEEL_UP || button == GLUT_WHEEL_DOWN)
	{
		glColor3f(0,0 ,1);
		glBegin(GL_LINES);
		glVertex3i(200, 200, 200);
		glVertex3i(-100, -100, -100);
		glEnd();

	}
	if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
	{
		glColor3f(1,1,1);
		glBegin(GL_LINES);
		glVertex2d((double)xmouse - 300, 300 - (double)ymouse);
		glVertex2d(0,1);
		glEnd();
	}
	glFlush();
}


void keyboard(GLubyte key, GLint x, GLint y)
{
	//int* view;

	switch(key)
	{
	case 'W':
	case 'w':
		/*glColor3f(1,0,0);
		glBegin(GL_LINES);
		glVertex2d(x - 300, 300 - y);
		glVertex2d(0,0);
		glEnd();
		glFlush();*/

		me.go();
		break;
	case 'S':
	case 's':
		me.back();
		break;
	case 'A':
	case 'a':
		me.left();
		break;
	case 'D':
	case 'd':
		me.right();
		break;
	case 'H':
	case 'h':
		me.reset();
		break;
	}
	//glMatrixMode(GL_MODELVIEW);  
	//glLoadIdentity();
	//me.pos();
	//gluLookAt(eyex, eyey, eyez, pointx, pointy, pointz, upx, upy,upz);
	//glutPostRedisplay();
	//glFlush();
}

void keyspeciall(GLint key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_UP:
		me.go();
		break;
	case GLUT_KEY_DOWN:
		me.back();
		break;
	case GLUT_KEY_LEFT:
		me.left();
		break;
	case GLUT_KEY_RIGHT:
		me.right();
		break;
	}
	//glMatrixMode(GL_MODELVIEW);  
	//glLoadIdentity();
	//me.pos();
	//glutPostRedisplay();
	//glFlush();
}

void mousemove(int x, int y)
{
	if(me.mousex() == -1000 && me.mousey() == -1000)
	{
		me.setmouse(x, y);
	}
	if(x != me.mousex())
	{
		me.viewturnleft(x);
	}
	if(y != me.mousey())
	{
		glColor3f(1,1,1);
		glBegin(GL_LINES);
		glVertex2d((double)x - 300, 300 - (double)y);
		glVertex2d(0,1);
		glEnd();
		glFlush();
		me.viewup(y);
	}
	//glMatrixMode(GL_MODELVIEW);  
	//glLoadIdentity();
	//me.pos();
	//glutPostRedisplay();
	//glFlush();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	init();
	glutDisplayFunc(zfensan);
	glutReshapeFunc(winReshapeFun);
	glutIdleFunc(&myIdle);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyspeciall);
	glutPassiveMotionFunc(mousemove);
	glutMainLoop();
	return 0;
}