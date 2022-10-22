// Guillermo Su�rez

#include "UI/HIBossHUD.h"

bool UHIBossHUD::Initialize()
{
   Super::Initialize();

   isVulnerable = false;

   return true;
}

void UHIBossHUD::NativePreConstruct()
{
   Super::NativePreConstruct();


}

void UHIBossHUD::NativeConstruct()
{
   Super::NativePreConstruct();


}

void UHIBossHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	HIUpdateData();
}

bool UHIBossHUD::HIGetvulnerability()
{
   return isVulnerable;
}

void UHIBossHUD::HISetvulnerability(bool _vulnerability)
{
   isVulnerable = _vulnerability;
}
