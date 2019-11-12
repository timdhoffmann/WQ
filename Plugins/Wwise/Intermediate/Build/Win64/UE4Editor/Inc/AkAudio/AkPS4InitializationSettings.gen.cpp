// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AkAudio/Classes/InitializationSettings/AkPS4InitializationSettings.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAkPS4InitializationSettings() {}
// Cross Module References
	AKAUDIO_API UScriptStruct* Z_Construct_UScriptStruct_FAkPS4AdvancedInitializationSettings();
	UPackage* Z_Construct_UPackage__Script_AkAudio();
	AKAUDIO_API UScriptStruct* Z_Construct_UScriptStruct_FAkAdvancedInitializationSettingsWithMultiCoreRendering();
	AKAUDIO_API UClass* Z_Construct_UClass_UAkPS4InitializationSettings_NoRegister();
	AKAUDIO_API UClass* Z_Construct_UClass_UAkPS4InitializationSettings();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	AKAUDIO_API UScriptStruct* Z_Construct_UScriptStruct_FAkCommunicationSettingsWithSystemInitialization();
	AKAUDIO_API UScriptStruct* Z_Construct_UScriptStruct_FAkCommonInitializationSettings();
// End Cross Module References
class UScriptStruct* FAkPS4AdvancedInitializationSettings::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern AKAUDIO_API uint32 Get_Z_Construct_UScriptStruct_FAkPS4AdvancedInitializationSettings_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAkPS4AdvancedInitializationSettings, Z_Construct_UPackage__Script_AkAudio(), TEXT("AkPS4AdvancedInitializationSettings"), sizeof(FAkPS4AdvancedInitializationSettings), Get_Z_Construct_UScriptStruct_FAkPS4AdvancedInitializationSettings_Hash());
	}
	return Singleton;
}
template<> AKAUDIO_API UScriptStruct* StaticStruct<FAkPS4AdvancedInitializationSettings>()
{
	return FAkPS4AdvancedInitializationSettings::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAkPS4AdvancedInitializationSettings(FAkPS4AdvancedInitializationSettings::StaticStruct, TEXT("/Script/AkAudio"), TEXT("AkPS4AdvancedInitializationSettings"), false, nullptr, nullptr);
static struct FScriptStruct_AkAudio_StaticRegisterNativesFAkPS4AdvancedInitializationSettings
{
	FScriptStruct_AkAudio_StaticRegisterNativesFAkPS4AdvancedInitializationSettings()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("AkPS4AdvancedInitializationSettings")),new UScriptStruct::TCppStructOps<FAkPS4AdvancedInitializationSettings>);
	}
} ScriptStruct_AkAudio_StaticRegisterNativesFAkPS4AdvancedInitializationSettings;
	struct Z_Construct_UScriptStruct_FAkPS4AdvancedInitializationSettings_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_UseHardwareCodecLowLatencyMode_MetaData[];
#endif
		static void NewProp_UseHardwareCodecLowLatencyMode_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_UseHardwareCodecLowLatencyMode;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ACPBatchBufferSize_MetaData[];
#endif
		static const UE4CodeGen_Private::FUInt32PropertyParams NewProp_ACPBatchBufferSize;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAkPS4AdvancedInitializationSettings_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Classes/InitializationSettings/AkPS4InitializationSettings.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAkPS4AdvancedInitializationSettings_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAkPS4AdvancedInitializationSettings>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAkPS4AdvancedInitializationSettings_Statics::NewProp_UseHardwareCodecLowLatencyMode_MetaData[] = {
		{ "Category", "Ak Initialization Settings" },
		{ "ModuleRelativePath", "Classes/InitializationSettings/AkPS4InitializationSettings.h" },
		{ "ToolTip", "Use low latency mode for ATRAC9 (default is false). If true, decoding jobs are submitted at the beginning of the Wwise update and it will be necessary to wait for the result." },
	};
#endif
	void Z_Construct_UScriptStruct_FAkPS4AdvancedInitializationSettings_Statics::NewProp_UseHardwareCodecLowLatencyMode_SetBit(void* Obj)
	{
		((FAkPS4AdvancedInitializationSettings*)Obj)->UseHardwareCodecLowLatencyMode = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FAkPS4AdvancedInitializationSettings_Statics::NewProp_UseHardwareCodecLowLatencyMode = { "UseHardwareCodecLowLatencyMode", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FAkPS4AdvancedInitializationSettings), &Z_Construct_UScriptStruct_FAkPS4AdvancedInitializationSettings_Statics::NewProp_UseHardwareCodecLowLatencyMode_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FAkPS4AdvancedInitializationSettings_Statics::NewProp_UseHardwareCodecLowLatencyMode_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAkPS4AdvancedInitializationSettings_Statics::NewProp_UseHardwareCodecLowLatencyMode_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAkPS4AdvancedInitializationSettings_Statics::NewProp_ACPBatchBufferSize_MetaData[] = {
		{ "Category", "Ak Initialization Settings" },
		{ "ModuleRelativePath", "Classes/InitializationSettings/AkPS4InitializationSettings.h" },
		{ "ToolTip", "ACP batch buffer size used for ATRAC9 decoding." },
	};
#endif
	const UE4CodeGen_Private::FUInt32PropertyParams Z_Construct_UScriptStruct_FAkPS4AdvancedInitializationSettings_Statics::NewProp_ACPBatchBufferSize = { "ACPBatchBufferSize", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::UInt32, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FAkPS4AdvancedInitializationSettings, ACPBatchBufferSize), METADATA_PARAMS(Z_Construct_UScriptStruct_FAkPS4AdvancedInitializationSettings_Statics::NewProp_ACPBatchBufferSize_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAkPS4AdvancedInitializationSettings_Statics::NewProp_ACPBatchBufferSize_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAkPS4AdvancedInitializationSettings_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAkPS4AdvancedInitializationSettings_Statics::NewProp_UseHardwareCodecLowLatencyMode,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAkPS4AdvancedInitializationSettings_Statics::NewProp_ACPBatchBufferSize,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAkPS4AdvancedInitializationSettings_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AkAudio,
		Z_Construct_UScriptStruct_FAkAdvancedInitializationSettingsWithMultiCoreRendering,
		&NewStructOps,
		"AkPS4AdvancedInitializationSettings",
		sizeof(FAkPS4AdvancedInitializationSettings),
		alignof(FAkPS4AdvancedInitializationSettings),
		Z_Construct_UScriptStruct_FAkPS4AdvancedInitializationSettings_Statics::PropPointers,
		ARRAY_COUNT(Z_Construct_UScriptStruct_FAkPS4AdvancedInitializationSettings_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAkPS4AdvancedInitializationSettings_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FAkPS4AdvancedInitializationSettings_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAkPS4AdvancedInitializationSettings()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAkPS4AdvancedInitializationSettings_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_AkAudio();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AkPS4AdvancedInitializationSettings"), sizeof(FAkPS4AdvancedInitializationSettings), Get_Z_Construct_UScriptStruct_FAkPS4AdvancedInitializationSettings_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAkPS4AdvancedInitializationSettings_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAkPS4AdvancedInitializationSettings_Hash() { return 2778531194U; }
	void UAkPS4InitializationSettings::StaticRegisterNativesUAkPS4InitializationSettings()
	{
	}
	UClass* Z_Construct_UClass_UAkPS4InitializationSettings_NoRegister()
	{
		return UAkPS4InitializationSettings::StaticClass();
	}
	struct Z_Construct_UClass_UAkPS4InitializationSettings_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AdvancedSettings_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_AdvancedSettings;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CommunicationSettings_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_CommunicationSettings;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CommonSettings_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_CommonSettings;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UAkPS4InitializationSettings_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_AkAudio,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAkPS4InitializationSettings_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "InitializationSettings/AkPS4InitializationSettings.h" },
		{ "ModuleRelativePath", "Classes/InitializationSettings/AkPS4InitializationSettings.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAkPS4InitializationSettings_Statics::NewProp_AdvancedSettings_MetaData[] = {
		{ "Category", "Initialization" },
		{ "ModuleRelativePath", "Classes/InitializationSettings/AkPS4InitializationSettings.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAkPS4InitializationSettings_Statics::NewProp_AdvancedSettings = { "AdvancedSettings", nullptr, (EPropertyFlags)0x0010040000004001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAkPS4InitializationSettings, AdvancedSettings), Z_Construct_UScriptStruct_FAkPS4AdvancedInitializationSettings, METADATA_PARAMS(Z_Construct_UClass_UAkPS4InitializationSettings_Statics::NewProp_AdvancedSettings_MetaData, ARRAY_COUNT(Z_Construct_UClass_UAkPS4InitializationSettings_Statics::NewProp_AdvancedSettings_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAkPS4InitializationSettings_Statics::NewProp_CommunicationSettings_MetaData[] = {
		{ "Category", "Initialization" },
		{ "ModuleRelativePath", "Classes/InitializationSettings/AkPS4InitializationSettings.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAkPS4InitializationSettings_Statics::NewProp_CommunicationSettings = { "CommunicationSettings", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAkPS4InitializationSettings, CommunicationSettings), Z_Construct_UScriptStruct_FAkCommunicationSettingsWithSystemInitialization, METADATA_PARAMS(Z_Construct_UClass_UAkPS4InitializationSettings_Statics::NewProp_CommunicationSettings_MetaData, ARRAY_COUNT(Z_Construct_UClass_UAkPS4InitializationSettings_Statics::NewProp_CommunicationSettings_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAkPS4InitializationSettings_Statics::NewProp_CommonSettings_MetaData[] = {
		{ "Category", "Initialization" },
		{ "ModuleRelativePath", "Classes/InitializationSettings/AkPS4InitializationSettings.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAkPS4InitializationSettings_Statics::NewProp_CommonSettings = { "CommonSettings", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAkPS4InitializationSettings, CommonSettings), Z_Construct_UScriptStruct_FAkCommonInitializationSettings, METADATA_PARAMS(Z_Construct_UClass_UAkPS4InitializationSettings_Statics::NewProp_CommonSettings_MetaData, ARRAY_COUNT(Z_Construct_UClass_UAkPS4InitializationSettings_Statics::NewProp_CommonSettings_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UAkPS4InitializationSettings_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAkPS4InitializationSettings_Statics::NewProp_AdvancedSettings,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAkPS4InitializationSettings_Statics::NewProp_CommunicationSettings,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAkPS4InitializationSettings_Statics::NewProp_CommonSettings,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UAkPS4InitializationSettings_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAkPS4InitializationSettings>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UAkPS4InitializationSettings_Statics::ClassParams = {
		&UAkPS4InitializationSettings::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UAkPS4InitializationSettings_Statics::PropPointers,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		ARRAY_COUNT(Z_Construct_UClass_UAkPS4InitializationSettings_Statics::PropPointers),
		0,
		0x001000A6u,
		METADATA_PARAMS(Z_Construct_UClass_UAkPS4InitializationSettings_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_UAkPS4InitializationSettings_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UAkPS4InitializationSettings()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UAkPS4InitializationSettings_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UAkPS4InitializationSettings, 1802750964);
	template<> AKAUDIO_API UClass* StaticClass<UAkPS4InitializationSettings>()
	{
		return UAkPS4InitializationSettings::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UAkPS4InitializationSettings(Z_Construct_UClass_UAkPS4InitializationSettings, &UAkPS4InitializationSettings::StaticClass, TEXT("/Script/AkAudio"), TEXT("UAkPS4InitializationSettings"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UAkPS4InitializationSettings);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
