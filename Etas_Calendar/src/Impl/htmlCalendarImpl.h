#pragma once

#include "Abstract\htmlCalendar.h"

namespace Etas {

	class htmlCalendarImpl : public htmlCalendar
	{
	public:

		htmlCalendarImpl();

		virtual ~htmlCalendarImpl() = default;

		virtual void htmlHead(std::ofstream& myFile) override;
		virtual std::string monthBody(const std::string& month) override;
		virtual std::string weekDays(int day, int num, int& weekNum) override;
		virtual bool isLeapYear(int year) override;
		virtual void monthGenerator(std::ofstream& myFile, const std::string& year) override;
		virtual void adjYears(std::ofstream& myFile, std::string& year) override;
		virtual void htmlEnd(std::ofstream& myFile) override;

		static Shared<htmlCalendar> Create();
	private:
		std::string css;
		std::string weekNames;
		std::string calHead;
		const std::string months[12] = { "March", "April", "May", "June",
										"July", "August", "September", "October",
										"November", "December", "January", "february" };
		const int daysNum[12] = { 31,30,31,30,31,31,30,31,30,31,31,28 };
	};

}

