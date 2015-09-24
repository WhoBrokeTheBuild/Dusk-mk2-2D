#ifndef DUSK_TRACKING_MEMORY_TRACKER_H
#define DUSK_TRACKING_MEMORY_TRACKER_H

#include <Dusk/Collections/Map.hpp>
#include <Dusk/Utility/Types.hpp>

namespace dusk
{

class ITrackedObject;

class MemoryTracker
{

    friend class ITrackedObject;

public:

    static bool Init();
    static void Term();

    static bool AddAllocation(ITrackedObject* pObject, size_t size,
                              unsigned int lineNumber, string filename);
    static bool RemoveAllocation(ITrackedObject* pObject);

    static inline unsigned int GetAllocationCount()
    {
        return (unsigned int)s_Allocations.size();
    }

    static void PrintAllocations();

private:

    struct AllocationRecord
    {
    public:

        unsigned int    Number,
            LineNumber;
        size_t            Size;
        string            Filename;

        AllocationRecord(int num, size_t size, int lineNum, string filename) :
            Number(num),
            LineNumber(lineNum),
            Size(size),
            Filename(filename)
        { }

    }; // struct AllocationRecord

    static Map<ITrackedObject*, AllocationRecord> s_Allocations;

    static unsigned int    s_AllocationIndex;

}; // class MemoryTracker

} // namespace dusk

#endif // DUSK_TRACKING_MEMORY_TRACKER_H