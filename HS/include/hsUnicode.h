#pragma once

#define _WIDE(STRING) L ## STRING
#define WIDE(TEXT) _WIDE(TEXT)

#ifndef TEXT
#define TEXT(STRING) _WIDE(STRING)
#endif