#include "NameTagC.h"

void UNameTagC::SetNameText(const FString& Name)
{
    if (NameText)
    {
        NameText->SetText(FText::FromString(Name));
    }
}

