#include <xt-cpp.hpp>
#include <memory>
#include <numeric>
#include <iostream>

static void OnFatal() {
  std::cout << "Fatal error.";
}

static void OnTrace(Xt::Level level, const std::string& message) {
  if(level != Xt::Level::Info)
    std::cout << "-- " << level << ": " << message << "\n";
}

int PrintDetailedMain(int argc, char** argv) {

  Xt::Audio audio("Sample", nullptr, OnTrace, OnFatal);

  try {
    auto version = Xt::Audio::GetVersion();
    std::cout << "Win32: " << Xt::Audio::IsWin32() << "\n";
    std::cout << "Version: " << version.major << "." << version.minor << "\n";
    
    auto pro = Xt::Audio::GetServiceBySetup(Xt::Setup::ProAudio);
    std::cout << "Pro Audio: " << (pro? pro->GetName(): "None") << "\n";
    auto system = Xt::Audio::GetServiceBySetup(Xt::Setup::SystemAudio);
    std::cout << "System Audio: " << (system? system->GetName(): "None") << "\n";
    auto consumer = Xt::Audio::GetServiceBySetup(Xt::Setup::ConsumerAudio);
    std::cout << "Consumer Audio: " << (consumer? consumer->GetName(): "None") << "\n";

    for(int s = 0; s < Xt::Audio::GetServiceCount(); s++) {

      std::unique_ptr<Xt::Service> service = Xt::Audio::GetServiceByIndex(s);
      std::cout << "Service " << service->GetName() + ":\n";
      std::cout << "  System: " << service->GetSystem() << "\n";
      std::cout << "  Device count: " << service->GetDeviceCount() << "\n";
      std::cout << "  Capabilities: " << service->GetCapabilities() << "\n";

      std::unique_ptr<Xt::Device> defaultInput = service->OpenDefaultDevice(false);
      if(defaultInput)
        std::cout << "  Default input: " << defaultInput->GetName() << "\n";

      std::unique_ptr<Xt::Device> defaultOutput = service->OpenDefaultDevice(true);
      if(defaultOutput)
        std::cout << "  Default output: " << defaultOutput->GetName() << "\n";

      for(int d = 0; d < service->GetDeviceCount(); d++) {
        std::unique_ptr<Xt::Device> device = service->OpenDevice(d);
        std::optional<Xt::Mix> mix = device->GetMix();
        std::cout << "  Device " << device->GetName() + ":" << "\n";
        std::cout << "    System: " << device->GetSystem() << "\n";
        if(mix)
          std::cout << "    Current mix: " << mix->rate << " " << mix->sample << "\n";
        std::cout << "    Input channels: " << device->GetChannelCount(false) << "\n";
        std::cout << "    Output channels: " << device->GetChannelCount(true) << "\n";
        std::cout << "    Interleaved access: " << device->SupportsAccess(true) << "\n";
        std::cout << "    Non-interleaved access: " << device->SupportsAccess(false) << "\n";
      }
    }
  }
  catch(const Xt::Exception& e) {
    auto info = Xt::Audio::GetErrorInfo(e.GetError());
    std::cout << "Error: "
      << "system " << info.system << ", "
      << "fault " << info.fault << ", "
      << "cause " << info.cause << ", "
      << "text " << info.text << ".\n";
  }
  return 0;
}