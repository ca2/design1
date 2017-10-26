#pragma once

namespace devedge
{

   class view;

   class CLASS_DECL_DEVEDGE document :
      public ::user::document
   {
   public:

      
      ::file::file_sp          m_file;
      int32_t                  m_iBranch;
      sp(view)               m_pview;


      document(::aura::application * papp);           

      virtual bool on_open_document(var varFile);



      sp(view) get_edit_view();

      void reload();
   
      DECL_GEN_SIGNAL(_001OnUpdateFileNew);
      DECL_GEN_SIGNAL(_001OnUpdateFileSave);
      DECL_GEN_SIGNAL(_001OnUpdateFilePut);
      DECL_GEN_SIGNAL(_001OnUpdateEditCut);
      DECL_GEN_SIGNAL(_001OnUpdateEditCopy);
      DECL_GEN_SIGNAL(_001OnUpdateEditPaste);
      DECL_GEN_SIGNAL(_001OnFileNew);
      DECL_GEN_SIGNAL(_001OnFileSave);
      DECL_GEN_SIGNAL(_001OnFilePut);
      DECL_GEN_SIGNAL(_001OnEditCut);
      DECL_GEN_SIGNAL(_001OnEditCopy);
      DECL_GEN_SIGNAL(_001OnEditPaste);

      void Put();
      void FtpPut(const char * lpcszLocal, const char * lpcszRemote);

      public:
   //   virtual void Serialize(CArchive& ar);   
      protected:
      virtual bool on_new_document();

   public:
      virtual ~document();
   
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   

      void write(::file::byte_ostream & ostream);


   };


} // namespace devedge