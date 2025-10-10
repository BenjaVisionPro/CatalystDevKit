// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "DataConfig/DcTypes.h"

#ifdef DATACONFIGCORE_DcTypes_generated_h
#error "DcTypes.generated.h already included, missing '#pragma once' in DcTypes.h"
#endif
#define DATACONFIGCORE_DcTypes_generated_h

#include "Templates/IsUEnumClass.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_DataConfigCore_Public_DataConfig_DcTypes_h

// ********** Begin Enum EDcDataEntry **************************************************************
#define FOREACH_ENUM_EDCDATAENTRY(op) \
	op(EDcDataEntry::None) \
	op(EDcDataEntry::Bool) \
	op(EDcDataEntry::Name) \
	op(EDcDataEntry::String) \
	op(EDcDataEntry::Text) \
	op(EDcDataEntry::Enum) \
	op(EDcDataEntry::Float) \
	op(EDcDataEntry::Double) \
	op(EDcDataEntry::Int8) \
	op(EDcDataEntry::Int16) \
	op(EDcDataEntry::Int32) \
	op(EDcDataEntry::Int64) \
	op(EDcDataEntry::UInt8) \
	op(EDcDataEntry::UInt16) \
	op(EDcDataEntry::UInt32) \
	op(EDcDataEntry::UInt64) \
	op(EDcDataEntry::StructRoot) \
	op(EDcDataEntry::StructEnd) \
	op(EDcDataEntry::ClassRoot) \
	op(EDcDataEntry::ClassEnd) \
	op(EDcDataEntry::MapRoot) \
	op(EDcDataEntry::MapEnd) \
	op(EDcDataEntry::ArrayRoot) \
	op(EDcDataEntry::ArrayEnd) \
	op(EDcDataEntry::SetRoot) \
	op(EDcDataEntry::SetEnd) \
	op(EDcDataEntry::OptionalRoot) \
	op(EDcDataEntry::OptionalEnd) \
	op(EDcDataEntry::ObjectReference) \
	op(EDcDataEntry::ClassReference) \
	op(EDcDataEntry::WeakObjectReference) \
	op(EDcDataEntry::LazyObjectReference) \
	op(EDcDataEntry::SoftObjectReference) \
	op(EDcDataEntry::SoftClassReference) \
	op(EDcDataEntry::InterfaceReference) \
	op(EDcDataEntry::Delegate) \
	op(EDcDataEntry::MulticastInlineDelegate) \
	op(EDcDataEntry::MulticastSparseDelegate) \
	op(EDcDataEntry::FieldPath) \
	op(EDcDataEntry::Blob) \
	op(EDcDataEntry::Extension) \
	op(EDcDataEntry::Ended) 

enum class EDcDataEntry : uint16;
template<> struct TIsUEnumClass<EDcDataEntry> { enum { Value = true }; };
template<> DATACONFIGCORE_API UEnum* StaticEnum<EDcDataEntry>();
// ********** End Enum EDcDataEntry ****************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
