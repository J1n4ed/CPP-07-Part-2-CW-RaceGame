#include <iostream>

export module jinx_exceptions;

export namespace jinx
{

	class WrongVehicleClassException : public std::exception
	{
	public:
		const char* what() const override
		{
			return "Неверный параметр класса тс!\n";
		}
	};

} // END OF jinx namespace