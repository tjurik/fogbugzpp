#ifndef _XMLHELPER_H
#define _XMLHELPER_H

#include<string>
#include<vector>
#include<stdexcept>

class FogBugzXml { 

    private:
	FogBugzXml() { }  

	static FogBugzXml *instance; 

	static const std::string sToken   ; 
	static const std::string eToken   ; 
	static const std::string sData    ; 
	static const std::string eData    ; 
	static const std::string sUrl     ; 
	static const std::string eUrl     ; 
	static const std::string sPeople  ; 
	static const std::string ePeople  ; 
	static const std::string sPerson  ; 
	static const std::string ePerson  ; 
	static const std::string sError   ; 
	static const std::string eError   ; 

	std::string GetElementValue(const std::string& aString, const std::string& beginning, const std::string& ending);

    public:
	static FogBugzXml* GetInstance(void) ; 
	static void Destroy(void) ;        

	std::string GetUrlValue(const std::string& str)   ; 
	std::string GetTokenValue(const std::string& str) ; 
	std::string GetErrorValue(const std::string& str) ;
	std::vector<std::string> GetPeopleList(const std::string& str); 
} ; 

#endif
