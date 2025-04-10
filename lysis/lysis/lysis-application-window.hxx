#pragma once

#include <lysis/lysis-application.hxx>

#include <adwaita.h>

G_BEGIN_DECLS

#define LYSIS_TYPE_APPLICATION_WINDOW (lysis_application_window_get_type ())

G_DECLARE_FINAL_TYPE (LysisApplicationWindow, lysis_application_window, LYSIS, APPLICATION_WINDOW, AdwApplicationWindow)

LysisApplicationWindow *lysis_application_window_new (LysisApplication *app);

G_END_DECLS
