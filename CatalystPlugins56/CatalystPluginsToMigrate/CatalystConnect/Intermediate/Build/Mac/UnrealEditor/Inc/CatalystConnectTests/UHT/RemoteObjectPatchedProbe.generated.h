// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Test/RemoteObjectPatchedProbe.h"

#ifdef CATALYSTCONNECTTESTS_RemoteObjectPatchedProbe_generated_h
#error "RemoteObjectPatchedProbe.generated.h already included, missing '#pragma once' in RemoteObjectPatchedProbe.h"
#endif
#define CATALYSTCONNECTTESTS_RemoteObjectPatchedProbe_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

struct FGuid;

// ********** Begin Class URemoteObjectPatchedProbe ************************************************
#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnectTests_Public_Test_RemoteObjectPatchedProbe_h_9_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnPatched);


CATALYSTCONNECTTESTS_API UClass* Z_Construct_UClass_URemoteObjectPatchedProbe_NoRegister();

#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnectTests_Public_Test_RemoteObjectPatchedProbe_h_9_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesURemoteObjectPatchedProbe(); \
	friend struct Z_Construct_UClass_URemoteObjectPatchedProbe_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend CATALYSTCONNECTTESTS_API UClass* Z_Construct_UClass_URemoteObjectPatchedProbe_NoRegister(); \
public: \
	DECLARE_CLASS2(URemoteObjectPatchedProbe, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/CatalystConnectTests"), Z_Construct_UClass_URemoteObjectPatchedProbe_NoRegister) \
	DECLARE_SERIALIZER(URemoteObjectPatchedProbe)


#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnectTests_Public_Test_RemoteObjectPatchedProbe_h_9_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API URemoteObjectPatchedProbe(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	URemoteObjectPatchedProbe(URemoteObjectPatchedProbe&&) = delete; \
	URemoteObjectPatchedProbe(const URemoteObjectPatchedProbe&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, URemoteObjectPatchedProbe); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(URemoteObjectPatchedProbe); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(URemoteObjectPatchedProbe) \
	NO_API virtual ~URemoteObjectPatchedProbe();


#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnectTests_Public_Test_RemoteObjectPatchedProbe_h_6_PROLOG
#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnectTests_Public_Test_RemoteObjectPatchedProbe_h_9_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnectTests_Public_Test_RemoteObjectPatchedProbe_h_9_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnectTests_Public_Test_RemoteObjectPatchedProbe_h_9_INCLASS_NO_PURE_DECLS \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnectTests_Public_Test_RemoteObjectPatchedProbe_h_9_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class URemoteObjectPatchedProbe;

// ********** End Class URemoteObjectPatchedProbe **************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnectTests_Public_Test_RemoteObjectPatchedProbe_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
