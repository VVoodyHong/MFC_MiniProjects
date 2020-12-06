#ifndef _MYHASH_H_
#define _MYHASH_H_

#include <string>

using namespace std;

// ���Ͽ� ���Ե� ��� Ŭ����
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

// �ؽ� Ŭ����
class MyHash
{
    NODE** bucketArray; // ���� �迭
    int bucketSize;     // ���� ������
public:
    MyHash(int N = 10); // ������ (����Ʈ ���� ������� 10���� ����)
    ~MyHash();

	NODE** getBucketArray() { return bucketArray; }

    NODE* searchNode(const string key);
    bool insertNode(const string key, const string mobile_tel, const string office_tel,
		const string home_tel, const string email, const string birth);
    void deleteNode(const string key);
    void deleteAll();
 //   void displayNodes();

private:
    int hash_func(const string key);   // �ؽ� �Լ�
    double polynomial(char* b, int n, int idx, double a);   // ���׽� �ؽ��ڵ�����Լ�
};

#endif