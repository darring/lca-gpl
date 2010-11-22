/*
 * The following is appended when we rebuild the gSOAP bindings
 */
struct ns1__ReplyTo
{
    char *t__Address;
};

struct SOAP_ENV__Header
{
   char *t__Action;
   mustUnderstand char *t__MessageID;
   mustUnderstand char *t__To;
   ns1__ReplyTo *t__ReplyTo;
};
