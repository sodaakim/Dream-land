#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemData.generated.h"


USTRUCT(BlueprintType)
struct FItemData
{
    GENERATED_BODY()

public:
    // 아이템의 고유 이름
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    FString Name = TEXT("Itemname");

    // 아이템 이미지의 경로 (UI 표시용)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    FString ImagePath = TEXT("path");

    // 아이템의 가격
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    int32 Price = 10;

    // 아이템의 수량
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    int32 Count = 10;
};
