// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "SubSystem/CCSubsystem.h"

#ifdef CATALYSTCONNECT_CCSubsystem_generated_h
#error "CCSubsystem.generated.h already included, missing '#pragma once' in CCSubsystem.h"
#endif
#define CATALYSTCONNECT_CCSubsystem_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class UBVCConnection;
class UCCSubsystem;
class UObject;
struct FBVCConnectionConfig;

// ********** Begin Class UCCSubsystem *************************************************************
#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_SubSystem_CCSubsystem_h_27_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execCreateConnection); \
	DECLARE_FUNCTION(execGet);


CATALYSTCONNECT_API UClass* Z_Construct_UClass_UCCSubsystem_NoRegister();

#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_SubSystem_CCSubsystem_h_27_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUCCSubsystem(); \
	friend struct Z_Construct_UClass_UCCSubsystem_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend CATALYSTCONNECT_API UClass* Z_Construct_UClass_UCCSubsystem_NoRegister(); \
public: \
	DECLARE_CLASS2(UCCSubsystem, UGameInstanceSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/CatalystConnect"), Z_Construct_UClass_UCCSubsystem_NoRegister) \
	DECLARE_SERIALIZER(UCCSubsystem)


#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_SubSystem_CCSubsystem_h_27_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UCCSubsystem(); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UCCSubsystem(UCCSubsystem&&) = delete; \
	UCCSubsystem(const UCCSubsystem&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCCSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCCSubsystem); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UCCSubsystem) \
	NO_API virtual ~UCCSubsystem();


#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_SubSystem_CCSubsystem_h_24_PROLOG
#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_SubSystem_CCSubsystem_h_27_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_SubSystem_CCSubsystem_h_27_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_SubSystem_CCSubsystem_h_27_INCLASS_NO_PURE_DECLS \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_SubSystem_CCSubsystem_h_27_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UCCSubsystem;

// ********** End Class UCCSubsystem ***************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_SubSystem_CCSubsystem_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
