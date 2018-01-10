#pragma once


#include "core/core/core.h"
//#include "core/user/user/user.h"
#include "core/user/userex/userex.h"
//#include "core/filesystem/filemanager/filemanager.h"


#ifdef _CA2_FONTOPUS_REFACTOR_DLL
    #define CLASS_DECL_CA2_REFACTOR  CLASS_DECL_EXPORT
#else
    #define CLASS_DECL_CA2_REFACTOR  CLASS_DECL_IMPORT
#endif

namespace refactor
{

   class application;


} // namespace flag

#undef App
#define App(pcaapp) (pcaapp->cast_app < ::refactor::application > ())


#include "refactor_document.h"
#include "refactor_view.h"
#include "refactor_frame.h"
#include "refactor_pane_view.h"
#include "refactor_pane_view_update_hint.h"

#include "refactor_application.h"
