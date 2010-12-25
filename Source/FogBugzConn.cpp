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
