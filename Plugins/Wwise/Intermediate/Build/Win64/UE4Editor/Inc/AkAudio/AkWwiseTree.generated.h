// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FGuid;
struct FAkWwiseObjectDetails;
#ifdef AKAUDIO_AkWwiseTree_generated_h
#error "AkWwiseTree.generated.h already included, missing '#pragma once' in AkWwiseTree.h"
#endif
#define AKAUDIO_AkWwiseTree_generated_h

#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkWwiseTree_h_18_DELEGATE \
struct _Script_AkAudio_eventOnItemDragDetected_Parms \
{ \
	FGuid ItemDraggedID; \
	FString ItemDraggedName; \
}; \
static inline void FOnItemDragDetected_DelegateWrapper(const FMulticastScriptDelegate& OnItemDragDetected, FGuid ItemDraggedID, const FString& ItemDraggedName) \
{ \
	_Script_AkAudio_eventOnItemDragDetected_Parms Parms; \
	Parms.ItemDraggedID=ItemDraggedID; \
	Parms.ItemDraggedName=ItemDraggedName; \
	OnItemDragDetected.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkWwiseTree_h_15_DELEGATE \
struct _Script_AkAudio_eventOnItemSelectionChanged_Parms \
{ \
	FGuid ItemSelectedID; \
}; \
static inline void FOnItemSelectionChanged_DelegateWrapper(const FMulticastScriptDelegate& OnItemSelectionChanged, FGuid ItemSelectedID) \
{ \
	_Script_AkAudio_eventOnItemSelectionChanged_Parms Parms; \
	Parms.ItemSelectedID=ItemSelectedID; \
	OnItemSelectionChanged.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkWwiseTree_h_30_RPC_WRAPPERS \
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
	DECLARE_FUNCTION(execGetSelectedItem) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FAkWwiseObjectDetails*)Z_Param__Result=P_THIS->GetSelectedItem(); \
		P_NATIVE_END; \
	}


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkWwiseTree_h_30_RPC_WRAPPERS_NO_PURE_DECLS \
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
	DECLARE_FUNCTION(execGetSelectedItem) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FAkWwiseObjectDetails*)Z_Param__Result=P_THIS->GetSelectedItem(); \
		P_NATIVE_END; \
	}


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkWwiseTree_h_30_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAkWwiseTree(); \
	friend struct Z_Construct_UClass_UAkWwiseTree_Statics; \
public: \
	DECLARE_CLASS(UAkWwiseTree, UWidget, COMPILED_IN_FLAGS(0 | CLASS_DefaultConfig), CASTCLASS_None, TEXT("/Script/AkAudio"), NO_API) \
	DECLARE_SERIALIZER(UAkWwiseTree) \
	static const TCHAR* StaticConfigName() {return TEXT("Editor");} \



#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkWwiseTree_h_30_INCLASS \
private: \
	static void StaticRegisterNativesUAkWwiseTree(); \
	friend struct Z_Construct_UClass_UAkWwiseTree_Statics; \
public: \
	DECLARE_CLASS(UAkWwiseTree, UWidget, COMPILED_IN_FLAGS(0 | CLASS_DefaultConfig), CASTCLASS_None, TEXT("/Script/AkAudio"), NO_API) \
	DECLARE_SERIALIZER(UAkWwiseTree) \
	static const TCHAR* StaticConfigName() {return TEXT("Editor");} \



#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkWwiseTree_h_30_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAkWwiseTree(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAkWwiseTree) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAkWwiseTree); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAkWwiseTree); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAkWwiseTree(UAkWwiseTree&&); \
	NO_API UAkWwiseTree(const UAkWwiseTree&); \
public:


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkWwiseTree_h_30_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAkWwiseTree(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAkWwiseTree(UAkWwiseTree&&); \
	NO_API UAkWwiseTree(const UAkWwiseTree&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAkWwiseTree); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAkWwiseTree); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAkWwiseTree)


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkWwiseTree_h_30_PRIVATE_PROPERTY_OFFSET
#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkWwiseTree_h_27_PROLOG
#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkWwiseTree_h_30_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkWwiseTree_h_30_PRIVATE_PROPERTY_OFFSET \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkWwiseTree_h_30_RPC_WRAPPERS \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkWwiseTree_h_30_INCLASS \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkWwiseTree_h_30_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkWwiseTree_h_30_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkWwiseTree_h_30_PRIVATE_PROPERTY_OFFSET \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkWwiseTree_h_30_RPC_WRAPPERS_NO_PURE_DECLS \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkWwiseTree_h_30_INCLASS_NO_PURE_DECLS \
	WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkWwiseTree_h_30_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class AkWwiseTree."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> AKAUDIO_API UClass* StaticClass<class UAkWwiseTree>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID WQ_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkWwiseTree_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
