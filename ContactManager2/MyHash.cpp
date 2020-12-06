#include "pch.h"
#include <iostream>
#include "MyHash.h"

using namespace std;

// 생성자, N : 버켓사이즈
MyHash::MyHash(int N) : bucketSize(N)
{
    // 버켓 배열 초기화
    bucketArray = new NODE * [N];
    for (int i = 0; i < N; i++)   bucketArray[i] = NULL;
}
// 소멸자
MyHash::~MyHash()
{
    deleteAll();

    delete[] bucketArray;
}
// b    : 키를 문자열 배열로 변경한 변수
// n    : 키배열의 길이
// idx  : 현재 인덱스
// a    : 해시상수
double MyHash::polynomial(char* b, int n, int idx, double a)
{
    if (n <= idx + 1) return 0.0;
    return (polynomial(b, n, idx + 1, a) + (a * b[idx] + b[idx + 1]));
}

// Hash 함수
int MyHash::hash_func(const string key)
{
    // 방법 1 : 나머지 연산
    //return (_key % bucketSize);

    // 방법 2 : 다항식(해시코드) --> 나머지(압축)
    char* b = (char*)key.c_str();
    double a = 0.5;

    int hcode = (int)polynomial(b, (int)key.size(), 0, a);

    return (hcode % bucketSize);
}

// 새로운 노드 삽입
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
// 키를 이용해서 노드 찾기
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
// 키를 이용해서 노드 삭제하기
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
            // 버켓의 첫번째 노드가 삭제 대상이면
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
