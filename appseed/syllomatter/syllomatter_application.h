#pragma once


namespace syllomatter
{


   class CLASS_DECL_CA2_SYLLOMATTER application :
      virtual public ::tesseract::application
   {
   public:


      sp(::user::single_document_template) m_ptemplateSyllomatter;



      application();
      virtual ~application();

      void construct();

      virtual void InitializeFileManager(const char * pszMatter);

      virtual bool initialize_application();
      virtual int32_t  exit_application() override;

      virtual void on_request(::create * pcreate);


      virtual void OnFileManagerOpenContextMenuFolder(::filemanager::data * pdata, const ::fs::item & item, stringa & straCommand, stringa & straCommandTitle);



      using ::object::create;
      virtual void create(const char * psz);
      virtual void commit(const char * pszDescriptor, const char * pszWorkingCopy);
      virtual void checkout(const char * pszRepos, const char * pszWorkingCopy);
      virtual void update(const char * pszWorkingCopy);


      DECL_GEN_SIGNAL(_001OnAddWorkingCopy);

   };


} // namespace syllomatter

