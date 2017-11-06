#include "hs_gl_font_utilities.h"

unsigned int hsRegisterFont(char *font_name,HDC hdc)
{
	HFONT hFont=NULL;
	unsigned int base=glGenLists(256);
	hFont=CreateFont(FONT_SIZE,FONT_SCALE,ANGLE_OF_ESCAPEMENT,ORIENTATION_ANGLE,BOLD,ITALIC,UNDERLINE,CROSSLINE,ANSI_CHARSET,OUT_TT_PRECIS,CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY,FF_DONTCARE|DEFAULT_PITCH,font_name);
  if(!hFont)
		return 0;
	SelectObject(hdc,hFont);
	wglUseFontBitmaps(hdc,0,255,base);
	return base;
}

void hsTextOut(unsigned int base,const char *string,...)
{
	char buffer[256];
  va_list ap;

	if(base==0||string==NULL)
		return;

	va_start(ap,string);
		vsprintf(buffer,string,ap);
	va_end(ap);

	glPushAttrib(GL_LIST_BIT);
  glListBase(base);
	glCallLists((GLsizei)strlen(buffer),GL_UNSIGNED_BYTE,buffer);
	glPopAttrib();
}

void hsDestroyFont(unsigned int base)
{
	if(base)
		glDeleteLists(base,256);
}
