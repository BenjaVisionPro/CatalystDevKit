// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Connection/UBVCConnectionManager.h"

#ifdef CATALYSTCONNECT_UBVCConnectionManager_generated_h
#error "UBVCConnectionManager.generated.h already included, missing '#pragma once' in UBVCConnectionManager.h"
#endif
#define CATALYSTCONNECT_UBVCConnectionManager_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

struct FBVCFlowRates;

// ********** Begin ScriptStruct FBVCFlowRates *****************************************************
#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Connection_UBVCConnectionManager_h_17_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FBVCFlowRates_Statics; \
	CATALYSTCONNECT_API static class UScriptStruct* StaticStruct();


struct FBVCFlowRates;
// ********** End ScriptStruct FBVCFlowRates *******************************************************

// ********** Begin Class UBVCConnectionManager ****************************************************
#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Connection_UBVCConnectionManager_h_38_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetFlowRates); \
	DECLARE_FUNCTION(execSetFlowRates); \
	DECLARE_FUNCTION(execIsConnected); \
	DECLARE_FUNCTION(execDisconnect); \
	DECLARE_FUNCTION(execConnect);


CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCConnectionManager_NoRegister();

#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Connection_UBVCConnectionManager_h_38_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUBVCConnectionManager(); \
	friend struct Z_Construct_UClass_UBVCConnectionManager_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCConnectionManager_NoRegister(); \
public: \
	DECLARE_CLASS2(UBVCConnectionManager, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/CatalystConnect"), Z_Construct_UClass_UBVCConnectionManager_NoRegister) \
	DECLARE_SERIALIZER(UBVCConnectionManager)


#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Connection_UBVCConnectionManager_h_38_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UBVCConnectionManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UBVCConnectionManager(UBVCConnectionManager&&) = delete; \
	UBVCConnectionManager(const UBVCConnectionManager&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBVCConnectionManager); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBVCConnectionManager); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBVCConnectionManager) \
	NO_API virtual ~UBVCConnectionManager();


#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Connection_UBVCConnectionManager_h_35_PROLOG
#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Connection_UBVCConnectionManager_h_38_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Connection_UBVCConnectionManager_h_38_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Connection_UBVCConnectionManager_h_38_INCLASS_NO_PURE_DECLS \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Connection_UBVCConnectionManager_h_38_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UBVCConnectionManager;

// ********** End Class UBVCConnectionManager ******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Connection_UBVCConnectionManager_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
