#include "Math/Math.h"


namespace Nexus
{

	CORE_API const FVector FVector::ZeroVector(0.0f, 0.0f, 0.0f);
	CORE_API const FVector FVector::OneVector(1.0f, 1.0f, 1.0f);

	CORE_API const FVector FVector::UpVector(0.0f, 0.0f, 1.0f);
	CORE_API const FVector FVector::DownVector(0.0f, 0.0f, -1.0f);

	CORE_API const FVector FVector::ForwardVector(1.0f, 0.0f, 0.0f);
	CORE_API const FVector FVector::BackwardVector(-1.0f, 0.0f, 0.0f);

	CORE_API const FVector FVector::LeftVector(0.0f, -1.0f, 0.0f);
	CORE_API const FVector FVector::RightVector(0.0f, 1.0f, 0.0f);

}