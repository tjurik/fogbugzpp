#ifndef _FOGBUGZ_CONN_
#define _FOGBUGZ_CONN_

#include<string>
#include<stdexcept>
#include "FogBugzUrlCreator.h"
#include "FogBugzXml.h"

class FogBugzConn 
{ 
    public:
	FogBugzConn(const std::string& url); 
       ~FogBugzConn() ; 

       std::string Login(std::string user, std::string pw) ;
       bool Logoff(void) ; 

       std::string GetToken(void) const { return mToken; } 
       std::string GetUrl(void)   const { return mUrl  ; }

    private:
       std::string mToken; 
       std::string mUrl  ; 

       FogBugzXml*         xmlHelper; 
       FogBugzUrlCreator*  urlHelper;

       void SetUrl(void); 
} ; 

#endif
