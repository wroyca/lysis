#include <lysis/lysis-application-window.hxx>

struct _LysisApplicationWindow
{
  AdwApplicationWindow  parent_instance;
};

G_DEFINE_FINAL_TYPE (LysisApplicationWindow, lysis_application_window, ADW_TYPE_APPLICATION_WINDOW)

static void
lysis_application_window_class_init (LysisApplicationWindowClass *klass)
{
  const auto object_class (G_OBJECT_CLASS (klass));
  const auto widget_class (GTK_WIDGET_CLASS (klass));

  gtk_widget_class_set_template_from_resource (widget_class, "/app/drey/Lysis/lysis-application-window.ui");
}

static void
lysis_application_window_init (LysisApplicationWindow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));

#if LYSIS_DEVELOP
  gtk_widget_add_css_class (GTK_WIDGET (self), "devel");
#endif
}

LysisApplicationWindow *
lysis_application_window_new (LysisApplication *app)
{
  g_autoptr (LysisApplicationWindow) self = nullptr;

  self = LYSIS_APPLICATION_WINDOW (g_object_new (LYSIS_TYPE_APPLICATION_WINDOW,
                                                 "application", app,
                                                 nullptr));

  return g_steal_pointer (&self);
}
