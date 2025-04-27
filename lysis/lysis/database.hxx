#pragma once

#include <filesystem>

#include <odb/database.hxx>

namespace lysis
{
  class database
  {
  public:
    explicit
    database (const std::filesystem::path&);

  private:
    std::unique_ptr<odb::database> db_;
  };
}
