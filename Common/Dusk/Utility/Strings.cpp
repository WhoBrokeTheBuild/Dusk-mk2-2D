#include "Strings.hpp"

#include <Dusk/Utility/Platform.hpp>

namespace dusk
{

string Basename(const string& filename)
{
	return filename.substr(filename.find_last_of("/\\") + 1);
}

string Dirname(const string& filename)
{
	if (filename.back() == '/' || filename.back() == '\\') {
		return filename.substr(0, filename.substr(0, filename.length() - 1).find_last_of("/\\"));
	}

	return filename.substr(0, filename.find_last_of("/\\"));
}

} // namespace dusk
