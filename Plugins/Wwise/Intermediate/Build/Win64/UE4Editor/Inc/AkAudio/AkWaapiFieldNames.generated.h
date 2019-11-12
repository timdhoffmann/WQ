// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FAkWaapiFieldNames;
#ifdef AKAUDIO_AkWaapiFieldNames_generated_h
#error "AkWaapiFieldNames.generated.h already included, missing '#pragma once' in AkWaapiFieldNames.h"
#endif
#define AKAUDIO_AkWaapiFieldNames_generated_h

#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiBlueprints_AkWaapiFieldNames_h_27_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FAkWaapiFieldNames_Statics; \
	static class UScriptStruct* StaticStruct();


template<> AKAUDIO_API UScriptStruct* StaticStruct<struct FAkWaapiFieldNames>();

#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiBlueprints_AkWaapiFieldNames_h_42_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execConv_FAkWaapiFieldNamesToText) \
	{ \
		P_GET_STRUCT_REF(FAkWaapiFieldNames,Z_Param_Out_INAkWaapiFieldNames); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FText*)Z_Param__Result=USAkWaapiFieldNamesConv::Conv_FAkWaapiFieldNamesToText(Z_Param_Out_INAkWaapiFieldNames); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execConv_FAkWaapiFieldNamesToString) \
	{ \
		P_GET_STRUCT_REF(FAkWaapiFieldNames,Z_Param_Out_INAkWaapiFieldNames); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=USAkWaapiFieldNamesConv::Conv_FAkWaapiFieldNamesToString(Z_Param_Out_INAkWaapiFieldNames); \
		P_NATIVE_END; \
	}


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiBlueprints_AkWaapiFieldNames_h_42_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execConv_FAkWaapiFieldNamesToText) \
	{ \
		P_GET_STRUCT_REF(FAkWaapiFieldNames,Z_Param_Out_INAkWaapiFieldNames); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FText*)Z_Param__Result=USAkWaapiFieldNamesConv::Conv_FAkWaapiFieldNamesToText(Z_Param_Out_INAkWaapiFieldNames); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execConv_FAkWaapiFieldNamesToString) \
	{ \
		P_GET_STRUCT_REF(FAkWaapiFieldNames,Z_Param_Out_INAkWaapiFieldNames); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=USAkWaapiFieldNamesConv::Conv_FAkWaapiFieldNamesToString(Z_Param_Out_INAkWaapiFieldNames); \
		P_NATIVE_END; \
	}


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiBlueprints_AkWaapiFieldNames_h_42_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUSAkWaapiFieldNamesConv(); \
	friend struct Z_Construct_UClass_USAkWaapiFieldNamesConv_Statics; \
public: \
	DECLARE_CLASS(USAkWaapiFieldNamesConv, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AkAudio"), NO_API) \
	DECLARE_SERIALIZER(USAkWaapiFieldNamesConv)


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiBlueprints_AkWaapiFieldNames_h_42_INCLASS \
private: \
	static void StaticRegisterNativesUSAkWaapiFieldNamesConv(); \
	friend struct Z_Construct_UClass_USAkWaapiFieldNamesConv_Statics; \
public: \
	DECLARE_CLASS(USAkWaapiFieldNamesConv, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AkAudio"), NO_API) \
	DECLARE_SERIALIZER(USAkWaapiFieldNamesConv)


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiBlueprints_AkWaapiFieldNames_h_42_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API USAkWaapiFieldNamesConv(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(USAkWaapiFieldNamesConv) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USAkWaapiFieldNamesConv); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USAkWaapiFieldNamesConv); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API USAkWaapiFieldNamesConv(USAkWaapiFieldNamesConv&&); \
	NO_API USAkWaapiFieldNamesConv(const USAkWaapiFieldNamesConv&); \
public:


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiBlueprints_AkWaapiFieldNames_h_42_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API USAkWaapiFieldNamesConv(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API USAkWaapiFieldNamesConv(USAkWaapiFieldNamesConv&&); \
	NO_API USAkWaapiFieldNamesConv(const USAkWaapiFieldNamesConv&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USAkWaapiFieldNamesConv); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USAkWaapiFieldNamesConv); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(USAkWaapiFieldNamesConv)


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiBlueprints_AkWaapiFieldNames_h_42_PRIVATE_PROPERTY_OFFSET
#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiBlueprints_AkWaapiFieldNames_h_39_PROLOG
#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiBlueprints_AkWaapiFieldNames_h_42_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiBlueprints_AkWaapiFieldNames_h_42_PRIVATE_PROPERTY_OFFSET \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiBlueprints_AkWaapiFieldNames_h_42_RPC_WRAPPERS \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiBlueprints_AkWaapiFieldNames_h_42_INCLASS \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiBlueprints_AkWaapiFieldNames_h_42_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiBlueprints_AkWaapiFieldNames_h_42_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiBlueprints_AkWaapiFieldNames_h_42_PRIVATE_PROPERTY_OFFSET \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiBlueprints_AkWaapiFieldNames_h_42_RPC_WRAPPERS_NO_PURE_DECLS \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiBlueprints_AkWaapiFieldNames_h_42_INCLASS_NO_PURE_DECLS \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiBlueprints_AkWaapiFieldNames_h_42_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class SAkWaapiFieldNamesConv."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> AKAUDIO_API UClass* StaticClass<class USAkWaapiFieldNamesConv>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiBlueprints_AkWaapiFieldNames_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
