#include "hsEthernet.h"

BOOL hsIsFrameCorrect(const HS_ETHERNET_MAC_HEADER &MAC)
{
 BOOL IsCorrect=FALSE;
 for(register unsigned int i=0;i<6;i++)
 {
  if(MAC.dstMAC[i]!=0x00)
  { IsCorrect=TRUE; }
 }
 return IsCorrect;
}