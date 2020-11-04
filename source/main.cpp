#include <iostream>
#include "util/sutils.h"

class CStringUtils
{
public:
	static void SplitStr(const std::string &str, std::vector<std::string> &vec, const char *splite)
	{
		size_t dwPos = 0;
		std::string strSubstr;
		std::string strTemp = str;
		size_t spLen = strlen(splite);

		while (true)
		{
			dwPos = strTemp.find(splite);
			if (dwPos != std::string::npos)
			{
				strSubstr = strTemp.substr(0, dwPos);
				vec.push_back(strSubstr);
				strTemp = strTemp.substr(dwPos + spLen, strTemp.length());
			}
			else
			{
				vec.push_back(strTemp);
				break;
			}
		}
	}
};


void parseBusi_Id(std::string &param)
{
	sp::str_arr par_arr;
	std::string strValue;
	size_t dwBusiIdSize = 0;
	const char *pchStr = "busi_id=";

	std::string strTail = param.substr(param.find(pchStr) + strlen(pchStr)); //pchStr后面的字符
	
	sp::split_str(strTail.c_str(), par_arr, "=", true, true, true);
	if (1 == par_arr.size())
	{
		dwBusiIdSize = strTail.size();
		strValue = par_arr[0];//获取***,***,***
	}
	else if(par_arr.size() > 1)
	{
		dwBusiIdSize = par_arr[0].find_last_of(',') + 1; //获取***,***,***长度
		strValue = par_arr[0].substr(0, par_arr[0].find_last_of(','));//获取***,***,***
	}
	else
	{
		std::cout << "error !\n";
	}
	 
	std::cout << "strValue:" << strValue << std::endl;
	dwBusiIdSize += strlen(pchStr);
	param.erase(param.find(pchStr), dwBusiIdSize);//删除busi_id=***,***,***
	if (1 == par_arr.size())
	{
		param.erase(param.find_last_of(','), 1);
	}
}

int main(int argc, char** argv)
{
	std::string param = "appid=MIME1000,aue=speex-wb,auf=audio/L16,rate=16000,svc=iat,session_hotword=你想干啥啊,domain=robot_ara,node_next=我不想干啥,type=1,url=172.31.97.33:9172,busi_id=,";//472CB1e,rwfhsa4,324808,extend_params = { \"params\":\"iat_best = 5, vad = 1\"}";
	
	parseBusi_Id(param);
	std::cout << param << std::endl;
	sp::str_arr par_arr;
	sp::split_str(param.c_str(), par_arr, ",", true, true, true);

	for (size_t i = 0; i < par_arr.size(); i++)
	{
		sp::str_arr strKV;
		sp::split_str(par_arr[i].c_str(), strKV, "=", true, true, true);
		if (2 == strKV.size())
		{
			printf("Key:%s, Val:%s\n", strKV[0].c_str(), strKV[1].c_str());
		}
		else
		{
			for (size_t dwIdx = 0; dwIdx < strKV.size(); ++dwIdx)
			{
				printf("Value:%s\n", strKV[dwIdx].c_str());
			}
		}
	}

	getchar();
	return 0;
}