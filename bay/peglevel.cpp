// Copyright (c) 2018 yshurik
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "pegdata.h"
#include "pegutil.h"

#include <map>
#include <set>
#include <cstdint>
#include <utility>
#include <algorithm> 
#include <type_traits>

#include <boost/multiprecision/cpp_int.hpp>

#include <zconf.h>
#include <zlib.h>

using namespace std;
using namespace boost;
using namespace pegutil;

CPegLevel::CPegLevel() {
    // invalid
    nSupply         = -1;
    nSupplyNext     = -1;
    nSupplyNextNext = -1;
}

CPegLevel::CPegLevel(std::string str) {
    vector<unsigned char> data(ParseHex(str));
    CDataStream finp(data, SER_NETWORK, CLIENT_VERSION);
    if (!Unpack(finp)) {
        // previous version
        CDataStream finp(data, SER_DISK, CLIENT_VERSION);
        if (!Unpack1(finp)) {
            // invalid
            nSupply         = -1;
            nSupplyNext     = -1;
            nSupplyNextNext = -1;
            nShift          = 0;
            nShiftLastPart  = 0;
            nShiftLastTotal = 0;
        }
    }
}

CPegLevel::CPegLevel(int cycle,
                     int cycle_prev,
                     int supply,
                     int supply_next,
                     int supply_next_next) {
    nCycle          = cycle;
    nCyclePrev      = cycle_prev;
    nSupply         = std::min(supply, PEG_SIZE-1);
    nSupplyNext     = std::min(supply_next, PEG_SIZE-1);
    nSupplyNextNext = std::min(supply_next_next, PEG_SIZE-1);
    nShift          = 0;
    nShiftLastPart  = 0;
    nShiftLastTotal = 0;
}

CPegLevel::CPegLevel(int cycle,
                     int cycle_prev,
                     int supply,
                     int supply_next,
                     int supply_next_next,
                     const CFractions & frInput,
                     const CFractions & frDistortion) {
    nCycle          = cycle;
    nCyclePrev      = cycle_prev;
    nSupply         = std::min(supply, PEG_SIZE-1);
    nSupplyNext     = std::min(supply_next, PEG_SIZE-1);
    nSupplyNextNext = std::min(supply_next_next, PEG_SIZE-1);
    nShift          = 0;
    nShiftLastPart  = 0;
    nShiftLastTotal = 0;
    
    CFractions frOutput = frInput + frDistortion;
    int64_t nInputLiquid = frInput.High(nSupply);
    int64_t nOutputLiquid = frOutput.High(nSupply);
    
    if (nOutputLiquid < nInputLiquid) {
        
        int64_t nLiquidDiff = nInputLiquid - nOutputLiquid;
        int64_t nLiquidDiffLeft = nLiquidDiff;
        nShiftLastTotal = 0;
        
        int i = nSupply;
        while(nLiquidDiffLeft > 0 && i < PEG_SIZE) {
            int64_t nLiquid = frInput.f[i];
            if (nLiquid > nLiquidDiffLeft) {
                // this fraction to distribute 
                // with ratio nLiquidCutLeft/nLiquid
                nShiftLastTotal = nLiquid;
                break;
            } 

            nShift++;
            nLiquidDiffLeft -= nLiquid;
            i++;
        }
        nShiftLastPart = nLiquidDiffLeft;
    }
}

bool CPegLevel::IsValid() const { 
    return  nSupply             >=0 && 
            nSupply             < PEG_SIZE &&
            nSupplyNext         >=0 && 
            nSupplyNext         < PEG_SIZE &&
            nSupplyNextNext     >=0 && 
            nSupplyNextNext     < PEG_SIZE && 
            nShift              >= 0 && 
            (nSupply+nShift)    < PEG_SIZE &&
            nShiftLastPart      >= 0 &&
            nShiftLastTotal     >= 0;
}

bool CPegLevel::Pack(CDataStream & fout) const {
    fout << nVersion;
    fout << nCycle;
    fout << nCyclePrev;
    fout << nSupply;
    fout << nSupplyNext;
    fout << nSupplyNextNext;
    fout << nShift;
    fout << nShiftLastPart;     // to distribute (part)
    fout << nShiftLastTotal;    // to distribute (total)
    return true;
}

bool CPegLevel::Unpack(CDataStream & finp) {
    try {
        finp >> nVersion;
        finp >> nCycle;
        finp >> nCyclePrev;
        finp >> nSupply;
        finp >> nSupplyNext;
        finp >> nSupplyNextNext;
        finp >> nShift;
        finp >> nShiftLastPart;     // to distribute (part)
        finp >> nShiftLastTotal;    // to distribute (total)
    }
    catch (std::exception &) {
        return false;
    }
    return true;
}

std::string CPegLevel::ToString() const {
    CDataStream fout(SER_NETWORK, CLIENT_VERSION);
    Pack(fout);
    return HexStr(fout.begin(), fout.end());
}

bool operator<(const CPegLevel &a, const CPegLevel &b) {
    int16_t nSupplyA = a.nSupply+a.nShift;
    int16_t nSupplyB = b.nSupply+b.nShift;
    if (nSupplyA < nSupplyB) return true;
    if (nSupplyA > nSupplyB) return false;
    
    multiprecision::uint128_t nShiftLastPartA(a.nShiftLastPart);
    multiprecision::uint128_t nShiftLastPartB(b.nShiftLastPart);
    multiprecision::uint128_t nShiftLastTotalA(a.nShiftLastTotal);
    multiprecision::uint128_t nShiftLastTotalB(b.nShiftLastTotal);
    
    multiprecision::uint128_t nPartNormA = nShiftLastPartA * nShiftLastTotalB;
    multiprecision::uint128_t nPartNormB = nShiftLastPartB * nShiftLastTotalA;
    
    return nPartNormA < nPartNormB;
}

bool operator==(const CPegLevel &a, const CPegLevel &b) {
    int16_t nSupplyA = a.nSupply+a.nShift;
    int16_t nSupplyB = b.nSupply+b.nShift;
    if (nSupplyA != nSupplyB) return false;
    
    multiprecision::uint128_t nShiftLastPartA(a.nShiftLastPart);
    multiprecision::uint128_t nShiftLastPartB(b.nShiftLastPart);
    multiprecision::uint128_t nShiftLastTotalA(a.nShiftLastTotal);
    multiprecision::uint128_t nShiftLastTotalB(b.nShiftLastTotal);
    
    multiprecision::uint128_t nPartNormA = nShiftLastPartA * nShiftLastTotalB;
    multiprecision::uint128_t nPartNormB = nShiftLastPartB * nShiftLastTotalA;
    
    return nPartNormA == nPartNormB;
}

bool operator!=(const CPegLevel &a, const CPegLevel &b) {
    return !operator==(a,b);
}

