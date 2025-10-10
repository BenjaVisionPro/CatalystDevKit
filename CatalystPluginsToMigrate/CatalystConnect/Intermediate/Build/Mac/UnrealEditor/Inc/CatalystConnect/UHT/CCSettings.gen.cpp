// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Core/CCSettings.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeCCSettings() {}

// ********** Begin Cross Module References ********************************************************
CATALYSTCONNECT_API UClass* Z_Construct_UClass_UCCEditorSettings();
CATALYSTCONNECT_API UClass* Z_Construct_UClass_UCCEditorSettings_NoRegister();
CATALYSTCONNECT_API UClass* Z_Construct_UClass_UCCSettings();
CATALYSTCONNECT_API UClass* Z_Construct_UClass_UCCSettings_NoRegister();
CATALYSTCONNECT_API UEnum* Z_Construct_UEnum_CatalystConnect_ECCDiscoveryServerType();
CATALYSTCONNECT_API UScriptStruct* Z_Construct_UScriptStruct_FCCServerSettings();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FDirectoryPath();
UPackage* Z_Construct_UPackage__Script_CatalystConnect();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum ECCDiscoveryServerType ****************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_ECCDiscoveryServerType;
static UEnum* ECCDiscoveryServerType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_ECCDiscoveryServerType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_ECCDiscoveryServerType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_CatalystConnect_ECCDiscoveryServerType, (UObject*)Z_Construct_UPackage__Script_CatalystConnect(), TEXT("ECCDiscoveryServerType"));
	}
	return Z_Registration_Info_UEnum_ECCDiscoveryServerType.OuterSingleton;
}
template<> CATALYSTCONNECT_API UEnum* StaticEnum<ECCDiscoveryServerType>()
{
	return ECCDiscoveryServerType_StaticEnum();
}
struct Z_Construct_UEnum_CatalystConnect_ECCDiscoveryServerType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Category", "CatalystConnect" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Atlas texture size must be power of 2 */" },
#endif
		{ "ModuleRelativePath", "Public/Core/CCSettings.h" },
		{ "SERVER_DEVELOPMENT.DisplayName", "Development" },
		{ "SERVER_DEVELOPMENT.Name", "ECCDiscoveryServerType::SERVER_DEVELOPMENT" },
		{ "SERVER_PRODUCTION.DisplayName", "Production" },
		{ "SERVER_PRODUCTION.Name", "ECCDiscoveryServerType::SERVER_PRODUCTION" },
		{ "SERVER_TESTING.DisplayName", "Testing" },
		{ "SERVER_TESTING.Name", "ECCDiscoveryServerType::SERVER_TESTING" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Atlas texture size must be power of 2" },
#endif
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ECCDiscoveryServerType::SERVER_DEVELOPMENT", (int64)ECCDiscoveryServerType::SERVER_DEVELOPMENT },
		{ "ECCDiscoveryServerType::SERVER_TESTING", (int64)ECCDiscoveryServerType::SERVER_TESTING },
		{ "ECCDiscoveryServerType::SERVER_PRODUCTION", (int64)ECCDiscoveryServerType::SERVER_PRODUCTION },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_CatalystConnect_ECCDiscoveryServerType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_CatalystConnect,
	nullptr,
	"ECCDiscoveryServerType",
	"ECCDiscoveryServerType",
	Z_Construct_UEnum_CatalystConnect_ECCDiscoveryServerType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_CatalystConnect_ECCDiscoveryServerType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_CatalystConnect_ECCDiscoveryServerType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_CatalystConnect_ECCDiscoveryServerType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_CatalystConnect_ECCDiscoveryServerType()
{
	if (!Z_Registration_Info_UEnum_ECCDiscoveryServerType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ECCDiscoveryServerType.InnerSingleton, Z_Construct_UEnum_CatalystConnect_ECCDiscoveryServerType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_ECCDiscoveryServerType.InnerSingleton;
}
// ********** End Enum ECCDiscoveryServerType ******************************************************

// ********** Begin ScriptStruct FCCServerSettings *************************************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FCCServerSettings;
class UScriptStruct* FCCServerSettings::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FCCServerSettings.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FCCServerSettings.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FCCServerSettings, (UObject*)Z_Construct_UPackage__Script_CatalystConnect(), TEXT("CCServerSettings"));
	}
	return Z_Registration_Info_UScriptStruct_FCCServerSettings.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FCCServerSettings_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Core/CCSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_serverName_MetaData[] = {
		{ "Category", "Server" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Server Name\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Core/CCSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Server Name" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_serverType_MetaData[] = {
		{ "Category", "Server" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Server Type */" },
#endif
		{ "ModuleRelativePath", "Public/Core/CCSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Server Type" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_serverAddress_MetaData[] = {
		{ "Category", "Server" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Server Address */" },
#endif
		{ "ModuleRelativePath", "Public/Core/CCSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Server Address" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bConnectOnStartup_MetaData[] = {
		{ "Category", "Server" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Connect to server on startup */" },
#endif
		{ "ModuleRelativePath", "Public/Core/CCSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Connect to server on startup" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_serverName;
	static const UECodeGen_Private::FBytePropertyParams NewProp_serverType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_serverType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_serverAddress;
	static void NewProp_bConnectOnStartup_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bConnectOnStartup;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FCCServerSettings>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FCCServerSettings_Statics::NewProp_serverName = { "serverName", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FCCServerSettings, serverName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_serverName_MetaData), NewProp_serverName_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FCCServerSettings_Statics::NewProp_serverType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FCCServerSettings_Statics::NewProp_serverType = { "serverType", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FCCServerSettings, serverType), Z_Construct_UEnum_CatalystConnect_ECCDiscoveryServerType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_serverType_MetaData), NewProp_serverType_MetaData) }; // 2972329256
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FCCServerSettings_Statics::NewProp_serverAddress = { "serverAddress", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FCCServerSettings, serverAddress), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_serverAddress_MetaData), NewProp_serverAddress_MetaData) };
void Z_Construct_UScriptStruct_FCCServerSettings_Statics::NewProp_bConnectOnStartup_SetBit(void* Obj)
{
	((FCCServerSettings*)Obj)->bConnectOnStartup = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FCCServerSettings_Statics::NewProp_bConnectOnStartup = { "bConnectOnStartup", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FCCServerSettings), &Z_Construct_UScriptStruct_FCCServerSettings_Statics::NewProp_bConnectOnStartup_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bConnectOnStartup_MetaData), NewProp_bConnectOnStartup_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FCCServerSettings_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCCServerSettings_Statics::NewProp_serverName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCCServerSettings_Statics::NewProp_serverType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCCServerSettings_Statics::NewProp_serverType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCCServerSettings_Statics::NewProp_serverAddress,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCCServerSettings_Statics::NewProp_bConnectOnStartup,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCCServerSettings_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FCCServerSettings_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_CatalystConnect,
	nullptr,
	&NewStructOps,
	"CCServerSettings",
	Z_Construct_UScriptStruct_FCCServerSettings_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCCServerSettings_Statics::PropPointers),
	sizeof(FCCServerSettings),
	alignof(FCCServerSettings),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCCServerSettings_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FCCServerSettings_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FCCServerSettings()
{
	if (!Z_Registration_Info_UScriptStruct_FCCServerSettings.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FCCServerSettings.InnerSingleton, Z_Construct_UScriptStruct_FCCServerSettings_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FCCServerSettings.InnerSingleton;
}
// ********** End ScriptStruct FCCServerSettings ***************************************************

// ********** Begin Class UCCSettings **************************************************************
void UCCSettings::StaticRegisterNativesUCCSettings()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UCCSettings;
UClass* UCCSettings::GetPrivateStaticClass()
{
	using TClass = UCCSettings;
	if (!Z_Registration_Info_UClass_UCCSettings.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("CCSettings"),
			Z_Registration_Info_UClass_UCCSettings.InnerSingleton,
			StaticRegisterNativesUCCSettings,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UCCSettings.InnerSingleton;
}
UClass* Z_Construct_UClass_UCCSettings_NoRegister()
{
	return UCCSettings::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UCCSettings_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Catalyst:Connect Settings\n" },
#endif
		{ "IncludePath", "Core/CCSettings.h" },
		{ "ModuleRelativePath", "Public/Core/CCSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Catalyst:Connect Settings" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAutomaticallyNegotiateKeys_MetaData[] = {
		{ "Category", "Security" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Automatic Key Negotiation\n" },
#endif
		{ "ModuleRelativePath", "Public/Core/CCSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Automatic Key Negotiation" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_pathToKeyFiles_MetaData[] = {
		{ "Category", "Security" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Path to key files for container secrets support\n" },
#endif
		{ "ModuleRelativePath", "Public/Core/CCSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Path to key files for container secrets support" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_servers_MetaData[] = {
		{ "Category", "DiscoveryServers" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Known DiscoveryServers\n" },
#endif
		{ "LongPackageName", "" },
		{ "ModuleRelativePath", "Public/Core/CCSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Known DiscoveryServers" },
#endif
	};
#endif // WITH_METADATA
	static void NewProp_bAutomaticallyNegotiateKeys_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAutomaticallyNegotiateKeys;
	static const UECodeGen_Private::FStructPropertyParams NewProp_pathToKeyFiles;
	static const UECodeGen_Private::FStructPropertyParams NewProp_servers_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_servers;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCCSettings>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
void Z_Construct_UClass_UCCSettings_Statics::NewProp_bAutomaticallyNegotiateKeys_SetBit(void* Obj)
{
	((UCCSettings*)Obj)->bAutomaticallyNegotiateKeys = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UCCSettings_Statics::NewProp_bAutomaticallyNegotiateKeys = { "bAutomaticallyNegotiateKeys", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UCCSettings), &Z_Construct_UClass_UCCSettings_Statics::NewProp_bAutomaticallyNegotiateKeys_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAutomaticallyNegotiateKeys_MetaData), NewProp_bAutomaticallyNegotiateKeys_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCCSettings_Statics::NewProp_pathToKeyFiles = { "pathToKeyFiles", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCCSettings, pathToKeyFiles), Z_Construct_UScriptStruct_FDirectoryPath, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_pathToKeyFiles_MetaData), NewProp_pathToKeyFiles_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCCSettings_Statics::NewProp_servers_Inner = { "servers", nullptr, (EPropertyFlags)0x0000000000004000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FCCServerSettings, METADATA_PARAMS(0, nullptr) }; // 1003852638
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UCCSettings_Statics::NewProp_servers = { "servers", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCCSettings, servers), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_servers_MetaData), NewProp_servers_MetaData) }; // 1003852638
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCCSettings_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCCSettings_Statics::NewProp_bAutomaticallyNegotiateKeys,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCCSettings_Statics::NewProp_pathToKeyFiles,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCCSettings_Statics::NewProp_servers_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCCSettings_Statics::NewProp_servers,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCCSettings_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UCCSettings_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_CatalystConnect,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCCSettings_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UCCSettings_Statics::ClassParams = {
	&UCCSettings::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UCCSettings_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UCCSettings_Statics::PropPointers),
	0,
	0x001000A6u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCCSettings_Statics::Class_MetaDataParams), Z_Construct_UClass_UCCSettings_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UCCSettings()
{
	if (!Z_Registration_Info_UClass_UCCSettings.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCCSettings.OuterSingleton, Z_Construct_UClass_UCCSettings_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UCCSettings.OuterSingleton;
}
UCCSettings::UCCSettings(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UCCSettings);
UCCSettings::~UCCSettings() {}
// ********** End Class UCCSettings ****************************************************************

// ********** Begin Class UCCEditorSettings ********************************************************
void UCCEditorSettings::StaticRegisterNativesUCCEditorSettings()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UCCEditorSettings;
UClass* UCCEditorSettings::GetPrivateStaticClass()
{
	using TClass = UCCEditorSettings;
	if (!Z_Registration_Info_UClass_UCCEditorSettings.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("CCEditorSettings"),
			Z_Registration_Info_UClass_UCCEditorSettings.InnerSingleton,
			StaticRegisterNativesUCCEditorSettings,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UCCEditorSettings.InnerSingleton;
}
UClass* Z_Construct_UClass_UCCEditorSettings_NoRegister()
{
	return UCCEditorSettings::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UCCEditorSettings_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Catalyst:Connect Editor Settings @todo:save config in editor\n" },
#endif
		{ "IncludePath", "Core/CCSettings.h" },
		{ "ModuleRelativePath", "Public/Core/CCSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Catalyst:Connect Editor Settings @todo:save config in editor" },
#endif
	};
#if WITH_EDITORONLY_DATA
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bConnectDiscoveryServersOnStartup_MetaData[] = {
		{ "Category", "DiscoveryServers" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Connect to Development Server on Startup\n" },
#endif
		{ "ModuleRelativePath", "Public/Core/CCSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Connect to Development Server on Startup" },
#endif
	};
#endif // WITH_EDITORONLY_DATA
#endif // WITH_METADATA
#if WITH_EDITORONLY_DATA
	static void NewProp_bConnectDiscoveryServersOnStartup_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bConnectDiscoveryServersOnStartup;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#endif // WITH_EDITORONLY_DATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCCEditorSettings>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
#if WITH_EDITORONLY_DATA
void Z_Construct_UClass_UCCEditorSettings_Statics::NewProp_bConnectDiscoveryServersOnStartup_SetBit(void* Obj)
{
	((UCCEditorSettings*)Obj)->bConnectDiscoveryServersOnStartup = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UCCEditorSettings_Statics::NewProp_bConnectDiscoveryServersOnStartup = { "bConnectDiscoveryServersOnStartup", nullptr, (EPropertyFlags)0x0010000800004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UCCEditorSettings), &Z_Construct_UClass_UCCEditorSettings_Statics::NewProp_bConnectDiscoveryServersOnStartup_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bConnectDiscoveryServersOnStartup_MetaData), NewProp_bConnectDiscoveryServersOnStartup_MetaData) };
#endif // WITH_EDITORONLY_DATA
#if WITH_EDITORONLY_DATA
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCCEditorSettings_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCCEditorSettings_Statics::NewProp_bConnectDiscoveryServersOnStartup,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCCEditorSettings_Statics::PropPointers) < 2048);
#endif // WITH_EDITORONLY_DATA
UObject* (*const Z_Construct_UClass_UCCEditorSettings_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_CatalystConnect,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCCEditorSettings_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UCCEditorSettings_Statics::ClassParams = {
	&UCCEditorSettings::StaticClass,
	"Editor",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	IF_WITH_EDITORONLY_DATA(Z_Construct_UClass_UCCEditorSettings_Statics::PropPointers, nullptr),
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	IF_WITH_EDITORONLY_DATA(UE_ARRAY_COUNT(Z_Construct_UClass_UCCEditorSettings_Statics::PropPointers), 0),
	0,
	0x001000A6u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCCEditorSettings_Statics::Class_MetaDataParams), Z_Construct_UClass_UCCEditorSettings_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UCCEditorSettings()
{
	if (!Z_Registration_Info_UClass_UCCEditorSettings.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCCEditorSettings.OuterSingleton, Z_Construct_UClass_UCCEditorSettings_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UCCEditorSettings.OuterSingleton;
}
UCCEditorSettings::UCCEditorSettings(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UCCEditorSettings);
UCCEditorSettings::~UCCEditorSettings() {}
// ********** End Class UCCEditorSettings **********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_CCSettings_h__Script_CatalystConnect_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ ECCDiscoveryServerType_StaticEnum, TEXT("ECCDiscoveryServerType"), &Z_Registration_Info_UEnum_ECCDiscoveryServerType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2972329256U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FCCServerSettings::StaticStruct, Z_Construct_UScriptStruct_FCCServerSettings_Statics::NewStructOps, TEXT("CCServerSettings"), &Z_Registration_Info_UScriptStruct_FCCServerSettings, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FCCServerSettings), 1003852638U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UCCSettings, UCCSettings::StaticClass, TEXT("UCCSettings"), &Z_Registration_Info_UClass_UCCSettings, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCCSettings), 1974097564U) },
		{ Z_Construct_UClass_UCCEditorSettings, UCCEditorSettings::StaticClass, TEXT("UCCEditorSettings"), &Z_Registration_Info_UClass_UCCEditorSettings, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCCEditorSettings), 94812651U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_CCSettings_h__Script_CatalystConnect_3632306352(TEXT("/Script/CatalystConnect"),
	Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_CCSettings_h__Script_CatalystConnect_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_CCSettings_h__Script_CatalystConnect_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_CCSettings_h__Script_CatalystConnect_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_CCSettings_h__Script_CatalystConnect_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_CCSettings_h__Script_CatalystConnect_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_CCSettings_h__Script_CatalystConnect_Statics::EnumInfo));
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
