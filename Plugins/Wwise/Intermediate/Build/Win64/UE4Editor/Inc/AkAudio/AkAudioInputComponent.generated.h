// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef AKAUDIO_AkAudioInputComponent_generated_h
#error "AkAudioInputComponent.generated.h already included, missing '#pragma once' in AkAudioInputComponent.h"
#endif
#define AKAUDIO_AkAudioInputComponent_generated_h

#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkAudioInputComponent_h_20_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execPostAssociatedAudioInputEvent) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(int32*)Z_Param__Result=P_THIS->PostAssociatedAudioInputEvent(); \
		P_NATIVE_END; \
	}


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkAudioInputComponent_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execPostAssociatedAudioInputEvent) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(int32*)Z_Param__Result=P_THIS->PostAssociatedAudioInputEvent(); \
		P_NATIVE_END; \
	}


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkAudioInputComponent_h_20_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAkAudioInputComponent(); \
	friend struct Z_Construct_UClass_UAkAudioInputComponent_Statics; \
public: \
	DECLARE_CLASS(UAkAudioInputComponent, UAkComponent, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/AkAudio"), NO_API) \
	DECLARE_SERIALIZER(UAkAudioInputComponent)


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkAudioInputComponent_h_20_INCLASS \
private: \
	static void StaticRegisterNativesUAkAudioInputComponent(); \
	friend struct Z_Construct_UClass_UAkAudioInputComponent_Statics; \
public: \
	DECLARE_CLASS(UAkAudioInputComponent, UAkComponent, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/AkAudio"), NO_API) \
	DECLARE_SERIALIZER(UAkAudioInputComponent)


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkAudioInputComponent_h_20_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAkAudioInputComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAkAudioInputComponent) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAkAudioInputComponent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAkAudioInputComponent); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAkAudioInputComponent(UAkAudioInputComponent&&); \
	NO_API UAkAudioInputComponent(const UAkAudioInputComponent&); \
public:


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkAudioInputComponent_h_20_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAkAudioInputComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAkAudioInputComponent(UAkAudioInputComponent&&); \
	NO_API UAkAudioInputComponent(const UAkAudioInputComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAkAudioInputComponent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAkAudioInputComponent); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAkAudioInputComponent)


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkAudioInputComponent_h_20_PRIVATE_PROPERTY_OFFSET
#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkAudioInputComponent_h_17_PROLOG
#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkAudioInputComponent_h_20_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkAudioInputComponent_h_20_PRIVATE_PROPERTY_OFFSET \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkAudioInputComponent_h_20_RPC_WRAPPERS \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkAudioInputComponent_h_20_INCLASS \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkAudioInputComponent_h_20_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkAudioInputComponent_h_20_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkAudioInputComponent_h_20_PRIVATE_PROPERTY_OFFSET \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkAudioInputComponent_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkAudioInputComponent_h_20_INCLASS_NO_PURE_DECLS \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkAudioInputComponent_h_20_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class AkAudioInputComponent."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> AKAUDIO_API UClass* StaticClass<class UAkAudioInputComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID WQ_Plugins_Wwise_Source_AkAudio_Classes_AkAudioInputComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
