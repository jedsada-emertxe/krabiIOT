#pragma once
#ifndef ARDUINO_DS323X_DATETIME_H
#define ARDUINO_DS323X_DATETIME_H

// namespace arduino {
// namespace ds323x {

// port of https://github.com/adafruit/RTClib

    class TimeSpan
    {
    protected:

        int32_t _seconds;   ///< Actual TimeSpan value is stored as seconds

    public:

        TimeSpan (const int32_t seconds = 0)
        : _seconds(seconds)
        {}
        TimeSpan (const int16_t days, const int8_t hours, const int8_t minutes, const int8_t seconds)
        : _seconds((int32_t)days * 86400L + (int32_t)hours * 3600 + (int32_t)minutes * 60 + seconds)
        {}
        TimeSpan (const TimeSpan& copy)
        : _seconds(copy._seconds)
        {}

        int16_t days() const
        {
            return _seconds / 86400L;
        }
        int8_t  hours() const
        {
            return _seconds / 3600 % 24;
        }
        int8_t  minutes() const
        {
            return _seconds / 60 % 60;
        }
        int8_t  seconds() const
        {
            return _seconds % 60;
        }
        int32_t totalseconds() const
        {
            return _seconds;
        }

        TimeSpan operator+(const TimeSpan& right)
        {
            return TimeSpan(_seconds+right._seconds);
        }
        TimeSpan operator-(const TimeSpan& right)
        {
            return TimeSpan(_seconds-right._seconds);
        }

    };

    class DateTime
    {

    protected:

        uint8_t yOff;   ///< Year offset from 2000
        uint8_t m;      ///< Month 1-12
        uint8_t d;      ///< Day 1-31
        uint8_t hh;     ///< Hours 0-23
        uint8_t mm;     ///< Minutes 0-59
        uint8_t ss;     ///< Seconds 0-59

        static constexpr uint32_t SECONDS_FROM_1970_TO_2000 {946684800};
        const uint8_t daysInMonth[12] {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    public:

        DateTime (uint32_t t = SECONDS_FROM_1970_TO_2000)
        {
            t -= SECONDS_FROM_1970_TO_2000;    // bring to 2000 timestamp from 1970

            ss = t % 60;
            t /= 60;
            mm = t % 60;
            t /= 60;
            hh = t % 24;
            uint16_t days = t / 24;
            uint8_t leap;
            for (yOff = 0; ; ++yOff) {
                leap = yOff % 4 == 0;
                if (days < 365 + leap)
                break;
                days -= 365 + leap;
            }
            for (m = 1; ; ++m) {
                uint8_t daysPerMonth = daysInMonth[m - 1];
                if (leap && m == 2)
                ++daysPerMonth;
                if (days < daysPerMonth)
                break;
                days -= daysPerMonth;
            }
            d = days + 1;
        }

        DateTime (const uint16_t year, const uint8_t month, const uint8_t day, const uint8_t hour = 0, const uint8_t min = 0, const uint8_t sec = 0)
        {
            if (year >= 2000) yOff = year - 2000;
            else              yOff = year;
            m = month;
            d = day;
            hh = hour;
            mm = min;
            ss = sec;
        }

        DateTime (const DateTime& copy)
        : yOff(copy.yOff) , m(copy.m) , d(copy.d) , hh(copy.hh), mm(copy.mm), ss(copy.ss)
        {}

        // DateTime (const char* date, const char* time)
        // {
        //     // sample input: date = "Dec 26 2009", time = "12:34:56"
        //     yOff = conv2d(date + 9);
        //     // Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec
        //     switch (date[0]) {
        //         case 'J': m = (date[1] == 'a') ? 1 : ((date[2] == 'n') ? 6 : 7); break;
        //         case 'F': m = 2; break;
        //         case 'A': m = date[2] == 'r' ? 4 : 8; break;
        //         case 'M': m = date[2] == 'r' ? 3 : 5; break;
        //         case 'S': m = 9; break;
        //         case 'O': m = 10; break;
        //         case 'N': m = 11; break;
        //         case 'D': m = 12; break;
        //     }
        //     d = conv2d(date + 4);
        //     hh = conv2d(time);
        //     mm = conv2d(time + 3);
        //     ss = conv2d(time + 6);
        // }

        // DateTime (const __FlashStringHelper* date, const __FlashStringHelper* time);
        // char* toString(char* buffer);

        uint16_t year() const { return 2000 + yOff; }
        uint8_t month() const { return m; }
        uint8_t day() const { return d; }
        uint8_t hour() const { return hh; }
        uint8_t minute() const { return mm; }
        uint8_t second() const { return ss; }

        uint16_t yearOffset() const { return yOff; }

        uint8_t dayOfTheWeek() const
        {
            uint16_t day = date2days(yOff, m, d);
            return (day + 6) % 7; // Jan 1, 2000 is a Saturday, i.e. returns 6
        }

        /** 32-bit times as seconds since 1/1/2000 */
        long secondstime() const
        {
            long t;
            uint16_t days = date2days(yOff, m, d);
            t = time2long(days, hh, mm, ss);
            return t;
        }

        /** 32-bit times as seconds since 1/1/1970 */
        uint32_t unixtime(void) const
        {
            uint32_t t;
            uint16_t days = date2days(yOff, m, d);
            t = time2long(days, hh, mm, ss);
            t += SECONDS_FROM_1970_TO_2000;  // seconds from 1970 to 2000

            return t;
        }

        /** ISO 8601 Timestamp function */
        enum timestampOpt{
            TIMESTAMP_FULL, // YYYY-MM-DDTHH:MM:SS
            TIMESTAMP_TIME, // HH:MM:SS
            TIMESTAMP_DATE  // YYYY-MM-DD
        };

        String timestamp(timestampOpt opt = TIMESTAMP_FULL)
        {
            char buffer[20];

            // Generate timestamp according to opt
            switch (opt) {
            case TIMESTAMP_TIME:
                // Only time
                sprintf(buffer, "%02d:%02d:%02d", hh, mm, ss);
                break;
            case TIMESTAMP_DATE:
                // Only date
                sprintf(buffer, "%d-%02d-%02d", 2000 + yOff, m, d);
                break;
            default:
                // Full
                sprintf(buffer, "%d-%02d-%02dT%02d:%02d:%02d", 2000 + yOff, m, d, hh, mm,
                        ss);
            }
            return String(buffer);
        }

        DateTime operator+(const TimeSpan& span)
        {
            return DateTime(unixtime()+span.totalseconds());
        }
        DateTime operator-(const TimeSpan& span)
        {
            return DateTime(unixtime()-span.totalseconds());
        }
        TimeSpan operator-(const DateTime& right)
        {
            return TimeSpan(unixtime()-right.unixtime());
        }
        bool operator<(const DateTime& right) const
        {
            return unixtime() < right.unixtime();
        }
        bool operator>(const DateTime& right) const
        {
            return right < *this;
        }
        bool operator<=(const DateTime& right) const
        {
            return !(*this > right);
        }
        bool operator>=(const DateTime& right) const
        {
            return !(*this < right);
        }
        bool operator==(const DateTime& right) const
        {
            return unixtime() == right.unixtime();
        }
        bool operator!=(const DateTime& right) const
        {
            return !(*this == right);
        }

    protected:

        uint16_t date2days(const uint16_t year, const uint8_t m, const uint8_t d) const
        {
            uint16_t y;
            if (year >= 2000) y = year - 2000;
            else              y = year;
            uint16_t days = d;
            for (uint8_t i = 1; i < m; ++i)
                days += daysInMonth[i - 1];
            if (m > 2 && y % 4 == 0)
                ++days;
            return days + 365 * y + (y + 3) / 4 - 1;
        }

        static long time2long(const uint16_t days, const uint8_t h, const uint8_t m, const uint8_t s)
        {
            return ((days * 24L + h) * 60 + m) * 60 + s;
        }
    };

// } // namespace ds323x
// } // namespace arduino

#endif // ARDUINO_DS323X_DATETIME_H
