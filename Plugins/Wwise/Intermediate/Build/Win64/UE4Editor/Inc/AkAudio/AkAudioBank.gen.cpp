// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AkAudio/Classes/AkAudioBank.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAkAudioBank() {}
// Cross Module References
	AKAUDIO_API UClass* Z_Construct_UClass_UAkAudioBank_NoRegister();
	AKAUDIO_API UClass* Z_Construct_UClass_UAkAudioBank();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_AkAudio();
// End Cross Module References
	void UAkAudioBank::StaticRegisterNativesUAkAudioBank()
	{
	}
	UClass* Z_Construct_UClass_UAkAudioBank_NoRegister()
	{
		return UAkAudioBank::StaticClass();
	}
	struct Z_Construct_UClass_UAkAudioBank_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AutoLoad_MetaData[];
#endif
		static void NewProp_AutoLoad_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_AutoLoad;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UAkAudioBank_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_AkAudio,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAkAudioBank_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "Comment", "/*------------------------------------------------------------------------------------\n\x09UAkAudioBank\n------------------------------------------------------------------------------------*/" },
		{ "IncludePath", "AkAudioBank.h" },
		{ "ModuleRelativePath", "Classes/AkAudioBank.h" },
		{ "ToolTip", "UAkAudioBank" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAkAudioBank_Statics::NewProp_AutoLoad_MetaData[] = {
		{ "Category", "Behaviour" },
		{ "Comment", "/** Auto-load bank when its package is accessed for the first time */" },
		{ "ModuleRelativePath", "Classes/AkAudioBank.h" },
		{ "ToolTip", "Auto-load bank when its package is accessed for the first time" },
	};
#endif
	void Z_Construct_UClass_UAkAudioBank_Statics::NewProp_AutoLoad_SetBit(void* Obj)
	{
		((UAkAudioBank*)Obj)->AutoLoad = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UAkAudioBank_Statics::NewProp_AutoLoad = { "AutoLoad", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UAkAudioBank), &Z_Construct_UClass_UAkAudioBank_Statics::NewProp_AutoLoad_SetBit, METADATA_PARAMS(Z_Construct_UClass_UAkAudioBank_Statics::NewProp_AutoLoad_MetaData, ARRAY_COUNT(Z_Construct_UClass_UAkAudioBank_Statics::NewProp_AutoLoad_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UAkAudioBank_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAkAudioBank_Statics::NewProp_AutoLoad,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UAkAudioBank_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAkAudioBank>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UAkAudioBank_Statics::ClassParams = {
		&UAkAudioBank::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UAkAudioBank_Statics::PropPointers,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		ARRAY_COUNT(Z_Construct_UClass_UAkAudioBank_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UAkAudioBank_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_UAkAudioBank_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UAkAudioBank()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UAkAudioBank_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UAkAudioBank, 1402321742);
	template<> AKAUDIO_API UClass* StaticClass<UAkAudioBank>()
	{
		return UAkAudioBank::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UAkAudioBank(Z_Construct_UClass_UAkAudioBank, &UAkAudioBank::StaticClass, TEXT("/Script/AkAudio"), TEXT("UAkAudioBank"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UAkAudioBank);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
