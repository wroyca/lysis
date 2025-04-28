#pragma once

#include <filesystem>

#include <odb/database.hxx>

#include <lysis/workspace.hxx>

namespace lysis
{
  class database
  {
  public:
    explicit
    database (const std::filesystem::path&);

    void
    commit (workspace&);

  private:
    std::unique_ptr<odb::database> db_;
  };
}
