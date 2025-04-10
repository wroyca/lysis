#pragma once

#include <stdexcept> // runtime_error

#include <liblysis/export.hxx>

namespace lysis
{
  class LIBLYSIS_SYMEXPORT elf_error : public std::runtime_error
  {
  public:
    explicit
    elf_error (const std::string& description);
  };

  class LIBLYSIS_SYMEXPORT elf
  {
  private:
    elf () = default;
  };
}
