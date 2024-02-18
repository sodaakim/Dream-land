#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h" 
#include "DialogueWidget.generated.h"

UCLASS()
class MYPROJECT2_API UDialogueWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Job")
    void SetJobName(const FString& JobName);

    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void SetDialogue(const FString& Dialogue);

    UFUNCTION(BlueprintCallable, Category = "Button")
    void InitializeWithNPC(ANPC* InNPC);

    UFUNCTION(BlueprintCallable, Category = "Button")
    void CloseDialogue();

    UFUNCTION(BlueprintCallable, Category = "Button")
    void SetNextBtnText(const FString& ButtonText);

    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueClosed);
    UPROPERTY(BlueprintAssignable, Category = "Dialogue")
    FOnDialogueClosed OnDialogueClosed;

protected:

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UTextBlock* JobText;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UTextBlock* DialogueText;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UButton* ExitButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UTextBlock* NextBtnText;
    
    virtual void NativeConstruct() override;

private:
    // ANPC 인스턴스에 대한 포인터
    ANPC* NPC;
};



