// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Schema/FBVCMAValidatorSpec.h"

#ifdef CATALYSTCONNECT_FBVCMAValidatorSpec_generated_h
#error "FBVCMAValidatorSpec.generated.h already included, missing '#pragma once' in FBVCMAValidatorSpec.h"
#endif
#define CATALYSTCONNECT_FBVCMAValidatorSpec_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin ScriptStruct FBVCMAValidatorSpec ***********************************************
#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_FBVCMAValidatorSpec_h_14_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FBVCMAValidatorSpec_Statics; \
	static class UScriptStruct* StaticStruct();


struct FBVCMAValidatorSpec;
// ********** End ScriptStruct FBVCMAValidatorSpec *************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Schema_FBVCMAValidatorSpec_h

// ********** Begin Enum EBVCMAValidatorType *******************************************************
#define FOREACH_ENUM_EBVCMAVALIDATORTYPE(op) \
	op(EBVCMAValidatorType::Required) \
	op(EBVCMAValidatorType::Length) \
	op(EBVCMAValidatorType::Range) \
	op(EBVCMAValidatorType::Regex) \
	op(EBVCMAValidatorType::Enumeration) \
	op(EBVCMAValidatorType::CrossField) \
	op(EBVCMAValidatorType::UniqueInArray) \
	op(EBVCMAValidatorType::CustomRef) 

enum class EBVCMAValidatorType : uint8;
template<> struct TIsUEnumClass<EBVCMAValidatorType> { enum { Value = true }; };
template<> CATALYSTCONNECT_API UEnum* StaticEnum<EBVCMAValidatorType>();
// ********** End Enum EBVCMAValidatorType *********************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
