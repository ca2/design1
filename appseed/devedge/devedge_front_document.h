#pragma once


namespace devedge
{


   class CLASS_DECL_DEVEDGE front_document :
      public html_document
   {
   public:
      front_document(::aura::application * papp);    

      virtual bool on_open_document(var varFile);
      virtual bool on_save_document(const char * lpszPathName);


      ::memory_file         m_memfile;
      ::file::file_sp           m_file;
      ::memory_file       m_memfileBody;

      bool _001OnUpdateCmdUi(command_ui * pcommandui);
      bool _001OnCommand(id id);

      void get_output(const char * lpcsz, string &strHead, ::memory_file & file);

      void OnUpdateStart(command_ui *pcommandui);
      void OnUpdateEditUndo(command_ui *pcommandui);
      void OnUpdateEditRedo(command_ui *pcommandui);
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


} // namespace devedge


