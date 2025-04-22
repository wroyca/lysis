#include <filesystem>
#include <iostream>

#include <lysis/lysis-options.hxx>
#include <lysis/version.hxx>

using namespace std;
using namespace lysis;

int
main (int argc, char* argv[])
{
  try
  {
    int end; // end of options
    lysis_options ops (argc, argv, end);

    // Handle --build2-metadata (see also buildfile).
    //
    if (ops.build2_metadata ())
    {
      auto& o (cout);

      // Note that the export.metadata variable should be the first
      // non-blank/comment line.
      //
      o << "# build2 buildfile lysis"                                  << endl
        << "export.metadata = 1 lysis"                                 << endl
        << "lysis.name = [string] lysis"                               << endl
        << "lysis.version = [string] '"  << LYSIS_VERSION_FULL << '\'' << endl
        << "lysis.checksum = [string] '" << LYSIS_VERSION_FULL << '\'' << endl;

      return 0;
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

    // We must provide at least one name,
    //
    if (end == argc)
    {
      auto& e (cerr);

      e << "error: missing names."                    << endl
        << "try 'lysis --help' for more information." << endl;

      ops.print_usage (e);

      return 1;
    }

    list <filesystem::path> l;
    {
      // Resolves given names into canonical filesystem path.
      //
      // First, attempts resolution as-is, failed that, attempts resolution
      // relative to the current working directory.
      //
      for (int i = end; i < argc; i++)
      {
        filesystem::path p;

        try
        {
          p = filesystem::canonical (argv[i]);
        }

        catch (const filesystem::filesystem_error&)
        {
          filesystem::path cwd = filesystem::current_path ();

          try
          {
            p = filesystem::canonical (cwd / argv[i]);
          }

          catch (const filesystem::filesystem_error&)
          {
            auto& e (cerr);

            e << "error: unable to locate '" << argv[i]
              << "' in provided path or current directory." << endl;

            return 1;
          }
        }

        // Push the canonical path to the list, so that we can
        // later use it around the database machinery.
        //
        l.push_back (p);
      }
    }
  }

  catch (const cli::exception& e)
  {
    return 1;
  }
}
