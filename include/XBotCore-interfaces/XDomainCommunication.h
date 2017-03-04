/*
 * Copyright (C) 2017 IIT-ADVR
 * Author: Arturo Laurenzi, Luca Muratore
 * email:  arturo.laurenzi@iit.it, luca.muratore@iit.it
 *
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

#ifndef __XBOTCORE_CROSS_DOMAIN_COMMUNICATION_H__
#define __XBOTCORE_CROSS_DOMAIN_COMMUNICATION_H__

#include <XBotCore-interfaces/pipes.h>

namespace XBot {

template <typename DataType>
class SubscriberRT {

public:

    SubscriberRT();
    explicit SubscriberRT(const std::string& socket_name);

    void init(const std::string& socket_name);

    void read(DataType& data);

private:

    DataType _last_received_data;
    XDDP_pipe _pipe;


};

template <typename DataType>
class PublisherRT {

public:

    PublisherRT();
    explicit PublisherRT(const std::string& socket_name);

    void init(const std::string& socket_name);

    void write(const DataType& data);

private:

    XDDP_pipe _pipe;


};

template <typename DataType>
class SubscriberNRT {

public:

    SubscriberNRT();
    explicit SubscriberNRT(const std::string& socket_name);

    void init(const std::string& socket_name);

    void read(DataType& data);

private:

    DataType _last_received_data;
    int _fd;


};

template <typename DataType>
class PublisherNRT {

public:

    PublisherNRT();
    explicit PublisherNRT(const std::string& socket_name);

    void init(const std::string& socket_name);

    void write(const DataType& data);

private:

    int _fd;


};


}
#endif
