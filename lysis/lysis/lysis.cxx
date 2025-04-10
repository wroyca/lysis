#include <lysis/lysis-application-window.hxx>

int
main (int argc, char *argv[])
{
  g_autoptr (LysisApplication) app = nullptr;
  int ret;

  app = LYSIS_APPLICATION (lysis_application_new ("com.github.wroyca.Lysis", G_APPLICATION_DEFAULT_FLAGS));
  ret = g_application_run (G_APPLICATION (app), argc, argv);

  return ret;
}
