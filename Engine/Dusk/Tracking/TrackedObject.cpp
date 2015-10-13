#include "TrackedObject.hpp"

#include <Dusk/Tracking/MemoryTracker.hpp>

namespace dusk
{

void* TrackedObject::operator new(size_t size)
{
    // Allocate memory normally 
    return malloc(size);
}

void* TrackedObject::operator new[](size_t size)
{
    // Allocate memory normally 
    return malloc(size);
}

void* TrackedObject::operator new(size_t size, int lineNumber, const char *filename)
{
    // Call base operator
    void* ptr = ::operator new(size);

    // Record allocation in memory tracker
    MemoryTracker::AddAllocation((TrackedObject*)ptr, size, lineNumber, string(filename));

    return ptr;
}

void* TrackedObject::operator new[](size_t size, int lineNumber, const char *filename)
{
    // Call base operator
    void* ptr = ::operator new(size);

    // Record allocation in memory tracker
    MemoryTracker::AddAllocation((TrackedObject*)ptr, size, lineNumber, string(filename));

    return ptr;
}

void TrackedObject::operator delete(void *ptr)
{
    // Remove the allocation record if it exists
    MemoryTracker::RemoveAllocation((TrackedObject*)ptr);

    // Free memory normally 
    free(ptr);
}

void TrackedObject::operator delete[](void *ptr)
{
    // Remove the allocation record if it exists
    MemoryTracker::RemoveAllocation((TrackedObject*)ptr);

    // Free memory normally 
    free(ptr);
}

} // namespace dusk
