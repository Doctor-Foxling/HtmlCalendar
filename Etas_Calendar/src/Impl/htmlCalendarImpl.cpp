#include "pch.h"
#include "htmlCalendarImpl.h"

namespace Etas {

	Shared<htmlCalendar> htmlCalendarImpl::Create()
	{
		return createShared<htmlCalendarImpl>();
	}

	htmlCalendarImpl::htmlCalendarImpl()
	{
		calHead = "<h1> Gregorian Calendar </h1>";

		weekNames = R"(
	  <tr>
		<th>Wk</th>
		<th>MON</th>
		<th>TUE</th>
		<th>WED</th>
		<th>THU</th>
		<th>FRI</th>
		<th>SAT</th>
		<th>SUN</th>
	  </tr>
	)";

		css = R"(<style>
	table, th, td, caption {
	  border: 1px solid black;
	  border-collapse: collapse;
	}

	caption {
		background-color: rgba(180, 200, 200, 0.5);
	}

	tr:nth-child(even) {
	  background-color: rgba(150, 182, 212, 0.4);
	}

	th:nth-child(even),td:nth-child(even) {
	  background-color: rgba(150, 212, 212, 0.4);
	}

	.split1 {
	  float: left;
	  top: 10%;
	  width: 33%;
	  z-index: 1;
	  top: 0;
	  overflow-x: hidden;
	  padding-top: 20px;
	}

	.split2 {
	  float: left;
	  width: 33%;
	  top: 10%;
	  left: 33%;
	  z-index: 1;
	  top: 0;
	  overflow-x: hidden;
	  padding-top: 20px;
	}

	.split3 {
	  float: right;
	  top: 10%;
	  left: 66%;
	  width: 33%;
	  z-index: 1;
	  top: 0;
	  overflow-x: hidden;
	  padding-top: 20px;
	}


	</style>)";
	}

	void htmlCalendarImpl::htmlHead(std::ofstream& myFile)
	{
		myFile << "<!DOCTYPE html><html><head>" << css << "</head><body>";
	}

	std::string htmlCalendarImpl::monthBody(const std::string& month)
	{
		std::stringstream body;
		body << R"(<table style = "width:10%; text-align:center">)";

		body << "<caption>" << month << "</caption>";

		return body.str();
	}

	std::string htmlCalendarImpl::weekDays(int day, int num, int& weekNum)
	{
		std::stringstream wkDays;
		wkDays << "<tr>" << "<td>" << weekNum << "</td>";
		int bp = 7;
		for (int i = 1; i < day; i++)
		{
			wkDays << "<td> </td>"; bp--;
		}

		for (int i = 1; i <= num; i++)
		{
			if (bp == 7)
				wkDays << "<tr>" << "<td>" << ++weekNum << "</td>";
			wkDays << "<td>" << i;
			wkDays << "</td>";
			bp--;
			if (bp == 0)
			{
				bp = 7;
				wkDays << "</tr>";
			}
		}

		if (bp != 7)
		{
			wkDays << "</tr>";
		}

		wkDays << "</table>";

		return wkDays.str();
	}

	bool htmlCalendarImpl::isLeapYear(int year)
	{
		if (year % 4 == 0)
		{
			if (year % 100 == 0)
			{
				if (year % 400 == 0)
					return true;
				else
					return false;
			}
			else
			{
				return true;
			}
		}
		return false;
	}

	void htmlCalendarImpl::monthGenerator(std::ofstream& myFile, const std::string& year)
	{
		int W;  // Week day to calculate for the 1st of a month
		int C = std::stoi(year.substr(0, 2)); // Century
		int Y = std::stoi(year.substr(2, 2));  // Year last 2 digits
		int Year = std::stoi(year);

		int m_offsets[12] = { 2, 5, 7, 10, 12, 15, 18, 20,23,25,28,31 };

		int weekNum = 1;

		int JanFeb_Y = Y - 1;


		for (int i = 10; i <= 11; i++)
		{
			int tmp = 1 + m_offsets[i] + JanFeb_Y + std::floor(JanFeb_Y / 4) + std::floor(C / 4) - (2 * C);
			W = tmp % 7;
			if (W < 0) W += 7;
			if (W == 0) W = 7;

			if (i == 10)
				myFile << monthBody(months[i]) << weekNames << weekDays(W, daysNum[i], weekNum); // Jan
			else // Feb
			{
				bool leap = isLeapYear(Year);
				if (leap)
					myFile << monthBody(months[i]) << weekNames << weekDays(W, 29, weekNum);
				else
					myFile << monthBody(months[i]) << weekNames << weekDays(W, 28, weekNum);
			}

		}
		for (int i = 0; i < 10; i++) {
			int tmp = 1 + m_offsets[i] + Y + std::floor(Y / 4) + std::floor(C / 4) - (2 * C);
			//if (W < 0) W = abs(W);
			W = tmp % 7;
			if (W < 0) W += 7;
			if (W == 0) W = 7;
			myFile << monthBody(months[i]) << weekNames << weekDays(W, daysNum[i], weekNum);
		}
	}

	void htmlCalendarImpl::adjYears(std::ofstream& myFile, std::string& year)
	{
		int y = std::stoi(year);
		for (int i = -1; i <= 1; i++) {
			year = std::to_string(y + i);
			myFile << "<h1>" << year << "</h1>" << R"(<div class="split1">)";
			monthGenerator(myFile, year);
			myFile << R"(</div>)";
		}
	}

	void htmlCalendarImpl::htmlEnd(std::ofstream& myFile)
	{
		myFile << "</body></html>";
		myFile.close();
	}
}