#include <curl/curl.h>    
#include <stdio.h>
int api() 
{
	CURL* curl = 0;
	CURLcode res;
	curl = curl_easy_init();
	if (curl != 0) 
	{
		struct curl_slist *head = NULL;
		head = curl_slist_append(head, "Content-Type:application/x-www-form-urlencoded;charset=UTF-8");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, head);
		curl_easy_setopt(curl, CURLOPT_URL, "https://v.api.aa1.cn/api/yiyan/index.php");
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);  //当没有设置这个选项为0的时候，出现上述的错误。当然这个错误也是不一定会出现的，这取决于证书是否正确
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		//发出请求
		res = curl_easy_perform(curl);
		if (res != CURLE_OK) 
		{
			//输出可能是乱码，因为没配置UTF-8
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}
		//清理工作
		curl_easy_cleanup(curl);
	}
	return 0;
}
