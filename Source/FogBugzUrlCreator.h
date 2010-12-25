#ifndef _FOGBUGZ_URL_CREATOR_
#define _FOGBUGZ_URL_CREATOR_

#include<string>
#include"FogBugzCase.h"

class FogBugzUrlCreator { 

    private:
	FogBugzUrlCreator() {  } ; 
	
	std::string UrlEncode(const std::string& str); 
	std::string CharToHex(char dec) ; 

	static FogBugzUrlCreator* instance  ; 

	static const std::string Cmd        ;
	static const std::string ApiUrl     ; 
	static const std::string Token      ; 
	static const std::string Logon      ; 
	static const std::string Logoff     ;
	static const std::string Email      ; 
	static const std::string Password   ; 
	static const std::string New        ; 
	static const std::string Title      ; 
	static const std::string Event      ; 
	static const std::string Project    ; 
	static const std::string ScoutDesc  ; 

    public:
	static FogBugzUrlCreator* GetInstance(void); 
	static void Destroy(void) ; 

	std::string AddApiUrl  (const std::string& url); 
	std::string AddUrl     (const std::string& url, const std::string& val)   ; 
	std::string AddToken   (const std::string& url, const std::string& token) ; 
	std::string AddLogoff  (const std::string& url) ; 
	std::string AddNewCase (const std::string& url, const FogBugzCase& fogCase); 
	std::string AddLogonInfo (const std::string& url, const std::string& email, const std::string& password); 
} ; 
#endif
