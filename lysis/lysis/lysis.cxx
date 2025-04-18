#include <iostream>

#include <lysis/version.hxx>
#include <lysis/lysis-options.hxx>

using namespace std;
using namespace lysis;

namespace lysis
{
  namespace
  {
    void
    usage (ostream& os)
    {
      os << "usage: driver [options] <names>" << endl
         << "options:"                        << endl;

      options::print_usage (os);
    }
  }
}

int
main (int argc, char* argv[])
{
  try
  {
    options o (argc, argv);

    if (o.build2_metadata_specified ())
    {
      auto& o (cout);

      // Note that the export.metadata variable should be the first non-
      // blank/comment line.
      //
      o << "# build2 buildfile lysis"                                  << endl
        << "export.metadata = 1 lysis"                                 << endl
        << "lysis.name = [string] lysis"                               << endl
        << "lysis.version = [string] '"  << LYSIS_VERSION_FULL << '\'' << endl
        << "lysis.checksum = [string] '" << LYSIS_VERSION_FULL << '\'' << endl;

      return 0;
    }

    if (o.help ())
    {
      usage (cout);
      return 0;
    }

    if (o.version ())
    {
      cout << "Lysis " << LYSIS_VERSION_ID << endl;
      return 0;
    }
  }
  catch (const cli::exception& e)
  {
    cerr << e << endl;
    usage (cerr);
    return 1;
  }
}
