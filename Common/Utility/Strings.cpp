#include "Strings.hpp"

#include <experimental/filesystem>

namespace Dusk
{

namespace fs = std::experimental::filesystem;

string Basename(const string& filename)
{
	fs::path tmp = filename;
	return tmp.filename().string();
}

string Dirname(const string& filename)
{
	fs::path tmp = filename;
	if (!tmp.has_filename())
	{
		return tmp.string();
	}
	else
	{
		return tmp.remove_filename().string();
	}
}

} // namespace Dusk