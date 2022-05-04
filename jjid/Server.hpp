#ifndef SERVER_HPP
# define SERVER_HPP

# include "uniHeader.hpp"
# include "Request.hpp"
# include "Response.hpp"

// class Location;

class Server 
	{
		enum METHOD_NAME {GET, HEAD, POST, DELETE};
		private:
			std::vector<std::string> hosts;//Host 클래스로 만들어서 호스트정보는 저장하고 메서드로 아이피 주소 퉤 하는 거 만들고싶다 
			// std::vector<int> ports;//파싱할때 알아서 서버별로 포트 구분하세요~
			int port;
			// std::vector<Location> locations;
			int clientBodySize;//이거 리퀘스트냐?? 리스폰스냐? 나중에 찌가 알아오기
			std::vector<std::string> allowMethod;
			//서버 상태 필요할듯 청크에서 등
			Request currRequest;
			Response currResponse;//구조적으로 맘에 안듦 (jji, 29, 무직)
			
			// test
			int clientSocket;
			
		protected:
			std::map<std::vector<int>, std::string> errPage; // errCode , Page;
			
		public:
			// Server();
			
			// test
			int getClientSocket() { return clientSocket; }
			void setClientSocket(int socketFd) { this->clientSocket = socketFd; }
			
			// set
			void setHost(std::vector<std::string> hosts);
			void setPorts(int port);
			void setClientBodySize(int clientBodySize);
			// void setErrPage(std::map<std::vector<int>, std::string> errPage);
			// void setLocation(std::vector<Location> locations);
			
			// get
			std::vector<std::string> getHost();
			int getPort();
			int getClientBodySize();
			Request& getRequestClass();
			Response& getResponseClass();
			
			void processMethod();
			// Request Method
			void getMethod();
			void postMethod();
			void deleteMethod();
			void headMethod();
			
	};



#endif