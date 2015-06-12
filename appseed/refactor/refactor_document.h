#pragma once


namespace refactor
{


   class CLASS_DECL_CA2_REFACTOR document :
      public ::user::document
   {
   public:


      ::file::buffer_sp             m_file;
      //ex1::filesp             m_fileSave;
      int                     m_iBranch;
//      edit_view *             m_pview;

      document(::aura::application * papp);
	   virtual ~document();

      
   #ifdef DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif

      bool on_open_document(var varFile);

   };


} // namespace refactor







