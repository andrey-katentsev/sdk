#include "hs_convert_utilities.h"

char* hsIntToChar(unsigned int number,char *buffer)
{
	char *_buffer=NULL;
	unsigned int ax=number;
	register unsigned int cx=0,bx=0;

	if(ax==0)
	{
		buffer[0]='0';
		buffer[1]='\0';
		return buffer;
	}

	for(cx=0;ax;cx++)
	{
		buffer[cx]=(ax%10)+'0';
		ax/=10;
	}
	_buffer=new char[cx];

	for(bx=0;cx>0;bx++,cx--)
		_buffer[bx]=buffer[cx-1];

	for(cx=0;cx<bx;cx++)
		buffer[cx]=_buffer[cx];

	buffer[cx]='\0';
	delete[] _buffer;
	return buffer;
}

void hsStringToUpperCase(char *String)
{
	size_t length=strlen(String);
	for(register unsigned int cx=0;cx<length;cx++)
	{
		if((-32)<=String[cx] && String[cx]<=(-1)) // RUS
		{ String[cx]-=32; }
		else // ENG
		{ String[cx]=toupper(String[cx]); }
	}
}

void hsStringToLowerCase(char *String)
{
	size_t length=strlen(String);
	for(register unsigned int cx=0;cx<length;cx++)
	{
		if((-64)<=String[cx] && String[cx]<=(-33)) // RUS
		{ String[cx]+=32; }
		else // ENG
		{ String[cx]=tolower(String[cx]); }
	}
}