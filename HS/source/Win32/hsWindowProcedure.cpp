// <Контроль качества>

//#include "hsWindowProcedures.h"
#include "hsMessageProcessing.h"
#include "hsProcessData.h"

LRESULT CALLBACK hsWindowProcedure(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
 switch(uMsg)
 {
 case WM_DESTROY:
 // If an application processes this message, it should return zero.
  {
   if(OnDestroy())
   { return 0; }
  }
 }
 return DefWindowProc(hWnd,uMsg,wParam,lParam);
}