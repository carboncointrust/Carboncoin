// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Copyright (c) 2013 CarbonCoin Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //

	// no checkpoint now, can be added in later releases
    static MapCheckpoints mapCheckpoints =
            boost::assign::map_list_of
            (     0, uint256("0xa94f1aae8c409a0bd1e53cbca92d7e506b61c51d955cf56f76da501718d48d6c"))
            (     1, uint256("0x27fe28d8f814805c20aa2a2b31f629cb8a52d7016894541c5e424c18d6810559"))
            (     2, uint256("0x763ce0b24417ea00b642ba2e9980189d7c6d5f2cd0fd1574ac35e0e8d27fb405"))
            ( 10000, uint256("0x12697138ac647bec1ad807dd45827e67d7ed334bb47d823849e3dbbb48eebf64"))
            ( 20000, uint256("0x66099425a0ed2c3899e85e015e06f52a6138574d983829390e667ef4b5a9c89a"))
            ( 30000, uint256("0x1a49a6076a25f7e2ba68f39131f0788b3dda5ac504c59b24f6182be1247cf65a"))
            ( 40000, uint256("0x10d2e04152bf5c21b585a8c9720de6dc2c9f8440b70560cb9c796ccedd0b0ac3"))
            ( 50000, uint256("0x80c232bc7ca8ea6905fda51b017d9d4fe37523953d840765e96540ece0f2f3ba"))
			;


    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
		// return true;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
	
        return mapCheckpoints.rbegin()->first;
		// return 0;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
				// return NULL;
        }
        return NULL;
    }
}
