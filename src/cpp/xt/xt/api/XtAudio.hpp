#ifndef XT_API_AUDIO_HPP
#define XT_API_AUDIO_HPP

/** @file */
/** @cond */
#include <xt/cpp/Core.hpp>
#include <xt/cpp/Error.hpp>
#include <xt/api/Structs.hpp>
#include <xt/api/XtService.hpp>
#include <xt/api/XtPlatform.hpp>

#include <memory>
#include <vector>
#include <string>
/** @endcond */

namespace Xt {

using namespace Detail;

class Audio final 
{
  Audio() = default;
public:
  static Version GetVersion();
  static void SetOnError(OnError onError);
  static ErrorInfo GetErrorInfo(uint64_t error);
  static Attributes GetSampleAttributes(Sample sample);
  static std::unique_ptr<Platform> Init(std::string const& id, void* window);
};

inline Version
Audio::GetVersion() 
{
  auto result = Detail::HandleError(XtAudioGetVersion);
  return *reinterpret_cast<Version*>(&result);
}

inline ErrorInfo
Audio::GetErrorInfo(uint64_t error) 
{ 
  ErrorInfo result;
  auto info = Detail::HandleError(XtAudioGetErrorInfo, error);
  result.fault = info.fault;
  result.system = static_cast<System>(info.system);
  result.service.text = std::string(info.service.text);
  result.service.cause = static_cast<Cause>(info.service.cause);
  return result;
}

inline Attributes 
Audio::GetSampleAttributes(Sample sample) 
{
  Attributes result;
  auto coreSample = static_cast<XtSample>(sample);
  auto attrs = Detail::HandleError(XtAudioGetSampleAttributes, coreSample);
  result.size = attrs.size;
  result.count = attrs.count;
  result.isFloat = attrs.isFloat != XtFalse;
  result.isSigned = attrs.isSigned != XtFalse;
  return result;
}

inline std::unique_ptr<Platform>
Audio::Init(std::string const& id, void* window) 
{
  XtPlatform* result = Detail::HandleError(XtAudioInit, id.c_str(), window);
  return std::unique_ptr<Platform>(new Platform(result));
}

inline void
Audio::SetOnError(OnError onError)
{ 
  Detail::_onError = onError;
  XtOnError coreOnError = onError == nullptr? nullptr: &Detail::ForwardOnError;
  Detail::HandleVoidError(XtAudioSetOnError, coreOnError);
}

} // namespace Xt
#endif // XT_API_AUDIO_HPP