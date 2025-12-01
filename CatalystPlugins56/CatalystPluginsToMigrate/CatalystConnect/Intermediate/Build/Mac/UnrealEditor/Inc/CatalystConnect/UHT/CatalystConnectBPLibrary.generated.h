// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "CatalystConnectBPLibrary.h"

#ifdef CATALYSTCONNECT_CatalystConnectBPLibrary_generated_h
#error "CatalystConnectBPLibrary.generated.h already included, missing '#pragma once' in CatalystConnectBPLibrary.h"
#endif
#define CATALYSTCONNECT_CatalystConnectBPLibrary_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UCatalystConnectBPLibrary ************************************************
#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_CatalystConnectBPLibrary_h_31_RPC_WRAPPERS \
	DECLARE_FUNCTION(execCatalystConnectSampleFunction);


CATALYSTCONNECT_API UClass* Z_Construct_UClass_UCatalystConnectBPLibrary_NoRegister();

#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_CatalystConnectBPLibrary_h_31_INCLASS \
private: \
	static void StaticRegisterNativesUCatalystConnectBPLibrary(); \
	friend struct Z_Construct_UClass_UCatalystConnectBPLibrary_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend CATALYSTCONNECT_API UClass* Z_Construct_UClass_UCatalystConnectBPLibrary_NoRegister(); \
public: \
	DECLARE_CLASS2(UCatalystConnectBPLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/CatalystConnect"), Z_Construct_UClass_UCatalystConnectBPLibrary_NoRegister) \
	DECLARE_SERIALIZER(UCatalystConnectBPLibrary)


#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_CatalystConnectBPLibrary_h_31_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UCatalystConnectBPLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UCatalystConnectBPLibrary) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCatalystConnectBPLibrary); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCatalystConnectBPLibrary); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UCatalystConnectBPLibrary(UCatalystConnectBPLibrary&&) = delete; \
	UCatalystConnectBPLibrary(const UCatalystConnectBPLibrary&) = delete; \
	NO_API virtual ~UCatalystConnectBPLibrary();


#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_CatalystConnectBPLibrary_h_28_PROLOG
#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_CatalystConnectBPLibrary_h_31_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_CatalystConnectBPLibrary_h_31_RPC_WRAPPERS \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_CatalystConnectBPLibrary_h_31_INCLASS \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_CatalystConnectBPLibrary_h_31_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UCatalystConnectBPLibrary;

// ********** End Class UCatalystConnectBPLibrary **************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_CatalystConnectBPLibrary_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
