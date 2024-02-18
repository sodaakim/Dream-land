#include "ShopSlot.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "ShopManager.h"
#include "NPC.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"


void UShopSlot::InitializeSlot(ANPC* InNPC, int32 InItemIndex)
{
    NPC = InNPC;
    ItemIndex = InItemIndex;
}

void UShopSlot::SetItemData(const FItemData& NewItemData)
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

void UShopSlot::NativeConstruct()
{
    Super::NativeConstruct();

    if (ItemButton)
    {
        ItemButton->OnClicked.AddDynamic(this, &UShopSlot::OnClick);
    }
}

void UShopSlot::OnClick()
{
    AShopManager* ShopManager = nullptr;
    UE_LOG(LogTemp, Warning, TEXT("OnClick called. ItemIndex: %d"), ItemIndex);
    
    // AShopManager를 찾습니다.
    for (TActorIterator<AShopManager> It(GetWorld()); It; ++It)
    {
        ShopManager = *It;
        break; // 첫 번째 AShopManager 인스턴스를 찾으면 중단
    }
    
    // ShopManager가 유효한지 확인합니다.
    if (ShopManager)
    {
        UE_LOG(LogTemp, Warning, TEXT("ShopManager found."));
        AMyProject2Character* Buyer = Cast<AMyProject2Character>(UGameplayStatics::GetPlayerCharacter(this, 0));

        if (Buyer && NPC)
        {
            ShopManager->PurchaseItem(NPC, Buyer, ItemIndex);
            SetItemData(NPC->ItemsForSale[ItemIndex]);
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ShopManager not found."));
    }
}
