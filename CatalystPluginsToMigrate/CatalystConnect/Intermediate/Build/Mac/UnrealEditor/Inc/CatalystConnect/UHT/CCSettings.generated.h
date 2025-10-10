// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Core/CCSettings.h"

#ifdef CATALYSTCONNECT_CCSettings_generated_h
#error "CCSettings.generated.h already included, missing '#pragma once' in CCSettings.h"
#endif
#define CATALYSTCONNECT_CCSettings_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin ScriptStruct FCCServerSettings *************************************************
#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_CCSettings_h_27_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FCCServerSettings_Statics; \
	static class UScriptStruct* StaticStruct();


struct FCCServerSettings;
// ********** End ScriptStruct FCCServerSettings ***************************************************

// ********** Begin Class UCCSettings **************************************************************
CATALYSTCONNECT_API UClass* Z_Construct_UClass_UCCSettings_NoRegister();

#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_CCSettings_h_54_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUCCSettings(); \
	friend struct Z_Construct_UClass_UCCSettings_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend CATALYSTCONNECT_API UClass* Z_Construct_UClass_UCCSettings_NoRegister(); \
public: \
	DECLARE_CLASS2(UCCSettings, UObject, COMPILED_IN_FLAGS(0 | CLASS_DefaultConfig | CLASS_Config), CASTCLASS_None, TEXT("/Script/CatalystConnect"), Z_Construct_UClass_UCCSettings_NoRegister) \
	DECLARE_SERIALIZER(UCCSettings) \
	static const TCHAR* StaticConfigName() {return TEXT("Engine");} \



#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_CCSettings_h_54_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UCCSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UCCSettings(UCCSettings&&) = delete; \
	UCCSettings(const UCCSettings&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCCSettings); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCCSettings); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UCCSettings) \
	NO_API virtual ~UCCSettings();


#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_CCSettings_h_51_PROLOG
#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_CCSettings_h_54_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_CCSettings_h_54_INCLASS_NO_PURE_DECLS \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_CCSettings_h_54_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UCCSettings;

// ********** End Class UCCSettings ****************************************************************

// ********** Begin Class UCCEditorSettings ********************************************************
CATALYSTCONNECT_API UClass* Z_Construct_UClass_UCCEditorSettings_NoRegister();

#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_CCSettings_h_82_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUCCEditorSettings(); \
	friend struct Z_Construct_UClass_UCCEditorSettings_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend CATALYSTCONNECT_API UClass* Z_Construct_UClass_UCCEditorSettings_NoRegister(); \
public: \
	DECLARE_CLASS2(UCCEditorSettings, UObject, COMPILED_IN_FLAGS(0 | CLASS_DefaultConfig | CLASS_Config), CASTCLASS_None, TEXT("/Script/CatalystConnect"), Z_Construct_UClass_UCCEditorSettings_NoRegister) \
	DECLARE_SERIALIZER(UCCEditorSettings) \
	static const TCHAR* StaticConfigName() {return TEXT("Editor");} \



#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_CCSettings_h_82_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UCCEditorSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UCCEditorSettings(UCCEditorSettings&&) = delete; \
	UCCEditorSettings(const UCCEditorSettings&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCCEditorSettings); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCCEditorSettings); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UCCEditorSettings) \
	NO_API virtual ~UCCEditorSettings();


#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_CCSettings_h_79_PROLOG
#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_CCSettings_h_82_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_CCSettings_h_82_INCLASS_NO_PURE_DECLS \
	FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_CCSettings_h_82_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UCCEditorSettings;

// ********** End Class UCCEditorSettings **********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_CCSettings_h

// ********** Begin Enum ECCDiscoveryServerType ****************************************************
#define FOREACH_ENUM_ECCDISCOVERYSERVERTYPE(op) \
	op(ECCDiscoveryServerType::SERVER_DEVELOPMENT) \
	op(ECCDiscoveryServerType::SERVER_TESTING) \
	op(ECCDiscoveryServerType::SERVER_PRODUCTION) 

enum class ECCDiscoveryServerType : uint8;
template<> struct TIsUEnumClass<ECCDiscoveryServerType> { enum { Value = true }; };
template<> CATALYSTCONNECT_API UEnum* StaticEnum<ECCDiscoveryServerType>();
// ********** End Enum ECCDiscoveryServerType ******************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
