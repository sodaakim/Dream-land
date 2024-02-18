#include "Item.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "NameTagC.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
    RootComponent = TriggerVolume;
    TriggerVolume->SetCollisionProfileName(TEXT("Trigger"));
    TriggerVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerVolume->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    TriggerVolume->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    TriggerVolume->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}


void AItem::BeginPlay()
{
	Super::BeginPlay();
	UWidgetComponent* WidgetComp = FindComponentByClass<UWidgetComponent>();
    if (WidgetComp)
    {
        UUserWidget* Widget = Cast<UUserWidget>(WidgetComp->GetUserWidgetObject());
        if (Widget)
        {
            UNameTagC* NameTagWidget = Cast<UNameTagC>(Widget);
            if (NameTagWidget)
            {
                NameTagWidget->SetNameText(ItemName);
            }
        }
    }
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

