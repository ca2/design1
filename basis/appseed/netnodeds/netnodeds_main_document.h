#pragma once


namespace netnodeds
{


   class CLASS_DECL_DESIGN_NETNODEDS main_document :
      public ::aura::document
   {
   public:


      ::file::memory_buffer *         m_pmemfile;
      ::file::buffer_sp *              m_pfile;


      main_document(::aura::application * papp);
      virtual ~main_document();



      virtual bool on_open_document(var varFile);
      virtual bool on_save_document(const char * lpszPathName);


      virtual bool on_new_document();

#ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
#endif

   };



} // namespace netnodeds



