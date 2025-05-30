#pragma once

#include "CoreMinimal.h"

/// <summary>
/// UnrealWorld Template Identifier
/// </summary>
struct FTId
{
public:
	void SetId(const FString& InId) { UniqueId = InId; }
	const FString& GetId() { return UniqueId; }

private:
	FString UniqueId;
};