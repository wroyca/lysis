#pragma once

#include <iosfwd>
#include <string>

#include <liblysis/export.hxx>

namespace lysis
{
  // Print a greeting for the specified name into the specified
  // stream. Throw std::invalid_argument if the name is empty.
  //
  LIBLYSIS_SYMEXPORT void
  say_hello (std::ostream&, const std::string& name);
}
