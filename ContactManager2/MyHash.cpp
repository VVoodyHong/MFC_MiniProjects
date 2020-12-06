#include "pch.h"
#include <iostream>
#include "MyHash.h"

using namespace std;

// ������, N : ���ϻ�����
MyHash::MyHash(int N) : bucketSize(N)
{
    // ���� �迭 �ʱ�ȭ
    bucketArray = new NODE * [N];
    for (int i = 0; i < N; i++)   bucketArray[i] = NULL;
}
// �Ҹ���
MyHash::~MyHash()
{
    deleteAll();

    delete[] bucketArray;
}
// b    : Ű�� ���ڿ� �迭�� ������ ����
// n    : Ű�迭�� ����
// idx  : ���� �ε���
// a    : �ؽû��
double MyHash::polynomial(char* b, int n, int idx, double a)
{
    if (n <= idx + 1) return 0.0;
    return (polynomial(b, n, idx + 1, a) + (a * b[idx] + b[idx + 1]));
}

// Hash �Լ�
int MyHash::hash_func(const string key)
{
    // ��� 1 : ������ ����
    //return (_key % bucketSize);

    // ��� 2 : ���׽�(�ؽ��ڵ�) --> ������(����)
    char* b = (char*)key.c_str();
    double a = 0.5;

    int hcode = (int)polynomial(b, (int)key.size(), 0, a);

    return (hcode % bucketSize);
}

// ���ο� ��� ����
bool MyHash::insertNode(const string key, const string mobile_tel, const string office_tel,
    const string home_tel, const string email, const string birth)
{
    NODE* t = new NODE;
    t->name = key;
    t->mobile_tel = mobile_tel;
    t->office_tel = office_tel;
    t->home_tel = home_tel;
    t->email = email;
    t->birth = birth;
    t->next = NULL;

    int bucket = hash_func(key);

    if (bucketArray[bucket] == NULL)
        bucketArray[bucket] = t;
    else
    {
        NODE* _t = bucketArray[bucket];
        while (1)
        {
            if (_t->next == NULL) break;
            _t = _t->next;
        }
        _t->next = t;
    }

    return true;
}
// Ű�� �̿��ؼ� ��� ã��
NODE* MyHash::searchNode(const string key)
{
    int bucket = hash_func(key);
    NODE* t = bucketArray[bucket];

    if (t == NULL)  return NULL;

    while (1)
    {
        if (t->name == key) return t;
        t = t->next;
        if (t == NULL) break;
    }

    return NULL;
}
// Ű�� �̿��ؼ� ��� �����ϱ�
void MyHash::deleteNode(const string key)
{
    int bucket = hash_func(key);
    NODE* t = bucketArray[bucket];
    NODE* prev = NULL;

    if (t == NULL)  return;

    while (1)
    {
        if (t->name == key)
        {
            // ������ ù��° ��尡 ���� ����̸�
            if (prev == NULL)
                bucketArray[bucket] = t->next;
            else
                prev->next = t->next;
            delete t;
            return;
        }
        prev = t;
        t = prev->next;
        if (t == NULL) break;
    }
}
void MyHash::deleteAll()
{
    cout << "deleteAll()" << endl;

    NODE* t, * _t;
    for (int i = 0; i < bucketSize; i++)
    {
        t = bucketArray[i];

        if (t == NULL)  continue;

        while (1)
        {
            _t = t;
            t = t->next;

            delete _t;

            if (t == NULL) break;
        }
    }
}

//void MyHash::displayNodes()
//{
//    int count = 0;
//    NODE* t;
//    for (int i = 0; i < bucketSize; i++)
//    {
//        t = bucketArray[i];
//
//        cout << "bucket : " << i;
//
//        if (t == NULL)
//        {
//            cout << "\tNone" << endl;
//            continue;
//        }
//        cout << "\t";
//        while (1)
//        {
//            count++;
//            cout << "[" << t->key << "," << t->name << "]";
//            t = t->next;
//            if (t == NULL) break;
//        }
//        cout << endl;
//    }
//    cout << "==============================================" << endl;
//    cout << "Total Count : " << count << endl;
//    cout << "==============================================" << endl;
//}
