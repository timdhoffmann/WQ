// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AudiokineticTools/Classes/AkAudioEventFactory.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAkAudioEventFactory() {}
// Cross Module References
	AUDIOKINETICTOOLS_API UClass* Z_Construct_UClass_UAkAudioEventFactory_NoRegister();
	AUDIOKINETICTOOLS_API UClass* Z_Construct_UClass_UAkAudioEventFactory();
	UNREALED_API UClass* Z_Construct_UClass_UFactory();
	UPackage* Z_Construct_UPackage__Script_AudiokineticTools();
// End Cross Module References
	void UAkAudioEventFactory::StaticRegisterNativesUAkAudioEventFactory()
	{
	}
	UClass* Z_Construct_UClass_UAkAudioEventFactory_NoRegister()
	{
		return UAkAudioEventFactory::StaticClass();
	}
	struct Z_Construct_UClass_UAkAudioEventFactory_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UAkAudioEventFactory_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UFactory,
		(UObject* (*)())Z_Construct_UPackage__Script_AudiokineticTools,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAkAudioEventFactory_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/*------------------------------------------------------------------------------------\n\x09UAkAudioEventFactory\n------------------------------------------------------------------------------------*/" },
		{ "HideCategories", "Object" },
		{ "IncludePath", "AkAudioEventFactory.h" },
		{ "ModuleRelativePath", "Classes/AkAudioEventFactory.h" },
		{ "ToolTip", "UAkAudioEventFactory" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UAkAudioEventFactory_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAkAudioEventFactory>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UAkAudioEventFactory_Statics::ClassParams = {
		&UAkAudioEventFactory::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x000000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UAkAudioEventFactory_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_UAkAudioEventFactory_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UAkAudioEventFactory()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UAkAudioEventFactory_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UAkAudioEventFactory, 272714363);
	template<> AUDIOKINETICTOOLS_API UClass* StaticClass<UAkAudioEventFactory>()
	{
		return UAkAudioEventFactory::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UAkAudioEventFactory(Z_Construct_UClass_UAkAudioEventFactory, &UAkAudioEventFactory::StaticClass, TEXT("/Script/AudiokineticTools"), TEXT("UAkAudioEventFactory"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UAkAudioEventFactory);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
