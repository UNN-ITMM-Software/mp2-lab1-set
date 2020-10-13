#include <gtest.h>
#include<conio.h>
#include"tbitfield.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
	 RUN_ALL_TESTS();

	 TBitField bf1(10);
	 
	 bf1.SetBit(1);
	 bf1.SetBit(2);
	 bf1.SetBit(4);
	 bf1.SetBit(5);
	 bf1.SetBit(6);
	 bf1.SetBit(8);

	 cout << "-------------------------------\n";
	 bf1.all_elem_degree_of_number(2);
	 cout << "-------------------------------\n";
	 bf1.all_elem_multiple(2);

	 _getch();
	 return 0;
}
