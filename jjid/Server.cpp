#include "Server.hpp"

void aliasRoot(Location currLocation, std::string &path);
int checkPath(std::string &path);

void Server::setServerFd(int fd)
{
	serverFd = fd;
}
int Server::getServerFd()
{
	return (serverFd);
}

int *Server::getReadFd()
{
	return (readFd);
}
int *Server::getWriteFd()
{
	return (writeFd);
}
	
void Server::setReadFd()
{
	pipe(readFd);
}

void Server::setWriteFd()
{
	pipe(writeFd);
}


// int *Server::getCgiWriteFd()
// {
// 	return (cgiWriteFd);
// }
// int *Server::getCgiReadFd()
// {
// 	return (cgiReadFd);
// }

// std::string Server::getCgiBody()
// {
// 	return (cgiBody);
// }
// char Server::**getEnvp()
// {
// 	return (envp);
// }

// void Server::setCgiWriteFd(int cgiWriteFd[2])
// {
// 	this->cgiWriteFd = cgiWriteFd;
// }
// void Server::setCgiReadFd(int cgiReadFd[2])
// {
// 	this->cgiReadFd = cgiReadFd;
// }
// void Server::setCgiBody(std::string str)
// {
// 	this->cgiBody = str;
// }
// void Server::setEnvp(char **envp)
// {
// 	this->envp = envp;
// }

Location Server::getCurrLocation()
{
	return (this->currLocation);
}


void change_events(std::vector<struct kevent>& change_list, uintptr_t ident, int16_t filter, uint16_t flags, uint32_t fflags, intptr_t data, void *udata)
{
    struct kevent temp_event;

    EV_SET(&temp_event, ident, filter, flags, fflags, data, udata);
    change_list.push_back(temp_event);
}

void Server::setRoot(std::string root)
{
	this->root = root;
}

void Server::setHosts(std::vector<std::string> hosts)
{
	this->hosts = hosts;
}

void Server::setPort(int port)
{
	this->port = port;
}

void Server::setClientBodySize(int clientBodySize)
{
	this->clientBodySize = clientBodySize;
}

void Server::setIndex(std::vector<std::string> index)
{
	this->index = index;
}

void Server::setErrPage(std::map<std::vector<int>, std::string> errPage)
{
	this->errPage = errPage;
}

void Server::setLocation(std::vector<Location> locations)
{
	this->locations = locations;
};

void Server::setAllowMethod(std::vector<std::string> allowMethod)
{
	this->allowMethod = allowMethod;
}

std::string Server::getRoot()
{
	return (root);
}

std::vector<std::string> Server::getHost()
{
	return (hosts);
}

int Server::getPort()
{
	return (port);
}

int Server::getClientBodySize()
{
	return (clientBodySize);
}

std::vector<std::string> Server::getIndex()
{
	return (index);
}

std::map<std::vector<int>, std::string> Server::getErrPage()
{
	return (errPage);
}

std::vector<std::string> Server::getAllowMethod()
{
	return (allowMethod);
}

std::vector<Location> Server::getLocations()
{
	return (locations);
}

Request& Server::getRequestClass()
{
	return (currRequest);
}

Response& Server::getResponseClass()
{
	return (currResponse);
}

void Server::setErrorResponse(int statusCode)
{
	this->currResponse.setStatusCode(statusCode);
}
void Server::linkFdManager(std::map<int, int> &fdManager)
{
	this->fdManager = &fdManager;
}

void Server::linkChangeList(std::vector <struct kevent> &changeList)
{
	this->changeList = &changeList;
}

void Server::setFdManager(int fd, int serverFd)
{
	fdManager->insert(std::pair<int, int>(fd,serverFd));
}


char  **makeEnvp(const char *str)
{
	char *test = "REQUEST_METHOD=POST";
	char **test2 = new char*[5];
	test2[0] = test;
	test = "SERVER_PROTOCOL=HTTP/1.1";
	test2[1] = test;
	test = "PATH_INFO=/Users/hyopark/b2c/webserv/0525/jjid/YoupiBanane/youpi.bla" ;
	test2[2] = test;
	test = "CONTENT_LENGTH=5" ;
	test2[3] = test;
	test2[4] = NULL;
	
	return (test2);
}

// void Server::setCgiEvent(std::vector <struct kevent> &change_list)
// {
// 	envp = makeEnvp();
// 	pipe(cgiWriteFd);
// 	pipe(cgiReadFd);
// 	change_events(change_list, writeFd[0], EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
// 	change_events(change_list, writeFd[1], EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
// 	change_events(change_list, readFd[0], EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
// 	change_events(change_list, readFd[1], EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
// }

void Server::preProcess()
{
    //allow method확인할것 // -> 메소드 함수 안에서 로케이션 정보 있이 하거나, 여기서 로케이션 결정후 확인하거나
	//isAllowMethod();
	//405ls
	this->currResponse.setBody("");
	this->currResponse.setStatusCode(0);
	// this->currResponse.setHeader(0);
	std::string pathTmp = currRequest.getStartLine().path;
	std::cout << "ori pathTmp: "<< pathTmp << std::endl;
	currLocation = whereIsLocation(pathTmp);
	aliasRoot(currLocation, pathTmp);
	checkPath(pathTmp);
	currRequest.setPath(pathTmp);
	std::cout << "pathTmp: "<< pathTmp << std::endl;
	std::cout << "path2: "<< currRequest.getStartLine().path << std::endl;
}

// int Server::checkMethod()
// {
	
// }

void Server::processMethod(std::vector <struct kevent> &change_list)
{
	//allow method확인할것 // -> 메소드 함수 안에서 로케이션 정보 있이 하거나, 여기서 로케이션 결정후 확인하거나
	//isAllowMethod();
	//405ls
	// this->currResponse.setBody("");
	// this->currResponse.setStatusCode(0);
	// // this->currResponse.setHeader(0);
	// std::string path = this->currRequest.getStartLine().path;
	// this->currLocation = whereIsLocation(path);
	// aliasRoot(currLocation, path);
	// checkPath(path);
	//인자로 넘겨주기 >< 경로는 바꾸는거 그대로

	if (currLocation.getLocationType() == LOCATIONTYPE_NORMAL)
	{
		switch (currRequest.getStartLine().method)
		{
			case GET:
				getMethod(NO_HEAD);
				break;
			case HEAD:
				getMethod(YES_HEAD);
				break;
			case POST:
				postMethod();
				break;
			case -1:
				postMethod();
				break;
			case DELETE:
				deleteMethod();
				break;
			default:
				return (setErrorResponse(405));
				//405와 같은 에러코드 처리
				break;
		}
	}
	else if (currLocation.getLocationType() ==  LOCATIONTYPE_CGI)
	{		
		setReadFd();
		setWriteFd();
		
		setFdManager(writeFd[1], getServerFd());
		std::cout << "before write event size: " << change_list.size() << std::endl;
		change_events(change_list, writeFd[1], EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
		std::cout << "after write event size: " << change_list.size() << std::endl;
		// setFdManager(readFd[0], getServerFd());
		// change_events(change_list, readFd[0], EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
		return ;
	}
	// else if (currLocation.getLocationType() ==  LOCATIONTYPE_REDIR)
	// {
	// 	// redir
	// }

}

int checkPath(std::string &path)
{
	struct stat buf;
	std::string originPath = path;
	
	if (path[path.size()-1] == '/')
		path.erase(path.size()-1);
	if (stat(path.c_str(), &buf) == -1)
		return NOT;
	if (S_ISDIR(buf.st_mode)) // 테스트해본결과 /로 끝나던 말던 디렉토리면 걍 디렉토리임
	{
		path = originPath;
		return DIR;
	}
	else if (S_ISREG(buf.st_mode))
		return _FILE;
	// else if (S_ISLNK())
	// 	return LINK;
	else
		return (-1);
}

Location Server::getDefaultLocation()
{
	Location defaultLocation;
	std::vector<std::string > tmpIndex;
	tmpIndex.push_back("index.html");
	defaultLocation.setIndex(tmpIndex);
	defaultLocation.setPath("/");
	defaultLocation.setRoot(".");
	//TODO
	return defaultLocation;
}

// checkLocation(std::string locationPath, std::string originpath)
// {
	
// }

Location Server::whereIsLocation(std::string const & path)
{
	std::vector < Location > locationVector = this->getLocations();
	
	for (int idx = 0 ; idx < locationVector.size(); idx++)
	{
		std::string findPath = locationVector[idx].getPath();
		if (findPath.size() > 1 && findPath[findPath.size()-1] == '/')
		{
			findPath.erase(findPath.size() - 1);
			std::cout << "findpath erase : " << findPath << std::endl;
		}
		if (path.find(findPath) == 0)
		{
			// std::cout << "checkechekcek" <<std::endl;
			// if (locationVector[idx].getExtension().empty())//확장자가 없으면
			// {
			// 	std::cout << "empty?:"<< locationVector[idx].getExtension().empty() <<std::endl;
			// 	std::cout << "exten:"<< locationVector[idx].getExtension() <<std::endl;
			// 	return (locationVector[idx]);
			// }
			// else if (locationVector[idx].getExtension() == currRequest.getExtension())
			// {
			// 	std::cout << "req exten:"<< currRequest.getExtension() <<std::endl;
				return (locationVector[idx]);
			// }
		}
	}
	return (getDefaultLocation());
}

// Location Server::whereIsLocation(std::string &path, std::vector<Location> locations)
// {
// 	// TODO : 로케이션이 디렉토리형식인지 파일형식인지 구분해서 다르게 처리 할 것
// 	//테스트 해보니까 로케이션이 없는경우 기본값 로케이션으로 하나봄 -> 메서드로 기본값로케이션 반환하는 거 하나 만들어서 (로케이션 사이즈가 0이거나 일치하는 로케이션이 없을때)에 예외처리 ㄱ
// 	//김진베는 뎁스로 가능한 로케이션 다 확인해서 구체적인거-> 일반적인거 순서로 해본다함
// 	std::cout << getPort() << getRoot() << "size:: " << locations.size() <<std::endl;
//  	std::string originpath = path;
// 	if (locations.size() == 0 )//|| pathType == )
// 	{
// 		path = DEFAULT_ROOT + path;// TODO : 디폴트의 루트를 넣어줘야함
// 		return (getDefaultLocation());
// 	}
// 	//형식 맞춰줌 인덱싱으로 연산 빠를 거라고 예상...	
// 	// 아무거토 없을때 현재로케이션에 있/없 서버에 있/없
// 	path = this->getRoot() + path; // TODO : 만약 서버블록안에도 루트가 있게 구조한다면 서버의 루트를 넣어줘야함
// 	std::cout << "seuan : " << path <<std::endl;
// 	// if (path[path.length() - 1] != '/')
// 	if (path[path.length() - 1] != '/'  && checkPath(path) == DIR )
// 			path += '/';
// 	//반복문 돌면서 일치하는거 확인
// 	for (int idx = 0 ; idx < locations.size(); idx++)
// 	{
// 		std::cout << "loca get path" << locations[idx].getPath() << std::endl;
// 		std::string locationPath = locations[idx].getPath();
// 		// if (locationPath[locationPath.length() - 1] != '/')
// 		// 	locationPath += '/';
// 		// if (checkLocation(locationPath,originpath))
// 		// {
		
// 		if (originpath.find(locationPath) == 0)
// 		{
// 			std::cout <<  "ori : " << originpath <<std::endl;
// 			std::cout <<  "location : " << locationPath <<std::endl;
// 			if (locationPath.size() != originpath.size())
// 			{
// 				path = locations[idx].getRoot() + originpath.substr(locationPath.size(), originpath.size() - locationPath.size() );
// 				std::cout << "get root : " <<locations[idx].getRoot() << " sub :: " << originpath.substr(locationPath.size(), originpath.size() - locationPath.size() ) << "path : " << path << std::endl; 
// 			}
// 			else
// 				path = locations[idx].getRoot() ;
// 			std::cout <<  "sub : " << originpath.substr(locationPath.size(), originpath.size() - locationPath.size() ) <<std::endl;
			
// 			// path = locations[idx].getRoot() + originpath;
// 			// path = (originpath.replace(0,locationPath.size(),locations[idx].getRoot()));
// 			std::cout << "path::: " << path << " ori::: "<<originpath << std::endl;
// 			// path = originpath.erase(0, locations[idx].getRoot().size());
// 			// path = locations[idx].getRoot() + originpath.substr(path.size(),locationPath.size());
// 			// // TODO getRoot 도 / 추가 할지말지
// 			// path = locations[idx].getRoot() ;//+ "/" ;//+ originpath; // alias 면 이거 , root면 오리진페스 까지 추가하면됨
// 			return (locations[idx]);
// 		}
// 	}
// 	return (getDefaultLocation());
// }

int Server::serchIndex(std::string &path, Location currLocation)
{
	struct stat buf;
	
	std::cout << "serchIndex" <<std::endl;
	//설정 인덱스가 없으면 디폴트 인덱스(현재는 index.html파일) 추가 후 종료
	if (path[path.size() - 1] != '/')
	{
		setErrorResponse(403);
		return (ADD_INDEX_FAIL);
	}
	if (currLocation.getIndex().size() == 0)
	{
		std::cout << "index 0 \n" ;
		path += DEFAULT_INDEX;
		return ADDED_INDEX;
	}
	//설정 인덱스가 있다면 가장 처음 있는 파일 경로 넣고 종료
	std::vector<std::string> currIndex = currLocation.getIndex();
	for (int idx = 0; idx < currIndex.size(); idx++)
	{
		std::string tryIndexPath = path + currIndex[idx];
		std::cout << tryIndexPath <<std::endl;
		if (stat((tryIndexPath).c_str(), &buf) == 0)
		{
			path = tryIndexPath;
			std::cout <<"fin"<< path<<std::endl;
			return ADDED_INDEX;
		}
	}
	setErrorResponse(404);
	return (ADD_INDEX_FAIL);
}

void Server::readFile(int fd)
{
    std::string content;
    int n;
    char buf[1024];
    while ((n = read(fd, buf,1024)) > 0)
    {
        buf[n] = '\0';
        content += buf;
        memset(buf, 0, 1024);
    }
    std::cout << "[ only for test read content ]" << std::endl;
    std::cout << content << std::endl;
    std::cout << "[ only for test read content ]" << std::endl;
    this->currResponse.setStatusCode(200);
    this->currResponse.setBody(content);
    close(fd);
}

void Server::openFile(std::string path, int isHead)
{		
	int	fd = open(path.c_str(), O_RDONLY);
	
	if (fd != -1)
	{
		if (isHead == NO_HEAD)
		{
			setFdManager(fd, getServerFd());
			change_events(*changeList, fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0,0,NULL);
		}
	}
	else
	{
		close(fd);
		return (setErrorResponse(404));
	}
	if (isHead == YES_HEAD)
	{
		this->currResponse.setStatusCode(405);
		close(fd);
	}
	// std::cout << "\nopen call \n "<< path<<std::endl;
	// // 파일 읽기 준비
	// std::ifstream in(path);
	
	// std::string body;
	// if (in.is_open()) {
	// 	if (isHead == NO_HEAD)
	// 	{
	// 		// 위치 지정자를 파일 끝으로 옮긴다.
	// 		in.seekg(0, std::ios::end);
	// 		// 그리고 그 위치를 읽는다. (파일의 크기)
	// 		int size = in.tellg();
	// 		// 그 크기의 문자열을 할당한다.
	// 		body.resize(size);
	// 		// 위치 지정자를 다시 파일 맨 앞으로 옮긴다.
	// 		in.seekg(0, std::ios::beg);
	// 		// 파일 전체 내용을 읽어서 문자열에 저장한다.
	// 		in.read(&body[0], size);
	// 		// std::cout << body << std::endl;
	// 	}
	// }
	// else {
	// 	std::cout << path +  " " << "파일을 찾을 수 없습니다!" << std::endl;
	// 	in.close();
	// 	// throw (404);//catch해서 set다 호출할것 TODO
	// 	return (setErrorResponse(404));
	// 	// return;
	// }
	// if (isHead == NO_HEAD)
	// 	this->currResponse.setStatusCode(200);
	// else
	// 	this->currResponse.setStatusCode(405);
	// this->currResponse.setBody(body);
	
	// std::cout << "whereis test::::\n";
	// std::cout << "test:::: " << currResponse.writeResponseMessage()<<std::endl;
	// in.close();
	// return ;
}

std::string whereIsRoot(std::string path, Location currLocation)
{
	// std::string retPath;
	
	// path = 
	return ("." +currLocation.getRoot() + "/");
}

void aliasRoot(Location currLocation, std::string &path)
{
// path : /aaa
// locationpath : /aaa/
// root : ./ccc
// expect : ./ccc/

	std::string currRoot = currLocation.getRoot();
	std::string locationPath = currLocation.getPath();
	
	if (path[path.size() - 1 ] != '/')
		path = path + "/";
	std::string originPath = path;
	std::cout << "curr Rot : "  << currRoot << "lo path: "<< locationPath << "ori path :" <<  originPath << std::endl;
	path = currRoot + originPath.substr(locationPath.size(), originPath.size() - locationPath.size() ); 
}

void Server::getMethod(int isHead)
{
	
	std::string path = this->currRequest.getStartLine().path;
	// Location currLocation = whereIsLocation(path);
	// aliasRoot(currLocation, path);
	// 	// return (setErrorResponse(403));
	std::cout << "resul ::" << path << std::endl;
	int pathType = checkPath(path);
	switch (pathType)
	{
		case DIR ://디렉토리 안에 설정된 인덱스 파일들 탐색 해볼것임 ,  인덱스 파일 없다면(권한없어도) 403 // 만약 설정된 인덱스가 두개 이상이라면 첫번째꺼 // 만약 설정이 없다면 기본적으로 index.html 을 탐색함
			if (serchIndex(path, currLocation) == ADD_INDEX_FAIL)
				return ;
		case _FILE ://해당파일찾아볼것 마찬가지로 없다면 403	
			openFile(path, isHead);
			break;
		case NOT ://404
			return (setErrorResponse(404));
			/* throw 404 error */
			break;
		default:
			return (setErrorResponse(404));
			break;
	}
	
	
}

void Server::postMethod()
{
	// 기존 파일이 있는지 확인 후 있으면 수정, 없으면 크리에이트 , 디렉토리면...?일단 에러
	// 쿼리날리는거, 디비접근 등도 고려해야하는지 섭젝 읽어볼것
		// std::string path = this->currRequest.getStartLine().path;
	// path = "." + path;//root 키워드로 설정하기 설정 없다면 디폴트로 추가하기, 절대경로로 바꿀것
	// std::cout << "postmethod:: " << path << std::endl;
	// int pathType = checkPath(path);
	
	
	// std::string path = this->currRequest.getStartLine().path;
	// path = "." + path;//root 키워드로 설정하기 설정 없다면 디폴트로 추가하기, 절대경로로 바꿀것
	// int pathType = checkPath(path);
	// Location currLocation = whereIsLocation(path, locations);
	
	// return (setErrorResponse(405));
	std::string path = this->currRequest.getStartLine().path;
	Location currLocation = whereIsLocation(path);//find or  map match 등 다른이름 추천받음
	aliasRoot(currLocation, path);
	// path = "." + path;//root 키워드로 설정하기 설정 없다면 디폴트로 추가하기, 절대경로로 바꿀것 // 서버의 루트 먼저 붙이고 로케이션 붙이기
	
	int pathType = checkPath(path);
	serchIndex(path, currLocation);

	int fd;
	std::cout << "post result:" << path << std::endl;
	if (pathType == _FILE || pathType == DIR)
	{
		std::cout << "file " << std::endl;
		if ((fd = open(path.c_str(), O_WRONLY | O_APPEND | O_NONBLOCK, 0644)) == -1)
			return (setErrorResponse(500));
	}
	else if (pathType == NOT)
	{
		std::cout << "not " << std::endl;
		std::string dirPath = path.substr(0, path.find_last_of("/"));
		std::cout << dirPath << std::endl;
		mkdir(dirPath.c_str(),0777);
		if ((fd = open(path.c_str(), O_WRONLY | O_CREAT | O_NONBLOCK, 0644)) == -1)
			return (setErrorResponse(500));
	}
	else if (pathType == DIR)
	{   
		std::cout << "dir " << std::endl;
		return (setErrorResponse(403));
	}
	currResponse.setStatusCode(201);
	std::cout << "bbbbbbeutetful" << currRequest.getBody() << std::endl;
	// if (currRequest.getHeader().getContent()["Content-Length"][0] == '0')
	if (currRequest.getBody().size() != 0)
		write(fd, currRequest.getBody().c_str(), currRequest.getBody().size());
	else
		{
			std::cout << " 504:::"<<std::endl;
			currResponse.setStatusCode(405);
		}
	close(fd);
	
}

void Server::deleteMethod()
{
	std::string path = this->currRequest.getStartLine().path;
	path = "." + path;
	currResponse.setStatusCode(200);
	this->currResponse.setBody("complite delete");
	
	std::remove(path.c_str());
}

// void Server::headMethod()
// {
		
// }
