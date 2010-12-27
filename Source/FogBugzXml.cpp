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

#include "FogBugzXml.h"

// instance of singleton class
FogBugzXml* FogBugzXml :: instance = NULL ; 

const std::string FogBugzXml :: sToken  = "<token>"   ; 
const std::string FogBugzXml :: eToken  = "</token>"  ;
const std::string FogBugzXml :: sData   = "[CDATA["   ; 
const std::string FogBugzXml :: eData   = "]]"        ; 
const std::string FogBugzXml :: sUrl    = "<url>"     ; 
const std::string FogBugzXml :: eUrl    = "</url>"    ; 
const std::string FogBugzXml :: sPeople = "<people>"  ; 
const std::string FogBugzXml :: ePeople = "</people>" ; 
const std::string FogBugzXml :: sPerson = "<person>"  ; 
const std::string FogBugzXml :: ePerson = "</person>" ;  
const std::string FogBugzXml :: sError  = "<error"    ; 
const std::string FogBugzXml :: eError  = "</error>"  ;  


// returns the instance of singleton
FogBugzXml* FogBugzXml :: GetInstance(void) { 
    if (instance == NULL)
	instance = new FogBugzXml; 
    return instance; 
}

// deletes the instance
void FogBugzXml :: Destroy(void) { 
    if (instance != NULL) { 
	delete instance; 
	instance = NULL; 
    }
}

// private method
// returns the value of the xml element
std::string FogBugzXml :: GetElementValue(const std::string& aString, const std::string& beginning, const std::string& ending) { 

    if (aString.length() < 1) 
	throw new std::invalid_argument("Error: string to be extracted from should not be empty"); 

    std::size_t endToken; 
    std::size_t begin = aString.find(beginning); 
    std::string result; // default value should be empty

    if (begin != std::string::npos) { 

	endToken = aString.find(ending, begin); 
	if (endToken != std::string::npos) 
	    result = aString.substr(begin + beginning.length(), endToken - (begin + beginning.length())); 
    }
    return result; 
}

// returns the url element value
std::string FogBugzXml :: GetUrlValue(const std::string& str) { 
    return GetElementValue(str, sUrl, eUrl); 
}

// returns the token tag value
std::string FogBugzXml :: GetTokenValue(const std::string& str) { 
    std::string tokenStr = GetElementValue(str, sToken, eToken); 
    return GetElementValue(tokenStr, sData, eData); 
}

// returns list of all people in persons
std::vector<std::string> FogBugzXml :: GetPeopleList(const std::string& str) { 

    std::vector<std::string> retVal; 
    std::string people = GetElementValue(str, sPeople, ePeople); 

    size_t begin = people.find(sPerson); 
    size_t end ; 

    while (begin != std::string::npos) { 
	end = people.find(ePerson);
	retVal.push_back(GetElementValue(people.substr(begin, end + ePerson.length()), sPerson, ePerson)); 

	begin = people.find(sPerson, begin + 1); 
    }

    return retVal;
}

// TODO
// returns the error message
std::string FogBugzXml :: GetErrorValue(const std::string& str) { 
    //TODO
    return "";
} 
