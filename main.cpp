#include "set.cpp"

int main()
{
	using std::cout;
	using std::string;

	MySet<int> set;

	set.insert(1);
	set.insert(0);
	set.insert(2);
	set.insert(3);
	set.insert(5);
	set.insert(9);
	set.insert(34);  
	set.insert(7);

    cout << "size: " << set.size() << "\n";

    for(auto it = set.begin(); it != set.end(); ++it)
    {
        cout << *it << ", ";
    }

    cout << std::endl;

    for(auto it : set)
    {
        cout << it << ", ";
    }
 
    cout << std::endl;
}