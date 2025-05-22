#include <iostream>

#include <lysis/lysis-options.hxx>
#include <lysis/version.hxx>

using namespace std;

int
main (int argc, char* argv[])
{
  try
  {
    lysis::options opt (argc, argv);

    // Handle --build2-metadata (see also buildfile).
    //
    if (opt.build2_metadata_specified ())
    {
      auto& o (cout);

      // The export.metadata variable must be the first
      // non-blank, non-comment line.
      //
      o << "# build2 buildfile lysis"                                  << "\n"
        << "export.metadata = 1 lysis"                                 << "\n"
        << "lysis.name = [string] lysis"                               << "\n"
        << "lysis.version = [string] '"  << LYSIS_VERSION_FULL << '\'' << "\n"
        << "lysis.checksum = [string] '" << LYSIS_VERSION_FULL << '\'' << "\n";

      return 0;
    }

    // Handle --version.
    //
    if (opt.version ())
    {
      auto& o (cout);

      o << "Lysis " << LYSIS_VERSION_ID << "\n";

      return 0;
    }

    // Handle --help.
    //
    if (opt.help ())
    {
      auto& o (cout);

      o << "usage: lysis [options] <names>" << "\n"
        << "options:"                       << "\n";

      opt.print_usage (o);

      return 0;
    }
  }

  catch (const lysis::cli::exception& e)
  {
    cerr << "error: " << e.what () << endl;

    return 1;
  }
}
