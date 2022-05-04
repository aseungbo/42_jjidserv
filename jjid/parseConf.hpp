#ifndef PARSECONF_HPP
# define PARSECONF_HPP

# include "uniHeader.hpp"
# include "WebServer.hpp"

int         checkArg(int ac, char **av, std::string& confPath);
std::string openConfigfile(std::string confPath);
void        makeServers(std::vector<Server>& servers, std::string config);

#endif