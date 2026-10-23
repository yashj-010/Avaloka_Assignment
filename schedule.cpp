#include <bits/stdc++.h>
using namespace std;

bool canAttendAllEvents(vector<pair<int, int>> eventList) {
    sort(eventList.begin(), eventList.end());

    for (int index = 1; index < eventList.size(); index++) {
        if (eventList[index].first < eventList[index - 1].second) {
            return false;
        }
    }

    return true;
}

int findMinimumRooms(vector<pair<int, int>> eventList) {
    if (eventList.empty()) {
        return 0;
    }

    sort(eventList.begin(), eventList.end());

    priority_queue<int, vector<int>, greater<int>> roomEndTimes;
    int maxRoomsNeeded = 0;

    for (int index = 0; index < eventList.size(); index++) {
        int eventStart = eventList[index].first;
        int eventEnd = eventList[index].second;

        while (!roomEndTimes.empty() &&
               roomEndTimes.top() <= eventStart) {
            roomEndTimes.pop();
        }

        roomEndTimes.push(eventEnd);

        maxRoomsNeeded = max(
            maxRoomsNeeded,
            static_cast<int>(roomEndTimes.size())
        );
    }

    return maxRoomsNeeded;
}

int main() {
    vector<pair<int, int>> morningMeetings = {
        {9, 10}, {10, 12}, {13, 14}
    };

    cout << "Example 1:" << endl;
    cout << "Can attend all events: "
         << (canAttendAllEvents(morningMeetings) ? "True" : "False")
         << endl;
    cout << "Minimum rooms required: "
         << findMinimumRooms(morningMeetings) << endl;

    vector<pair<int, int>> conferenceSessions = {
        {9, 12}, {10, 11}, {11, 13}, {12, 14}
    };

    cout << "\nExample 2:" << endl;
    cout << "Can attend all events: "
         << (canAttendAllEvents(conferenceSessions) ? "True" : "False")
         << endl;
    cout << "Minimum rooms required: "
         << findMinimumRooms(conferenceSessions) << endl;

    return 0;
}