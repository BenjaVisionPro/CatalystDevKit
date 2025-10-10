// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Schema/UBVCSchemaRegistry.h"

#ifdef CATALYSTCONNECT_UBVCSchemaRegistry_generated_h
#error "UBVCSchemaRegistry.generated.h already included, missing '#pragma once' in UBVCSchemaRegistry.h"
#endif
#define CATALYSTCONNECT_UBVCSchemaRegistry_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

struct FBVCMADescription;
struct FBVCMADescriptionContainer;

// ********** Begin Class UBVCSchemaRegistry *******************************************************
#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_UBVCSchemaRegistry_h_10_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execResolveUObjectTypeName); \
	DECLARE_FUNCTION(execSetProjectPrefix); \
	DECLARE_FUNCTION(execFindByName); \
	DECLARE_FUNCTION(execRegisterCatalog);


CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCSchemaRegistry_NoRegister();

#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_UBVCSchemaRegistry_h_10_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUBVCSchemaRegistry(); \
	friend struct Z_Construct_UClass_UBVCSchemaRegistry_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCSchemaRegistry_NoRegister(); \
public: \
	DECLARE_CLASS2(UBVCSchemaRegistry, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/CatalystConnect"), Z_Construct_UClass_UBVCSchemaRegistry_NoRegister) \
	DECLARE_SERIALIZER(UBVCSchemaRegistry)


#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_UBVCSchemaRegistry_h_10_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UBVCSchemaRegistry(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UBVCSchemaRegistry(UBVCSchemaRegistry&&) = delete; \
	UBVCSchemaRegistry(const UBVCSchemaRegistry&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBVCSchemaRegistry); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBVCSchemaRegistry); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBVCSchemaRegistry) \
	NO_API virtual ~UBVCSchemaRegistry();


#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_UBVCSchemaRegistry_h_7_PROLOG
#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_UBVCSchemaRegistry_h_10_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_UBVCSchemaRegistry_h_10_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_UBVCSchemaRegistry_h_10_INCLASS_NO_PURE_DECLS \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_UBVCSchemaRegistry_h_10_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UBVCSchemaRegistry;

// ********** End Class UBVCSchemaRegistry *********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_UBVCSchemaRegistry_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
