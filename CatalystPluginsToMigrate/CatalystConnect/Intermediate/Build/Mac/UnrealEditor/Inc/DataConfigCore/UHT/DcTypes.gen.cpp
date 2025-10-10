// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DataConfig/DcTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeDcTypes() {}

// ********** Begin Cross Module References ********************************************************
DATACONFIGCORE_API UEnum* Z_Construct_UEnum_DataConfigCore_EDcDataEntry();
UPackage* Z_Construct_UPackage__Script_DataConfigCore();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum EDcDataEntry **************************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EDcDataEntry;
static UEnum* EDcDataEntry_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EDcDataEntry.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EDcDataEntry.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_DataConfigCore_EDcDataEntry, (UObject*)Z_Construct_UPackage__Script_DataConfigCore(), TEXT("EDcDataEntry"));
	}
	return Z_Registration_Info_UEnum_EDcDataEntry.OuterSingleton;
}
template<> DATACONFIGCORE_API UEnum* StaticEnum<EDcDataEntry>()
{
	return EDcDataEntry_StaticEnum();
}
struct Z_Construct_UEnum_DataConfigCore_EDcDataEntry_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "ArrayEnd.Name", "EDcDataEntry::ArrayEnd" },
		{ "ArrayRoot.Comment", "//\x09""Array\n" },
		{ "ArrayRoot.Name", "EDcDataEntry::ArrayRoot" },
		{ "ArrayRoot.ToolTip", "Array" },
		{ "Blob.Comment", "//\x09""Extra\n" },
		{ "Blob.Name", "EDcDataEntry::Blob" },
		{ "Blob.ToolTip", "Extra" },
		{ "Bool.Name", "EDcDataEntry::Bool" },
		{ "ClassEnd.Name", "EDcDataEntry::ClassEnd" },
		{ "ClassReference.Name", "EDcDataEntry::ClassReference" },
		{ "ClassRoot.Comment", "//\x09""Class\n" },
		{ "ClassRoot.Name", "EDcDataEntry::ClassRoot" },
		{ "ClassRoot.ToolTip", "Class" },
		{ "Delegate.Comment", "//\x09""Delegates\n" },
		{ "Delegate.Name", "EDcDataEntry::Delegate" },
		{ "Delegate.ToolTip", "Delegates" },
		{ "Double.Name", "EDcDataEntry::Double" },
		{ "Ended.Comment", "//\x09""End\n" },
		{ "Ended.Name", "EDcDataEntry::Ended" },
		{ "Ended.ToolTip", "End" },
		{ "Enum.Name", "EDcDataEntry::Enum" },
		{ "Extension.Comment", "//\x09""Extension\n" },
		{ "Extension.Name", "EDcDataEntry::Extension" },
		{ "Extension.ToolTip", "Extension" },
		{ "FieldPath.Comment", "//\x09""Field\n" },
		{ "FieldPath.Name", "EDcDataEntry::FieldPath" },
		{ "FieldPath.ToolTip", "Field" },
		{ "Float.Name", "EDcDataEntry::Float" },
		{ "Int16.Name", "EDcDataEntry::Int16" },
		{ "Int32.Name", "EDcDataEntry::Int32" },
		{ "Int64.Name", "EDcDataEntry::Int64" },
		{ "Int8.Name", "EDcDataEntry::Int8" },
		{ "InterfaceReference.Name", "EDcDataEntry::InterfaceReference" },
		{ "LazyObjectReference.Name", "EDcDataEntry::LazyObjectReference" },
		{ "MapEnd.Name", "EDcDataEntry::MapEnd" },
		{ "MapRoot.Comment", "//\x09Map\n" },
		{ "MapRoot.Name", "EDcDataEntry::MapRoot" },
		{ "MapRoot.ToolTip", "Map" },
		{ "ModuleRelativePath", "Public/DataConfig/DcTypes.h" },
		{ "MulticastInlineDelegate.Name", "EDcDataEntry::MulticastInlineDelegate" },
		{ "MulticastSparseDelegate.Name", "EDcDataEntry::MulticastSparseDelegate" },
		{ "Name.Name", "EDcDataEntry::Name" },
		{ "None.Name", "EDcDataEntry::None" },
		{ "ObjectReference.Comment", "//\x09Reference\n" },
		{ "ObjectReference.Name", "EDcDataEntry::ObjectReference" },
		{ "ObjectReference.ToolTip", "Reference" },
		{ "OptionalEnd.Name", "EDcDataEntry::OptionalEnd" },
		{ "OptionalRoot.Comment", "//\x09Optional\n" },
		{ "OptionalRoot.Name", "EDcDataEntry::OptionalRoot" },
		{ "OptionalRoot.ToolTip", "Optional" },
		{ "SetEnd.Name", "EDcDataEntry::SetEnd" },
		{ "SetRoot.Comment", "//\x09Set,\n" },
		{ "SetRoot.Name", "EDcDataEntry::SetRoot" },
		{ "SetRoot.ToolTip", "Set," },
		{ "SoftClassReference.Name", "EDcDataEntry::SoftClassReference" },
		{ "SoftObjectReference.Name", "EDcDataEntry::SoftObjectReference" },
		{ "String.Name", "EDcDataEntry::String" },
		{ "StructEnd.Name", "EDcDataEntry::StructEnd" },
		{ "StructRoot.Comment", "//\x09Struct\n" },
		{ "StructRoot.Name", "EDcDataEntry::StructRoot" },
		{ "StructRoot.ToolTip", "Struct" },
		{ "Text.Name", "EDcDataEntry::Text" },
		{ "UInt16.Name", "EDcDataEntry::UInt16" },
		{ "UInt32.Name", "EDcDataEntry::UInt32" },
		{ "UInt64.Name", "EDcDataEntry::UInt64" },
		{ "UInt8.Name", "EDcDataEntry::UInt8" },
		{ "WeakObjectReference.Name", "EDcDataEntry::WeakObjectReference" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EDcDataEntry::None", (int64)EDcDataEntry::None },
		{ "EDcDataEntry::Bool", (int64)EDcDataEntry::Bool },
		{ "EDcDataEntry::Name", (int64)EDcDataEntry::Name },
		{ "EDcDataEntry::String", (int64)EDcDataEntry::String },
		{ "EDcDataEntry::Text", (int64)EDcDataEntry::Text },
		{ "EDcDataEntry::Enum", (int64)EDcDataEntry::Enum },
		{ "EDcDataEntry::Float", (int64)EDcDataEntry::Float },
		{ "EDcDataEntry::Double", (int64)EDcDataEntry::Double },
		{ "EDcDataEntry::Int8", (int64)EDcDataEntry::Int8 },
		{ "EDcDataEntry::Int16", (int64)EDcDataEntry::Int16 },
		{ "EDcDataEntry::Int32", (int64)EDcDataEntry::Int32 },
		{ "EDcDataEntry::Int64", (int64)EDcDataEntry::Int64 },
		{ "EDcDataEntry::UInt8", (int64)EDcDataEntry::UInt8 },
		{ "EDcDataEntry::UInt16", (int64)EDcDataEntry::UInt16 },
		{ "EDcDataEntry::UInt32", (int64)EDcDataEntry::UInt32 },
		{ "EDcDataEntry::UInt64", (int64)EDcDataEntry::UInt64 },
		{ "EDcDataEntry::StructRoot", (int64)EDcDataEntry::StructRoot },
		{ "EDcDataEntry::StructEnd", (int64)EDcDataEntry::StructEnd },
		{ "EDcDataEntry::ClassRoot", (int64)EDcDataEntry::ClassRoot },
		{ "EDcDataEntry::ClassEnd", (int64)EDcDataEntry::ClassEnd },
		{ "EDcDataEntry::MapRoot", (int64)EDcDataEntry::MapRoot },
		{ "EDcDataEntry::MapEnd", (int64)EDcDataEntry::MapEnd },
		{ "EDcDataEntry::ArrayRoot", (int64)EDcDataEntry::ArrayRoot },
		{ "EDcDataEntry::ArrayEnd", (int64)EDcDataEntry::ArrayEnd },
		{ "EDcDataEntry::SetRoot", (int64)EDcDataEntry::SetRoot },
		{ "EDcDataEntry::SetEnd", (int64)EDcDataEntry::SetEnd },
		{ "EDcDataEntry::OptionalRoot", (int64)EDcDataEntry::OptionalRoot },
		{ "EDcDataEntry::OptionalEnd", (int64)EDcDataEntry::OptionalEnd },
		{ "EDcDataEntry::ObjectReference", (int64)EDcDataEntry::ObjectReference },
		{ "EDcDataEntry::ClassReference", (int64)EDcDataEntry::ClassReference },
		{ "EDcDataEntry::WeakObjectReference", (int64)EDcDataEntry::WeakObjectReference },
		{ "EDcDataEntry::LazyObjectReference", (int64)EDcDataEntry::LazyObjectReference },
		{ "EDcDataEntry::SoftObjectReference", (int64)EDcDataEntry::SoftObjectReference },
		{ "EDcDataEntry::SoftClassReference", (int64)EDcDataEntry::SoftClassReference },
		{ "EDcDataEntry::InterfaceReference", (int64)EDcDataEntry::InterfaceReference },
		{ "EDcDataEntry::Delegate", (int64)EDcDataEntry::Delegate },
		{ "EDcDataEntry::MulticastInlineDelegate", (int64)EDcDataEntry::MulticastInlineDelegate },
		{ "EDcDataEntry::MulticastSparseDelegate", (int64)EDcDataEntry::MulticastSparseDelegate },
		{ "EDcDataEntry::FieldPath", (int64)EDcDataEntry::FieldPath },
		{ "EDcDataEntry::Blob", (int64)EDcDataEntry::Blob },
		{ "EDcDataEntry::Extension", (int64)EDcDataEntry::Extension },
		{ "EDcDataEntry::Ended", (int64)EDcDataEntry::Ended },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_DataConfigCore_EDcDataEntry_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_DataConfigCore,
	nullptr,
	"EDcDataEntry",
	"EDcDataEntry",
	Z_Construct_UEnum_DataConfigCore_EDcDataEntry_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_DataConfigCore_EDcDataEntry_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_DataConfigCore_EDcDataEntry_Statics::Enum_MetaDataParams), Z_Construct_UEnum_DataConfigCore_EDcDataEntry_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_DataConfigCore_EDcDataEntry()
{
	if (!Z_Registration_Info_UEnum_EDcDataEntry.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EDcDataEntry.InnerSingleton, Z_Construct_UEnum_DataConfigCore_EDcDataEntry_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EDcDataEntry.InnerSingleton;
}
// ********** End Enum EDcDataEntry ****************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_DataConfigCore_Public_DataConfig_DcTypes_h__Script_DataConfigCore_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EDcDataEntry_StaticEnum, TEXT("EDcDataEntry"), &Z_Registration_Info_UEnum_EDcDataEntry, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3999272434U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_DataConfigCore_Public_DataConfig_DcTypes_h__Script_DataConfigCore_3274430306(TEXT("/Script/DataConfigCore"),
	nullptr, 0,
	nullptr, 0,
	Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_DataConfigCore_Public_DataConfig_DcTypes_h__Script_DataConfigCore_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_DataConfigCore_Public_DataConfig_DcTypes_h__Script_DataConfigCore_Statics::EnumInfo));
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
