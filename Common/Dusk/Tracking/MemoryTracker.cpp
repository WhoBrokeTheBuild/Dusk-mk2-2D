#include "MemoryTracker.hpp"

#include <Dusk/Tracking/ITrackedObject.hpp>

namespace dusk
{

Map<ITrackedObject*, MemoryTracker::AllocationRecord> MemoryTracker::s_Allocations = Map<ITrackedObject*, MemoryTracker::AllocationRecord>();

unsigned int MemoryTracker::s_AllocationIndex = 0;

bool MemoryTracker::Init()
{
	s_AllocationIndex = 0;
	s_Allocations.clear();

	return true;
}

void MemoryTracker::Term()
{
	s_Allocations.clear();
}

bool MemoryTracker::AddAllocation(ITrackedObject* pObject, size_t size, unsigned int lineNumber, string filename)
{
	if (s_Allocations.contains_key(pObject))
		return false;

	s_Allocations.add(pObject,
		AllocationRecord(s_AllocationIndex, size, lineNumber, filename));
	s_AllocationIndex++;

	return true;
}

bool MemoryTracker::
	RemoveAllocation(ITrackedObject* pObject)
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
