
#include "HAL/MemoryTracker.h"


namespace Nexus
{

	FMemoryTracker* FMemoryTracker::TrackerInstance = nullptr;

	FMemoryTracker& FMemoryTracker::Construct()
	{
		static FMemoryTracker Tracker;

		TrackerInstance = &Tracker;
		return Tracker;
	}

	void FMemoryTracker::OnAlloc(const void* Ptr, uint64 Size)
	{
		TotalAllocated += Size;
		CurrentlyAllocated += Size;
	}

	void FMemoryTracker::OnFree(const void* Ptr)
	{
		// TODO: Get size of Ptr via HashMap.
		// TotalFreed += Size;
		// CurrentlyAllocated -= Size;
	}

}