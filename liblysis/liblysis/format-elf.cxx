#include <liblysis/format-elf.hxx>

#include <string>

using namespace std;

namespace lysis
{
  elf_error::
  elf_error (const string& d)
    : runtime_error (d)
  {
  }
}
