#include "DialogueWidget.h"
#include "NPC.h"

void UDialogueWidget::InitializeWithNPC(ANPC* InNPC)
{
    NPC = InNPC;
}

void UDialogueWidget::SetJobName(const FString& JobName)
{
    if (JobText) { JobText->SetText(FText::FromString(JobName)); }
}

void UDialogueWidget::SetDialogue(const FString& Dialogue)
{
    if (DialogueText){ DialogueText->SetText(FText::FromString(Dialogue)); }
}

void UDialogueWidget::NativeConstruct()
{
    Super::NativeConstruct();    
    if (ExitButton)
    {
        ExitButton->OnClicked.AddDynamic(this, &UDialogueWidget::CloseDialogue);
    }
}

void UDialogueWidget::SetNextBtnText(const FString& ButtonText)
{
    if (NextBtnText) { NextBtnText->SetText(FText::FromString(ButtonText)); }
}


void UDialogueWidget::CloseDialogue()
{
    RemoveFromParent();
    OnDialogueClosed.Broadcast(); // 이벤트 방출
    //NPC->CloseWidget();
}
