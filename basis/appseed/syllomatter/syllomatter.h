#pragma once


#include "app-core/appseed/tesseract/tesseract/tesseract.h"
#include "html/html/html.h"
#include "core/filesystem/filemanager/filemanager.h"


#ifdef _CA2_FONTOPUS_SYLLOMATTER_LIBRARY
    #define CLASS_DECL_CA2_SYLLOMATTER  CLASS_DECL_EXPORT
#else
    #define CLASS_DECL_CA2_SYLLOMATTER  CLASS_DECL_IMPORT
#endif

namespace tesseract
{

   class application;

} // namespace tesseract


#include "syllomatter_frame.h"
#include "syllomatter_document.h"
#include "syllomatter_view.h"
#include "syllomatter_list_view.h"


#include "syllomatter_filemanager_document.h"
#include "syllomatter_filemanager_frame.h"
#include "syllomatter_filemanager_template.h"


#include "syllomatter_main_document.h"
#include "syllomatter_main_frame.h"


#include "syllomatter_svn_view.h"


#include "syllomatter_pane_view.h"
#include "syllomatter_pane_view_update_hint.h"



#include "syllomatter_application.h"


