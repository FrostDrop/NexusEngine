#include <memory>

#include "HAL/MallocAnsi.h"

#include "HAL/Memory.h"
#include "Math/Math.h"

#include "Templates/AlignmentTemplates.h"


namespace Nexus
{

	void* FMallocAnsi::Malloc(PlatformSizeType Size, uint32 Alignment)
	{
		Alignment = FMath::Max(Size >= 16 ? static_cast<uint32>(16) : static_cast<uint32>(8), Alignment);

		void* Result = nullptr;
		void* Ptr = ::malloc(Size + Alignment + sizeof(void*) + sizeof(PlatformSizeType));

		if (Ptr)
		{
			Result = FAlign::Align((uint8*)Ptr + sizeof(void*) + sizeof(PlatformSizeType), Alignment);
			*((void**)((uint8*)Result - sizeof(void*))) = Ptr;
			*((PlatformSizeType*)((uint8*)Result - sizeof(void*) - sizeof(PlatformSizeType))) = Size;
		}

		return Result;
	}

	void* FMallocAnsi::Realloc(void* Original, PlatformSizeType NewSize, uint32 Alignment)
	{
		Alignment = FMath::Max(NewSize >= 16 ? (uint32)16 : (uint32)8, Alignment);

		void* Result = nullptr;

		if (Original && NewSize)
		{
			// Can't use realloc as it might screw with alignment.

			Result = Malloc(NewSize, Alignment);
			PlatformSizeType PtrSize = GetAnsiAllocationSize(Original);

			FMemory::Memcpy(Result, Original, FMath::Min(NewSize, PtrSize));
			Free(Original);
		}
		else if (Original == nullptr)
		{
			Result = Malloc(NewSize, Alignment);
		}
		else
		{
			::free(*((void**)((uint8*)Original - sizeof(void*))));
			Result = nullptr;
		}

		return Result;
	}

	void FMallocAnsi::Free(void* Original)
	{
		if (Original)
		{
			::free(*((void**)((uint8*)Original - sizeof(void*))));
		}
	}

	PlatformSizeType FMallocAnsi::GetAnsiAllocationSize(void* Original) const
	{
		return *((PlatformSizeType*)((uint8*)Original - sizeof(void*) - sizeof(PlatformSizeType)));
	}

}