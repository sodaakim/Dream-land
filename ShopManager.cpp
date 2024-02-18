#include "ShopManager.h"


// 정적 멤버 변수를 초기화합니다.
AShopManager* AShopManager::Instance = nullptr;

AShopManager* AShopManager::GetInstance()
{
    // 인스턴스가 생성되지 않았다면 생성하여 반환합니다.
    if (Instance == nullptr)
    {
        Instance = NewObject<AShopManager>();
        Instance->AddToRoot(); // GC에 의해 메모리에서 삭제되지 않도록 추가합니다.
    }
    return Instance;
}

void AShopManager::PurchaseItem(ANPC* ShopOwner, AMyProject2Character* Buyer, int32 ItemIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("buybuy!"));
    if(ShopOwner && Buyer && ShopOwner->ItemsForSale.IsValidIndex(ItemIndex))
    {
        FItemData& ItemForSale = ShopOwner->ItemsForSale[ItemIndex];

        // 아이템이 충분한지 확인하고, 플레이어가 동전을 충분히 가지고 있는지 확인합니다.
        if(ItemForSale.Count > 0 && Buyer->Coins >= ItemForSale.Price)
        {
            // 동전을 지불합니다.
            Buyer->Coins -= ItemForSale.Price;

            // 상점의 아이템 개수를 감소시킵니다.
            ItemForSale.Count--;

            // 플레이어의 인벤토리에 아이템을 추가합니다.
            bool bItemAdded = false;
            for(FItemData& InventoryItem : Buyer->InventoryItems)
            {
                if(InventoryItem.Name == ItemForSale.Name)
                {
                    InventoryItem.Count += 1;
                    bItemAdded = true;
                    break;
                }
            }

            // 인벤토리에 같은 아이템이 없으면 새로운 아이템을 추가합니다.
            if(!bItemAdded)
            {
                FItemData NewItem = ItemForSale;
                NewItem.Count = 1; // 구매는 한 번에 하나씩만 가능하다고 가정합니다.
                Buyer->InventoryItems.Add(NewItem);
            }

            // 플레이어의 CoinText UI 업데이트 함수를 호출합니다.
            Buyer->UpdateCoinDisplay();

			// 플레이어의 인벤토리 UI 업데이트
			if (Buyer->InventoryWidget)
			{
				Buyer->InventoryWidget->UpdateInventoryUI();
			}
            // 상점 및 인벤토리 UI 업데이트 로직을 호출합니다. (해당 함수는 구현되어 있어야 합니다.)
            // UpdateShopUI();
            // UpdateInventoryUI();
        }
    }
}
