#include <string>
#include <vector>

#include "IHardware.h"

#include <cstdlib>

std::string getVersion() {
  #ifdef APPLICATION_VERSION
    std::string version = APPLICATION_VERSION;
  #else
    std::string version = "development";
  #endif

  return version;
}

std::vector<byte> createSysExMessage(const std::string& version) {
    std::vector<byte> byteArray = {0xF0, 0x7D, 0x02};
    for (char c : version) {
        byteArray.push_back(static_cast<byte>(c));
    }
    byteArray.push_back(0xF7);
    return byteArray;
}

// Command interface for handling SysEx messages
class SysExCommand {
public:
  virtual void execute(const uint8_t* data, unsigned int length, IHardware* deps) = 0;
  virtual ~SysExCommand() = default;
};

// Command to report back the software version
class ReportVersionCommand : public SysExCommand {
public:
  void execute(const uint8_t* data, unsigned int length, IHardware* deps) override {
    deps->print("running version command");

    std::vector<byte> msg = createSysExMessage(getVersion());
    deps->sendSysEx(msg.size(), msg.data());
  }
};

// Command to greet the user
class GreetingCommand : public SysExCommand {
public:
  void execute(const uint8_t* data, unsigned int length, IHardware* deps) override {
    std::vector<byte> msg = createSysExMessage("Hey there bud");
    deps->sendSysEx(msg.size(), msg.data());
  }
};
