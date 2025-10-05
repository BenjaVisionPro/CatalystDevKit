#pragma once
#include "CoreMinimal.h"

// --------------------------------------------------------------
// Log categories (declared once in the public header)
// --------------------------------------------------------------
DECLARE_LOG_CATEGORY_EXTERN(LogCatalystFoundation,       Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogCatalystFoundationEditor, Log, All);

// --------------------------------------------------------------
// Compile-time toggle (strip logs in Shipping)
// --------------------------------------------------------------
#ifndef CATALYST_LOG
# if UE_BUILD_SHIPPING
#   define CATALYST_LOG 0
# else
#   define CATALYST_LOG 1
# endif
#endif

// --------------------------------------------------------------
// Convenience macros (Foundation default category)
// --------------------------------------------------------------
#if CATALYST_LOG
  #define CF_INFO(Format, ...)  UE_LOG(LogCatalystFoundation,       Display, Format, ##__VA_ARGS__)
  #define CF_WARN(Format, ...)  UE_LOG(LogCatalystFoundation,       Warning, Format, ##__VA_ARGS__)
  #define CF_ERR(Format, ...)   UE_LOG(LogCatalystFoundation,       Error,   Format, ##__VA_ARGS__)
  // If you need a different category in a callsite:
  #define CF_CAT_LOG(Category, Verbosity, Format, ...) UE_LOG(Category, Verbosity, Format, ##__VA_ARGS__)
#else
  #define CF_INFO(Format, ...)  do {} while(0)
  #define CF_WARN(Format, ...)  do {} while(0)
  #define CF_ERR(Format, ...)   do {} while(0)
  #define CF_CAT_LOG(Category, Verbosity, Format, ...) do {} while(0)
#endif

// --------------------------------------------------------------
// Optional scope timer: logs to LogCatalystFoundation
// --------------------------------------------------------------
struct FCFLogScopeTimer
{
  explicit FCFLogScopeTimer(const TCHAR* InLabel, double InThresholdMs = 0.0)
  : Label(InLabel ? InLabel : TEXT("Scope"))
  , ThresholdMs(InThresholdMs)
  , Start(FPlatformTime::Seconds())
  {}

  ~FCFLogScopeTimer()
  {
#if CATALYST_LOG
    const double Ms = (FPlatformTime::Seconds() - Start) * 1000.0;
    if (Ms >= ThresholdMs)
    {
      CF_INFO(TEXT("%s took %.2f ms"), *Label, Ms);
    }
#endif
  }

private:
  FString Label;
  double  ThresholdMs;
  double  Start;
};