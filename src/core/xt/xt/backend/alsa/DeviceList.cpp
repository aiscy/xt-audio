#if XT_ENABLE_ALSA
#include <xt/backend/alsa/Shared.hpp>
#include <xt/backend/alsa/Private.hpp>

#include <cstring>
#include <sstream>

XtFault
AlsaDeviceList::GetCount(int32_t* count) const
{ *count = static_cast<int32_t>(_devices.size()); return 0; }  
XtFault 
AlsaDeviceList::GetId(int32_t index, char* buffer, int32_t* size) const
{ XtiCopyString(XtiGetAlsaDeviceId(_devices[index]).c_str(), buffer, size); return 0; }

XtFault
AlsaDeviceList::GetCapabilities(char const* id, XtDeviceCaps* capabilities) const
{
  // TODO
  return 0;
}

XtFault
AlsaDeviceList::GetName(char const* id, char* buffer, int32_t* size) const
{
  int32_t index = -1;
  for(size_t i = 0; i < _devices.size(); i++)
    if(!strcmp(XtiGetAlsaDeviceId(_devices[i]).c_str(), id))
    {
      index = static_cast<int32_t>(i);
      break;
    }
  
  if(index == -1) return -EINVAL;
  std::ostringstream oss;
  oss << _devices[index].name << " (" << XtiGetAlsaNameSuffix(_devices[index].type) << ")";
  XtiCopyString(oss.str().c_str(), buffer, size);
  return 0;
}

#endif // XT_ENABLE_ALSA