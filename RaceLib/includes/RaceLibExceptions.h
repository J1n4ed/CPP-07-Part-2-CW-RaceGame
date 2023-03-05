#include <iostream>

namespace jinx
{

	class WrongVehicleClassException : public std::exception
	{
	public:
		const char* what() const override
		{
			return "Неверный параметр класса тс!\n";
		}
	};

	class ErrorReadingFileForInput : public std::exception
	{
	public:
		const char* what() const override
		{
			return "Неудалось прочитать файл!\n";
		}
	};

} // END OF jinx namespace