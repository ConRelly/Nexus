/*__________________________________________________________________________________________
 
			(c) Hash(BEGIN(Satoshi[2010]), END(Sunny[2012])) == Videlicet[2017] ++
			
			(c) Copyright The Nexus Developers 2014 - 2017
			
			Distributed under the MIT software license, see the accompanying
			file COPYING or http://www.opensource.org/licenses/mit-license.php.
			
			"fides in stellis, virtus in numeris" - Faith in the Stars, Power in Numbers
  
____________________________________________________________________________________________*/

#ifndef _NexusRPC_H_
#define _NexusRPC_H_ 1

#include <string>
#include <map>

#include "json/json_spirit_reader_template.h"
#include "json/json_spirit_writer_template.h"
#include "json/json_spirit_utils.h"

#define MAINNET_RPC_PORT 9336
#define TESTNET_RPC_PORT 9336


#define IMPLEMENT_RANDOMIZE_STACK(ThreadFn)     \
    {                                           \
        static char nLoops;                     \
        if (nLoops <= 0)                        \
            nLoops = GetRand(20) + 1;           \
        if (nLoops-- > 1)                       \
        {                                       \
            ThreadFn;                           \
            return;                             \
        }                                       \
    }

namespace Wallet { class CReserveKey; }

namespace RPC
{
	void ThreadRPCServer(void* parg);
	int CommandLineRPC(int argc, char *argv[]);

	/** Convert parameter values for RPC call from strings to command-specific JSON objects. */
	json_spirit::Array RPCConvertValues(const std::string &strMethod, const std::vector<std::string> &strParams);

	typedef json_spirit::Value(*rpcfn_type)(const json_spirit::Array& params, bool fHelp);

	class CRPCCommand
	{
	public:
		std::string name;
		rpcfn_type actor;
		bool okSafeMode;
	};

	/**
	 * Nexus RPC command dispatcher.
	 */
	class CRPCTable
	{
	private:
		std::map<std::string, const CRPCCommand*> mapCommands;
	public:
		CRPCTable();
		const CRPCCommand* operator[](std::string name) const;
		std::string help(std::string name) const;

		/**
		 * Execute a method.
		 * @param method   Method to execute
		 * @param params   Array of arguments (JSON objects)
		 * @returns Result of the call.
		 * @throws an exception (json_spirit::Value) when an error happens.
		 */
		json_spirit::Value execute(const std::string &method, const json_spirit::Array &params) const;
	};

	extern const CRPCTable tableRPC;
	extern Wallet::CReserveKey* pMiningKey;

}

#endif
