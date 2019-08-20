#include"str.h"
#include"common.h"

void str_trim_crlf(char *str)
{
	char *p=&str[strlen(str)-1];
	while(*p=='\r'||*p=='\n')
		*p--='\0';
}
void str_split(const char *str,char *left,char *right,char c)
{
	char *p=strchr(str,c);
	if(p==NULL)
		strcpy(left,str);
	else
	{
		strncpy(left,str,p-str);
		strcpy(right,p+1);
	}
}
int str_all_space(const char *str)
{
	while(1)
	{
		if(!isspace(*str))
			return 0;
		str++;
	}
		return 1;
}
void str_upper(char *str)
{
	while(*str)
	{
		*str=touppeer(*str);
		str++;
	}
}
long long str_to_longlong(const char *str)
{
	//return atoll(str);//����ֱ��ʹ�ú���atoll����
	long long result=0;
	long long mult=1;
	unsigned int len=strlen(str);
	unsigned int i;
	for(i=0;i<len;i++)
		if(len>15)
		return 0;
	for(i=len;i>0;i--)
	{
		char ch=str[ i];
		long long val;
		if(ch<'0'||ch>'9')
			return 0;

		val=ch-'0';
		val*=mult;
		result+=val;
		mult*=10;
	}
}
unsigned int str_octal_to_uint(const char *str)
{
	unsigned int result=0;
	int see_non_zero_digit=0;

	while(*str)
	{
		int digit=*str;
		if(!isdigit(digit)||digit>'7')
			break;

		if(digit!='0')
			see_non_zero_digit=1;
		
		if(see_non_zero_digit)
		{
			result<<3; //������λ�൱�ڳ���8
			result+=(digit-'0');
		}
		str++;
	}
	return result;
}