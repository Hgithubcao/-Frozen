#include<gl/glut.h>
#include<math.h>
struct point
{
	double x;
	double y;
	double z;
	point* next;
	void plotriangle(const point& p0, const point& p1)
	{
		//glFlush();
		//glColor3f(0.94, 0.94, 1);
		glColor3f(0.59, 0.65, 0.91);
		glBegin(GL_TRIANGLES);
			glVertex3f(x, y, z);
			glVertex3f(p0.x, p0.y, p0.z);
			glVertex3f(p1.x, p1.y, p1.z);
		glEnd();
		glColor3f(0.01, 0.01, 1);
		glBegin(GL_LINE_LOOP);
			glVertex3f(x, y, z);
			glVertex3f(p0.x, p0.y, p0.z);
			glVertex3f(p1.x, p1.y, p1.z);
		glEnd();
		//glFlush();//经过这个刷出来
	}
	void rotate(const point& p, point& p1)
	{
		//glFlush();
		p1.x = p.x + (x - p.x) * cos(60.0 / 180.0 * 3.14) - (y - p.y) * sin(60.0 / 180.0 * 3.14);
		p1.y = p.y + (x - p.x) * sin(60.0 / 180.0 * 3.14) + (y - p.y) * cos(60.0 / 180.0 * 3.14);
		p1.z = p.z;
		this -> plotriangle(p, p1);
		//glFlush();
	}
};