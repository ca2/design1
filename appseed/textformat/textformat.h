#pragma once


#include "core/core/core.h"
#include "core/filesystem/filemanager/filemanager.h"


#ifdef _DESIGN_TEXTFORMAT_LIBRARY
#define CLASS_DECL_DESIGN_TEXTFORMAT  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_DESIGN_TEXTFORMAT  CLASS_DECL_IMPORT
#endif


namespace textformat
{


   class application;
   class document;
   class view;


} // namespace flag


#undef App
#define App(papp) (*papp->cast < ::textformat::application > ())

#include "userex_dialog_frame.h"
#include "userex_progress_view.h"
#include "user_image_list_view.h"
#include "user_menu_view.h"

#include "userex_image_list_view.h"
#include "userex_group_image_list_view.h"

#include "user_object.h"
#include "user_pic.h"
#include "user_font_combo_box.h"
#include "user_tool_window.h"
#include "aura/xml/xml.h"
#include "user_rich_text.h"
#include "userex_font_format_tool.h"
#include "user_rich_text_edit.h"
#include "user_text_format_object.h"
#include "composite_data.h"
#include "composite_view.h"


#include "textformat_document.h"
#include "textformat_view.h"
#include "textformat_frame.h"
#include "textformat_main_frame.h"
#include "textformat_pane_view_update_hint.h"
#include "textformat_pane_view.h"

#include "textformat_application.h"

