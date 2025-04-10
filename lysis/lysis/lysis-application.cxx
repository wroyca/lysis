#include <lysis/lysis-application.hxx>
#include <lysis/lysis-application-window.hxx>

struct _LysisApplication
{
  AdwApplication parent_instance;
};

static void lysis_application_about (GSimpleAction *action,
                                     GVariant      *param,
                                     gpointer       user_data);

static GActionEntry action_entries[] = {
  {"about", lysis_application_about},
};

G_DEFINE_FINAL_TYPE (LysisApplication, lysis_application, ADW_TYPE_APPLICATION)

static void
lysis_application_activate (GApplication *app)
{
  g_autoptr (LysisApplication) self = nullptr;
  g_autoptr (LysisApplicationWindow) window = nullptr;

  self = LYSIS_APPLICATION (app);

  g_assert (LYSIS_IS_APPLICATION (self));

  window = LYSIS_APPLICATION_WINDOW (gtk_application_get_active_window (GTK_APPLICATION (app)));

  if (window == nullptr)
    window = lysis_application_window_new (self);

  gtk_window_present (GTK_WINDOW (window));

  g_steal_pointer (&self);
  g_steal_pointer (&window);
}

static void
lysis_application_class_init (LysisApplicationClass *self)
{
  const auto obj_class (G_OBJECT_CLASS (self));
  const auto app_class (G_APPLICATION_CLASS (self));

  app_class->activate = lysis_application_activate;
}

static void
lysis_application_about (GSimpleAction *action,
                         GVariant *param,
                         gpointer user_data)
{
  g_autoptr (LysisApplication) self = nullptr;
  g_autoptr (GtkWindow) window = nullptr;

  self = LYSIS_APPLICATION (user_data);

  g_assert (LYSIS_IS_APPLICATION (self));

  window = gtk_application_get_active_window (GTK_APPLICATION (self));

  adw_show_about_dialog (GTK_WIDGET (window),
                         "application-name", "Lysis",
                         "application-icon", "com.github.wroyca.Lysis",
                         "developer-name", "William Roy",
                         "version", "0.1.0",
                         nullptr);

  g_steal_pointer (&self);
  g_steal_pointer (&window);
}

static void
lysis_application_init (LysisApplication *self)
{
  g_action_map_add_action_entries (G_ACTION_MAP (self),
                                   action_entries,
                                   G_N_ELEMENTS (action_entries),
                                   self);
}

LysisApplication *
lysis_application_new (const char *application_id,
                       GApplicationFlags flags)
{
  g_autoptr (LysisApplication) self = nullptr;

  g_return_val_if_fail (application_id != nullptr, nullptr);
  g_return_val_if_fail (g_application_id_is_valid (application_id), nullptr);

  self = LYSIS_APPLICATION (g_object_new (LYSIS_TYPE_APPLICATION,
                                          "application-id", application_id,
                                          "flags", flags,
                                          nullptr));

  return g_steal_pointer (&self);
}
