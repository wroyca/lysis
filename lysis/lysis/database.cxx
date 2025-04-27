#include <lysis/database.hxx>

#include <odb/schema-catalog.hxx>
#include <odb/sqlite/database.hxx>

using namespace std;
using namespace std::filesystem;
using namespace odb;

namespace lysis
{
  database::
  database (const path& db)
  {
    bool db_exists (exists (db));

    db_ = make_unique<sqlite::database> (
      db.string (),
      (SQLITE_OPEN_READWRITE | (!db_exists ? SQLITE_OPEN_CREATE : 0)));

    if (!db_exists)
    {
      transaction t (db_->begin ());
      schema_catalog::create_schema (*db_);
      t.commit ();
    }
  }
}
