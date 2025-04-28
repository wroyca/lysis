#pragma once

#include <string>
#include <cstdint>

#include <odb/core.hxx>

namespace lysis
{
  #pragma db object
  class workspace
  {
  public:
    workspace () = default;

  private:
    friend class odb::access;

    #pragma db id auto
    std::uint64_t id_;
  };
}
