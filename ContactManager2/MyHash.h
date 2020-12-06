#ifndef _MYHASH_H_
#define _MYHASH_H_

#include <string>

using namespace std;

// 버켓에 삽입될 노드 클래스
class NODE
{
public:
	NODE()
	{
		name = mobile_tel = office_tel = home_tel = email = birth = "";
		next = NULL;
	}
	string name;
	string mobile_tel;
	string office_tel;
	string home_tel;
	string email;
	string birth;
	NODE* next;
};

// 해시 클래스
class MyHash
{
    NODE** bucketArray; // 버켓 배열
    int bucketSize;     // 버켓 사이즈
public:
    MyHash(int N = 10); // 생성자 (디폴트 버켓 사이즈는 10으로 설정)
    ~MyHash();

	NODE** getBucketArray() { return bucketArray; }

    NODE* searchNode(const string key);
    bool insertNode(const string key, const string mobile_tel, const string office_tel,
		const string home_tel, const string email, const string birth);
    void deleteNode(const string key);
    void deleteAll();
 //   void displayNodes();

private:
    int hash_func(const string key);   // 해시 함수
    double polynomial(char* b, int n, int idx, double a);   // 다항식 해시코드생성함수
};

#endif