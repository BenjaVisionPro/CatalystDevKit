// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Runtime/UBVCOfflineStore.h"

#ifdef CATALYSTCONNECT_UBVCOfflineStore_generated_h
#error "UBVCOfflineStore.generated.h already included, missing '#pragma once' in UBVCOfflineStore.h"
#endif
#define CATALYSTCONNECT_UBVCOfflineStore_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Interface UBVCOfflineStore *****************************************************
CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCOfflineStore_NoRegister();

#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCOfflineStore_h_9_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UBVCOfflineStore(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UBVCOfflineStore(UBVCOfflineStore&&) = delete; \
	UBVCOfflineStore(const UBVCOfflineStore&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBVCOfflineStore); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBVCOfflineStore); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBVCOfflineStore) \
	virtual ~UBVCOfflineStore() = default;


#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCOfflineStore_h_9_GENERATED_UINTERFACE_BODY() \
private: \
	static void StaticRegisterNativesUBVCOfflineStore(); \
	friend struct Z_Construct_UClass_UBVCOfflineStore_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend CATALYSTCONNECT_API UClass* Z_Construct_UClass_UBVCOfflineStore_NoRegister(); \
public: \
	DECLARE_CLASS2(UBVCOfflineStore, UInterface, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Interface), CASTCLASS_None, TEXT("/Script/CatalystConnect"), Z_Construct_UClass_UBVCOfflineStore_NoRegister) \
	DECLARE_SERIALIZER(UBVCOfflineStore)


#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCOfflineStore_h_9_GENERATED_BODY \
	PRAGMA_DISABLE_DEPRECATION_WARNINGS \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCOfflineStore_h_9_GENERATED_UINTERFACE_BODY() \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCOfflineStore_h_9_ENHANCED_CONSTRUCTORS \
private: \
	PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCOfflineStore_h_9_INCLASS_IINTERFACE_NO_PURE_DECLS \
protected: \
	virtual ~IBVCOfflineStore() {} \
public: \
	typedef UBVCOfflineStore UClassType; \
	typedef IBVCOfflineStore ThisClass; \
	virtual UObject* _getUObject() const { return nullptr; }


#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCOfflineStore_h_6_PROLOG
#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCOfflineStore_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCOfflineStore_h_9_INCLASS_IINTERFACE_NO_PURE_DECLS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UBVCOfflineStore;

// ********** End Interface UBVCOfflineStore *******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Runtime_UBVCOfflineStore_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
