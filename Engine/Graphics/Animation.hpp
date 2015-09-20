#ifndef DUSK_GRAPHICS_ANIMATION_HPP
#define DUSK_GRAPHICS_ANIMATION_HPP

#include <Tracking/ITrackedObject.hpp>

namespace dusk 
{

class Animation :
	public ITrackedObject
{
public:

	Animation();
	~Animation();

}; // class Animation

} // namespace dusk

#endif // DUSK_GRAPHICS_ANIMATION_HPP