// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Core/BVCValue.h"

#ifdef CATALYSTCONNECT_BVCValue_generated_h
#error "BVCValue.generated.h already included, missing '#pragma once' in BVCValue.h"
#endif
#define CATALYSTCONNECT_BVCValue_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin ScriptStruct FBVCValue *********************************************************
#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_BVCValue_h_14_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FBVCValue_Statics; \
	static class UScriptStruct* StaticStruct();


struct FBVCValue;
// ********** End ScriptStruct FBVCValue ***********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_BVCValue_h

// ********** Begin Enum EBVCValueType *************************************************************
#define FOREACH_ENUM_EBVCVALUETYPE(op) \
	op(EBVCValueType::None) \
	op(EBVCValueType::Bool) \
	op(EBVCValueType::Int32) \
	op(EBVCValueType::Int64) \
	op(EBVCValueType::Float) \
	op(EBVCValueType::Double) \
	op(EBVCValueType::String) \
	op(EBVCValueType::Name) \
	op(EBVCValueType::Guid) \
	op(EBVCValueType::ByteArray) \
	op(EBVCValueType::Array) \
	op(EBVCValueType::Map) \
	op(EBVCValueType::EnumString) 

enum class EBVCValueType : uint8;
template<> struct TIsUEnumClass<EBVCValueType> { enum { Value = true }; };
template<> CATALYSTCONNECT_API UEnum* StaticEnum<EBVCValueType>();
// ********** End Enum EBVCValueType ***************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
