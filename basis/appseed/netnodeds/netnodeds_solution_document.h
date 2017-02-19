#pragma once

namespace netnodeds
{

   class solution_view;

   class CLASS_DECL_DESIGN_NETNODEDS solution_document :
      public ::user::document
   {
   public:
      

      ::netnodeds::solution *      m_psolution;
      ::file::file_sp                m_file;
      ::file::file_sp                m_fileSave;
      int32_t                        m_iBranch;
      solution_view *            m_pview;


      solution_document(::aura::application * papp);           
      virtual ~solution_document();


      virtual bool on_open_document(var varFile);
      virtual bool on_save_document(const char * lpszPathName);


      void reload();


      void Put();
      void FtpPut(const char * lpcszLocal, const char * lpcszRemote);

      virtual bool on_new_document();

#ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
#endif

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

   };


} // namespace netnodeds


