// Copyright Epic Games, Inc. All Rights Reserved.

#include "FIrstPlugin.h"
#include "FIrstPluginStyle.h"
#include "FIrstPluginCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName FIrstPluginTabName("FIrstPlugin");

#define LOCTEXT_NAMESPACE "FFIrstPluginModule"

void FFIrstPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FFIrstPluginStyle::Initialize();
	FFIrstPluginStyle::ReloadTextures();

	FFIrstPluginCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FFIrstPluginCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FFIrstPluginModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FFIrstPluginModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(FIrstPluginTabName, FOnSpawnTab::CreateRaw(this, &FFIrstPluginModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FFIrstPluginTabTitle", "FIrstPlugin"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FFIrstPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FFIrstPluginStyle::Shutdown();

	FFIrstPluginCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(FIrstPluginTabName);
}

TSharedRef<SDockTab> FFIrstPluginModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FFIrstPluginModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("FIrstPlugin.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FFIrstPluginModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(FIrstPluginTabName);
}

void FFIrstPluginModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FFIrstPluginCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FFIrstPluginCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFIrstPluginModule, FIrstPlugin)