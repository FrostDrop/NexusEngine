

namespace Nexus
{

	void* FMemory::Malloc(PlatformSizeType Size, uint32 Alignment)
	{
		return GMalloc->Malloc(Size, Alignment);
	}

	void* FMemory::Realloc(void* Original, PlatformSizeType Size, uint32 Alignment)
	{
		return GMalloc->Realloc(Original, Size, Alignment);
	}

	void FMemory::Free(void* Original)
	{
		GMalloc->Free(Original);
	}

	void* FMemory::Memcpy(void* Dest, const void* Src, PlatformSizeType Size)
	{
		return FPlatformMemory::Memcpy(Dest, Src, Size);
	}

	void* FMemory::Memmove(void* Dest, const void* Src, PlatformSizeType Count)
	{
		return FPlatformMemory::Memmove(Dest, Src, Count);
	}

}