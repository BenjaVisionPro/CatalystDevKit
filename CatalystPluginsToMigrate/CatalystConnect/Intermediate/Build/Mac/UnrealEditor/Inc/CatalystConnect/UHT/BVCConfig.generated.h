// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Core/BVCConfig.h"

#ifdef CATALYSTCONNECT_BVCConfig_generated_h
#error "BVCConfig.generated.h already included, missing '#pragma once' in BVCConfig.h"
#endif
#define CATALYSTCONNECT_BVCConfig_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin ScriptStruct FBVCConfig ********************************************************
#define FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_BVCConfig_h_8_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FBVCConfig_Statics; \
	CATALYSTCONNECT_API static class UScriptStruct* StaticStruct();


struct FBVCConfig;
// ********** End ScriptStruct FBVCConfig **********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_opt_git_BenjaVision_CatalystDevKit_CatalystPlugins_Plugins_CatalystConnect_Source_CatalystConnect_Public_Core_BVCConfig_h

// ********** Begin Enum EBVCQoS *******************************************************************
#define FOREACH_ENUM_EBVCQOS(op) \
	op(EBVCQoS::High) \
	op(EBVCQoS::Medium) \
	op(EBVCQoS::Low) 

enum class EBVCQoS : uint8;
template<> struct TIsUEnumClass<EBVCQoS> { enum { Value = true }; };
template<> CATALYSTCONNECT_API UEnum* StaticEnum<EBVCQoS>();
// ********** End Enum EBVCQoS *********************************************************************

// ********** Begin Enum EBVCValidationSetMode *****************************************************
#define FOREACH_ENUM_EBVCVALIDATIONSETMODE(op) \
	op(EBVCValidationSetMode::Off) \
	op(EBVCValidationSetMode::Deferred) \
	op(EBVCValidationSetMode::Eager) 

enum class EBVCValidationSetMode : uint8;
template<> struct TIsUEnumClass<EBVCValidationSetMode> { enum { Value = true }; };
template<> CATALYSTCONNECT_API UEnum* StaticEnum<EBVCValidationSetMode>();
// ********** End Enum EBVCValidationSetMode *******************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
