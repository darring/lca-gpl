/*
 * The following is appended when we rebuild the gSOAP bindings
 */

struct SOAP_ENV__Header
{
   char *t__Action;
   mustUnderstand char *t__MessageID;
   mustUnderstand char *t__To;
   struct t__ReplyTo
   {
      char *t__Address;
   };
};
