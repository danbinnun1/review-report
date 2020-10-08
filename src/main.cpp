#include "LinksTextCache.hpp"
#include "LinksCache.hpp"
#include <iostream>
int main(){
    std::string file="f.txt";
    grading::LinksCache* cache =new grading::LinksTextCache(file);
    cache->insertLink("aab");
    std::cout<<cache->linkInCache("tttt")<<"\n"<<cache->linkInCache("aab")<<std::endl;
    delete cache;
}