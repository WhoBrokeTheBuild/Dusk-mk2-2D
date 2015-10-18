#include "MemoryTracker.hpp"

#include <Dusk/Tracking/TrackedObject.hpp>

namespace dusk
{

Map<TrackedObject*, MemoryTracker::AllocationRecord> MemoryTracker::s_Allocations = Map<TrackedObject*, MemoryTracker::AllocationRecord>();

unsigned int MemoryTracker::s_AllocationIndex = 0;

bool MemoryTracker::AddAllocation(TrackedObject* pObject, size_t size, unsigned int lineNumber, string filename)
{
    if (s_Allocations.contains_key(pObject))
        return false;

    s_Allocations.add(pObject, { s_AllocationIndex, lineNumber, size, filename });
    s_AllocationIndex++;

    return true;
}

bool MemoryTracker::
RemoveAllocation(TrackedObject* pObject)
{
    if (!s_Allocations.contains_key(pObject))
        return false;

    s_Allocations.erase(pObject);

    return true;
}

void MemoryTracker::
PrintAllocations()
{
    printf("Allocations:\n");
    for (auto it = s_Allocations.begin(); it != s_Allocations.end(); ++it)
    {
        printf("#%d: (address: %p) %s \n\t At %s:%d\n",
               it->second.Number,
               (void*)it->first,
               it->first->GetClassName().c_str(),
               it->second.Filename.c_str(),
               it->second.LineNumber);
    }
}

} // namespace dusk
