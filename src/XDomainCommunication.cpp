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

#include <XBotCore-interfaces/XDomainCommunication.h>
#include <sys/stat.h>
#include <fcntl.h>

namespace XBot {

template <typename DataType>
PublisherNRT<DataType>::PublisherNRT(const std::string& socket_name): _fd(-1)
{
    init(socket_name);
}

template <typename DataType>
PublisherNRT<DataType>::PublisherNRT(): _fd(-1)
{

}

template <typename DataType>
void PublisherNRT<DataType>::init(const std::string& socket_name)
{
    while( _fd < 0 ){
        _fd = open((pipe_prefix + socket_name).c_str(), O_WRONLY);
    }
}

template <typename DataType>
void PublisherNRT<DataType>::write(const DataType& data)
{
    int bytes = write(_fd, (void *)(&data), sizeof(data));
}

template <typename DataType>
void PublisherRT<DataType>::init(const std::string& socket_name)
{
    _pipe.init(socket_name);
}

template <typename DataType>
PublisherRT<DataType>::PublisherRT(const std::string& socket_name)
{
    init(socket_name);
}

template <typename DataType>
PublisherRT<DataType>::PublisherRT()
{

}

template <typename DataType>
void SubscriberNRT<DataType>::init(const std::string& socket_name)
{
    while( _fd < 0 ){
        _fd = open((pipe_prefix + socket_name).c_str(), O_RDONLY);
    }
}

template <typename DataType>
void PublisherRT<DataType>::write(const DataType& data)
{
    _pipe.xddp_write(data);
}

template <typename DataType>
void SubscriberNRT<DataType>::read(DataType& data)
{
    int bytes = read(_fd, (void *)&_last_received_data, sizeof(_last_received_data));
    data = _last_received_data;
}


template <typename DataType>
SubscriberNRT<DataType>::SubscriberNRT(const std::string& socket_name): _fd(-1)
{
    init(socket_name);
}

template <typename DataType>
SubscriberNRT<DataType>::SubscriberNRT(): _fd(-1)
{

}

template <typename DataType>
void SubscriberRT<DataType>::init(const std::string& socket_name)
{
    _pipe.init(socket_name);
}

template <typename DataType>
void SubscriberRT<DataType>::read(DataType& data)
{
    _pipe.xddp_read(_last_received_data);
    data = _last_received_data;
}

template <typename DataType>
SubscriberRT<DataType>::SubscriberRT(const std::string& socket_name)
{
    init(socket_name);
}

template <typename DataType>
SubscriberRT<DataType>::SubscriberRT()
{

}



}