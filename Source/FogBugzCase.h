#ifndef _FOGBUGZ_CASE_H_
#define _FOGBUGZ_CASE_H_

#include<string>

class FogBugzCase { 

    private:
	std::string mTitle   ; 
	std::string mContent ;
        std::string mProject ; 
	std::string mScout   ; 

    public:
	FogBugzCase(const std::string& title = "", const std::string& content = "", const std::string& scout = "", const std::string& project = "");
	virtual ~FogBugzCase() {}
	
	std::string GetTitle(void)   const { return mTitle;   }
	std::string GetContent(void) const { return mContent; }
	std::string GetProject(void) const { return mProject; }
	std::string GetScout(void)   const { return mScout;   }
} ;

#endif
