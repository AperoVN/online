/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4; fill-column: 100 -*- */
/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <config.h>
#include <string>
#include <vector>
#include "ConfigUtil.hpp"
#include "Util.hpp"
#include "Freemium.hpp"

namespace Freemium
{

bool FreemiumManager::_isFreemiumUser = false;
std::vector<std::string> FreemiumManager::FreemiumBlacklist;
std::string FreemiumManager::FreemiumBlacklistString;

FreemiumManager::FreemiumManager() {}

void FreemiumManager::generateBlacklist()
{
#ifdef ENABLE_FREEMIUM

    FreemiumBlacklistString = config::getString("freemium.disabled_commands", "");
    Util::trim(FreemiumBlacklistString);
    StringVector commandList = Util::tokenize(FreemiumBlacklistString);

    std::string command;
    for (std::size_t i = 0; i < commandList.size(); i++)
    {
        // just an extra check to make sure any whitespace does not sniff in command
        // or else command will not be recognized
        command = Util::trim_whitespace(commandList[i]);
        if(!command.empty())
        {
            FreemiumBlacklist.emplace_back(command);
        }
    }
#endif
}

const std::vector<std::string>& FreemiumManager::getFreemiumBlacklist()
{
    if (FreemiumBlacklist.empty())
        generateBlacklist();

    return FreemiumBlacklist;
}

const std::string FreemiumManager::getFreemiumBlacklistString()
{
    if (FreemiumBlacklistString.empty())
        generateBlacklist();

    return FreemiumBlacklistString;
}
} // namespace Freemium

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
