/*
 Copyright (c) 
 All rights reserved.

 Author: kevinchkin
 
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

#include "FogBugzUrlCreator.h"

FogBugzUrlCreator* FogBugzUrlCreator :: instance = NULL ;

const std::string FogBugzUrlCreator :: Cmd       = "cmd="       ; 
const std::string FogBugzUrlCreator :: ApiUrl    = "/api.xml"   ; 
const std::string FogBugzUrlCreator :: Token     = "&token="    ; 
const std::string FogBugzUrlCreator :: Logon     = "logon"      ; 
const std::string FogBugzUrlCreator :: Logoff    = "logoff"     ; 
const std::string FogBugzUrlCreator :: Email     = "&email="    ; 
const std::string FogBugzUrlCreator :: Password  = "&password=" ; 
const std::string FogBugzUrlCreator :: New       = "new"        ; 
const std::string FogBugzUrlCreator :: Title     = "&sTitle="   ; 
const std::string FogBugzUrlCreator :: Event     = "&sEvent="   ; 
const std::string FogBugzUrlCreator :: Project   = "&sProject=" ; 
const std::string FogBugzUrlCreator :: ScoutDesc = "&sScoutDescription=" ;  

// create singleton object
FogBugzUrlCreator* FogBugzUrlCreator :: GetInstance() { 
    if (instance == NULL)
	instance = new FogBugzUrlCreator; 
    return instance;
}

// delete singleton object
void FogBugzUrlCreator :: Destroy(void) { 
    if (instance != NULL) { 
	delete instance; 
	instance = NULL;
    }
}

//TODO: Ref (Method from internet) 
std::string FogBugzUrlCreator :: UrlEncode(const std::string& str) { 

    std::string escaped = ""; 
    int last = str.length() ; 

    for (int index = 0; index < last; index++) { 

	if (  (48 <= str[index] && str[index] <= 57)  || 
	      (65 <= str[index] && str[index] <= 90)  || 
      	      (97 <= str[index] && str[index] <= 122) ||
	      (str[index] == '~' || str[index] == '*' || str[index] == '(' || str[index] == ')' || str[index] == '\'')) 
	{ 
	    escaped.append(&str[index], 1); 
	}	
    	else { 
	    escaped.append("%"); 
	    escaped.append(CharToHex(str[index])) ; 
	}	    
    }
    return escaped;
}

//TODO: Ref (Method from Internet) 
std::string FogBugzUrlCreator :: CharToHex(char dec) { 

    char dig1 = (dec&0xF0) >> 4; 
    char dig2 = (dec&0x0F)     ; 

    if ( 0  <= dig1 && dig1 <= 9 )  dig1 += 48;      // 0, 48 in ascii
    if ( 10 <= dig1 && dig1 <= 15)  dig1 += 97 - 10; // 0, 97 in ascii 
    if ( 0  <= dig2 && dig2 <= 9 )  dig2 += 48;      // 0, 48 in ascii
    if ( 10 <= dig1 && dig1 <= 15)  dig2 += 97 - 10; // 0, 97 in ascii 

    std::string result; 
    result.append(&dig1, 1); 
    result.append(&dig2, 1);

    return result;
}

// Add api.xml
std::string FogBugzUrlCreator :: AddApiUrl(const std::string& url) { 
    std::string result = url + ApiUrl; 
    return result ; 
}

// Add val from <url>val</url>
std::string FogBugzUrlCreator :: AddUrl(const std::string& url, const std::string& val) { 
    std::string result = url + "/" + val; 
    return result;
}

// Add token
std::string FogBugzUrlCreator :: AddToken(const std::string& url, const std::string& val) { 
    std::string result = url + Token + val;  
    return result;
}

// Add logoff
std::string FogBugzUrlCreator :: AddLogoff(const std::string& url) {
    std::string result = url + Cmd + Logoff ; 
    return result;
}

// Add New Case
std::string FogBugzUrlCreator :: AddNewCase(const std::string& url, const FogBugzCase& fogCase) { 

    std::string result = url + Cmd + New + Title + UrlEncode(fogCase.GetTitle()) ; 
    result += Event + UrlEncode(fogCase.GetContent()) ; 
    
    if (fogCase.GetProject().length() > 0) 
	result += Project + fogCase.GetProject(); 

    if (fogCase.GetScout().length() > 0) 
	result += ScoutDesc + fogCase.GetScout(); 

    return result;
}

// Add logon information on the url
std::string FogBugzUrlCreator :: AddLogonInfo(const std::string& url, const std::string& email, const std::string& password) { 

    std::string result = url + Cmd   + Logon ;
    result += Email + email ; 
    result += Password + password ; 
    return result;
}
