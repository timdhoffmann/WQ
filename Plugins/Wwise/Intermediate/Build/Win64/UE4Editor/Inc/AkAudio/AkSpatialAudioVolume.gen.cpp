// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AkAudio/Classes/AkSpatialAudioVolume.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAkSpatialAudioVolume() {}
// Cross Module References
	AKAUDIO_API UClass* Z_Construct_UClass_AAkSpatialAudioVolume_NoRegister();
	AKAUDIO_API UClass* Z_Construct_UClass_AAkSpatialAudioVolume();
	ENGINE_API UClass* Z_Construct_UClass_AVolume();
	UPackage* Z_Construct_UPackage__Script_AkAudio();
	AKAUDIO_API UClass* Z_Construct_UClass_UAkRoomComponent_NoRegister();
	AKAUDIO_API UClass* Z_Construct_UClass_UAkLateReverbComponent_NoRegister();
	AKAUDIO_API UClass* Z_Construct_UClass_UAkSurfaceReflectorSetComponent_NoRegister();
// End Cross Module References
	void AAkSpatialAudioVolume::StaticRegisterNativesAAkSpatialAudioVolume()
	{
	}
	UClass* Z_Construct_UClass_AAkSpatialAudioVolume_NoRegister()
	{
		return AAkSpatialAudioVolume::StaticClass();
	}
	struct Z_Construct_UClass_AAkSpatialAudioVolume_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Room_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Room;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LateReverb_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_LateReverb;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SurfaceReflectorSet_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_SurfaceReflectorSet;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AAkSpatialAudioVolume_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AVolume,
		(UObject* (*)())Z_Construct_UPackage__Script_AkAudio,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAkSpatialAudioVolume_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ClassGroupNames", "Audiokinetic" },
		{ "Comment", "/*------------------------------------------------------------------------------------\n\x09""AAkSpatialAudioVolume\n------------------------------------------------------------------------------------*/" },
		{ "HideCategories", "Advanced Attachment Volume Brush Physics Object Display Rendering Physics Input Blueprint" },
		{ "IncludePath", "AkSpatialAudioVolume.h" },
		{ "ModuleRelativePath", "Classes/AkSpatialAudioVolume.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
		{ "ToolTip", "AAkSpatialAudioVolume" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAkSpatialAudioVolume_Statics::NewProp_Room_MetaData[] = {
		{ "Category", "Room" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Classes/AkSpatialAudioVolume.h" },
		{ "ShowOnlyInnerProperties", "" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAkSpatialAudioVolume_Statics::NewProp_Room = { "Room", nullptr, (EPropertyFlags)0x00100000000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AAkSpatialAudioVolume, Room), Z_Construct_UClass_UAkRoomComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AAkSpatialAudioVolume_Statics::NewProp_Room_MetaData, ARRAY_COUNT(Z_Construct_UClass_AAkSpatialAudioVolume_Statics::NewProp_Room_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAkSpatialAudioVolume_Statics::NewProp_LateReverb_MetaData[] = {
		{ "Category", "LateReverb" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Classes/AkSpatialAudioVolume.h" },
		{ "ShowOnlyInnerProperties", "" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAkSpatialAudioVolume_Statics::NewProp_LateReverb = { "LateReverb", nullptr, (EPropertyFlags)0x00100000000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AAkSpatialAudioVolume, LateReverb), Z_Construct_UClass_UAkLateReverbComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AAkSpatialAudioVolume_Statics::NewProp_LateReverb_MetaData, ARRAY_COUNT(Z_Construct_UClass_AAkSpatialAudioVolume_Statics::NewProp_LateReverb_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAkSpatialAudioVolume_Statics::NewProp_SurfaceReflectorSet_MetaData[] = {
		{ "Category", "SurfaceReflectorSet" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Classes/AkSpatialAudioVolume.h" },
		{ "ShowOnlyInnerProperties", "" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAkSpatialAudioVolume_Statics::NewProp_SurfaceReflectorSet = { "SurfaceReflectorSet", nullptr, (EPropertyFlags)0x00100000000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AAkSpatialAudioVolume, SurfaceReflectorSet), Z_Construct_UClass_UAkSurfaceReflectorSetComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AAkSpatialAudioVolume_Statics::NewProp_SurfaceReflectorSet_MetaData, ARRAY_COUNT(Z_Construct_UClass_AAkSpatialAudioVolume_Statics::NewProp_SurfaceReflectorSet_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AAkSpatialAudioVolume_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAkSpatialAudioVolume_Statics::NewProp_Room,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAkSpatialAudioVolume_Statics::NewProp_LateReverb,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAkSpatialAudioVolume_Statics::NewProp_SurfaceReflectorSet,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AAkSpatialAudioVolume_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AAkSpatialAudioVolume>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AAkSpatialAudioVolume_Statics::ClassParams = {
		&AAkSpatialAudioVolume::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AAkSpatialAudioVolume_Statics::PropPointers,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		ARRAY_COUNT(Z_Construct_UClass_AAkSpatialAudioVolume_Statics::PropPointers),
		0,
		0x009000A0u,
		METADATA_PARAMS(Z_Construct_UClass_AAkSpatialAudioVolume_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_AAkSpatialAudioVolume_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AAkSpatialAudioVolume()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AAkSpatialAudioVolume_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AAkSpatialAudioVolume, 696321869);
	template<> AKAUDIO_API UClass* StaticClass<AAkSpatialAudioVolume>()
	{
		return AAkSpatialAudioVolume::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AAkSpatialAudioVolume(Z_Construct_UClass_AAkSpatialAudioVolume, &AAkSpatialAudioVolume::StaticClass, TEXT("/Script/AkAudio"), TEXT("AAkSpatialAudioVolume"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AAkSpatialAudioVolume);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
