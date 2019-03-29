#include "set.cpp"

int main()
{
	using std::cout;
	using std::string;

	MySet<int> set;

	set.insert(8);
	set.insert(4);
	set.insert(10);  
	set.insert(10);
	set.insert(2);  
	set.insert(5); 
	set.insert(9);    
	set.insert(12);
	set.insert(12);      
	set.insert(1);  
	set.insert(14);   
	set.insert(7);
    
    set.remove(4);    
    set.remove(12);  
    set.remove(14);  

    for(auto it = set.begin(); it != set.end(); ++it)
    {  
        cout << *it << ", ";
    }  
      
    cout << std::endl;  
 
    auto set2 = set;
    cout  << "size: " << set.size() << " set: " << set;
    cout  << "size: " << set2.size() << " set2: " <<  set2;

    for(const auto& it : set) 
    {     
        cout << it << ", ";  
    }
    cout << std::endl;
   
    for(auto it = set2.begin(); it != set2.end(); ++it)
    {   
        cout << *it << ", "; 
    }

    cout << "\n";
} 