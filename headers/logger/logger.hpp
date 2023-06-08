#pragma once

#include <core/engine.hpp>
namespace Logger
{
  // Logger namespace which holds all usefull functions for logging

  const std::string _MsgText[]{
      "Info",
      "Warn",
      "Error",
  };

  enum class MsgType
  {
    Info,
    Warn,
    Error,
    LAST
  };

  static_assert(sizeof(_MsgText) / sizeof(std::string) == int(MsgType::LAST),
                "The number of textes is not equal to number of messages\n "
                "headers/logger/message.hpp");

  struct Message
  {
    const std::string msg;
    const MsgType type;
  };

  Message create(const MsgType type, const std::string text);

  // namespace Msg

  void log(Message &message);

  void warn(const std::string text);

  void error(const std::string text);

  void info(const std::string text);

} // namespace Logger
