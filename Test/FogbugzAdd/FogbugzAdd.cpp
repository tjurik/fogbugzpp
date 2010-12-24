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

#include "stdafx.h"
#include <iostream> 
#include "CreateFogbugzCase.h"

using namespace std;

void Usage()
{
	cout << "Usage:\nFogbugzAdd <FB url> <user> <password> <title> [content] [ScoutDescription] [Project]" << endl << endl;
}

int _tmain(int argc, char* argv[])
{	
	if (argc < 5)
	{
		Usage();
		return 0;
	}
	
	string content;
	string project;
	string scout;

	if (argc > 5)
	{
		content = argv[5];
	}
	if (argc > 6)
	{
		scout = argv[6];
	}
	if (argc > 7)
	{
		project = argv[7];
	}
	
	FogBugz fb(argv[1], argv[2], argv[3]);
	string fbcase = fb.AddCase(argv[4], content, scout, project);
	cout << "FB Case : " << fbcase << endl;
	
	return 0;
}

