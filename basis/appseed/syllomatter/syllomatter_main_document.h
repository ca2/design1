#pragma once


namespace syllomatter
{


   class CLASS_DECL_CA2_SYLLOMATTER main_document : public ::user::document
   {
   public:


      main_document(::aura::application * papp);
      virtual ~main_document();

      
      DECL_GEN_SIGNAL(_001OnTest);


      DECL_GEN_SIGNAL(_001OnCommit_);
      DECL_GEN_SIGNAL(_001OnUpdate);
      DECL_GEN_SIGNAL(_001OnMajorCheckout);


   };


} // namespace syllomatter



