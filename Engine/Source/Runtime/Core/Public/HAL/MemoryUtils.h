#pragma once

#include "CoreTypes.h"


namespace Nexus
{

	struct FMTMapNode
	{

	public:

		const void* Ptr;
		uint32 Size;

	public:

		FMTMapNode()
			: Ptr(nullptr)
			, Size(0)
		{

		}

		FMTMapNode(const void* Ptr, uint32 Size)
			: Ptr(Ptr)
			, Size(Size)
		{

		}

	};

	struct FMTMap
	{

	public:

		void Add(const void* Ptr, uint32 Size)
		{
			uint32 Hash = *(uint32*)(Ptr);
			uint32 MapIndex = GetMapIndex(Ptr, Hash);

			// TODO: Grow Map.
			Map[MapIndex] = FMTMapNode(Ptr, Size);
		}

		void Drop(const void* Ptr)
		{

		}

	private:
		
		uint32 GetMapIndex(const void* Ptr, uint32 Hash) const
		{
			uint32 Mask = Capacity - 1;
			uint32 MapIndex = Hash & Mask;

			FMTMapNode& Node = Map[MapIndex];

			while (Node.Ptr != Ptr)
			{
				MapIndex = (MapIndex + 1) & Mask;
				Node = Map[MapIndex];
			}

			return MapIndex;
		}

		FORCEINLINE bool GrowNeeded(uint32 MapIndex) const
		{
			return MapIndex > Capacity - 1;
		}

		void GrowMap(uint32 MapIndex)
		{

		}

	private:

		FMTMapNode* Map;
		uint32 Capacity;

	};

}