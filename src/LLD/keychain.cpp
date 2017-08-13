/*__________________________________________________________________________________________
 
			(c) Hash(BEGIN(Satoshi[2010]), END(Sunny[2012])) == Videlicet[2017] ++
			
			(c) Copyright The Nexus Developers 2014 - 2017
			
			Distributed under the MIT software license, see the accompanying
			file COPYING or http://www.opensource.org/licenses/mit-license.php.
			
			"fides in stellis, virtus in numeris" - Faith in the Stars, Power in Numbers
  
____________________________________________________________________________________________*/

#include "templates/keychain.h"


/** Lower Level Database Name Space. **/
namespace LLD
{
	
	/** Handle the Registry of Shared Keychain Pointer Objects. **/
	std::map<std::string, KeyDatabase*> mapKeychainRegistry;
	
	
	/** Handle the Key Registry. **/
	Mutex_t REGISTRY_MUTEX;
	
	/** Handle the Registrying of Keychains for LLD Sectors. **/
	void RegisterKeychain(std::string strRegistryName, std::string strBaseName)
	{
		LOCK(REGISTRY_MUTEX);
		
		/** Create the New Keychain Database. **/
		KeyDatabase* SectorKeys = new KeyDatabase(GetDataDir().string() + "/keychain/", strBaseName);
		SectorKeys->Initialize();
		
		/** Log the new Keychain into the Memeory Map. **/
		mapKeychainRegistry[strRegistryName] = SectorKeys;
		
		/** Debug Output for Keychain Database Initialization. **/
		printf("[KEYCHAIN] Registered Keychain For Database %s\n", strRegistryName.c_str());
	}
	
	
	/** Return the Keychain Pointer Object. **/
	KeyDatabase* GetKeychain(std::string strRegistryName) {
		if(!mapKeychainRegistry.count(strRegistryName))
			return NULL;
		
		return mapKeychainRegistry[strRegistryName];
	}
	
	
	/** TODO:: Break Keychain Registry into another Database that stores the Keychain Registry and States on Disk.
		This can then be used to remove all memory requirements of the Database if so Desired. **/
}
