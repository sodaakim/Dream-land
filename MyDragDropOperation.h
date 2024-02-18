#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "MyDragDropOperation.generated.h"

UCLASS()
class MYPROJECT2_API UMyDragDropOperation : public UDragDropOperation
{
    GENERATED_BODY()

public:
    // 드래그 중인 위젯에 대한 참조를 저장할 변수입니다.
    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "DragDrop")
    UWidget* DraggedWidget;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "DragDrop")
    FVector2D DragOffset;
};
