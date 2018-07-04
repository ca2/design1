#include "framework.h"


serialize::serialize(::aura::application * papp) :
   ::object(papp)
{

   m_iVersion = 0;

}

serialize::~serialize()
{


}

void serialize::operator()(serializable & serializable)
{
   
   serializable(*this);

}

bool serialize::is_version(index i)
{

   return i <= m_iVersion;

}

void serialize::operator()(double & d)
{

   blt(d);

}

void serialize::operator()(RECTD & rectd)
{

   operator()(rectd.left);
   operator()(rectd.top);
   operator()(rectd.right);
   operator()(rectd.bottom);

}

void serialize::operator()(bool & b)
{

   blt(b);

}

void serialize::operator()(POINTD & pointd)
{

   operator()(pointd.x);
   operator()(pointd.y);

}


void serializable::operator()(serialize & serialize)
{

}


namespace file
{


   serialize::serialize(::aura::application * papp) :
      ::object(papp),
      ::serialize(papp)
   {


   }


   serialize::~serialize()
   {


   }

   
   void serialize::operator()(void * p, memory_size_t s)
   {

      if (m_bStoring)
      {

         m_pfile->write(p, s);

      }
      else
      {

         memory_size_t iRead = m_pfile->read(p, s);

         if (iRead != s)
         {

            throw io_exception(get_app());

         }


      }

   }


} // namespace file


