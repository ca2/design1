#pragma once


namespace syllomatter
{


   class CLASS_DECL_CA2_SYLLOMATTER filemanager_template :
      public ::filemanager::manager_template
   {
   public:
   
      
      filemanager_template(::filemanager::filemanager * papp);
      virtual ~filemanager_template();

      
      virtual void Initialize(int32_t iTemplate, const char * pszMatter);

   };


}//  namespace syllomatter



