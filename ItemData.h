#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NameTypes.h"
#include "ItemData.generated.h"


USTRUCT(BlueprintType)
struct FItemData
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    FGuid ItemID; // 고유 식별자
    
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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    TSubclassOf<AActor> ItemClass;

    bool operator==(const FItemData& Other) const
    {
        // 비교 로직 구현. 예를 들어 ItemID를 비교하도록 할 수 있습니다.
        return ItemID == Other.ItemID;
    }
};
