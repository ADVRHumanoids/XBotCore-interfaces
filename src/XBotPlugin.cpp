/*
   Copyright (C) 2016 Italian Institute of Technology

   Developer:
       Luca Muratore (2016-, luca.muratore@iit.it)
       
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>       
   
*/

#include <XBotCore-interfaces/XBotPlugin.h>

namespace XBot {
    
XBotPlugin::XBotPlugin()
{

}

XBotPlugin::~XBotPlugin()
{

}

std::shared_ptr< XBot::IXBotJoint > XBotPlugin::get_xbotcore_joint()
{
    return _joint;
}

std::shared_ptr< XBot::IXBotChain > XBotPlugin::get_xbotcore_chain()
{
    return _chain;
}

std::shared_ptr< XBot::IXBotRobot > XBotPlugin::get_xbotcore_robot()
{
    return _robot;
}

std::shared_ptr< XBot::IXBotModel > XBotPlugin::get_xbotcore_model()
{
    return _model;
}

std::shared_ptr< XBot::IXBotFT > XBotPlugin::get_xbotcore_ft()
{
    return _ft;
}

    
}