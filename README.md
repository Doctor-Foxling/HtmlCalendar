# HtmlCalendar

## File Structure
<img src=https://github.com/Doctor-Foxling/HtmlCalendar/blob/master/Image/FileStructure.PNG>

This project is a Gregorian calendar generator for a given year that generates static ```html``` files for the years that are passed into the ```command-line``` of the program. For each year that is passed into the ```command-line``` it generates a ```.html``` file that contains the calendar for that year the years before and after it.

The gnenerated ```.html``` file has the following format:

<img src=https://github.com/Doctor-Foxling/HtmlCalendar/blob/master/Image/htmlSample.PNG>

## Building the Project

Premake5 is used to build the project for ```visual_Studio-2019```. To build the project binaries:
<ul>
<li>Run the ```GenProjects.bat``` </li>
<li>The batch file would run premake5.exe using the ```premake5.lua``` script</li> 
<li>Open the generated ```.sln``` file in Visual_Studio-2019</li>
<li>Build the project</li>
</ul>

## Code

The program is written with scalability in mind. The htmlCalendar class itself is an abstract interface class that can be implemented differently if needed (e.g., For other types calendars, like Julian etc.).

```c++
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
```

The namesake class with the ```Impl``` suffix provides the implementation for the htmlCalendar generation.

The <a href=https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week#Disparate_variation>```Disparate Variation```</a> formula is used to predict the week day for a given date/year.

<img src=https://wikimedia.org/api/rest_v1/media/math/render/svg/4eaab594fb0c6eb1750c61b90de736a73fe821c0>

However, the formula doesn't account for the fact that the calculated ```W``` values can be negative. The program uses a simple fix for that, which is that when the values are negative, it adds 7 to that value, producing the correct number for the week day.

See the function ```htmlCalendarImpl::monthGenerator(std::ofstream& myFile, const std::string& year)``` for how the formula is used

The program also keeps into account ```leap years``` using the following check:

```c++
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
          return true;
  }
  return false;
}
```


