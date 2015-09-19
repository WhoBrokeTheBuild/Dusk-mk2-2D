#include "Texture.hpp"

#include <Logging/LoggingSystem.hpp>

namespace Dusk
{

Texture::~Texture()
{
}

bool Texture::Load(const string& filename)
{
	DuskExtLog("verbose", "Load from file \"%s\"", filename.c_str());

	return true;
}

} // namespace Dusk