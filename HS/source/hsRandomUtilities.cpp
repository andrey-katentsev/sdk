#include "../include/hsRandomUtilities.h"

bool hs_randomize_initialized=false;

int hsRandomA(int a)
{
	if(!hs_randomize_initialized)
	{
		DWORD tick_count=GetTickCount();
		srand(tick_count%UINT_MAX);
		hs_randomize_initialized=true;
	}
	return rand()%(a+1);
}

int hsRandomAB(int a,int b)
{
	if(!hs_randomize_initialized)
	{
		DWORD tick_count=GetTickCount();
		srand(tick_count%UINT_MAX);
		hs_randomize_initialized=true;
	}
	int random=a+(b-a)*rand()/HS_RANDOM_MAX;
	return random;
}