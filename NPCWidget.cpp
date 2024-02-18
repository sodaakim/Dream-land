#include "NPCWidget.h"
#include "Shop.h"
#include "DialogueWidget.h"
#include "NPC.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


void UNPCWidget::SetJobName(const FString& JobName)
{
    if (JobText) { JobText->SetText(FText::FromString(JobName)); }
}

void UNPCWidget::SetDialogue(const FString& Dialogue)
{
    if (DialogueText){ DialogueText->SetText(FText::FromString(Dialogue)); }
}

void UNPCWidget::InitializeNPC(ANPC* InNPC)
{
    NPC = InNPC;
}

void UNPCWidget::OpenShop()
{
    if (NPC)
    {
        APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
        NPC->OpenShopWidget(PC);
    }
    RemoveFromParent();
}

void UNPCWidget::OpenDialogue()
{
    if (NPC)
    {
        // 대화를 시작하기 위해 ANPC의 함수 호출
        APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
        NPC->StartDialogue(PC);
    }
    RemoveFromParent();
}

void UNPCWidget::CloseDialogue()
{
    OnDialogueClosed.Broadcast();
    NPC->CloseWidget();
    RemoveFromParent();
}

void UNPCWidget::NativeConstruct()
{
    Super::NativeConstruct();    
    if (CloseButton)
    {
        CloseButton->OnClicked.AddDynamic(this, &UNPCWidget::CloseDialogue);
    }
    if (ShopButton)
    {
        ShopButton->OnClicked.AddDynamic(this, &UNPCWidget::OpenShop);
    }
    if (DialogueButton)
    {
        DialogueButton->OnClicked.AddDynamic(this, &UNPCWidget::OpenDialogue);
    }
}

