#include<math.h>
#include"glprint.h"
extern float times;
class people
{
	double eyex;
	double eyey;
	double eyez;
	double pointx;
	double pointy;
	double pointz;
	double upx;
	double upy;
	double upz;
	double xmouse;
	double ymouse;
	double thta;
	//int view[9];
public:
	people()
	{
		eyex = 200;
		eyey = 200;
		eyez = 200;
		pointx = 0;
		pointy = 0;
		pointz = 0;
		upx = 0;
		upy = 0;
		upz = 1;
		thta = -0.785;
		xmouse = -1000;
		ymouse = -1000;
	}
	double xdistant()
	{
		double xt = pointx - eyex;
		double yt = pointy - eyey;
		double dis = sqrt(xt * xt + yt * yt);
		return 10 * xt / dis;
	}
	double ydistant()
	{
		double xt = pointx - eyex;
		double yt = pointy - eyey;
		double dis = sqrt(xt * xt + yt * yt);
		return 10 * yt / dis;
	}
	void go()//Wwǰ��
	{
		double x = xdistant();
		double y = ydistant();
		eyex += x;
		eyey += y;
		pointx += x;
		pointy += y;
	}
	void back()//Ss����
	{
		double x = xdistant();
		double y = ydistant();
		eyex -= x;
		eyey -= y;
		pointx -= x;
		pointy -= y;
	}
	void left()//Aa����
	{
		double x = xdistant();
		double y = ydistant();
		eyex -= y;
		eyey += x;
		pointx -= y;
		pointy += x;
	}
	void right()//Dd����
	{
		double x = xdistant();
		double y = ydistant();
		eyex += y;
		eyey -= x;
		pointx += y;
		pointy -= x;
	}
	void setmouse(double x, double y)
	{
		xmouse = x;
		ymouse = y;
	}
	double mousex()
	{
		return xmouse;
	}
	double mousey()
	{
		return ymouse;
	}
	void viewturnleft(double x)//����󻮣���Ұ����
	{
		double angle = (xmouse - x) * 0.6 * 3.14 / 180;
		xmouse = x;
		//pointx = pointx + (eyex - pointx) * cos(angle) + (eyey - pointy) * sin(angle);
		//pointy = pointy + (eyex - pointx) * sin(angle) + (eyey - pointy) * cos(angle);
		double point0x, point0y;
		point0x = eyex + (pointx - eyex) * cos(angle) - (pointy - eyey) * sin(angle);
		point0y = eyey + (pointx - eyex) * sin(angle) + (pointy - eyey) * cos(angle);
		pointx = point0x;
		pointy = point0y;
	}
	void viewturnright(double x)//����һ�����Ұ����
	{
		double angle = (xmouse - x) * 5 * 3.14 / 180;
	}
	void viewup(double yt)//���ǰ������Ұ����
	{
		double x;
		double y;
		double z;
		double angle = (ymouse - yt) * 1 * 3.14 / 180;
		ymouse = yt;
		if(thta + angle > 1.57)
		{
			angle = 1.57 - thta;
		}
		if(thta + angle < -1.57)
		{
			angle = -1.57 - thta;
		}
		thta += angle;
		double xpedistant = pointx - eyex;
		double ypedistant = pointy - eyey;
		double zpedistant = pointz - eyez;
		double pedistant = sqrt(xpedistant * xpedistant + ypedistant * ypedistant);
		/*if(thta < 0 && angle)
		{
			upx = -xpedistant;
			upy = -ypedistant;
			upz = abs(pedistant / tan(angle));
		}
		else if(thta == 0)
		{
			upx = 0;
			upy = 0;
			upz = 1;
		}
		else if(thta > 0 && angle)
		{
			upx = -xpedistant;
			upy = -ypedistant;
			upz = abs(pedistant / tan(angle));
		}*/
		if(xpedistant == 0)
		{
			x = pointx;
			y = eyey + ypedistant * cos(angle) - zpedistant * sin(angle);
			z = eyez + ypedistant * sin(angle) + zpedistant * cos(angle);
		}
		else if(ypedistant == 0)
		{
			x = eyex + zpedistant * sin(angle) + xpedistant * cos(angle);
			y = pointy;
			z = eyez + zpedistant * cos(angle) - xpedistant * sin(angle);
		}
		else
		{
			double kmian = ypedistant / xpedistant;
			double kn = -1 / kmian;
			double sina = 1 / sqrt(1 + kn * kn);
			double cosa = kn / sqrt(1 + kn * kn);
			double x0, x1, x2;
			double y0, y1, y2;
			double z0, z1, z2;
			//��������ת-a��x��
			x0 = xpedistant * cosa + ypedistant * sina;
			y0 = -xpedistant * sina + ypedistant * cosa;
			z0 = zpedistant;
			//p��x����ת0��
			x1 = x0;
			y1 = y0 * cos(angle) - z0 * sin(angle);
			z1 = y0 * sin(angle) + z0 * cos(angle); 
			//��������תa��ԭλ��
			x2 = x1 * cosa - y1 * sina;
			y2 = x1 * sina + y1 * cosa;
			z2 = z1;
			//������ƽ�ƻ�ԭλ��;
			x = x2 + eyex;
			y = y2 + eyey;
			z = z2 + eyez;
		}
		

		pointx = x;
		pointy = y;
		pointz = z;

	}
	void viewdown(double y)//���󻮣���Ұ����
	{
	}
	void viewsmaller()//�������ϣ���Ұ��С��������
	{
	}
	void viewbigger()//�������£���Ұ��������С
	{
	}
	void reset()//�ָ�ԭλ
	{
		eyex = 200;
		eyey = 200;
		eyez = 10;
		pointx = 0;
		pointy = 0;
		pointz = 0;
		upx = 0;
		upy = 0;
		upz = 1;
		thta = -0.785;
		xmouse = -1000;
		ymouse = -1000;
	}
	void pos()//������Ұ����
	{
		/*view[0] = eyex;
		view[1] = eyey;
		view[2] = eyez;
		view[3] = pointx;
		view[4] = pointy;
		view[5] = pointz;
		view[6] = upx;
		view[7] = upy;
		view[8] = upz;
		return view;*/




		


		glBegin(GL_LINES);
		glVertex3d(eyex, eyey, eyez);
		glVertex3d(pointx, pointy, pointz);
		glColor3f(1, 1, 0.3);
		glVertex3d(pointx - 10, pointy - 10, pointz + 10);
		glVertex3d(pointx, pointy, pointz);
		glVertex3d(pointx + 10, pointy - 10, pointz + 10);
		glVertex3d(pointx, pointy, pointz);
		glEnd();
		glMatrixMode(GL_PROJECTION);  
		glLoadIdentity();  //����ǰ���û�����ϵ��ԭ���Ƶ�����Ļ����
		gluPerspective(120, 1, 10, 1000); 
		glMatrixMode(GL_MODELVIEW);  
		glLoadIdentity();
		gluLookAt(eyex, eyey, eyez, pointx, pointy, pointz, upx, upy,upz);
		//glColor3f(0, 1, 0);


		char str[100];
		sprintf(str, "times:%.0f", times);
		glColor3f(1, 1, 1);
		glWindowPos2i(0, 585);
		selectFont(15, ANSI_CHARSET, "����");
		drawCNString(str); 

		sprintf(str, "theta:%.4f  mx:%.4f  my:%.4f", thta, xmouse, ymouse);
		glWindowPos2i(0, 570);
		drawCNString(str); 
		
		sprintf(str, "ex:%.4f  ey:%.4f  ez:%.4f", eyex, eyey, eyez);
		glWindowPos2i(0, 555);
		drawCNString(str);

		sprintf(str, "px:%.4f  py:%.4f  pz:%.4f", pointx, pointy, pointz);
		glWindowPos2i(0, 540);
		drawCNString(str);

		sprintf(str, "ux:%.4f  uy:%.4f  uz:%.4f", upx, upy, upz);
		glWindowPos2i(0, 525);
		drawCNString(str);

		glutPostRedisplay();
		glFlush();
	}
	~people()
	{
	}
};