/*******************************************************************************************
 
			(c) Hash(BEGIN(Satoshi[2010]), END(Sunny[2012])) == Videlicet[2017] ++
			
			(c) Copyright Nexus Developers 2014 - 2017
			
			http://www.opensource.org/licenses/mit-license.php
  
*******************************************************************************************/

#include <string>

#include "include/version.h"

#include "../Util/include/debug.h"
#include "../LLP/include/network.h"


const int DATABASE_VERSION =
                    1000000 * DATABASE_MAJOR
                  +   10000 * DATABASE_MINOR 
                  +     100 * DATABASE_PATCH
                  +       1 * DATABASE_BUILD;

#ifdef USE_LLD
const std::string DATABASE_NAME("LLD");
#else
const std::string DATABASE_NAME("BDB");
#endif



const int CLIENT_VERSION =
                    1000000 * CLIENT_MAJOR
                  +   10000 * CLIENT_MINOR 
                  +     100 * CLIENT_PATCH
                  +       1 * CLIENT_BUILD;
				  
				  
/* Used to determine the features available in the Nexus Network */
const int PROTOCOL_VERSION =
                   1000000 * PROTOCOL_MAJOR
                 +   10000 * PROTOCOL_MINOR
                 +     100 * PROTOCOL_REVISION
                 +       1 * PROTOCOL_BUILD;
					  

/* Used to Lock-Out Nodes that are running a protocol version that is too old, 
 * Or to allow certain new protocol changes without confusing Old Nodes. */
const int MIN_PROTO_VERSION = 10000;

						
const std::string CLIENT_NAME("Tritium");
const std::string CLIENT_TYPE("Alpha");
const std::string CLIENT_DATE(__DATE__ " " __TIME__);

						
std::string FormatVersion(int nVersion)
{
    if (nVersion % 100 == 0)
        return strprintf("%d.%d.%d", nVersion/1000000, (nVersion/10000)%100, (nVersion/100)%100);
    else
        return strprintf("%d.%d.%d.%d", nVersion/1000000, (nVersion/10000)%100, (nVersion/100)%100, nVersion%100);
}


std::string FormatSubVersion()
{
	 std::ostringstream ss;
	 ss << "Nexus Version " << FormatVersion(CLIENT_VERSION) << " - " << CLIENT_NAME << " [" << DATABASE_NAME << "]";
	 
    return ss.str();
}


std::string FormatFullVersion()
{
    std::ostringstream ss;
    ss << FormatSubVersion();
    ss << " | DB: "    << FormatVersion(DATABASE_VERSION);
    ss << " | PROTO: " << FormatVersion(PROTOCOL_VERSION);
    
    return ss.str();
}
