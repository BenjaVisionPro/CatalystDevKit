// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Connection/UBVCConnection.h"

#ifdef CATALYSTCONNECT_UBVCConnection_generated_h
#error "UBVCConnection.generated.h already included, missing '#pragma once' in UBVCConnection.h"
#endif
#define CATALYSTCONNECT_UBVCConnection_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

struct FBVCConnectionConfig;

// ********** Begin Class UBVCConnection ***********************************************************
#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Connection_UBVCConnection_h_32_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execSend); \
	DECLARE_FUNCTION(execIsConnected); \
	DECLARE_FUNCTION(execDisconnect); \
	DECLARE_FUNCTION(execConnect); \
	DECLARE_FUNCTION(execInitializeConnection);


CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCConnection_NoRegister();

#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Connection_UBVCConnection_h_32_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUBVCConnection(); \
	friend struct Z_Construct_UClass_UBVCConnection_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCConnection_NoRegister(); \
public: \
	DECLARE_CLASS2(UBVCConnection, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/CatalystConnect"), Z_Construct_UClass_UBVCConnection_NoRegister) \
	DECLARE_SERIALIZER(UBVCConnection)


#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Connection_UBVCConnection_h_32_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UBVCConnection(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UBVCConnection(UBVCConnection&&) = delete; \
	UBVCConnection(const UBVCConnection&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBVCConnection); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBVCConnection); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBVCConnection) \
	NO_API virtual ~UBVCConnection();


#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Connection_UBVCConnection_h_29_PROLOG
#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Connection_UBVCConnection_h_32_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Connection_UBVCConnection_h_32_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Connection_UBVCConnection_h_32_INCLASS_NO_PURE_DECLS \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Connection_UBVCConnection_h_32_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UBVCConnection;

// ********** End Class UBVCConnection *************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Connection_UBVCConnection_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
