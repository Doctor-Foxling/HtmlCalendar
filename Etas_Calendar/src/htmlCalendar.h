#pragma once

#include "base.h"

namespace Etas {

	class htmlCalendar {
	public:

		virtual ~htmlCalendar() = default;

		virtual void htmlHead(std::ofstream& myFile) = 0;
		virtual std::string monthBody(const std::string& month) = 0;
		virtual std::string weekDays(int day, int num, int& weekNum) = 0;
		virtual bool isLeapYear(int year) = 0;
		virtual void monthGenerator(std::ofstream& myFile, const std::string& year) = 0;
		virtual void adjYears(std::ofstream& myFile, std::string& year) = 0;
		virtual void htmlEnd(std::ofstream& myFile) = 0;
	};

}