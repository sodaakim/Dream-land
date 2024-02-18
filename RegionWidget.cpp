#include "RegionWidget.h"

void URegionWidget::SetRegionName(const FString& RegionName)
{
    if (RegionText)
    {
        RegionText->SetText(FText::FromString(RegionName));
    }
}

