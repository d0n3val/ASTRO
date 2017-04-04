#include <stdio.h>

#ifdef _WIN32
	#include "SDL/include/SDL_log.h"
#else
	#include "SDL_log.h"
#endif

void log(const char file[], int line, const char* format, ...)
{
	static char tmp_string[4096];
	static char tmp_string2[4096];
	static va_list  ap;

	// Construct the string from variable arguments
	va_start(ap, format);
	vsnprintf(tmp_string, 4096, format, ap);
	va_end(ap);
	snprintf(tmp_string2, 4096, "\n%s(%d) : %s", file, line, tmp_string);
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s", tmp_string2);
}
