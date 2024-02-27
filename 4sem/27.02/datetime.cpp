#include <iostream>
#include <cmath>
#include <string>

using namespace std;
string s;

class DateTimeSpan;

class DateTime
{ 
    private:
        double date_time;
        friend class DateTimeSpan;
        friend DateTimeSpan operator-(const DateTime& d, const DateTime& d1);
        friend DateTime operator+(const DateTime& d, const DateTimeSpan& s);
        friend DateTime operator-(const DateTime& d, const DateTimeSpan& s);
    public:
        DateTime(double date=0)
        {
            date_time = date;
        }
        DateTime(string dt)
        {
            date_time = 0.0;
            int day,month,year,time;
            day = stoi(dt.substr(0,2));
            month = stoi(dt.substr(3,2));
            year = stoi(dt.substr(6,4));
            time = (stoi(dt.substr(11,2)))*60*60 + (stoi(dt.substr(14,2)))*60 + (stoi(dt.substr(17,2))); // час+мин+сек
            if(year >= 2000)
            {
                date_time = day -1;
                for (int m = 1; m < month; m++)
                {
                    switch (m)
                    {
                        case 4:
                            date_time += 30;
                            break;
                        case 6:
                            date_time += 30;
                            break;
                        case 9:
                            date_time += 30;
                            break;
                        case 11:
                            date_time += 30;
                            break;
                        case 2:
                            if(year % 4 == 0 && year % 100 != 0)
                                date_time += 29;
                            else
                                date_time += 28;
                            break;
                        default:
                            date_time += 31;
                            break;
                    }
                }
                for (int y = 2000; y < year; y++){
                    if(y % 4 == 0 && y % 100 != 0){
                        date_time += 366;
                    }
                    else{
                        date_time += 365;
                    }
                }   
                date_time += double(time)/(3600*24);
            }
            else{
                 switch (month)
                    {
                    case 4:
                        date_time -= 30-day;
                        break;
                    case 6:
                        date_time -= 30-day;
                        break;
                    case 9:
                        date_time -= 30-day;
                        break;
                    case 11:
                        date_time -= 30-day;
                        break;

                    case 2:
                        if(year % 4 == 0 && year % 100 != 0){
                            date_time -= 29 - day;
                        }
                        else{
                            date_time -= 28 - day;
                        }
                        break;
                    default:
                        date_time -= 31 - day;
                        break;
                    }
                for (int m = 12; m > month; m--){
                    switch (m)
                    {
                    case 4:
                        date_time -= 30;
                        break;
                    case 6:
                        date_time -= 30;
                        break;
                    case 9:
                        date_time -= 30;
                        break;
                    case 11:
                        date_time -= 30;
                        break;

                    case 2:
                        if(year % 4 == 0 && year % 100 != 0){
                            date_time -= 29;
                        }
                        else{
                            date_time -= 28;
                        }
                        break;
                    default:
                        date_time -= 31;
                        break;
                    }
                }
                for (int y = 1999; y > year; y--){
                    if(y % 4 == 0 && y % 100 !=0){
                        date_time -= 366;
                    }
                    else{
                        date_time -= 365;
                    }
                }
                date_time -= 1 - double(time)/(3600*24);
            }
            // cout<<date_time<<endl;
        }
        void printdata()
        {
            int year = 2000, month = 1, hour = 0, min = 0, sec = 0;
            if (date_time >= 0)
            {
                int days = int(trunc(date_time));
                double time = date_time - days;
                while (days > 365)
                {
                    if (year % 4 == 0 && year % 100 != 0)
                        days -= 366;
                    else 
                        days -= 365;
                    year++;
                }
                while (days > 30)
                {
                    switch (month)
                    {
                        case 4:
                            days -= 30;
                            break;
                        case 6:  
                            days -= 30;
                            break;
                        case 9:
                            days -= 30;
                            break;
                        case 11:
                            days -= 30;
                            break;
                        case 2:
                            if(year % 4 == 0 && year % 100 != 0){
                                days -= 29;
                            }
                            else{
                                days -= 28;
                            }
                            break;
                        default:
                            days -= 31;
                            break;
                    }
                    month++;
                }
                if (days == 28 && month == 2 && !(year % 4 == 0 && year % 100 != 0))
                {
                    days -= 28;
                }
                else if (days == 29 && month == 2)
                {
                    if(year % 4 == 0 && year % 100 != 0)
                    {
                        days -= 29;
                    }
                    else
                    {
                        days -= 28;
                    }
                }
                else if (days == 30)
                {
                    switch (month)
                    {
                        case 4:
                            days -= 30;
                            break;
                        case 6:
                            days -= 30;
                            break;
                        case 9:
                            days -= 30;
                            break;
                        case 11:
                            days -= 30;
                            break;
                        case 2:
                            if(year % 4 == 0 && year % 100 != 0){
                                days -= 29;
                            }
                            else{
                                days -= 28;
                            }
                            break;
                        default:
                            break;
                    }
                }
                days++;
                sec = time * (3600*24);
                while(sec >= 60)
                {
                    if (min == 60)
                    {
                        hour ++;
                        min = 0;
                    }
                    if (hour == 24)
                    {
                        min = 0;
                        hour = 0;
                    }
                    sec -= 60;
                    min ++;
                }
                cout<<days<<"."<<month<<"."<<year<<" "<<hour<<":"<<min<<":"<<sec<<endl;
            }
            else 
            {
                // cout<<"xui"<<endl;
                double time; int days;
                int year = 2000, month = 12, hour = 24, min = 60, sec = 0;
                // int days = int((fabs(date_time))-0.5);
                if (int(fabs(date_time)) > int((fabs(date_time))-0.5))
                    days = int((fabs(date_time)));
                else
                    days = int((fabs(date_time))-0.5);
                // cout<<days<<endl;
                if ((fabs(date_time) +1 - days) != 0)
                    time = fabs((fabs(date_time)+1- int((fabs(date_time))+1))-1);
                else time = 0;
                days++;
                // cout<<time<<endl;
                while (days > 365)
                {
                    if (year % 4 == 0 && year % 100 != 0)
                        days -= 366;
                    else 
                        days -= 365;
                    year--;
                }
                while (days > 30)
                {
                    // cout<<"Go fuck yourself"<<endl;
                    // cout<<month<<endl;
                    // cout<<days<<endl;
                    switch (month)
                    {
                        case 4:
                            days -= 30;
                            break;
                        case 6:  
                            days -= 30;
                            break;
                        case 9:
                            days -= 30;
                            break;
                        case 11:
                            days -= 30;
                            break;
                        case 2:
                            if(year % 4 == 0 && year % 100 != 0){
                                days -= 29;
                            }
                            else{
                                days -= 28;
                            }
                            break;
                        default:
                            days -= 31;
                            break;
                    }
                    month--;
                    // cout<<days<<endl;
                }
                if (days == 28 && month == 2 && !(year % 4 == 0 && year % 100 != 0))
                {
                    days = abs(28 - days);
                }
                else if (days == 29 && month == 2)
                {
                    if(year % 4 == 0 && year % 100 != 0)
                    {
                        days = abs(29 - days);
                    }
                    else
                    {
                        days = abs(28 - days);
                    }
                }
                else if (days > 0)
                {
                    // cout<<"zalupa"<<endl;
                    // cout<<month<<endl;
                    switch (month)
                    {
                        case 4:
                            days = abs(30 - days);
                            break;
                        case 6:
                            days = abs(30 - days);
                            break;
                        case 9:
                            days = abs(30 - days);
                            break;
                        case 11:
                            days = abs(30 - days);
                            break;
                        case 2:
                            if(year % 4 == 0 && year % 100 != 0){
                                days = abs(29 - days);
                            }
                            else{
                                days = abs(28 - days);
                            }
                            break;
                        default:
                            days = abs(31 - days);
                            break;                                                  
                    }
                }
                days++;
                year--;
                sec = time * (3600*24);
                sec++;
                while(sec >= 60)
                {
                    if (min == 0)
                    {
                        hour --;
                        min = 60;
                    }
                    if (hour == 0)
                    {
                        min = 60;
                        hour = 24;
                    }
                    sec -= 60;
                    min --;
                }
                if (min <= 60 && min != 0)
                {
                    min = 60 - min;
                }   
                if (hour <= 24 && hour != 0)
                {
                    hour = 24 - hour;
                }
                cout<<days<<"."<<month<<"."<<year<<" "<<hour<<":"<<min<<":"<<sec<<endl; 
            } 
        } 
        void printdouble()
        {
            cout << date_time << endl;
        }        
};

class DateTimeSpan
{
    double span;
    friend class DateTime;
    friend DateTime operator+(const DateTime& d, const DateTimeSpan& s);
    friend DateTime operator-(const DateTime& d, const DateTimeSpan& s);
    public:
        DateTimeSpan(int days = 0, int hours = 0, int minutes = 0, int seconds = 0)
        {
            span = 0;
            double time = seconds + minutes*60  + hours*3600;
            span += days + time/(24*3600);
        }
        DateTimeSpan(double span1 = 0)
        {
            span = span1;
        }
        
        void printSpan()
        {
            cout << span << endl;
        }
        DateTimeSpan operator-() const 
        {
            return DateTimeSpan{-span};
        };
        DateTimeSpan operator-(const DateTimeSpan& sp) const 
        {
            return DateTimeSpan{span - sp.span};
        };
        DateTimeSpan operator+(const DateTimeSpan& sp) const 
        {
            return DateTimeSpan{span + sp.span};
        };
};

DateTimeSpan operator-(const DateTime& d, const DateTime& d1)
{
        return DateTimeSpan{d.date_time - d1.date_time};
};
DateTime operator+(const DateTime& d, const DateTimeSpan& s)
{
        return DateTime{d.date_time + s.span};
};
DateTime operator-(const DateTime& d, const DateTimeSpan& s)
{
        return DateTime{d.date_time - s.span};
};

int main()
{
    DateTime date1("12.05.1999 19:36:19");
    date1.printdata();
    DateTime date2("29.02.2004 00:00:00");  
    date2.printdata();
    DateTimeSpan span(date1 - date2);
    DateTime newdate(date2 + span);
    newdate.printdata();
    
}




