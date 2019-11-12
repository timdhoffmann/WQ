// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AkAudio/Classes/AkLateReverbComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAkLateReverbComponent() {}
// Cross Module References
	AKAUDIO_API UClass* Z_Construct_UClass_UAkLateReverbComponent_NoRegister();
	AKAUDIO_API UClass* Z_Construct_UClass_UAkLateReverbComponent();
	ENGINE_API UClass* Z_Construct_UClass_USceneComponent();
	UPackage* Z_Construct_UPackage__Script_AkAudio();
	AKAUDIO_API UClass* Z_Construct_UClass_UAkAuxBus_NoRegister();
// End Cross Module References
	void UAkLateReverbComponent::StaticRegisterNativesUAkLateReverbComponent()
	{
	}
	UClass* Z_Construct_UClass_UAkLateReverbComponent_NoRegister()
	{
		return UAkLateReverbComponent::StaticClass();
	}
	struct Z_Construct_UClass_UAkLateReverbComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_NextLowerPriorityComponent_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_NextLowerPriorityComponent;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Priority_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Priority;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FadeRate_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_FadeRate;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SendLevel_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_SendLevel;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AuxBusName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_AuxBusName;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AuxBus_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_AuxBus;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bEnable_MetaData[];
#endif
		static void NewProp_bEnable_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bEnable;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UAkLateReverbComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USceneComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_AkAudio,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAkLateReverbComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "BlueprintType", "true" },
		{ "ClassGroupNames", "Audiokinetic" },
		{ "HideCategories", "Transform Rendering Mobility LOD Component Activation Tags Trigger PhysicsVolume" },
		{ "IncludePath", "AkLateReverbComponent.h" },
		{ "ModuleRelativePath", "Classes/AkLateReverbComponent.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_NextLowerPriorityComponent_MetaData[] = {
		{ "Comment", "/** We keep a  linked list of ReverbVolumes sorted by priority for faster finding of reverb volumes at a specific location.\n\x09 *\x09This points to the next volume in the list.\n\x09 */" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Classes/AkLateReverbComponent.h" },
		{ "ToolTip", "We keep a  linked list of ReverbVolumes sorted by priority for faster finding of reverb volumes at a specific location.\n    This points to the next volume in the list." },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_NextLowerPriorityComponent = { "NextLowerPriorityComponent", nullptr, (EPropertyFlags)0x0010000000082008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAkLateReverbComponent, NextLowerPriorityComponent), Z_Construct_UClass_UAkLateReverbComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_NextLowerPriorityComponent_MetaData, ARRAY_COUNT(Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_NextLowerPriorityComponent_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_Priority_MetaData[] = {
		{ "Category", "LateReverb" },
		{ "Comment", "/**\n\x09 * The precedence in which the AkReverbVolumes will be applied. In the case of overlapping volumes, only the ones \n\x09 * with the highest priority are chosen (the number of simultaneous AkReverbVolumes is configurable in the Unreal \n\x09 * Editor Project Settings under Plugins > Wwise). If two or more overlapping AkReverbVolumes have the same \n\x09 * priority, the chosen AkReverbVolume is unpredictable.\n\x09 */" },
		{ "ModuleRelativePath", "Classes/AkLateReverbComponent.h" },
		{ "ToolTip", "The precedence in which the AkReverbVolumes will be applied. In the case of overlapping volumes, only the ones\nwith the highest priority are chosen (the number of simultaneous AkReverbVolumes is configurable in the Unreal\nEditor Project Settings under Plugins > Wwise). If two or more overlapping AkReverbVolumes have the same\npriority, the chosen AkReverbVolume is unpredictable." },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_Priority = { "Priority", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAkLateReverbComponent, Priority), METADATA_PARAMS(Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_Priority_MetaData, ARRAY_COUNT(Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_Priority_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_FadeRate_MetaData[] = {
		{ "Category", "LateReverb" },
		{ "ClampMin", "0.000000" },
		{ "Comment", "/** Rate at which to fade in/out the SendLevel of the current Reverb Volume when entering/exiting it, in percentage per second (0.2 will make the fade time 5 seconds) */" },
		{ "ModuleRelativePath", "Classes/AkLateReverbComponent.h" },
		{ "ToolTip", "Rate at which to fade in/out the SendLevel of the current Reverb Volume when entering/exiting it, in percentage per second (0.2 will make the fade time 5 seconds)" },
		{ "UIMin", "0.000000" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_FadeRate = { "FadeRate", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAkLateReverbComponent, FadeRate), METADATA_PARAMS(Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_FadeRate_MetaData, ARRAY_COUNT(Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_FadeRate_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_SendLevel_MetaData[] = {
		{ "Category", "LateReverb" },
		{ "ClampMax", "1.000000" },
		{ "ClampMin", "0.000000" },
		{ "Comment", "/** Maximum send level to the Wwise Auxiliary Bus associated to this AkReverbVolume */" },
		{ "ModuleRelativePath", "Classes/AkLateReverbComponent.h" },
		{ "ToolTip", "Maximum send level to the Wwise Auxiliary Bus associated to this AkReverbVolume" },
		{ "UIMax", "1.000000" },
		{ "UIMin", "0.000000" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_SendLevel = { "SendLevel", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAkLateReverbComponent, SendLevel), METADATA_PARAMS(Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_SendLevel_MetaData, ARRAY_COUNT(Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_SendLevel_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_AuxBusName_MetaData[] = {
		{ "Category", "LateReverb" },
		{ "Comment", "/** Wwise Auxiliary Bus associated to this AkReverbVolume */" },
		{ "ModuleRelativePath", "Classes/AkLateReverbComponent.h" },
		{ "ToolTip", "Wwise Auxiliary Bus associated to this AkReverbVolume" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_AuxBusName = { "AuxBusName", nullptr, (EPropertyFlags)0x0010040000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAkLateReverbComponent, AuxBusName), METADATA_PARAMS(Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_AuxBusName_MetaData, ARRAY_COUNT(Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_AuxBusName_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_AuxBus_MetaData[] = {
		{ "Category", "LateReverb" },
		{ "ModuleRelativePath", "Classes/AkLateReverbComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_AuxBus = { "AuxBus", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAkLateReverbComponent, AuxBus), Z_Construct_UClass_UAkAuxBus_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_AuxBus_MetaData, ARRAY_COUNT(Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_AuxBus_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_bEnable_MetaData[] = {
		{ "Category", "Toggle" },
		{ "Comment", "/** Whether this volume is currently enabled and able to affect sounds */" },
		{ "DisplayName", "Enable Late Reverb" },
		{ "ModuleRelativePath", "Classes/AkLateReverbComponent.h" },
		{ "ToolTip", "Whether this volume is currently enabled and able to affect sounds" },
	};
#endif
	void Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_bEnable_SetBit(void* Obj)
	{
		((UAkLateReverbComponent*)Obj)->bEnable = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_bEnable = { "bEnable", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool , RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(uint8), sizeof(UAkLateReverbComponent), &Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_bEnable_SetBit, METADATA_PARAMS(Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_bEnable_MetaData, ARRAY_COUNT(Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_bEnable_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UAkLateReverbComponent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_NextLowerPriorityComponent,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_Priority,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_FadeRate,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_SendLevel,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_AuxBusName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_AuxBus,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAkLateReverbComponent_Statics::NewProp_bEnable,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UAkLateReverbComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAkLateReverbComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UAkLateReverbComponent_Statics::ClassParams = {
		&UAkLateReverbComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UAkLateReverbComponent_Statics::PropPointers,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		ARRAY_COUNT(Z_Construct_UClass_UAkLateReverbComponent_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UAkLateReverbComponent_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_UAkLateReverbComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UAkLateReverbComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UAkLateReverbComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UAkLateReverbComponent, 429945638);
	template<> AKAUDIO_API UClass* StaticClass<UAkLateReverbComponent>()
	{
		return UAkLateReverbComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UAkLateReverbComponent(Z_Construct_UClass_UAkLateReverbComponent, &UAkLateReverbComponent::StaticClass, TEXT("/Script/AkAudio"), TEXT("UAkLateReverbComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UAkLateReverbComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
