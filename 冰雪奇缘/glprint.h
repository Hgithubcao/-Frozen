#include<gl/glut.h>
#include<Windows.h>
/*void doubletochar(double num, char* str)
{
	str = new char[100];
	int n = 0;
	int zsnum = (int)num;
	double xsnum = num - zsnum;
	while(zsnum)
	{
		str[n ++] = zsnum % 10 + 48;
		zsnum /= 10;
	}
	for(int i = 0; i < n / 2; i ++)
	{
		char t = str[i];
		str[i] = str[n - i - 1];
		str[n - i - 1] = t;
	}
	str[n ++] = '.';
	while((int)xsnum != xsnum && n < 4)
	{
		xsnum *= 10;
		str[n ++] = (int)xsnum % 10 + 48;
	}
	//str[n] = '/0';
}

void glPrint(GLfloat x, GLfloat y, char *string)
{
	HWND m_hWnd;
	RECT rect;
	GLuint base;

	glColor3f(1.0f , 0.0f , 0.0f);
	glRasterPos2f(x , y);
	glPushAttrib(GL_LIST_BIT);							
	glListBase(base - 32);								
	glCallLists(strlen(string), GL_UNSIGNED_BYTE, string);	
	glPopAttrib();
	glColor3f(1.0f , 1.0f , 1.0f);
}*/

void glWindowPos2i(GLint x,GLint y)
{/*new method,here we need extra code on Windows */
     typedef void (__stdcall * ARBFUNC)(GLint x,GLint y);
    
     ARBFUNC glptr = 0;
     glptr = (ARBFUNC)wglGetProcAddress("glWindowPos2iARB");

     if(glptr)
         glptr(x,y); 
     else printf("glWindowPos2iARB NOT exit\n");
}

void drawCNString(const char* str) {
	int len, i;
	wchar_t* wstring;
	HDC hDC = wglGetCurrentDC();
	GLuint list = glGenLists(1);
	// �����ַ��ĸ���
	// �����˫�ֽ��ַ��ģ����������ַ����������ֽڲ���һ���ַ�
	// ����һ���ֽ���һ���ַ�
	len = 0;
	for (i = 0; str[i] != '\0'; ++i)
	{
		if (IsDBCSLeadByte(str[i]))
			++i;
		++len;
	}
	// ������ַ�ת��Ϊ���ַ�
	wstring = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
	wstring[len] = L'\0';

	// �������ַ�
	for (i = 0; i<len; ++i)
	{
		wglUseFontBitmapsW(hDC, wstring[i], 1, list);
		glCallList(list);
	}

	// ����������ʱ��Դ
	free(wstring);
	glDeleteLists(list, 1);
	// ������ַ�ת��Ϊ���ַ�  
	wstring = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
	wstring[len] = L'\0';
	// �����ǵ��ͷ��ڴ�  
	free(wstring);
}

void selectFont(int size, int charset, const char* face) {
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
		charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}