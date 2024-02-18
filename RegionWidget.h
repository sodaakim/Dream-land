#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "RegionWidget.generated.h"

UCLASS()
class MYPROJECT2_API URegionWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    // 지역 이름을 설정하는 함수
    UFUNCTION(BlueprintCallable, Category = "Region")
    void SetRegionName(const FString& RegionName);

protected:
    // 위젯 내의 텍스트 블록에 바인딩될 변수
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UTextBlock* RegionText;
};
