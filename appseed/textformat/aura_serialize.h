#pragma once


class serializable;


#define FIRST_VERSION 0




class CLASS_DECL_APP_CORE_TEXTFORMAT serialize :
   virtual public object
{
public:


   index    m_iVersion;
   bool     m_bStoring;


   serialize(::aura::application * papp);
   virtual ~serialize();

   virtual void operator()(serializable & serializable);

   bool is_version(index i);

   template < typename BLOCK_TYPE >
   void blt(BLOCK_TYPE & t) // block transfer // classes/structures with no virtual members
   {
      operator()(&t, sizeof(t));
   }

   template < typename ARRAY >
   void serialize_array(ARRAY & a)
   {
      for (auto & element : a)
      {
         operator()(element);
      }
   }

   virtual void operator()(void * p, memory_size_t s) = 0;

   virtual void operator()(RECTD & rectd);
   virtual void operator()(double & d);
   virtual void operator()(bool & b);
   virtual void operator()(POINTD & d);

};


class CLASS_DECL_APP_CORE_TEXTFORMAT serializable :
   virtual public object
{
public:

   
   virtual void operator()(serialize & serialize);


};


namespace file
{


   class CLASS_DECL_APP_CORE_TEXTFORMAT serialize :
      virtual public ::serialize
   {
   public:

      ::file::file_sp   m_pfile;

      serialize(::aura::application * papp);
      virtual ~serialize();

      virtual void operator()(void * p, memory_size_t s);

   };



} // namespace file