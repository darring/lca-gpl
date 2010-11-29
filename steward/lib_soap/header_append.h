/*
 * The following is appended when we rebuild the gSOAP bindings
 */
#import "wsa.h"

//! Standard GetCommand header
struct SOAP_ENV__Header
{
    mustUnderstand _wsa__MessageID wsa__MessageID 0;
    mustUnderstand _wsa__ReplyTo *wsa__ReplyTo 0;
    mustUnderstand _wsa__To wsa__To 0;
    mustUnderstand _wsa__Action wsa__Action 0;
};

//! Full header (if needed)
struct SOAP_ENV__Header
{
    mustUnderstand _wsa__MessageID wsa__MessageID 0;
    mustUnderstand _wsa__RelatesTo *wsa__RelatesTo 0;
    mustUnderstand _wsa__From *wsa__From 0;
    mustUnderstand _wsa__ReplyTo *wsa__ReplyTo 0;
    mustUnderstand _wsa__FaultTo *wsa__FaultTo 0;
    mustUnderstand _wsa__To wsa__To 0;
    mustUnderstand _wsa__Action wsa__Action 0;
};
