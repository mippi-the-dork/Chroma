// Copyright Epic Games, Inc. All Rights Reserved.

#include "ChromaSettings.h"
#include "ChromaState.h"
UChromaSettings::UChromaSettings()
{
    const TCHAR* Names[] = {TEXT("Red"),TEXT("Orange"),TEXT("Yellow"),TEXT("Green"),TEXT("Blue"),TEXT("Purple")};
    const FColor Colors[] = {FColor(225,74,74),FColor(235,145,60),FColor(230,200,70),FColor(83,180,111),FColor(75,147,225),FColor(165,104,214)};
    for(int32 I=0; I<6; ++I)
    {
        FChromaPreset P; P.Id=FGuid(0x4348524f,0x4d410001,0,I+1); P.Name=Names[I]; P.Color=FLinearColor::FromSRGBColor(Colors[I]); Palette.Add(P);
    }
}
void UChromaSettings::PostEditChangeProperty(FPropertyChangedEvent& Event)
{
    TSet<FGuid> Seen;
    for(auto& P:Palette)
    {
        if(!P.Id.IsValid() || Seen.Contains(P.Id)) P.Id=FGuid::NewGuid();
        Seen.Add(P.Id); P.Color.A=1.f;
        if(P.Name.TrimStartAndEnd().IsEmpty()) P.Name=TEXT("New Color");
    }
    Super::PostEditChangeProperty(Event);
    Chroma::RequestViewportRefresh();
}
void UChromaSettings::PostEditUndo()
{
    Super::PostEditUndo();
    TryUpdateDefaultConfigFile();
    Chroma::RequestViewportRefresh();
}
