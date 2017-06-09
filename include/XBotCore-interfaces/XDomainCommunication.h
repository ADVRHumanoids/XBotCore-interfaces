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

#include <XBotCore-interfaces/XBotPipes.h>

namespace XBot {

/**
* @brief Class which acts as a std::string of maximum length equal to 40
* chars. It is commonly used to send textual commands over XDDP pipes.
*/
class Command {

public:

    Command(const std::string& string = "")
    {
        int str_end = std::min((int)string.length(), 40);
        int i;
        for( i = 0; i < str_end; i++ ){
            char_array[i] = string[i];
        }
        char_array[i] = '\0';
    }

    std::string str() const
    {
        return std::string(char_array);
    }

    Command& operator=(const std::string& string)
    {
        *this = Command(string);
        return *this;
    }

    operator std::string()
    {
        return str();
    }

private:

    char char_array[41];

};

template <typename DataType>
class Subscriber {

public:
    
    Subscriber();
    explicit Subscriber(const std::string& socket_name);

    virtual void init(const std::string& socket_name) = 0;

    virtual bool read(DataType& data) = 0;

protected:
    
    std::string _name;
};

template <typename DataType>
class Publisher {

public:

    Publisher();
    explicit Publisher(const std::string& socket_name);

    virtual void init(const std::string& socket_name) = 0;

    virtual void write(const DataType& data) = 0;

protected:
    
    std::string _name;
};

template <typename DataType>
class SubscriberRT : public Subscriber<DataType> {

public:

    SubscriberRT();
    explicit SubscriberRT(const std::string& socket_name);

    virtual void init(const std::string& socket_name);

    virtual bool read(DataType& data);

private:

    XDDP_pipe::Ptr _pipe;


};

template <typename DataType>
class PublisherRT : public Publisher<DataType> {

public:

    PublisherRT();
    explicit PublisherRT(const std::string& socket_name);

    virtual void init(const std::string& socket_name);

    virtual void write(const DataType& data);

private:

    XDDP_pipe::Ptr _pipe;


};

template <typename DataType>
class SubscriberNRT : public Subscriber<DataType>  {

public:

    SubscriberNRT();
    explicit SubscriberNRT(const std::string& socket_name);

    virtual void init(const std::string& socket_name);

    virtual bool read(DataType& data);

private:

    int _fd;


};

template <typename DataType>
class PublisherNRT : public Publisher<DataType> {

public:

    PublisherNRT();
    explicit PublisherNRT(const std::string& socket_name);

    virtual void init(const std::string& socket_name);

    virtual void write(const DataType& data);

private:

    int _fd;


};


}

/* IMPLEMENTATION */

#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>

namespace XBot {

    
template <typename DataType>
PublisherNRT<DataType>::PublisherNRT() : 
    _fd(-1)
{

}

template <typename DataType>
PublisherNRT<DataType>::PublisherNRT(const std::string& socket_name) : 
    _fd(-1),
    Publisher<DataType>(socket_name)
{
    init(socket_name);
}

template <typename DataType>
void PublisherNRT<DataType>::init(const std::string& socket_name)
{
    while( _fd < 0 ){
        _fd = open((pipe_prefix + socket_name).c_str(), O_WRONLY | O_NONBLOCK);
        std::cout << "Waiting for some RT subscriber to create pipe " << pipe_prefix+socket_name << "..." << std::endl;
//         perror("Open: ");
        if(_fd < 0)
            sleep(1);
    }
}

template <typename DataType>
void PublisherNRT<DataType>::write(const DataType& data)
{
    int bytes = ::write(_fd, (void *)(&data), sizeof(data));
}



template <typename DataType>
PublisherRT<DataType>::PublisherRT()
{
    _pipe = std::make_shared<XBot::XDDP_pipe>();
}

template <typename DataType>
PublisherRT<DataType>::PublisherRT(const std::string& socket_name) : 
    Publisher<DataType>(socket_name)
{
    _pipe = std::make_shared<XBot::XDDP_pipe>();
    init(socket_name);
}

template <typename DataType>
void PublisherRT<DataType>::init(const std::string& socket_name)
{
    _pipe->init(socket_name);
}

template <typename DataType>
void PublisherRT<DataType>::write(const DataType& data)
{
    _pipe->xddp_write(data);
}



template <typename DataType>
SubscriberNRT<DataType>::SubscriberNRT() : 
    _fd(-1)
{

}

template <typename DataType>
SubscriberNRT<DataType>::SubscriberNRT(const std::string& socket_name) : 
    _fd(-1),
    Subscriber<DataType>(socket_name)
{
    init(socket_name);
}

template <typename DataType>
void SubscriberNRT<DataType>::init(const std::string& socket_name)
{
    while( _fd < 0 ){
        _fd = open((pipe_prefix + socket_name).c_str(), O_RDONLY | O_NONBLOCK);
        std::cout << "Waiting for some RT publisher to create pipe " << pipe_prefix+socket_name << "..." << std::endl;
        if(_fd < 0)
            sleep(1);
    }
}

template <typename DataType>
bool SubscriberNRT<DataType>::read(DataType& data)
{
    int bytes = 1;
    bool success = false;

    while( bytes > 0 ){
        bytes = ::read(_fd, (void *)&data, sizeof(data));
        success = success || bytes > 0;
    }

    return success;
}



template <typename DataType>
SubscriberRT<DataType>::SubscriberRT()
{
    _pipe = std::make_shared<XBot::XDDP_pipe>();
}

template <typename DataType>
SubscriberRT<DataType>::SubscriberRT(const std::string& socket_name) : 
    Subscriber<DataType>(socket_name)
{
    _pipe = std::make_shared<XBot::XDDP_pipe>();
    init(socket_name);
}

template <typename DataType>
void SubscriberRT<DataType>::init(const std::string& socket_name) 
{
    _pipe->init(socket_name);
}

template <typename DataType>
bool SubscriberRT<DataType>::read(DataType& data)
{
    int bytes = 1;
    bool success = false;

    while( bytes > 0 ){
        bytes = _pipe->xddp_read(data);
        success = success || bytes > 0;
    }

    return success;
}




template <typename DataType>
Subscriber<DataType>::Subscriber() : 
    _name("")
{

}

template <typename DataType>
Subscriber<DataType>::Subscriber(const std::string& socket_name) : 
    _name(socket_name)
{

}

template <typename DataType>
Publisher<DataType>::Publisher() : 
    _name("")
{

}

template <typename DataType>
Publisher<DataType>::Publisher(const std::string& socket_name) : 
    _name(socket_name)
{

}




}

#endif
