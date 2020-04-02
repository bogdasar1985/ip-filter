#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <range/v3/algorithm.hpp>
/**
 *  Оптимизация алгоритма:
 *  Т.к. наш массив уже отсортирован, то мы можем воспользоваться lower_bound или upper_bound,
 *  и итерироваться начиная с найденных элементов.
 *  
 *  Новый функционал:
 *  1. Сделать функции filter, функцией с переменным количеством аргументов.
 *  2. Либо, сделать одну функцию с четырьмя аргументами.
 *  3. Где "-" в одном из аргументов, будет означать то, что он не учитывается.
 * */
// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

bool less_lexicographic_compare(const std::vector<std::string>& first, const std::vector<std::string>& second)
{
    for(int i = 0; i < first.size(); i++)
    {
        if(std::stoi(first[i]) > std::stoi(second[i]))
        {
            return false;
        }
        if(std::stoi(first[i]) < std::stoi(second[i]))
        {
            return true;
        }
    }
    return false;  
}

bool filter(const std::vector<std::string>& ip, std::string first_byte)
{
    if(ip[0] == first_byte)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool filter(const std::vector<std::string>& ip, std::string first_byte, std::string second_byte)
{
    if(ip[0] == first_byte && ip[1] == second_byte)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool filter_any(const std::vector<std::string>& ip, std::string any_byte)
{
    for(auto it = ip.begin(); it != ip.end(); it++)
    {
        if(*it == any_byte)
        {
            return true;
        }
    }
    return false;
}

int main(int argc, char const *argv[])
{
    try
    {
        std::vector<std::vector<std::string>> ip_pool;

        for(std::string line; std::getline(std::cin, line);)    //Ввод в ip_pool
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // TODO reverse lexicographically sort
        std::sort(ip_pool.rbegin(), ip_pool.rend(), less_lexicographic_compare);

        for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip) //Вывод ip_pool
        {
            for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
            {
                if (ip_part != ip->cbegin())
                {
                    std::cout << ".";
                }
                std::cout << *ip_part;
            }
            std::cout << std::endl;
        }

        // TODO filter by first byte and output
        // ip = filter(1)
        for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip) //Вывод ip_pool
        {
            if(filter(*ip, "1"))
            {
                for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
                {
                    if (ip_part != ip->cbegin())
                    {
                        std::cout << ".";
                    }
                    std::cout << *ip_part;
                }
                std::cout << std::endl;
            }
        }

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)
        for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip) //Вывод ip_pool
        {
            if(filter(*ip, "46", "70"))
            {
                for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
                {
                    if (ip_part != ip->cbegin())
                    {
                        std::cout << ".";
                    }
                    std::cout << *ip_part;
                }
                std::cout << std::endl;
            }
        }

        // TODO filter by any byte and output
        // ip = filter_any(46)

        for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip) //Вывод ip_pool
        {
            if(filter_any(*ip, "46"))
            {
                for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
                {
                    if (ip_part != ip->cbegin())
                    {
                        std::cout << ".";
                    }
                    std::cout << *ip_part;
                }
                std::cout << std::endl;
            }
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
