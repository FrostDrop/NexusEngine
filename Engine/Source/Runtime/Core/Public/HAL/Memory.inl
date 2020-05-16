

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

	PlatformSizeType FMemory::QuantizeSize(PlatformSizeType Size, uint32 Alignment)
	{
		if (!GMalloc)
		{
			return Size;
		}

		return GMalloc->QuantizeSize(Size, Alignment);
	}

	void* FMemory::Memcpy(void* Dest, const void* Src, PlatformSizeType Size)
	{
		return FPlatformMemory::Memcpy(Dest, Src, Size);
	}

	void* FMemory::Memmove(void* Dest, const void* Src, PlatformSizeType Size)
	{
		return FPlatformMemory::Memmove(Dest, Src, Size);
	}

	int32 FMemory::Memcmp(const void* Buffer1, const void* Buffer2, PlatformSizeType Size)
	{
		return FPlatformMemory::Memcmp(Buffer1, Buffer2, Size);
	}

}