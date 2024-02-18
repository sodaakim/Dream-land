#pragma once

#include "CoreMinimal.h"
#include "NPC.h"
#include "MyProject2Character.h"
#include "ShopManager.generated.h"

UCLASS()
class MYPROJECT2_API AShopManager : public AActor
{
    GENERATED_BODY()

public:
    // 함수 정의
    void PurchaseItem(ANPC* ShopOwner, AMyProject2Character* Buyer, int32 ItemIndex);

	static AShopManager* GetInstance();

private:
    // 싱글톤 인스턴스를 저장할 정적 멤버 변수
    static AShopManager* Instance;
};