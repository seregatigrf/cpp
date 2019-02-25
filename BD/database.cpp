#include "database.h"
#include <sstream>
void Database::Add(const Date& date, const string& event)
{
    if(!eventsUnique_.count({date, event}))
    {
        eventsByDate_[date].push_back(event);
        eventsUnique_.insert({date, event});
    }
}
void Database::Print(ostream& out) const
{
    for (const auto& Day : eventsByDate_){
            for(const string& event : Day.second){
                out << Day.first;
                out << " " << event << endl;
        }
    }
}
string Database::Last(const Date& date) const
{
    string s;
    auto firstGreaterIt = eventsByDate_.upper_bound(date);
    if (firstGreaterIt!=begin(eventsByDate_))
    {
        auto lastNotGreaterIt = prev(firstGreaterIt);
        //if there are events at this date...(opposite should never occur)
        if ( ! lastNotGreaterIt->second.empty() ) {
            //            auto d2 = lastNotGreaterIt->first;
            stringstream ss;
            ss << lastNotGreaterIt->first;
            s = ss.str() + " " + lastNotGreaterIt->second.back();
        }
        return s;
    } else throw std::invalid_argument("No entries");
}

ostream& operator<<(ostream& out, const MyPair& entry) {
    out << entry.first << " " << entry.second;
    return out;
}

ostream& operator<< (ostream& out, const vector<string>& events){
    out << "{ ";
    bool first = true;
    for(const auto& event: events){
        if(!first) out << ", ";
        out << event;
        first = false;
    }
    return out;
}

ostream& operator<< (ostream& out, const vector<MyPair>& p){
    for(auto& item: p){
        out << item.first << " " << item.second << "\n";
    }
    return out;
}
