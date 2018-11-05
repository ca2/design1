#pragma once


namespace syllomatter
{


   class CLASS_DECL_CA2_SYLLOMATTER filemanager_document :
      virtual public ::filemanager::manager
   {
   public:


      filemanager_document(::aura::application * papp);
      virtual ~filemanager_document();


      DECL_GEN_SIGNAL(_001OnCommit_);


   };


}//  namespace syllomatter



