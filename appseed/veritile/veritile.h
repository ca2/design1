#pragma once


#include "app-core/appseed/tesseract/tesseract/tesseract.h"
#include "core/user/userex/userex.h"



#ifdef _APP_CORE_VERITILE_LIBRARY
#define CLASS_DECL_APP_CORE_VERITILE  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_CORE_VERITILE  CLASS_DECL_IMPORT
#endif



namespace veritile
{

   class application;
   class drawing;
   class element;
   class tileset_view;
   class pane_view;

} // namespace veritile




#undef App
#define App(papp) (*papp->cast < ::veritile::application > ())

#include "veritile_general_data.h"
#include "veritile_property_sheet.h"


#include "veritile_enum.h"


#include "veritile_area.h"

#include "veritile_layer.h"

#include "veritile_element.h"
#include "veritile_element_array.h"



#include "veritile_tileset.h"
#include "veritile_tileset_view.h"
#include "veritile_tileset_pane_view.h"



#include "veritile_polygon.h"
#include "veritile_polygon_array.h"
#include "veritile_drawing.h"

#include "veritile_data.h"


#include "veritile_document.h"
#include "veritile_frame.h"
#include "veritile_view.h"


#include "veritile_main_document.h"
#include "veritile_main_frame.h"
#include "veritile_pane_view.h"
#include "veritile_pane_view_update_hint.h"


#include "veritile_application.h"

