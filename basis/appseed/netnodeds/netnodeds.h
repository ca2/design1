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




#ifdef _DEVEDGE_LIBRARY
#define CLASS_DECL_DEVEDGE  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_DEVEDGE  CLASS_DECL_IMPORT
#endif




namespace devedge
{

   class application;


} // namespace devedge




#undef App
#define App(pbaseapp) (pbaseapp->m_pcoreapp->cast_app < ::devedge::application > ())



#include "devedge_document.h"
#include "devedge_main_frame.h"
#include "devedge_child_frame.h"
#include "devedge_view.h"

#include "devedge_elemental.h"

#include "devedge_elemental_file.h"
#include "devedge_elemental_folder.h"
#include "devedge_elemental_headers.h"
#include "devedge_elemental_source.h"
#include "devedge_elemental_project.h"
#include "devedge_elemental_solution.h"

#include "devedge_solution_tree_data.h"


#include "devedge_solution_document.h"
#include "devedge_solution_view.h"


#include "devedge_main_document.h"
#include "devedge_pane_view.h"
#include "devedge_pane_view_update_hint.h"




#include "devedge_front_thread.h"

#include "devedge_front_document.h"
#include "devedge_front_child_frame.h"
#include "devedge_front_view.h"



#include "devedge_html_edit_document.h"
#include "devedge_html_edit_child_frame.h"
#include "devedge_html_edit_view.h"


#include "devedge_html_stage_document.h"
#include "devedge_html_stage_child_frame.h"
#include "devedge_html_stage_view.h"


#include "devedge_devedge.h"
#include "devedge_application.h"