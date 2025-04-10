#include <lysis/lysis-application-window.hxx>

struct _LysisApplicationWindow
{
  AdwApplicationWindow  parent_instance;

  GtkButton            *open_file;
};

G_DEFINE_FINAL_TYPE (LysisApplicationWindow, lysis_application_window, ADW_TYPE_APPLICATION_WINDOW)

static void
lysis_application_window_open_file_cb (GObject      *source_object,
                                       GAsyncResult *result,
                                       gpointer      user_data)
{
  g_autoptr (GtkFileDialog) dialog = nullptr;
  g_autoptr (LysisApplicationWindow) window = nullptr;
  g_autoptr (GError) error = nullptr;
  g_autoptr (GFile) file = nullptr;

  dialog = GTK_FILE_DIALOG (source_object);
  window = LYSIS_APPLICATION_WINDOW (user_data);

  g_assert (GTK_IS_FILE_DIALOG (dialog));
  g_assert (G_IS_ASYNC_RESULT (result));
  g_assert (LYSIS_IS_APPLICATION_WINDOW (window));

  // TODO: Actually process the selected file.
  //
  if ((file = gtk_file_dialog_open_finish (dialog, result, &error)))
    {
      g_print ("Selected file: %s\n", g_file_get_path (file));
    }

  g_steal_pointer (&dialog);
  g_steal_pointer (&window);
}

void
lysis_application_window_open_file (GtkButton *button,
                                    gpointer user_data)
{
  g_autoptr (GtkFileDialog) dialog = nullptr;
  g_autoptr (LysisApplicationWindow) window = nullptr;

  dialog = gtk_file_dialog_new ();
  window = LYSIS_APPLICATION_WINDOW (gtk_widget_get_root (GTK_WIDGET (button)));

  g_assert (GTK_IS_FILE_DIALOG (dialog));
  g_assert (LYSIS_IS_APPLICATION_WINDOW (window));

  gtk_file_dialog_set_title (dialog, "Open File");
  gtk_file_dialog_set_modal (dialog, TRUE);

  gtk_file_dialog_open (dialog,
                        GTK_WINDOW (window),
                        nullptr,
                        lysis_application_window_open_file_cb,
                        window);

  g_steal_pointer (&window);
}

static void
lysis_application_window_class_init (LysisApplicationWindowClass *klass)
{
  const auto object_class (G_OBJECT_CLASS (klass));
  const auto widget_class (GTK_WIDGET_CLASS (klass));

  gtk_widget_class_set_template_from_resource (widget_class, "/app/drey/Lysis/lysis-application-window.ui");

  gtk_widget_class_bind_template_child (widget_class, LysisApplicationWindow, open_file);
  gtk_widget_class_bind_template_callback (widget_class, lysis_application_window_open_file);
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
