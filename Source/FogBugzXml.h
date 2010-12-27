/*
   Copyright (c) 
   All rights reserved.

   Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

   * Redistributions in binary form must reproduce the above copyright notice, this list of conditions 
   and the following disclaimer in the documentation and/or other materials provided with the distribution.

   * Neither the name of Open Cage Software nor the names of its contributors may be used to endorse 
   or promote products derived from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE 
   USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
*/

#ifndef _XMLHELPER_H_
#define _XMLHELPER_H_

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
