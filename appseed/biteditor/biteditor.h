#pragma once


#include "app-core/appseed/tesseract/tesseract/tesseract.h"
#include "core/user/html/html/html.h"
#include "core/filesystem/filemanager/filemanager.h"


#ifdef _CA2_FONTOPUS_BITEDITOR_LIBRARY
    #define CLASS_DECL_CA2_BITEDITOR  CLASS_DECL_EXPORT
#else
    #define CLASS_DECL_CA2_BITEDITOR  CLASS_DECL_IMPORT
#endif


#undef App
#define App(pcaapp) (pcaapp->cast_app < ::biteditor::application > ())



#include "biteditor_ascii_box.h"
#include "biteditor_hex_box.h"


#include "biteditor_main_document.h"
#include "biteditor_frame.h"
#include "biteditor_child_frame.h"
#include "biteditor_pane_view_update_hint.h"
#include "biteditor_pane_view.h"


#include "biteditor_document.h"
#include "biteditor_child_frame.h"
#include "biteditor_view.h"


#include "biteditor_front_document.h"
#include "biteditor_front_child_frame.h"
#include "biteditor_front_view.h"


#include "biteditor_application.h"



