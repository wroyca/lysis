#pragma once

#include <adwaita.h>

G_BEGIN_DECLS

#define LYSIS_TYPE_APPLICATION (lysis_application_get_type())

G_DECLARE_FINAL_TYPE (LysisApplication, lysis_application, LYSIS, APPLICATION, AdwApplication)

LysisApplication *lysis_application_new (const char        *application_id,
                                         GApplicationFlags  flags);

G_END_DECLS
