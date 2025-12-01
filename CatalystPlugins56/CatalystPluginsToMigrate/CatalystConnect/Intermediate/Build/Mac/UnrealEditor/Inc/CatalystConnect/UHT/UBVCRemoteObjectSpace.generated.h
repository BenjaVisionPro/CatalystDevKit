// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Runtime/UBVCRemoteObjectSpace.h"

#ifdef CATALYSTCONNECT_UBVCRemoteObjectSpace_generated_h
#error "UBVCRemoteObjectSpace.generated.h already included, missing '#pragma once' in UBVCRemoteObjectSpace.h"
#endif
#define CATALYSTCONNECT_UBVCRemoteObjectSpace_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

struct FBVCSubscriptionHandle;

// ********** Begin Class UBVCRemoteObjectSpace ****************************************************
#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCRemoteObjectSpace_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execUnsubscribe); \
	DECLARE_FUNCTION(execSubscribe);


CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCRemoteObjectSpace_NoRegister();

#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCRemoteObjectSpace_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUBVCRemoteObjectSpace(); \
	friend struct Z_Construct_UClass_UBVCRemoteObjectSpace_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCRemoteObjectSpace_NoRegister(); \
public: \
	DECLARE_CLASS2(UBVCRemoteObjectSpace, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/CatalystConnect"), Z_Construct_UClass_UBVCRemoteObjectSpace_NoRegister) \
	DECLARE_SERIALIZER(UBVCRemoteObjectSpace)


#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCRemoteObjectSpace_h_16_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UBVCRemoteObjectSpace(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UBVCRemoteObjectSpace(UBVCRemoteObjectSpace&&) = delete; \
	UBVCRemoteObjectSpace(const UBVCRemoteObjectSpace&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBVCRemoteObjectSpace); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBVCRemoteObjectSpace); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBVCRemoteObjectSpace) \
	NO_API virtual ~UBVCRemoteObjectSpace();


#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCRemoteObjectSpace_h_13_PROLOG
#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCRemoteObjectSpace_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCRemoteObjectSpace_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCRemoteObjectSpace_h_16_INCLASS_NO_PURE_DECLS \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCRemoteObjectSpace_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UBVCRemoteObjectSpace;

// ********** End Class UBVCRemoteObjectSpace ******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCRemoteObjectSpace_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
