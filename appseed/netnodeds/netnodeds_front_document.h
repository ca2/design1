#pragma once


namespace netnodeds
{


   class CLASS_DECL_DESIGN_NETNODEDS front_document :
      public html_document
   {
   public:
      front_document(::aura::application * papp);    

      virtual bool on_open_document(var varFile);
      virtual bool on_save_document(const char * lpszPathName);


      ::file::memory_buffer         m_memfile;
      ::file::file_sp           m_file;
      ::file::memory_buffer       m_memfileBody;

      bool _001OnUpdateCmdUi(cmd_ui * pcmdui);
      bool _001OnCommand(id id);

      void get_output(const char * lpcsz, string &strHead, ::file::memory_buffer & file);

      void OnUpdateStart(cmd_ui *pcmdui);
      void OnUpdateEditUndo(cmd_ui *pcmdui);
      void OnUpdateEditRedo(cmd_ui *pcmdui);
      void OnStart();
      void OnEditUndo();
      void OnEditRedo();

      // Overrides
      // ClassWizard generated virtual function overrides
      //{{AFX_VIRTUAL(screencaptureDoc)
   public:
      //   virtual void Serialize(CArchive& ar);   // overridden for document i/o
   protected:
      virtual bool on_new_document();
      //}}AFX_VIRTUAL

      // Implementation
   public:
      virtual ~front_document();
#ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
#endif

   };


} // namespace netnodeds


