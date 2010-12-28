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

#include "FogBugzConn.h"

FogBugzConn :: FogBugzConn(const std::string& url) : mUrl(url)  { 

    xmlHelper = FogBugzXml::GetInstance() ; 
    urlHelper = FogBugzUrlCreator::GetInstance(); 
    this->SetUrl(); 
} 

FogBugzConn :: ~FogBugzConn() { } 

std::string FogBugzConn :: Login(std::string user, std::string pw) { 

    if (user.length() < 1 || pw.length() < 1) 
	throw new std::invalid_argument("Error: User name or password cannot be empty");

    std::string loginUrl = urlHelper->AddLogonInfo(this->mUrl, user, pw); 

    // TODO Use the code below after wrapping Send method in some class
    // std::string response = Send(loginUrl, false); 

    // if (response.length() > 0) 
    //	this->mToken = xmlHelper->GetTokenValue(response); 

    return this->mToken;  
}

bool FogBugzConn :: Logoff(void) {
    std::string logoff = urlHelper->AddLogoff(this->mUrl);

    // TODO Wrap the send method in class. Then activate the code below.
    // Send(logoff); 
    return true; 
}

void FogBugzConn :: SetUrl(void) {

    std::string apiUrl   = urlHelper->AddApiUrl(this->mUrl); 

    // TODO Wrap the send method in class. Then activate the code below.
    // std::string response = Send(apiUrl, false) ;

    // this->mUrl = urlHelper->AddUrl(this->mUrl, xmlHelper->GetUrlValue(response)); 
}
