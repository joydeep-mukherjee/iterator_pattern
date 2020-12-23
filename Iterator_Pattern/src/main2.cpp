#include<iostream>
#include<vector>
using namespace std;

template<typename T>
class Iterator {
 public:
 typedef T value_type;
 virtual bool hasNext() = 0;
 virtual T next() = 0;
};

//aggregator
class NameManager {
 typedef vector<string> NameCollection;
 NameCollection m_names;
 public:
 class NameIterator: public Iterator< NameCollection::value_type > {
        friend class NameManager;
 private:
        NameManager::NameCollection & m_names;
        NameManager::NameCollection::iterator m_itr;
        NameIterator(NameManager::NameCollection & names) : m_names(names), m_itr(m_names.begin()) {}
 public:
        virtual bool hasNext() {
                return m_itr!=m_names.end();
        }
        virtual NameIterator::value_type next(void) {
                NameIterator::value_type value = (*m_itr);
                ++m_itr;
                return value;
        }
 };
 void addName(NameCollection::value_type name){
        m_names.push_back(name);
 }
 NameIterator getNameIterator(void) {
        return NameIterator(m_names);
        }
 };

int main(void) {
        NameManager nameMgr;
        nameMgr.addName("Jobs");
        nameMgr.addName("Bill");
        nameMgr.addName("Larry");

        NameManager::NameIterator nameItr = nameMgr.getNameIterator();

        while(nameItr.hasNext()) {
                cout<<nameItr.next() << endl;
        }
        return 0;
}
