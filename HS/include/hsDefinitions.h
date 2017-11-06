/* Win32 Definitions */
/* Programmed: Hyperlink Software®, 2008-2012 */
/* Copyright: ©2008-2012, Hyperlink Software® */

/* Contacts: */
/* E-Mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

#pragma message("Last modified on " __TIMESTAMP__ )

#pragma once

/* Keywords */
#define CONST    const
#define STATIC   static
#define REGISTER register

/* Dialog procedure return codes */
#define HS_DLG_OK     0
#define HS_DLG_CLOSE  1
#define HS_DLG_CANCEL 2
#define HS_DLG_ERROR  (-1)

#define HS_DLG_SUCCESS HS_DLG_OK
#define HS_DLG_FAILURE HS_DLG_CANCEL

/* Dialog modes */
#define HS_DLG_MODE_BLANK 0
#define HS_DLG_MODE_FILL  1

#define HS_DLG_MODE_NEW  HS_DLG_MODE_BLANK
#define HS_DLG_MODE_EDIT HS_DLG_MODE_FILL

/* Windows common controls return codes */
/* List View */
#define HS_LV_NO_ITEMS 0
#define HS_LV_NO_SELECTION_MARK (-1)