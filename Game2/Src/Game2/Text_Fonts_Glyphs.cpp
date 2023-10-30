#include "pch.h"
#include <ft2build.h>
#include FT_FREETYPE_H

FT_Library ft;
FT_Face face;

bool error = FT_Init_FreeType(&ft);

