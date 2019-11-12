// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef AKAUDIO_AkReverbVolume_generated_h
#error "AkReverbVolume.generated.h already included, missing '#pragma once' in AkReverbVolume.h"
#endif
#define AKAUDIO_AkReverbVolume_generated_h

#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkReverbVolume_h_18_RPC_WRAPPERS
#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkReverbVolume_h_18_RPC_WRAPPERS_NO_PURE_DECLS
#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkReverbVolume_h_18_ARCHIVESERIALIZER \
	DECLARE_FSTRUCTUREDARCHIVE_SERIALIZER(AAkReverbVolume, NO_API)


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkReverbVolume_h_18_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAAkReverbVolume(); \
	friend struct Z_Construct_UClass_AAkReverbVolume_Statics; \
public: \
	DECLARE_CLASS(AAkReverbVolume, AVolume, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AkAudio"), NO_API) \
	DECLARE_SERIALIZER(AAkReverbVolume) \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkReverbVolume_h_18_ARCHIVESERIALIZER


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkReverbVolume_h_18_INCLASS \
private: \
	static void StaticRegisterNativesAAkReverbVolume(); \
	friend struct Z_Construct_UClass_AAkReverbVolume_Statics; \
public: \
	DECLARE_CLASS(AAkReverbVolume, AVolume, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AkAudio"), NO_API) \
	DECLARE_SERIALIZER(AAkReverbVolume) \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkReverbVolume_h_18_ARCHIVESERIALIZER


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkReverbVolume_h_18_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AAkReverbVolume(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AAkReverbVolume) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AAkReverbVolume); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AAkReverbVolume); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AAkReverbVolume(AAkReverbVolume&&); \
	NO_API AAkReverbVolume(const AAkReverbVolume&); \
public:


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkReverbVolume_h_18_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AAkReverbVolume(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AAkReverbVolume(AAkReverbVolume&&); \
	NO_API AAkReverbVolume(const AAkReverbVolume&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AAkReverbVolume); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AAkReverbVolume); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AAkReverbVolume)


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkReverbVolume_h_18_PRIVATE_PROPERTY_OFFSET
#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkReverbVolume_h_15_PROLOG
#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkReverbVolume_h_18_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkReverbVolume_h_18_PRIVATE_PROPERTY_OFFSET \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkReverbVolume_h_18_RPC_WRAPPERS \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkReverbVolume_h_18_INCLASS \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkReverbVolume_h_18_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkReverbVolume_h_18_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkReverbVolume_h_18_PRIVATE_PROPERTY_OFFSET \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkReverbVolume_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkReverbVolume_h_18_INCLASS_NO_PURE_DECLS \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkReverbVolume_h_18_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class AkReverbVolume."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> AKAUDIO_API UClass* StaticClass<class AAkReverbVolume>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID WQ_Plugins_Wwise_Source_AkAudio_Classes_AkReverbVolume_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
