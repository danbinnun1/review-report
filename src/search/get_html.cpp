#include "get_html.hpp"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

#include <iostream>
#include <sstream>
#include <string>

#define HEADER_ACCEPT "Accept:text/html,application/xhtml+xml,application/xml"
#define HEADER_USER_AGENT "User-Agent:Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.17 (KHTML, like Gecko) Chrome/24.0.1312.70 Safari/537.17"
 

std::string get_html(const std::string &url)
{
    curlpp::Easy request;
 
    // Specify the URL
    request.setOpt(curlpp::options::Url(url));
 
    // Specify some headers
    std::list<std::string> headers;
    headers.push_back(HEADER_ACCEPT);
    headers.push_back(HEADER_USER_AGENT);
    request.setOpt(new curlpp::options::HttpHeader(headers));
    request.setOpt(new curlpp::options::FollowLocation(true));
 
    // Configure curlpp to use stream
    std::ostringstream responseStream;
    curlpp::options::WriteStream streamWriter(&responseStream);
    request.setOpt(streamWriter);
 
    // Collect response
    request.perform();
    std::string re = responseStream.str();
    return re;
}