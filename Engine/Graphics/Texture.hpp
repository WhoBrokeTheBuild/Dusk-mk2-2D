#ifndef DUSK_TEXTURE_HPP
#define DUSK_TEXTURE_HPP

#include <Tracking/ITrackedObject.hpp>

namespace Dusk
{

class Texture :
	public ITrackedObject
{
public:

	inline Texture()
	{ }

	virtual ~Texture();

	virtual inline string GetClassName() const { return "Texture"; }

	bool Load(const string& filename);

private:


}; // class Texture

} // namespace Dusk

#endif // DUSK_TEXTURE_HPP
