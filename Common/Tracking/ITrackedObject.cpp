#include "ITrackedObject.hpp"

#include <Tracking/MemoryTracker.hpp>

namespace Dusk
{

void* ITrackedObject::operator new(size_t size)
{
	// Allocate memory normally 
	return malloc(size);
}

void* ITrackedObject::operator new[](size_t size)
{
	// Allocate memory normally 
	return malloc(size);
}

void* ITrackedObject::operator new(size_t size, int lineNumber, const char *filename)
{
	// Call base operator
	void* ptr = ::operator new(size);

	// Record allocation in memory tracker
	MemoryTracker::AddAllocation((ITrackedObject*)ptr, size, lineNumber, string(filename));

	return ptr;
}

void* ITrackedObject::operator new[](size_t size, int lineNumber, const char *filename)
{
	// Call base operator
	void* ptr = ::operator new(size);

	// Record allocation in memory tracker
	MemoryTracker::AddAllocation((ITrackedObject*)ptr, size, lineNumber, string(filename));

	return ptr;
}

void ITrackedObject::operator delete(void *ptr)
{
	// Remove the allocation record if it exists
	MemoryTracker::RemoveAllocation((ITrackedObject*)ptr);

	// Free memory normally 
	free(ptr);
}

void ITrackedObject::operator delete[](void *ptr)
{
	// Remove the allocation record if it exists
	MemoryTracker::RemoveAllocation((ITrackedObject*)ptr);

	// Free memory normally 
	free(ptr);
}

} // namespace Dusk