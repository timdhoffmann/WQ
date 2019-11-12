// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FAkBoolPropertyToControl;
#ifdef AKAUDIO_AkItemBoolProperties_generated_h
#error "AkItemBoolProperties.generated.h already included, missing '#pragma once' in AkItemBoolProperties.h"
#endif
#define AKAUDIO_AkItemBoolProperties_generated_h

#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_32_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FAkBoolPropertyToControl_Statics; \
	static class UScriptStruct* StaticStruct();


template<> AKAUDIO_API UScriptStruct* StaticStruct<struct FAkBoolPropertyToControl>();

#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_20_DELEGATE \
struct _Script_AkAudio_eventOnItemBoolPropertyDragDetected_Parms \
{ \
	FString PropertyDragged; \
}; \
static inline void FOnItemBoolPropertyDragDetected_DelegateWrapper(const FMulticastScriptDelegate& OnItemBoolPropertyDragDetected, const FString& PropertyDragged) \
{ \
	_Script_AkAudio_eventOnItemBoolPropertyDragDetected_Parms Parms; \
	Parms.PropertyDragged=PropertyDragged; \
	OnItemBoolPropertyDragDetected.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_17_DELEGATE \
struct _Script_AkAudio_eventOnItemBoolPropertySelectionChanged_Parms \
{ \
	FString PropertySelected; \
}; \
static inline void FOnItemBoolPropertySelectionChanged_DelegateWrapper(const FMulticastScriptDelegate& OnItemBoolPropertySelectionChanged, const FString& PropertySelected) \
{ \
	_Script_AkAudio_eventOnItemBoolPropertySelectionChanged_Parms Parms; \
	Parms.PropertySelected=PropertySelected; \
	OnItemBoolPropertySelectionChanged.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_48_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execConv_FAkBoolPropertyToControlToText) \
	{ \
		P_GET_STRUCT_REF(FAkBoolPropertyToControl,Z_Param_Out_INAkBoolPropertyToControl); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FText*)Z_Param__Result=UAkItemBoolPropertiesConv::Conv_FAkBoolPropertyToControlToText(Z_Param_Out_INAkBoolPropertyToControl); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execConv_FAkBoolPropertyToControlToString) \
	{ \
		P_GET_STRUCT_REF(FAkBoolPropertyToControl,Z_Param_Out_INAkBoolPropertyToControl); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=UAkItemBoolPropertiesConv::Conv_FAkBoolPropertyToControlToString(Z_Param_Out_INAkBoolPropertyToControl); \
		P_NATIVE_END; \
	}


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_48_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execConv_FAkBoolPropertyToControlToText) \
	{ \
		P_GET_STRUCT_REF(FAkBoolPropertyToControl,Z_Param_Out_INAkBoolPropertyToControl); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FText*)Z_Param__Result=UAkItemBoolPropertiesConv::Conv_FAkBoolPropertyToControlToText(Z_Param_Out_INAkBoolPropertyToControl); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execConv_FAkBoolPropertyToControlToString) \
	{ \
		P_GET_STRUCT_REF(FAkBoolPropertyToControl,Z_Param_Out_INAkBoolPropertyToControl); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=UAkItemBoolPropertiesConv::Conv_FAkBoolPropertyToControlToString(Z_Param_Out_INAkBoolPropertyToControl); \
		P_NATIVE_END; \
	}


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_48_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAkItemBoolPropertiesConv(); \
	friend struct Z_Construct_UClass_UAkItemBoolPropertiesConv_Statics; \
public: \
	DECLARE_CLASS(UAkItemBoolPropertiesConv, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AkAudio"), NO_API) \
	DECLARE_SERIALIZER(UAkItemBoolPropertiesConv)


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_48_INCLASS \
private: \
	static void StaticRegisterNativesUAkItemBoolPropertiesConv(); \
	friend struct Z_Construct_UClass_UAkItemBoolPropertiesConv_Statics; \
public: \
	DECLARE_CLASS(UAkItemBoolPropertiesConv, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AkAudio"), NO_API) \
	DECLARE_SERIALIZER(UAkItemBoolPropertiesConv)


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_48_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAkItemBoolPropertiesConv(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAkItemBoolPropertiesConv) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAkItemBoolPropertiesConv); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAkItemBoolPropertiesConv); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAkItemBoolPropertiesConv(UAkItemBoolPropertiesConv&&); \
	NO_API UAkItemBoolPropertiesConv(const UAkItemBoolPropertiesConv&); \
public:


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_48_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAkItemBoolPropertiesConv(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAkItemBoolPropertiesConv(UAkItemBoolPropertiesConv&&); \
	NO_API UAkItemBoolPropertiesConv(const UAkItemBoolPropertiesConv&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAkItemBoolPropertiesConv); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAkItemBoolPropertiesConv); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAkItemBoolPropertiesConv)


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_48_PRIVATE_PROPERTY_OFFSET
#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_45_PROLOG
#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_48_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_48_PRIVATE_PROPERTY_OFFSET \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_48_RPC_WRAPPERS \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_48_INCLASS \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_48_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_48_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_48_PRIVATE_PROPERTY_OFFSET \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_48_RPC_WRAPPERS_NO_PURE_DECLS \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_48_INCLASS_NO_PURE_DECLS \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_48_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class AkItemBoolPropertiesConv."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> AKAUDIO_API UClass* StaticClass<class UAkItemBoolPropertiesConv>();

#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_69_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execSetSearchText) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_newText); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->SetSearchText(Z_Param_newText); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetSearchText) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=P_THIS->GetSearchText(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetSelectedProperty) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=P_THIS->GetSelectedProperty(); \
		P_NATIVE_END; \
	}


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_69_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execSetSearchText) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_newText); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->SetSearchText(Z_Param_newText); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetSearchText) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=P_THIS->GetSearchText(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetSelectedProperty) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=P_THIS->GetSelectedProperty(); \
		P_NATIVE_END; \
	}


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_69_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAkItemBoolProperties(); \
	friend struct Z_Construct_UClass_UAkItemBoolProperties_Statics; \
public: \
	DECLARE_CLASS(UAkItemBoolProperties, UWidget, COMPILED_IN_FLAGS(0 | CLASS_DefaultConfig), CASTCLASS_None, TEXT("/Script/AkAudio"), NO_API) \
	DECLARE_SERIALIZER(UAkItemBoolProperties) \
	static const TCHAR* StaticConfigName() {return TEXT("Editor");} \



#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_69_INCLASS \
private: \
	static void StaticRegisterNativesUAkItemBoolProperties(); \
	friend struct Z_Construct_UClass_UAkItemBoolProperties_Statics; \
public: \
	DECLARE_CLASS(UAkItemBoolProperties, UWidget, COMPILED_IN_FLAGS(0 | CLASS_DefaultConfig), CASTCLASS_None, TEXT("/Script/AkAudio"), NO_API) \
	DECLARE_SERIALIZER(UAkItemBoolProperties) \
	static const TCHAR* StaticConfigName() {return TEXT("Editor");} \



#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_69_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAkItemBoolProperties(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAkItemBoolProperties) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAkItemBoolProperties); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAkItemBoolProperties); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAkItemBoolProperties(UAkItemBoolProperties&&); \
	NO_API UAkItemBoolProperties(const UAkItemBoolProperties&); \
public:


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_69_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAkItemBoolProperties(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAkItemBoolProperties(UAkItemBoolProperties&&); \
	NO_API UAkItemBoolProperties(const UAkItemBoolProperties&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAkItemBoolProperties); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAkItemBoolProperties); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAkItemBoolProperties)


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_69_PRIVATE_PROPERTY_OFFSET
#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_66_PROLOG
#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_69_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_69_PRIVATE_PROPERTY_OFFSET \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_69_RPC_WRAPPERS \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_69_INCLASS \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_69_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_69_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_69_PRIVATE_PROPERTY_OFFSET \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_69_RPC_WRAPPERS_NO_PURE_DECLS \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_69_INCLASS_NO_PURE_DECLS \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h_69_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class AkItemBoolProperties."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> AKAUDIO_API UClass* StaticClass<class UAkItemBoolProperties>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkItemBoolProperties_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
