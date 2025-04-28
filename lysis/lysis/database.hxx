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

    // List all workspaces in the database.
    //
    // NOTE: This is a draft implementation.
    //
    std::vector<workspace>
    list_workspaces ();

  private:
    std::unique_ptr<odb::database> db_;
  };
}
