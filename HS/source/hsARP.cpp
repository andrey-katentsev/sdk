#include "hsARP.h"
#include "hsBitwise.h"

void hsTranslateBytesOrder(HS_IPv4_ARP_HEADER &ARPHeader)
{
 ARPHeader.HTYPE=SWAP_BYTES(ARPHeader.HTYPE);
 ARPHeader.PTYPE=SWAP_BYTES(ARPHeader.PTYPE);
 ARPHeader.OPER=SWAP_BYTES(ARPHeader.OPER);
}