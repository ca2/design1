#pragma once



namespace syllomatter
{

   class CLASS_DECL_CA2_SYLLOMATTER filemanager_frame :
      public ::filemanager::frame
   {
   public:
      filemanager_frame(::aura::application * papp);
      virtual ~filemanager_frame();
   };

}//  namespace syllomatter