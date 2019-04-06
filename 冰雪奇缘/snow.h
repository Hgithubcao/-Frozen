#include<iostream>
#include"point.h"
#include<queue>
using namespace std;

extern float times;

class snow
{
	int pnum;
	queue<point> pointqueue;
	point origin[3];
	point* head;
	point* tail;
	GLuint snowy;
public:
	snow()
	{
		//times = 1000;
		pnum = 0;
		origin[0].x = 300;
		origin[0].y = -240;
		origin[0].z = 0;
		origin[1].x = -300;
		origin[1].y = -240;
		origin[1].z = 0;
		head = &origin[0];
		origin[0].next = &origin[1];
		//origin[0].rotate(origin[1], origin[2]);
		pointqueue.push(origin[0]);
		pointqueue.push(origin[1]);
		tail = NULL;
		//pointqueue.push(origin[2]);
		//glFlush();
	}

	void origintriangle()
	{
		origin[0].plotriangle(origin[1], origin[2]);
	}
	/*void drawsnow(int times)
	{
	if(times == 0)
	{
	point p;
	origin[0].rotate(origin[1], p);
	pointqueue.push(p);
	times ++;
	drawsnow(times);
	}
	else if(times < 500)
	{
	times ++;
	point p0;
	point p1;
	point p3;
	point p4;
	point p5;
	p0 = pointqueue.front();
	pointqueue.pop();
	p1 = pointqueue.front();
	pointqueue.push(p0);
	p3.x = p1.x / 3 + p0.x * 2 / 3;
	p3.y = p1.y / 3 + p0.y * 2 / 3;
	p3.z = p1.z;
	p5.x = p0.x / 3 + p1.x * 2 / 3;
	p5.y = p0.y / 3 + p1.y * 2 / 3;
	p5.z = p1.z;
	p5.rotate(p3, p4);
	pointqueue.push(p3);
	pointqueue.push(p4);
	pointqueue.push(p5);
	drawsnow(times);
	}
	}*/
	
	void drawsnow()
	{
		//glFlush();
		//origin[0].plotriangle(origin[1], origin[2]);
		point p0;
		point p1;

		point* pnext1;
		point* pnext2;
		if(times > 4)
		{
			glColor3f(0.59, 0.65, 0.91);
			if(!glIsList(1))
			{
				snowy = glGenLists(1);
				glNewList(snowy, GL_COMPILE);
				pnext1 = head;
				glBegin(GL_TRIANGLES);
				while(pnext1)
				{
					glVertex3d(pnext1 -> x, pnext1 -> y, pnext1 -> z);
					pnext1 = pnext1 -> next;
				}
				/*for(int i = 0; i <= 3 * pnum; i ++)
				{
				p0 = pointqueue.front();
				pointqueue.pop();
				pointqueue.push(p0);
				glVertex3d(p0.x, p0.y, p0.z);
				}*/
				glEnd();
				/*pnext1 = head;
				glColor3f(0, 0, 0);
				glBegin(GL_LINES);
				while(pnext1)
				{
					glVertex3d(pnext1 -> x, pnext1 -> y, pnext1 -> z);
					pnext1 = pnext1 -> next;
				}
				glEnd();*/
				//boundfill4(0, 0);
				glEndList();
			}
			glCallList(snowy);
			return;
		}
		float p = 3 * pow(4, times - 1);
		pnum += p;
		//if(times < 1)
		//{
		//p = 1;
		//}
		for(int i = 0; i < p; i ++)
			//while(pointqueue.front().x != origin[0].x)
		{
			point* p3 = new point;
			point* p4 = new point;
			point* p5 = new point;
			glFlush();
			p0 = pointqueue.front();
			pointqueue.pop();
			p1 = pointqueue.front();
			pointqueue.push(p0);
			if(p > 1)
			{
				//glFlush();
				p3 -> x = p1.x / 3 + p0.x * 2 / 3;
				p3 -> y = p1.y / 3 + p0.y * 2 / 3;
				p3 -> z = p1.z;
				p5 -> x = p0.x / 3 + p1.x * 2 / 3;
				p5 -> y = p0.y / 3 + p1.y * 2 / 3;
				p5 -> z = p1.z;
				//glFlush();//这里之后刷没了=。=
				p5 -> rotate(*p3, *p4);
				//glFlush();
				pointqueue.push(*p3);
				pointqueue.push(*p4);

				tail -> next = p3;
				p3 -> next = p4;
				p4 -> next = p5;
				tail = p5;
				tail -> next = NULL;
				/*tail -> next = &p3;
				tail = tail -> next;
				tail -> next = &p4;
				tail = tail -> next;
				tail -> next = &p5;
				tail = tail -> next;
				tail -> next = NULL;;*/
			}
			else
			{
				pointqueue.pop();
				pointqueue.push(p1);
				//glFlush();
				p0.rotate(p1, *p5);
				origin[2] = *p5;
				origin[1].next = &origin[2];
				tail = origin[1].next;
				tail -> next = NULL;
				//glFlush();
			}
			pointqueue.push(*p5);
			//glFlush();
		}
	}
	void boundfill4(int x, int y)
	{
		double color[3];
		point p;
		point p1;
		p.x = x;
		p.y = y;
		p.z = 0;
		queue<point> fill;
		fill.push(p);
		while(fill.size())
		{
			p = fill.front();
			fill.pop();
			glReadPixels(p.x, p.y, 1, 1, GL_RGB, GL_DOUBLE, color);
			if(color[0] != 0.59 || color[1] != 0.65 || color[2] != 0.91)
			{
				glColor3f(0.59, 0.65, 0.91);
				glBegin(GL_POINTS);
				//glVertex3d(100, 10, -100);
				glVertex3d(x, y, 0);
				glEnd();
				glFlush();
				p1 = p;
				p1. x ++;//x+1
				fill.push(p1);
				p.x --;
				p1.y ++;//y+1
				fill.push(p1);
				p.x --;
				p.y --;//x-1
				fill.push(p1);
				p.x ++;
				p.y --;//y--
				fill.push(p1);
			}
			glFlush();
		}
		/*glReadPixels(x,y,1,1,GL_RGB,GL_DOUBLE,color);
		//glColor3f(0.59, 0.65, 0.91);
		if(color[0] != 0.59 || color[1] != 0.65 || color[2] != 0.91)
		{
		glColor3f(0.59, 0.65, 0.91);
		glBegin(GL_LINES);
		glVertex3d(100, 10, -100);
		glVertex3d(x, y, 0);
		glEnd();
		glFlush();
		//boundfill4(x + 1, y);
		//boundfill4(x, y + 1);
		//boundfill4(x , y - 1);
		//boundfill4(x - 1, y);
		}*/
	}

	~snow()
	{
	}
};