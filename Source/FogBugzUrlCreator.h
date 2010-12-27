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
