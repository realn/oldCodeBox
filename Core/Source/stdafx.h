#pragma once

#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <windows.h>

#undef GetMessage
#undef GetObject

#include <ft2build.h>
#include FT_FREETYPE_H

#include <FreeImage.h>

#include <sndfile.h>

#include <cmath>
#include <vector>
#include <cstdlib>

#pragma comment(lib, "FreeImage.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "libsndfile.lib")
