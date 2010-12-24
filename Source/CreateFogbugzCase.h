#pragma once

// wrapper for fogbugz reporting
// This could eventually be a full-fledged wrapper for fogbugz, but for now
// it is just for inserting/creating a simple case.

// The original/initial goal is to create a FB case with a minidump (crash) file passed to it.  
// The bugzscout api/sample is unable to include files, so we have to write our own.
// FogCreek was kind enough to supply examples and code for the XML API for lots of programming languages.
// C++ got left out.

// This is not intended to be a wrapper for all cases - especially for GETTING information from FB server
// This is ONLY for creating a new FB case right now and it does not handle error conditions well/at all.
// The expected/planned use case is a "best effort" scenario - try to create/append to a case.  If it works, great.
// if not, no big deal.

// see http://fogbugz.stackexchange.com/fogbugz-xml-api for a full description of the "api"
// post files? --> http://stackoverflow.com/questions/1510346/how-to-upload-file-by-post-in-libcurl

#include <string>


class FogbugzCase
{
public:
	FogbugzCase(const std::string& title = "", const std::string& content = "", const std::string& scout = "", const std::string& project = "");
	virtual ~FogbugzCase() {}
	
	std::string Title()		{return mTitle;}
	std::string Content()	{return mContent;}
	std::string Project()	{return mProject;}
	std::string Scout()		{return mScout;}

private:
	std::string mTitle;
	std::string mContent;
	std::string mProject;
	std::string mScout;
};

// Wrap connection with the FB server
class FogBugz
{
public:
	FogBugz(const std::string& url, const std::string& user, const std::string& pw);
	~FogBugz();
	
	// returns token if successful
	std::string Login(const std::string& url, const std::string& user, const std::string& pw);

	std::string AddCase(FogbugzCase* fbCase);
	std::string AddCase(const std::string& title, const std::string& content = "", const std::string& scout = "", const std::string& project = "");

	// the callback for getting data from curl library
	static size_t FogBugz::write_response_to_string(void *ptr, size_t size, size_t count, void *stream);

private:
	bool Logoff();
	std::string GetAPIurl(const std::string& baseUrl);
	std::string Send(const std::string& message, bool appendToken = true);

private:
	std::string		mToken;
	std::string		mURL;	
};

