#ifndef REQUEST_HPP
# define REQUEST_HPP

# include "uniHeader.hpp"
# include "RequestHeader.hpp"
# include <sstream> // istringstream

#define CHUNKED_SERVER 2
	
typedef struct s_StartLine
{
	int method;
	std::string http;
	std::string path;
} t_StartLine;
	
class Request
{
	private:
		std::string extension;
		t_StartLine startline;
		Header header;                                
		std::string body;
		bool cgi;//해당 요청(확장자 보고 판단 )이 cgi인지
		
	public:
		void clearRequest();
		std::vector<std::string> splitRequestMessage(std::string str, char delimiter);
		void initStartLine(const std::string &str);
		int methodToNum(const std::string& str);
		std::pair <std::string, std::string> initRequestHeader(const std::string header);
		// void parseRequestMessage(std::string requestMessage);
		void parseRequestMessage(std::string requestMessage, int serverStatus);

		t_StartLine getStartLine();
		Header& getHeader();
		std::string getBody();
		std::string getExtension();

		void addBody(std::string str);
		void setBody(std::string str);
		void setPath(std::string str)
		{
			startline.path = str;
		}
		class StartLineErr : public std::exception
		{
			const char *what() const throw ()
			{
				return ("StartLine Err\n");
			}
		};
};

#endif