// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Runtime/UBVCValidationEngine.h"

#ifdef CATALYSTCONNECT_UBVCValidationEngine_generated_h
#error "UBVCValidationEngine.generated.h already included, missing '#pragma once' in UBVCValidationEngine.h"
#endif
#define CATALYSTCONNECT_UBVCValidationEngine_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

struct FBVCMADescription;
struct FBVCValidationIssue;

// ********** Begin ScriptStruct FBVCValidationIssue ***********************************************
#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCValidationEngine_h_11_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FBVCValidationIssue_Statics; \
	static class UScriptStruct* StaticStruct();


struct FBVCValidationIssue;
// ********** End ScriptStruct FBVCValidationIssue *************************************************

// ********** Begin Class UBVCValidationEngine *****************************************************
#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCValidationEngine_h_26_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execValidateObject); \
	DECLARE_FUNCTION(execValidateField);


CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCValidationEngine_NoRegister();

#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCValidationEngine_h_26_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUBVCValidationEngine(); \
	friend struct Z_Construct_UClass_UBVCValidationEngine_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCValidationEngine_NoRegister(); \
public: \
	DECLARE_CLASS2(UBVCValidationEngine, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/CatalystConnect"), Z_Construct_UClass_UBVCValidationEngine_NoRegister) \
	DECLARE_SERIALIZER(UBVCValidationEngine)


#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCValidationEngine_h_26_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UBVCValidationEngine(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UBVCValidationEngine(UBVCValidationEngine&&) = delete; \
	UBVCValidationEngine(const UBVCValidationEngine&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBVCValidationEngine); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBVCValidationEngine); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBVCValidationEngine) \
	NO_API virtual ~UBVCValidationEngine();


#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCValidationEngine_h_23_PROLOG
#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCValidationEngine_h_26_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCValidationEngine_h_26_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCValidationEngine_h_26_INCLASS_NO_PURE_DECLS \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCValidationEngine_h_26_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UBVCValidationEngine;

// ********** End Class UBVCValidationEngine *******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCValidationEngine_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
