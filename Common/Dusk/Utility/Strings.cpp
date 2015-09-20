#include "Strings.hpp"

#if defined(DUSK_OS_WINDOWS)

#else

#define MAX_PATH 1024
#include <libgen.h>
#include <string.h>

#endif

namespace dusk
{

string Basename(const string& filename)
{
#if defined(DUSK_OS_WINDOWS)
#else

	if (filename.size() >= MAX_PATH)
		return "";

	char buffer[MAX_PATH];
	strcpy(buffer, filename.c_str());
	return string(basename(buffer));

#endif
}

string Dirname(const string& filename)
{
#if defined(DUSK_OS_WINDOWS)
#else

	if (filename.size() >= MAX_PATH)
		return "";

	char buffer[MAX_PATH];
	strcpy(buffer, filename.c_str());
	return string(dirname(buffer));

#endif
}

} // namespace dusk
