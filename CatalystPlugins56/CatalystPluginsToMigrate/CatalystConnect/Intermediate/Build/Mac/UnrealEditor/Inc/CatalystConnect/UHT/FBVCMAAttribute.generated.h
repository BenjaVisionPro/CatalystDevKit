// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Schema/FBVCMAAttribute.h"

#ifdef CATALYSTCONNECT_FBVCMAAttribute_generated_h
#error "FBVCMAAttribute.generated.h already included, missing '#pragma once' in FBVCMAAttribute.h"
#endif
#define CATALYSTCONNECT_FBVCMAAttribute_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin ScriptStruct FBVCMAAttribute ***************************************************
#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_FBVCMAAttribute_h_12_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FBVCMAAttribute_Statics; \
	static class UScriptStruct* StaticStruct();


struct FBVCMAAttribute;
// ********** End ScriptStruct FBVCMAAttribute *****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_FBVCMAAttribute_h

// ********** Begin Enum EBVCMAKind ****************************************************************
#define FOREACH_ENUM_EBVCMAKIND(op) \
	op(EBVCMAKind::Scalar) \
	op(EBVCMAKind::ToOne) \
	op(EBVCMAKind::ToMany) \
	op(EBVCMAKind::Enum) \
	op(EBVCMAKind::Map) 

enum class EBVCMAKind : uint8;
template<> struct TIsUEnumClass<EBVCMAKind> { enum { Value = true }; };
template<> CATALYSTCONNECT_API UEnum* StaticEnum<EBVCMAKind>();
// ********** End Enum EBVCMAKind ******************************************************************

// ********** Begin Enum EBVCMAScalarType **********************************************************
#define FOREACH_ENUM_EBVCMASCALARTYPE(op) \
	op(EBVCMAScalarType::None) \
	op(EBVCMAScalarType::Bool) \
	op(EBVCMAScalarType::Int32) \
	op(EBVCMAScalarType::Int64) \
	op(EBVCMAScalarType::Float32) \
	op(EBVCMAScalarType::Float64) \
	op(EBVCMAScalarType::String) \
	op(EBVCMAScalarType::Name) \
	op(EBVCMAScalarType::Guid) \
	op(EBVCMAScalarType::ByteArray) \
	op(EBVCMAScalarType::DateTime) 

enum class EBVCMAScalarType : uint8;
template<> struct TIsUEnumClass<EBVCMAScalarType> { enum { Value = true }; };
template<> CATALYSTCONNECT_API UEnum* StaticEnum<EBVCMAScalarType>();
// ********** End Enum EBVCMAScalarType ************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
