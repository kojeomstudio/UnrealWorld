#pragma once

#include "CoreMinimal.h"

namespace UWUtils
{
	/**
	 * Converts a string to a FName.
	 * @param InString The string to convert.
	 * @return The converted FName.
	 */
	FORCEINLINE FName StringToFName(const FString& InString)
	{
		return FName(*InString);
	}
	/**
	 * Converts a FName to a string.
	 * @param InName The FName to convert.
	 * @return The converted string.
	 */
	FORCEINLINE FString FNameToString(const FName& InName)
	{
		return InName.ToString();
	}

	/// <summary>
	/// UEnum to FString conversion.
	/// </summary>
	/// <typeparam name="TEnum"></typeparam>
	/// <param name="EnumValue"></param>
	/// <returns></returns>
	template<typename TEnum>
	FString EnumToString(TEnum EnumValue)
	{
		static_assert(TIsEnum<TEnum>::Value, "TEnum must be an enum type.");
		const UEnum* EnumPtr = StaticEnum<TEnum>();
		if (!EnumPtr) return TEXT("Invalid");
		return EnumPtr->GetNameStringByValue(static_cast<int64>(EnumValue));
	}

	/**
	 * Prints a debug message on screen and logs it to the output log.
	 * @param Message The message to print.
	 * @param Key Unique key for on-screen messages (for updating/removing).
	 * @param Duration How long the message should remain on screen.
	 * @param Color The color of the message.
	 * @param LogCategory The log category used with UE_LOG.
	 */
	FORCEINLINE void DebugLogToScreen(const FString& Message, int32 Key = -1, float Duration = 5.0f, FColor Color = FColor::Green, const FName& LogCategory = TEXT("Log"))
	{
#if !(UE_BUILD_SHIPPING)
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(Key, Duration, Color, Message);
		}
		UE_LOG(LogTemp, Log, TEXT("[%s] %s"), *LogCategory.ToString(), *Message);
#endif
	}

} // namespace UWUtils
