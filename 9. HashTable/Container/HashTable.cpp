#include "HashTable.h"
#include <iostream>

// 해시 함수(Hash Function).
// 키를 어떠한 과정을 통해서 숫자로 변환해주는 함수.
// 여기에 붙이는 static은 전역이 아니라 private의 의미. cpp에서만 접근이 가능하다.
static int GenerateHash(const std::string& keyString)
{
    int hash = 0;

    // 문자열을 문자 배열로 활용해 해시 생성.
    const int length = static_cast<int>(keyString.size());

    for (int i = 0; i < length; i++)
    {
        //hash += keyString[i] * (i + 1);
        hash = 31 * hash + keyString[i]; // Hornor's method
    }

    // overflow방지.
    return std::abs(hash);
}

HashTable::HashTable()
{
}

HashTable::~HashTable()
{
}

bool HashTable::Add(const std::string& key, const std::string& value)
{
    // 해시 값을 생성한 후에 이를 버킷 인덱스로 변환.
    int bucketIndex = GenerateHash(key) % bucketCount;
    
    std::vector<Entry>& position = table[bucketIndex];

    const int length = static_cast<int>(position.size());
    for (int i = 0; i < length; i++)
    {
        // 중복된 키 확인.
        if (position[i].key == key)
            return false;
    }

    position.emplace_back(Entry(key, value));
    return true;
}

bool HashTable::Delete(const std::string& key)
{
    // 해시 값을 생성한 후에 이를 버킷 인덱스로 변환.
    int bucketIndex = GenerateHash(key) % bucketCount;

    std::vector<Entry>& position = table[bucketIndex];

    const int length = static_cast<int>(position.size());
    for (int i = 0; i < length; i++)
    {
        // 중복된 키 확인.
        if (position[i].key == key)
        {
            // 해당 키를 갖는 데이터를 2차 자료구조에서 제거.
            position.erase(position.begin() + i);
            return true;
        }
    }

    return false;
}

bool HashTable::Find(const std::string& key, Entry& outEntry)
{
    // 해시 값을 생성한 후에 이를 버킷 인덱스로 변환.
    int bucketIndex = GenerateHash(key) % bucketCount;

    std::vector<Entry>& position = table[bucketIndex];

    // 예외처리 - 2차 자료구조에 저장된 데이터가 없으면 실패.
    if (position.size() == 0)
        return false;


    const int length = static_cast<int>(position.size());
    for (int i = 0; i < length; i++)
    {
        // 중복된 키 확인.
        if (position[i].key == key)
        {
            // 해당 키를 갖는 데이터를 2차 자료구조에서 제거.
            //position.erase(position.begin() + i);
            outEntry = position[i];
            return true;
        }
    }


    return false;
}

// 출력 함수.
void HashTable::Print()
{
    for (const auto& container : table)
    {
        if (container.size() == 0)
            continue;

        // 데이터가 있으면 출력.
        for (const auto& item : container)
        {
            std::cout << "Key: " << item.key << " | Value: " << item.value << "\n";
        }
    }
}

// Getter
bool HashTable::IsEmpty() const
{
    int sum = 0;
    for (const auto& container : table)
    {
        sum += static_cast<int>(container.size());
    }
    
    return sum == 0;
}