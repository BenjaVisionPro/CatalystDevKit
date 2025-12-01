// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Runtime/UBVCRemoteObject.h"

#ifdef CATALYSTCONNECT_UBVCRemoteObject_generated_h
#error "UBVCRemoteObject.generated.h already included, missing '#pragma once' in UBVCRemoteObject.h"
#endif
#define CATALYSTCONNECT_UBVCRemoteObject_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

struct FGuid;

// ********** Begin Delegate FBVCPatched ***********************************************************
#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCRemoteObject_h_8_DELEGATE \
CATALYSTCONNECT_API void FBVCPatched_DelegateWrapper(const FMulticastScriptDelegate& BVCPatched, FGuid const& ObjectId);


// ********** End Delegate FBVCPatched *************************************************************

// ********** Begin Class UBVCRemoteObject *********************************************************
#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCRemoteObject_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execSetStringField); \
	DECLARE_FUNCTION(execGetStringField);


CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCRemoteObject_NoRegister();

#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCRemoteObject_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUBVCRemoteObject(); \
	friend struct Z_Construct_UClass_UBVCRemoteObject_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCRemoteObject_NoRegister(); \
public: \
	DECLARE_CLASS2(UBVCRemoteObject, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/CatalystConnect"), Z_Construct_UClass_UBVCRemoteObject_NoRegister) \
	DECLARE_SERIALIZER(UBVCRemoteObject)


#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCRemoteObject_h_13_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UBVCRemoteObject(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UBVCRemoteObject(UBVCRemoteObject&&) = delete; \
	UBVCRemoteObject(const UBVCRemoteObject&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBVCRemoteObject); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBVCRemoteObject); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBVCRemoteObject) \
	NO_API virtual ~UBVCRemoteObject();


#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCRemoteObject_h_10_PROLOG
#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCRemoteObject_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCRemoteObject_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCRemoteObject_h_13_INCLASS_NO_PURE_DECLS \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCRemoteObject_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UBVCRemoteObject;

// ********** End Class UBVCRemoteObject ***********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCRemoteObject_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
