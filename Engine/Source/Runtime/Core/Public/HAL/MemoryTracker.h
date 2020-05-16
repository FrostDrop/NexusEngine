#pragma once

#include "CoreTypes.h"


namespace Nexus
{

	/**
	 * The main memory tracker.
	 */
	class CORE_API FMemoryTracker
	{

	public:

		/**
		 * Gets the singleton instance of the memory tracker.
		 */
		inline static FMemoryTracker& Get()
		{
			if (TrackerInstance)
				return *TrackerInstance;
			else
				return Construct();
		}

	public:

		/**
		 * Tracks allocated memory.
		 */
		void OnAlloc(const void* Ptr, uint64 Size);

		/**
		 * Tracks a memory free operation.
		 */
		void OnFree(const void* Ptr);

	private:

		/**
		 * Constructs the singleton instance of the memory tracker.
		 */
		static FMemoryTracker& Construct();

	private:

		uint64 TotalAllocated;
		uint64 TotalFreed;

		uint64 CurrentlyAllocated;

	private:

		/**
		 * Holds the singleton instance of the memory tracker.
		 */
		static FMemoryTracker* TrackerInstance;

	};


}