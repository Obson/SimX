#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char  _DATE[] = "11";
	static const char  _MONTH[] = "03";
	static const char  _YEAR[] = "2016";
	static const char  _UBUNTU_VERSION_STYLE[] = "16.03";
	
	//Software Status
	static const char  _STATUS[] = "Development";
	static const char  _STATUS_SHORT[] = "dev";
	
	//Standard Version Type
	static const long  _MAJOR = 0;
	static const long  _MINOR = 0;
	static const long  _BUILD = 18;
	static const long  _REVISION = 107;
	
	//Miscellaneous Version Types
	static const long  _BUILDS_COUNT = 2447;
	#define  _RC_FILEVERSION 0,0,18,107
	#define  _RC_FILEVERSION_STRING "0, 0, 18, 107\0"
	static const char  _FULLVERSION_STRING[] = "0.0.18.107";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long  _BUILD_HISTORY = 18;
	

}
#endif //VERSION_H
