#include "framework.h"


namespace syllomatter
{


   document::document(::aura::application * papp) :
      element(papp),
      ::data::data_container_base(papp),
      ::aura::document(papp),
      html_document(papp),
      form_document(papp)
   {



   }

   bool document::on_new_document()
   {
      if (!form_document::on_new_document())
         return FALSE;

      update_all_views(NULL, 0);

      return TRUE;
   }

   document::~document()
   {
   }



#ifdef DEBUG
   void document::assert_valid() const
   {
      ::aura::document::assert_valid();
   }

   void document::dump(dump_context & dumpcontext) const
   {
      ::aura::document::dump(dumpcontext);
   }
#endif //DEBUG

   void document::data_on_after_change(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   bool document::on_open_document(var varFile)
   {
      return form_document::on_open_document(varFile);
   }

   bool document::open_commit_message()
   {
      string strTime;
      strTime = Application.file().time_square();
      string strContents;
      string strMessages;

      property_set set;

      set["user"] = &ApplicationUser;

      Application.http().get("https://api.ca2.cc/i2com/commit_message", strMessages, set);

      xml::document doc(get_app());
      doc.load(strMessages);
      strContents = "<html><head></head><body style=\"background-color:#FFFFFF;\">";
      for(int32_t i = 0; i < doc.get_children_count(); i++)
      {

         sp(::xml::node) lpnode = doc.child_at(i);
         string strId;
         strId.Format("messagetext_%s", lpnode->attr("id").get_string());
         strContents += "<span id=\"" + strId +"\">";
         strContents += System.url().url_decode(lpnode->attr("value")).Left(255);
         TRACE(strContents);
         strContents += "</span>";
         strContents += "<br />";
         strId.Format("message_%s", lpnode->attr("id").get_string());
         strContents += "<input type=\"button\" id=\"" +strId + "\" value=\"Select\" />";
         strContents += "<br />";
         strContents += "<br />";
         TRACE(strContents);
      }
      strContents += "<br />";
      strContents += "</body>";
      strContents += "</html>";
      TRACE(strContents);
      Application.file().put_contents(strTime, strContents);

      return open_document(strTime);


   }





} // namespace syllomatter








