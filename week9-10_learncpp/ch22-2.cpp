int main()
{
	int x{};

	// l-value references
	int& ref1{ x }; // A yes
	int& ref2{ 5 }; // B no

	const int& ref3{ x }; // C yes
	const int& ref4{ 5 }; // D yes

	// r-value references
	int&& ref5{ x }; // E no
	int&& ref6{ 5 }; // F yes

	const int&& ref7{ x }; // G no
	const int&& ref8{ 5 }; // H yes

	return 0;
}