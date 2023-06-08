#include <logger/logger.hpp>

namespace Logger
{

  Message create(const MsgType type, const std::string text)
  {
    auto new_msg = Message{text, type};
    return new_msg;
  }

  void log(Message &message)
  {
    std::cout << "[" << _MsgText[int(message.type)] << "]"
              << ": " << message.msg << std::endl;
  }

  void info(const std::string text)
  {
    auto msg = create(MsgType::Info, text);
    log(msg);
  }

  void warn(const std::string text)
  {
    auto msg = create(MsgType::Warn, text);
    log(msg);
  }

  void error(const std::string text)
  {
    auto msg = create(MsgType::Error, text);
    log(msg);
  }

} // namespace Logger