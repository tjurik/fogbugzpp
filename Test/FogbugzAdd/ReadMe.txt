

This is a SIMPLE test application for the FogBugz C++ XML API wrapper.

To build this project:

1. download the CURL library (I have built against libcurl-7.19.3-win32-ssl-msvc)
2. unzip it to a directory on your build machine/dev machine
3. Set up an environment variable called 'CURL_DIR' and set it to the path of the curl dir.
  e.g. F:\Development\3rdParty\Win32\libcurl\libcurl-7.19.3-win32-ssl-msvc

Additional notes:

- There is a post build/custom build step that copies the DLLs required to run the app to the output directory.  
- If you have suggestions on how to improve the ease of use of building and testing this class please let me know.
I am sure there are better ways to configure these kinds of things for disparate teams to use in heterogenous environments.  
The way I have set it up seems to be reasonable, but improvements are welcome.

References:
- http://fogbugz.stackexchange.com/fogbugz-xml-api for a full description of the "api"
- http://stackoverflow.com/questions/1510346/how-to-upload-file-by-post-in-libcurl
