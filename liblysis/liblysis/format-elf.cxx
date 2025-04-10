#include <liblysis/format-elf.hxx>

#include <algorithm> // copy_n
#include <string>
#include <sstream>

using namespace std;

namespace lysis
{
  elf_error::
  elf_error (const string& d)
    : runtime_error (d)
  {
  }

  elf elf::
  parse (istream& s)
  {
    elf result;
    result.read_header(s);
    return result;
  }

  void elf::
  read_header (istream& is)
  {
    // Read ELF identification.
    //
    ident.resize (EI_NIDENT);
    is.read (reinterpret_cast<char*> (ident.data ()), EI_NIDENT);

    if (!is.good ())
      throw elf_error ("error reading ELF identification");

    // Check magic number.
    //
    if (ident[EI_MAG0] != ELFMAG0 ||
        ident[EI_MAG1] != ELFMAG1 ||
        ident[EI_MAG2] != ELFMAG2 ||
        ident[EI_MAG3] != ELFMAG3)
    {
      ostringstream os;
      os << "invalid ELF magic number: ";
      os << hex << showbase
         << static_cast<unsigned int> (ident[EI_MAG0]) << " "
         << static_cast<unsigned int> (ident[EI_MAG1]) << " "
         << static_cast<unsigned int> (ident[EI_MAG2]) << " "
         << static_cast<unsigned int> (ident[EI_MAG3]);

      throw elf_error (os.str ());
    }

    // Check file class.
    //
    switch (ident[EI_CLASS])
    {
    case ELFCLASS32:
      {
        // Read 32-bit ELF header.
        //
        copy_n (ident.begin (), EI_NIDENT, ehdr32.e_ident);

        is.read (reinterpret_cast<char*> (&ehdr32.e_type),
                 sizeof (Elf32_Ehdr) - EI_NIDENT);

        if (!is.good ())
          throw elf_error ("error reading 32-bit ELF header");

        break;
      }
    case ELFCLASS64:
      {
        // Read 64-bit ELF header.
        //
        copy_n (ident.begin (), EI_NIDENT, ehdr64.e_ident);

        is.read (reinterpret_cast<char*> (&ehdr64.e_type),
                 sizeof (Elf64_Ehdr) - EI_NIDENT);

        if (!is.good ())
          throw elf_error ("error reading 64-bit ELF header");

        break;
      }
    default:
      throw elf_error ("unsupported ELF class: " +
                       to_string (ident[EI_CLASS]));
    }

    // Check data encoding.
    //
    // @@ should we handle byte-swapping?
    //
    if (ident[EI_DATA] != ELFDATA2LSB && ident[EI_DATA] != ELFDATA2MSB)
      throw elf_error ("unsupported ELF data encoding: " +
                       to_string (ident[EI_DATA]));
  }

  bool elf::
  is_32bit () const
  {
    return ident[EI_CLASS] == ELFCLASS32;
  }

  bool elf::
  is_64bit () const
  {
    return ident[EI_CLASS] == ELFCLASS64;
  }

  uint8_t elf::
  elf_class () const
  {
    return ident[EI_CLASS];
  }

  uint8_t elf::
  elf_data () const
  {
    return ident[EI_DATA];
  }

  uint16_t elf::
  elf_type () const
  {
    return is_32bit () ? ehdr32.e_type : ehdr64.e_type;
  }

  uint16_t elf::
  elf_machine () const
  {
    return is_32bit () ? ehdr32.e_machine : ehdr64.e_machine;
  }
}
