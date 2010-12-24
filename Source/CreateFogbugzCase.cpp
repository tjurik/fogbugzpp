/*
Copyright (c) 2010, Tim Jurik, Open Cage Software
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

// Wrapper for fogbugz reporting
// This will eventually be a full-fledged wrapper for fogbugz, but for now
// it is just for inserting/creating a simple case.
// The goal is to create a bug with a minidump file passed to it.

// see http://fogbugz.stackexchange.com/fogbugz-xml-api for a full description of the "api"
// post files? --> http://stackoverflow.com/questions/1510346/how-to-upload-file-by-post-in-libcurl

#include <string>
#include <assert.h>
#include <iostream> 

// If error not found - ensure that CURL_DIR environment variable is set correctly
// or set the include path to point to the curl directory 
// (something like: c:\libcurl\libcurl-7.19.3-win32-ssl-msvc)
#include <curl/curl.h>  

#include "CreateFogbugzCase.h"

using namespace std;

std::string char2hex( char dec );
std::string GetTokenValue(const std::string& aString, const std::string& beginning, const std::string& ending);

// do simple text encoding of urls
// based on javascript encodeURIComponent()

// This methods pulled of the internets
std::string URLEncode(const string &c)
{   
    string escaped = "";
    int last = c.length();
    for(int i = 0; i < last; i++)
    {
        if ( (48 <= c[i] && c[i] <= 57) ||  //0-9
             (65 <= c[i] && c[i] <= 90) ||  //abc...xyz
             (97 <= c[i] && c[i] <= 122) || //ABC...XYZ
             (c[i]=='~' || c[i]=='!' || c[i]=='*' || c[i]=='(' || c[i]==')' || c[i]=='\''))
        {
            escaped.append( &c[i], 1);
        }
        else
        {
            escaped.append("%");
            escaped.append( char2hex(c[i]) );//converts char 255 to string "ff"
        }
    }
    return escaped;
}

// This methods pulled of the internets
std::string char2hex( char dec )
{
    char dig1 = (dec&0xF0) >> 4;
    char dig2 = (dec&0x0F);
    if ( 0<= dig1 && dig1 <= 9)  dig1+=48;    //0,48inascii
    if (10<= dig1 && dig1 <= 15) dig1+=97-10; //a,97inascii
    if ( 0<= dig2 && dig2 <= 9)  dig2+=48;
    if (10<= dig2 && dig2 <= 15) dig2+=97-10;

    string r;
    r.append( &dig1, 1);
    r.append( &dig2, 1);
    return r;
}

FogbugzCase::FogbugzCase(const std::string& title, const std::string& content, const std::string& scout, const std::string& project) :
	mTitle(title), mContent(content), mProject(project), mScout(scout)
{	
}

FogBugz::FogBugz(const std::string& url, const std::string& user, const std::string& pw) 
{
	// initially go to url/api.xml and it returns something like: <url>api.asp?</url>
	mURL = GetAPIurl(url);
	mToken = Login(mURL, user, pw);
}

FogBugz::~FogBugz() 
{ 
	bool b = Logoff(); 
	assert(b);
}

std::string FogBugz::AddCase(FogbugzCase* fbCase)
{
	// do the work of adding
	string ret;

	string text = mURL;
	text = text + "cmd=new&sTitle=" + URLEncode(fbCase->Title()) + "&sEvent=" + URLEncode(fbCase->Content());

	// Only assign a project name if we that was filled in
	if (fbCase->Project().length() > 0)
	{
		text = text + "&sProject=" + URLEncode(fbCase->Project());
	}

	if (fbCase->Scout().length() > 0)
	{
		text = text + "&sScoutDescription=" + URLEncode(fbCase->Scout());
	}

	string result = Send(text);
	ret = GetTokenValue(result, "<case ixBug=\"", "\"");
	return ret;
}

std::string FogBugz::AddCase(const std::string& title, const std::string& content, const std::string& scout, const std::string& project)
{
	FogbugzCase fb(title, content, scout, project);
	return AddCase(&fb);
}

std::string FogBugz::GetAPIurl(const std::string& baseUrl)
{
	string url = baseUrl;
	// add "/api.xml" to the base url
	string test = baseUrl + "/api.xml";

	string response = Send(test, false);
	url = baseUrl + "/" + GetTokenValue(response, "<url>", "</url>");
	return url;
}

std::string FogBugz::Login(const std::string& url, const std::string& user, const std::string& pw)
{
	// create the login url/request
	// (might have to get the correct url by first querying "[url]/api.xml"  - this returns something like "[url]/api.asp?"
	string token;
	string loginurl = url + "cmd=logon&email=" + user + "&password=" + pw;	
	string response = Send(loginurl, false);

	if (response.length() > 0)
	{
		// find the token between "<token> and </token>
		// data can also have the form of: <token><![CDATA[pn2ij9ejuo1jc3h9vhpeknab7ruri2]]></token>
		// We don't want the [CDATA stuff...
		token = GetTokenValue(response, "<token>", "</token>");
		token = GetTokenValue(token, "[CDATA[", "]]");
	}
	return token;
}

// the callback we passed to curl to get the response
size_t FogBugz::write_response_to_string(void *ptr, size_t size, size_t count, void *stream) 
{
  ((string*)stream)->append((char*)ptr, 0, size*count);
  return size*count;
}

std::string FogBugz::Send(const std::string& message, bool appendToken)
{
	string		ret;
	CURLcode	res;	
	string		toSend	= message;
	CURL*		curl	= curl_easy_init();

	if (appendToken)
	{
		assert (mToken.length() > 0);
		toSend = toSend + "&token=" + mToken;
	}

	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, toSend.c_str());
		curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION, write_response_to_string);
		curl_easy_setopt(curl,CURLOPT_WRITEDATA, &ret);

		// skip some SSL verification - may want to ifdef this in the build
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

		// cout << endl << "Sending to URL:\n" << toSend << endl << endl;
		res = curl_easy_perform(curl);

		if (res != CURLE_OK)
		{
			// any error handling code here
		}
 
	    curl_easy_cleanup(curl);  		
	}

	// std::cout << endl << "Response:\n" << ret << endl << endl;
	return ret;
}

bool FogBugz::Logoff()
{
	bool ret = true;

	string logoff = mURL + "cmd=logoff";
	Send(logoff);
	return true;
}

std::string GetTokenValue(const std::string& aString, const std::string& beginning, const std::string& ending)
{
	// by default just return the entire string.
	// If there is a token in there delimited by the begin and end, then return that
	string::size_type endToken;	
	string::size_type begin = aString.find(beginning);
	std::string ret = aString;

	if (begin != std::string::npos)
	{
		endToken = aString.find(ending, begin);

		if (endToken != std::string::npos)
		{
			ret = aString.substr(begin + beginning.length(), endToken - (begin + beginning.length()));
		}
	}

	return ret;
}

