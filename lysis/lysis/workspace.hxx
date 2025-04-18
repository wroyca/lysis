#pragma once

#include <string>
#include <cstdint>

#include <odb/core.hxx>

namespace lysis
{
  #pragma db object
  class workspace
  {
  private:
    workspace () = default;

    friend class odb::access;

    #pragma db id auto
    std::uint64_t id_;
  };
}
