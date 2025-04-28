#include <filesystem>
#include <iostream>

#include <lysis/database.hxx>
#include <lysis/lysis-options.hxx>
#include <lysis/version.hxx>

using namespace std;
using namespace std::filesystem;
using namespace lysis;

int
main (int argc, char* argv[])
{
  database ldb ("/tmp/lysis.db");

  try
  {
    int end; // end of parsed options
    lysis_options ops (argc, argv, end);

    // Handle --build2-metadata (see also buildfile).
    //
    if (ops.build2_metadata ())
    {
      auto& o (cout);

      // The export.metadata variable must be the first
      // non-blank, non-comment line.
      //
      o << "# build2 buildfile lysis"                                  << endl
        << "export.metadata = 1 lysis"                                 << endl
        << "lysis.name = [string] lysis"                               << endl
        << "lysis.version = [string] '"  << LYSIS_VERSION_FULL << '\'' << endl
        << "lysis.checksum = [string] '" << LYSIS_VERSION_FULL << '\'' << endl;

      return 0;
    }

    // Handle --list-workspaces.
    //
    if (ops.list_workspaces ())
    {

    }

    // Handle --version.
    //
    if (ops.version ())
    {
      auto& o (cout);

      o << "Lysis " << LYSIS_VERSION_ID << endl;

      return 0;
    }

    // Handle --help.
    //
    if (ops.help ())
    {
      auto& o (cout);

      o << "usage: lysis [options] <names>" << endl
        << "options:"                       << endl;

      ops.print_usage (o);

      return 0;
    }

    // At least one name must be provided.
    //
    if (end == argc)
    {
      auto& e (cerr);

      e << "error: missing names."                    << endl
        << "try 'lysis --help' for more information." << endl;

      ops.print_usage (e);

      return 1;
    }

    // Resolve given names into canonical filesystem paths.
    //
    // First, attempts resolution as-is, failed that, attempts resolution
    // relative to the current working directory.
    //
    for (int i = end; i < argc; i++)
    {
      path p;

      try
      {
        p = canonical (argv[i]);
      }

      catch (const filesystem_error&)
      {
        path cwd = current_path ();

        try
        {
          p = canonical (cwd / argv[i]);
        }

        catch (const filesystem_error&)
        {
          auto& e (cerr);

          e << "error: unable to locate '" << argv[i]
            << "' in provided path or current directory." << endl;

          return 1;
        }
      }

      // Set up the workspace directory structure.
      //
      // First, check if the workspace directory exists. If it does not, create
      // the necessary directory structure.
      //
      try
      {
        (void) canonical (p.stem () / ".lysis");
      }

      // Directory does not exist; create it.
      //
      // Note: the workspace name is derived from the binary's stem. While not
      // strictly required, keeping the workspace and binary names aligned is
      // generally a good idea.
      //
      catch (const filesystem_error&)
      {
        error_code ec;

        create_directories (p.stem () / ".lysis", ec);

        if (ec)
        {
          auto& e (cerr);

          e << "error: unable to create directory structure for '"
            << p.stem () << "': " << ec.message () << endl;

          return 1;
        }
      }

      // Create a new workspace object. The workspace ID is automatically assigned.
      //
      workspace w;

      // Initialize the workspace database.
      //
      database wdb (p.stem () / ".lysis" / "lysis.db");

      // Insert the workspace object into the workspace database.
      //
      wdb.commit (w);

      // Insert the workspace object into the logical database.
      //
      ldb.commit (w);
    }
  }

  catch (const cli::exception& e)
  {
    return 1;
  }
}
