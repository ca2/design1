#pragma once


#include "app-core/appseed/tesseract/tesseract/tesseract.h"
#include "core/user/simple/simple.h" // it is not time for optimzation on time of insertion, sure!! in creation it is not time for optimization
// hey but its not creation... it is recreation... it is porting... --- you answered> porting>re-creation->instance/object of creation class... no time for optimization, so...
#include "core/user/userex/userex.h" // it is not time for optimzation on time of insertion, sure!! in creation it is not time for optimization
// hey but its not creation... it is recreation... it is porting... --- you answered> porting>re-creation->instance/object of creation class... no time for optimization, so...
#include "html/html/html.h"// it is not time for optimzation on time of insertion, sure!! in creation it is not time for optimization
// hey but its not creation... it is recreation... it is porting... --- you answered> porting>re-creation->instance/object of creation class... no time for optimization, so...

#include "core/filesystem/filemanager/filemanager.h"// it is not time for optimzation on time of insertion, sure!! in creation it is not time for optimization
// hey but its not creation... it is recreation... it is porting... --- you answered> porting>re-creation->instance/object of creation class... no time for optimization, so...




#ifdef _DESIGN_NENOTDEDS_LIBRARY
#define CLASS_DECL_DESIGN_NETNODEDS  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_DESIGN_NETNODEDS  CLASS_DECL_IMPORT
#endif




namespace netnodeds
{

   class application;


} // namespace netnodeds




#undef App
#define App(pbaseapp) (pbaseapp->m_pcoreapp->cast_app < ::netnodeds::application > ())



#include "netnodeds_document.h"
#include "netnodeds_main_frame.h"
#include "netnodeds_child_frame.h"
#include "netnodeds_view.h"

#include "netnodeds_elemental.h"

#include "netnodeds_elemental_file.h"
#include "netnodeds_elemental_folder.h"
#include "netnodeds_elemental_headers.h"
#include "netnodeds_elemental_source.h"
#include "netnodeds_elemental_project.h"
#include "netnodeds_elemental_solution.h"

#include "netnodeds_solution_tree_data.h"


#include "netnodeds_solution_document.h"
#include "netnodeds_solution_view.h"


#include "netnodeds_main_document.h"
#include "netnodeds_pane_view.h"
#include "netnodeds_pane_view_update_hint.h"




#include "netnodeds_front_thread.h"

#include "netnodeds_front_document.h"
#include "netnodeds_front_child_frame.h"
#include "netnodeds_front_view.h"



#include "netnodeds_html_edit_document.h"
#include "netnodeds_html_edit_child_frame.h"
#include "netnodeds_html_edit_view.h"


#include "netnodeds_html_stage_document.h"
#include "netnodeds_html_stage_child_frame.h"
#include "netnodeds_html_stage_view.h"


#include "netnodeds_netnodeds.h"
#include "netnodeds_application.h"