#ifndef XT_BACKEND_ALSA_PRIVATE_HPP
#define XT_BACKEND_ALSA_PRIVATE_HPP
#if XT_ENABLE_ALSA

#include <alsa/asoundlib.h>
#include <string>

#define XT_VERIFY_ALSA(c)     \
  do { int e = (c); if(e < 0) \
  return XT_TRACE(#c), e; } while(0)

enum XtAlsaType
{
  InputRw,
  InputMMap,
  OutputRw,
  OutputMMap
};

struct XtAlsaDeviceInfo
{
  XtAlsaType type;
  std::string name;
};

struct XtAlsaPcm
{
  snd_pcm_t* pcm;
  XtAlsaPcm(): pcm(nullptr) { }
  XtAlsaPcm(snd_pcm_t* pcm): pcm(pcm) { }
  ~XtAlsaPcm() { if(pcm != nullptr) XT_TRACE_IF(snd_pcm_close(pcm) != 0); }
};

bool
XtiAlsaTypeIsMMap(XtAlsaType type);
bool
XtiAlsaTypeIsOutput(XtAlsaType type);
char const*
XtiGetAlsaNameSuffix(XtAlsaType type);
std::string
XtiGetAlsaHint(void const* hint, char const* id);
std::string
XtiGetAlsaDeviceId(XtAlsaDeviceInfo const& info);
snd_pcm_access_t
XtiGetAlsaAccess(XtAlsaType type, XtBool interleaved);
int
XtiAlsaOpenPcm(XtAlsaDeviceInfo const& info, XtAlsaPcm* pcm);
bool
XtiParseAlsaDeviceInfo(std::string const& id, XtAlsaDeviceInfo* info);
void
XtiLogAlsaError(char const* file, int line, char const* fun, int err, char const* fmt, ...);

#endif // XT_ENABLE_ALSA
#endif // XT_BACKEND_ALSA_PRIVATE_HPP