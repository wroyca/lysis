#pragma once

#include <vector>
#include <cstdint>
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
  public:
    // ELF types as defined in System V ABI.
    //
    using Elf32_Addr = std::uint32_t;
    using Elf32_Off = std::uint32_t;
    using Elf32_Half = std::uint16_t;
    using Elf32_Word = std::uint32_t;
    using Elf32_Sword = std::int32_t;

    using Elf64_Addr = std::uint64_t;
    using Elf64_Off = std::uint64_t;
    using Elf64_Half = std::uint16_t;
    using Elf64_Word = std::uint32_t;
    using Elf64_Sword = std::int32_t;
    using Elf64_Xword = std::uint64_t;
    using Elf64_Sxword = std::int64_t;

    // ELF header identification indexes.
    //
    enum
    {
      EI_MAG0 = 0,       // File identification.
      EI_MAG1 = 1,
      EI_MAG2 = 2,
      EI_MAG3 = 3,
      EI_CLASS = 4,      // File class.
      EI_DATA = 5,       // Data encoding.
      EI_VERSION = 6,    // File version.
      EI_OSABI = 7,      // OS/ABI identification.
      EI_ABIVERSION = 8, // ABI version.
      EI_PAD = 9,        // Start of padding bytes.
      EI_NIDENT = 16     // Size of e_ident[].
    };

    // ELF magic numbers.
    //
    enum
    {
      ELFMAG0 = 0x7F,
      ELFMAG1 = 'E',
      ELFMAG2 = 'L',
      ELFMAG3 = 'F'
    };

    // ELF file format classes.
    //
    enum
    {
      ELFCLASSNONE = 0, // Invalid class.
      ELFCLASS32 = 1,   // 32-bit objects.
      ELFCLASS64 = 2    // 64-bit objects.
    };

    // ELF data encoding.
    //
    enum
    {
      ELFDATANONE = 0, // Invalid data encoding.
      ELFDATA2LSB = 1, // Little-endian.
      ELFDATA2MSB = 2  // Big-endian.
    };

    // ELF file types.
    //
    enum
    {
      ET_NONE = 0, // No file type.
      ET_REL = 1,  // Relocatable file.
      ET_EXEC = 2, // Executable file.
      ET_DYN = 3,  // Shared object file.
      ET_CORE = 4  // Core file.
    };

    // ELF header structures as defined in System V ABI (Page 18).
    //

    // 32-bit ELF header.
    //
    struct Elf32_Ehdr
    {
      unsigned char e_ident[EI_NIDENT]; // Magic number and other info.
      Elf32_Half e_type;                // Object file type.
      Elf32_Half e_machine;             // Architecture.
      Elf32_Word e_version;             // Object file version.
      Elf32_Addr e_entry;               // Entry point virtual address.
      Elf32_Off e_phoff;                // Program header table file offset.
      Elf32_Off e_shoff;                // Section header table file offset.
      Elf32_Word e_flags;               // Processor-specific flags.
      Elf32_Half e_ehsize;              // ELF header size in bytes.
      Elf32_Half e_phentsize;           // Program header table entry size.
      Elf32_Half e_phnum;               // Program header table entry count.
      Elf32_Half e_shentsize;           // Section header table entry size.
      Elf32_Half e_shnum;               // Section header table entry count.
      Elf32_Half e_shstrndx;            // Section header string table index.
    };

    // 64-bit ELF header.
    //
    struct Elf64_Ehdr
    {
      unsigned char e_ident[EI_NIDENT]; // Magic number and other info.
      Elf64_Half e_type;                // Object file type.
      Elf64_Half e_machine;             // Architecture.
      Elf64_Word e_version;             // Object file version.
      Elf64_Addr e_entry;               // Entry point virtual address.
      Elf64_Off e_phoff;                // Program header table file offset.
      Elf64_Off e_shoff;                // Section header table file offset.
      Elf64_Word e_flags;               // Processor-specific flags.
      Elf64_Half e_ehsize;              // ELF header size in bytes.
      Elf64_Half e_phentsize;           // Program header table entry size.
      Elf64_Half e_phnum;               // Program header table entry count.
      Elf64_Half e_shentsize;           // Section header table entry size.
      Elf64_Half e_shnum;               // Section header table entry count.
      Elf64_Half e_shstrndx;            // Section header string table index.
    };

  private:
    elf () = default;

  private:
    std::vector<unsigned char> ident; // ELF identification bytes.

    // Union to store either 32-bit or 64-bit header.
    //
    union
    {
      Elf32_Ehdr ehdr32;
      Elf64_Ehdr ehdr64;
    };
  };
}
