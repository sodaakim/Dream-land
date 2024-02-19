#include "InventorySlot.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "Item.h"
#include "Components/Button.h"
#include "MyProject2Character.h"
#include "Kismet/KismetSystemLibrary.h"


void UInventorySlot::NativeConstruct()
{
    Super::NativeConstruct();

    if (ItemButton)
    {
        ItemButton->OnClicked.AddDynamic(this, &UInventorySlot::OnSlotClicked);
    }
}

void UInventorySlot::SetItemData(const FItemData& NewItemData)
{
    ItemData = NewItemData; // 멤버 변수에 데이터 저장

    // UI 컴포넌트에 데이터 바인딩
    if (ItemName)
    {
        ItemName->SetText(FText::FromString(ItemData.Name));
    }
    if (ItemPrice)
    {
        ItemPrice->SetText(FText::AsNumber(ItemData.Price));
    }
    if (ItemCount)
    {
        ItemCount->SetText(FText::AsNumber(ItemData.Count));
    }

    if (ItemImage && !ItemData.ImagePath.IsEmpty())
    {
        // 이미지 경로로부터 텍스처 로드 (예시 경로: "/Game/Textures/MyItem")
        UTexture2D* ItemTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ItemData.ImagePath));
        if (ItemTexture)
        {
            ItemImage->SetBrushFromTexture(ItemTexture);
        }
    }
}


void UInventorySlot::OnSlotClicked()
{
    /*
    if (!ItemData.IsValid())
    {
        return; // 유효한 아이템 데이터가 없는 경우 함수를 종료합니다.
    }*/

    AMyProject2Character* PlayerCharacter = Cast<AMyProject2Character>(UGameplayStatics::GetPlayerCharacter(this, 0));
    if (PlayerCharacter)
    {
        FVector SpawnLocation = PlayerCharacter->GetActorLocation() + PlayerCharacter->GetActorForwardVector() * 100.0f; // 플레이어 앞
        FRotator SpawnRotation = FRotator(0.0f);

        AItem* DroppedItem = GetWorld()->SpawnActor<AItem>(ItemData.ItemClass, SpawnLocation, SpawnRotation);
        if (DroppedItem)
        {
            // 버린 아이템에 대한 정보를 설정
            DroppedItem->SetItemData(ItemData);
            DroppedItem->ItemName = ItemData.Name;
            PlayerCharacter->RemoveItemFromInventory(ItemData.ItemID);
        }

        if (DroppedItem)
        {
            // ...
            UE_LOG(LogTemp, Warning, TEXT("Item spawned successfully."));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to spawn item."));
        }

    }
}

