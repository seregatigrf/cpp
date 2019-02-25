#pragma once

#include "date.h"
#include <set>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


using MyPair = pair<Date,string>;
ostream& operator<< (ostream& ost, const MyPair& p);
ostream& operator<< (ostream& ost, const vector<MyPair>&);
ostream& operator<< (ostream& ost, const vector<string>& events);

class Database {
public:
    void Add(const Date& date, const string& event);
    void Print(ostream& out) const;

    template <typename Func>
    vector<MyPair> FindIf(Func pred) const {
        vector<MyPair> result;
        for (const auto& entry : eventsByDate_)
        {
            for(const auto& event : entry.second)
            {
                if (pred(entry.first, event)) result.emplace_back(entry.first, event);
            }
        }
        return result;
    }

    template <typename Func>
    int RemoveIf(Func pred){
        int total = 0;
        for (auto& item : eventsByDate_)
        {
                int count =0 ;
                long del = 0;
                const Date& date = item.first;
                auto bound = stable_partition(item.second.begin(),
                                              item.second.end(),
                       [date,pred](const string& event){
                            bool Erase = pred(date, event);
                            return !Erase;
                        });
                if(bound != item.second.end()) del = item.second.end() - bound;
                for(int i = 0; i<del; ++i) {
                    if(!item.second.empty()) {
                        eventsUnique_.erase(make_pair(date, item.second.back()));
                        item.second.pop_back();
                        ++count;
                    }
                    else {
                        eventsByDate_.erase(date);
                    }
                }

                total+=count;
                if(item.second.empty()) eventsByDate_.erase(date);
        }
        return total;
    }
    string Last(const Date& date) const;
private:
    map<Date, vector<string>> eventsByDate_;
    set<MyPair> eventsUnique_;
};
