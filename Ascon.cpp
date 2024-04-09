
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

//char S[16] = { 4,31,26,9,27,8,29,6,30,7,0,17,16,1,22,15 };     //stuck-at-0 fault on 1st bit           //The intersection is 2
//char S[16] = { 11,20,21,2,5,18,3,28,19,14,13,24,12,25,10,23 };     //stuck-at-1 fault on 1st bit
//char S[16] = { 4,11,26,21,27,5,29,3,30,19,0,13,16,12,22,10 };     //stuck-at-0 fault on 2nd bit        //The intersection is 2
//char S[16] = { 31,20,9,2,8,18,6,28,7,14,17,24,1,25,15,23 };     //stuck-at-1 fault on 2nd bit    
char S[16] = { 4,11,31,20,27,5,8,18,30,19,7,14,16,12,1,25 };     //stuck-at-0 fault on 3rd bit           //The intersection is 1
//char S[16] = { 26,21,9,2,29,3,6,28,0,13,17,24,22,10,15,23 };     //stuck-at-1 fault on 3rd bit
//char S[16] = { 4,11,31,20,26,21,9,2,30,19,7,14,0,13,17,24 };     //stuck-at-0 fault on 4th bit         //The intersection is 4
//char S[16] = { 27,5,8,18,29,3,6,28,16,12,1,25,22,10,15,23 };     //stuck-at-1 fault on 4th bit
//char S[16] = { 4,11,31,20,26,21,9,2,27,5,8,18,29,3,6,28 };     //stuck-at-0 fault on 5th bit           //The intersection is 4
//char S[16] = { 30,19,7,14,0,13,17,24,16,12,1,25,22,10,15,23 };     //stuck-at-1 fault on 5th bit

// Improved S-box
//char S[16] = { 4,25,31,6,26,7,9,16,27,5,8,18,15,17,20,14 };   //stuck-at-0 fault on 5th bit
//char S[16] = { 30,19,21,28,0,13,3,10,2,12,1,11,22,24,29,23 };   //stuck-at-1 fault on 5th bit
//char S[16] = { 4,25,31,6,26,7,9,16,30,19,21,28,0,13,3,10 };   //stuck-at-0 fault on 4th bit
//char S[16] = { 27,5,8,18,15,17,20,14,2,12,1,11,22,24,29,23 };   //stuck-at-1 fault on 4th bit
//char S[16] = { 4,25,31,6,27,5,8,18,30,19,21,28,2,12,1,11 };   //stuck-at-0 fault on 3rd bit
//char S[16] = { 26,7,9,16,15,17,20,14,0,13,3,10,22,24,29,23 };   //stuck-at-1 fault on 3rd bit
//char S[16] = { 4,25,26,7,27,5,15,17,30,19,0,13,2,12,22,24 };   //stuck-at-0 fault on 2nd bit
//char S[16] = { 31,6,9,16,8,18,20,14,21,28,3,10,1,11,29,23 };   //stuck-at-1 fault on 2nd bit
//char S[16] = { 4,31,26,9,27,8,15,20,30,21,0,3,2,1,22,29 };   //stuck-at-0 fault on 1st bit
//char S[16] = { 25,6,7,16,5,18,17,14,19,28,13,10,12,11,24,23 };   //stuck-at-1 fault on 1st bit

// Function: Find the intersection of two sets
std::vector<int> calculateIntersection(const std::vector<int>& set1, const std::vector<int>& set2) {
	// If two out-of-order sets execute this function, they must be sorted first.
	// 
	//// Duplicate the collection so as not to modify the original input.
	//std::vector<int> sortedSet1 = set1;
	//std::vector<int> sortedSet2 = set2;

	//// Sort the sets.
	//std::sort(sortedSet1.begin(), sortedSet1.end());
	//std::sort(sortedSet2.begin(), sortedSet2.end());

	// Create a container for intersection.
	std::vector<int> intersection;

	// Use set_intersection to compute the intersection.
	std::set_intersection(
		set1.begin(), set1.end(),
		set2.begin(), set2.end(),
		std::back_inserter(intersection)
	);

	return intersection;
}


int main()
{
	int out;
	int flag;
	int Num;

	// Defines a three-dimensional variable length array: 16¡Á4¡Á?
	std::vector<std::vector<std::vector<int>>> differ_LSB_2(16, std::vector<std::vector<int>>(4));

	// Used to store the sequence number of the column containing the element Num.
	int columnsWith_Num[16][16] = { 0 };
	int counti[16][4] = { 0 };
	//	int flag;

	// Solution of differential equations
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 32; j++) {
			for (int in = 0; in < 16; in++) {
				out = S[in] ^ S[i ^ in];
				if (j == out) {
					differ_LSB_2[i][j % 4].push_back(in);
					counti[in][j % 4]++;
				}
			}
			std::sort(differ_LSB_2[i][j % 4].begin(), differ_LSB_2[i][j % 4].end()); // Reorder the collection (important)
		}
	}

	for (int i = 0; i < 16; ++i) {
		for (int j = 0; j < 4; ++j) {
			std::cout << "\n differ_LSB_2[" << i << "][" << j << "]: ";

			// If the current cell contains the element Num, record the serial number of the column.
			for (int Num = 0; Num < 16; ++Num) {
				if (std::find(differ_LSB_2[i][j].begin(), differ_LSB_2[i][j].end(), Num) != differ_LSB_2[i][j].end()) {
					columnsWith_Num[Num][i] = j;
				}
			}

			// Prints the element in the current cell.
			for (int k = 0; k < differ_LSB_2[i][j].size(); ++k) {
				std::cout << differ_LSB_2[i][j][k] << ",";
			}
		}
		std::cout << std::endl;
		for (int k = 0; k < 4; ++k) {
			std::cout << counti[i][k] << ",";
		}
	}

	std::cout << std::endl;

	// Output the fastest reduced set of possible input values Num for each S-box (achieved with two fault injections |H| : 16->1).
	//for (int Num = 0; Num < 16; ++Num) {
	//	std::cout << "\nThe optimal fault trail when the S-box input value is " << Num << ": \n";
	//	for (int i = 0; i < 16; ++i) {               //First fault injection
	//		for (int j = 0; j < 16; ++j) {           //Second fault injection
	//			if (calculateIntersection(differ_LSB_2[i][columnsWith_Num[Num][i]], differ_LSB_2[j][columnsWith_Num[Num][j]]).size() == 1) {
	//				std::cout << i << " -> " << j << "\t";
	//			}
	//		}
	//		std::cout << "\n";
	//	}
	//	std::cout << "\n";
	//}

	std::vector<int> temp;
	std::vector<int> temp1;
	std::vector<int> temp2;
	std::vector<int> temp3;
	std::vector<int> temp4;
	std::vector<int> temp5;
	std::vector<int> temp6;
	unsigned int count;
	Num = 1;
	int X[16] = { 0 };

	// The corresponding fastest reduction set when the output is fixed Num (that is, three fault injections can achieve |H|: 16->?->1).
	//for (int Num = 0; Num < 16; ++Num) {
	//	std::cout << "\nThe optimal fault trail when the S-box input value is " << Num << ": \n";
	//	for (int i = 0; i < 16; ++i) {                 //First fault injection
	//		for (int j = 0; j < 16; ++j) {               //Second fault injection
	//			temp = calculateIntersection(differ_LSB_2[i][columnsWith_Num[1][i]], differ_LSB_2[j][columnsWith_Num[1][j]]);
	//			for (int k = 0; k < 16; ++k) {           //Third fault injection
	//				if (calculateIntersection(temp, differ_LSB_2[k][columnsWith_Num[1][k]]).size() == 1) {
	//					std::cout << i << " -> " << j << " -> " << k << "\t";
	//				}
	//			}
	//		}
	//		std::cout << std::endl;
	//	}
	//}
	//std::cout << std::endl;

	// For a single S-box, the number of fault trails that can obtain a unique solution after 'count' fault injections.
	//for (int Num = 0; Num < 16; ++Num) {
	//	std::cout << "\nThe fault trails when the S-box input value is " << Num << " after two injections:\n"; //36
	//	count = 0;
	//	for (int i = 0; i < 16; ++i) {               //First fault injection
	//		for (int j = 0; j < 16; ++j) {               //Second fault injection
	//			if (calculateIntersection(differ_LSB_2[i][columnsWith_Num[Num][i]], differ_LSB_2[j][columnsWith_Num[Num][j]]).size() == 2) {
	//				count++;
	//				std::cout << i << " -> " << j << "\t";
	//			}
	//		}
	//	}
	//	std::cout << count << " ";
	//}

	for (int Num = 0; Num < 16; ++Num) {
		std::cout << "\nThe fault trails when the S-box input value is " << Num << " after three injections:\n"; //1764
		count = 0;
		for (int i = 0; i < 16; ++i) {               //First fault injection
			for (int j = 0; j < 16; ++j) {               //Second fault injection
				temp = calculateIntersection(differ_LSB_2[i][columnsWith_Num[Num][i]], differ_LSB_2[j][columnsWith_Num[Num][j]]);
				for (int k = 0; k < 16; ++k) {           //Third fault injection
					if (calculateIntersection(temp, differ_LSB_2[k][columnsWith_Num[Num][k]]).size() == 1) {
						X[i]++;
						std::cout << i << " -> " << j << " -> " << k << "\t";
					}
				}
			}
			std::cout << X[i] << " ";
			std::cout << std::endl;
			std::cout << std::endl;
		}
		std::cout << count << " ";
	}

	// When the number of fault injections is greater than 3, all fault trails will no longer be displayed; instead, specific fault values will be analyzed to discover patterns (all comments below).
	// 
////	std::cout << "\nThe fault trails when the S-box input value is " << Num << " after 4 injections:\n"; //58276
//	count = 0;
////	for (int i = 0; i < 16; ++i) {                 //First fault injection
//		int i=2;
////		for (int j = 0; j < 16; ++j) {             //Second fault injection
//		int j = 9;
//			temp = calculateIntersection(differ_LSB_2[i][columnsWith_Num[Num][i]], differ_LSB_2[j][columnsWith_Num[Num][j]]);
//			for (int k = 0; k < 16; ++k) {             //Third fault injection
//				temp1 = calculateIntersection(temp, differ_LSB_2[k][columnsWith_Num[Num][k]]);
//				for (int l = 0; l < 16; ++l) {         //The fourth fault injection
//					if (calculateIntersection(temp1, differ_LSB_2[l][columnsWith_Num[Num][l]]).size() == 1) {
//						count++;
//						X[j]++;
//						std::cout << j << " -> " << k << " -> " << l << "\t";
//					}
//				}
//			}
//			std::cout << X[j] << " ";
//			std::cout << std::endl;
//			std::cout << std::endl;
////		}
//		std::cout << std::endl; 



//	//for (int Num = 0; Num < 16; ++Num) {
//		//std::cout << "\nThe fault trails when the S-box input value is " << Num << " after 5 injections:\n"; //1041316
//		count = 0;
////		for (int i = 0; i < 16; ++i) {                      //First fault injection
//		int i = 2;
////			for (int j = 0; j < 16; ++j) {                  //Second fault injection
//		int j = 9;
//				temp = calculateIntersection(differ_LSB_2[i][columnsWith_Num[Num][i]], differ_LSB_2[j][columnsWith_Num[Num][j]]);
//	//			for (int k = 0; k < 16; ++k) {                  //Third fault injection
//				int k =11;
//					temp1 = calculateIntersection(temp, differ_LSB_2[k][columnsWith_Num[Num][k]]);
//					for (int l = 0; l < 16; ++l) {              //The fourth fault injection
//						temp2 = calculateIntersection(temp1, differ_LSB_2[l][columnsWith_Num[Num][l]]);
//						for (int m = 0; m < 16; ++m) {          //The fifth fault injection
//							if (calculateIntersection(temp2, differ_LSB_2[m][columnsWith_Num[Num][m]]).size() == 1) {
//							count++;
//							X[l]++;
//							std::cout  << k << " -> " << l << " -> " << m << "\t";
//							}
//						}
//						std::cout << X[l] << " ";
//						std::cout << std::endl;
//						std::cout << std::endl;
//					}
//
////				}
//			
//	//		}
//
//			std::cout << count << " ";
//			std::cout << std::endl;
	//	}
	//}

	//for (int Num = 0; Num < 16; ++Num) {
		//count = 0;
		//std::cout << "\nThe fault trails when the S-box input value is " << Num << " after 6 injections:\n"; //16769956
		//for (int i = 0; i < 16; ++i) {               //First fault injection
		//	for (int j = 0; j < 16; ++j) {           //Second fault injection
		//		temp = calculateIntersection(differ_LSB_2[i][columnsWith_Num[Num][i]], differ_LSB_2[j][columnsWith_Num[Num][j]]);
		//		for (int k = 0; k < 16; ++k) {           //Third fault injection
		//			temp1 = calculateIntersection(temp, differ_LSB_2[k][columnsWith_Num[Num][k]]);
		//			for (int l = 0; l < 16; ++l) {           //The fourth fault injection
		//				temp2 = calculateIntersection(temp1, differ_LSB_2[l][columnsWith_Num[Num][l]]);
		//				for (int m = 0; m < 16; ++m) {           //The fifth fault injection
		//					temp3 = calculateIntersection(temp2, differ_LSB_2[m][columnsWith_Num[Num][m]]);
		//					for (int n = 0; n < 16; ++n) {           //The sixth fault injection
		//						if (calculateIntersection(temp3, differ_LSB_2[n][columnsWith_Num[Num][n]]).size() == 1) {
		//						count++;
		//						X[i]++;
		//						//std::cout << i << " -> " << j << " -> " << k << " -> " << l << " -> " << m << " -> " << n << "\t";
		//						}
		//					}
		//				}
		//			}
		//		}
		//	}
		//	std::cout << X[i] << " ";
		//	std::cout << std::endl;
		//	std::cout << std::endl;
		//}
		//std::cout << count << " ";
	//}
	// 
	//unsigned long w = 0;
	//for (int Num = 0; Num < 16; ++Num) {
		//std::cout << "\nThe fault trails when the S-box input value is " << Num << " after 7 injections:\n"; 
		//for (int i = 0; i < 16; ++i) {               //First fault injection
		//	for (int j = 0; j < 16; ++j) {           //Second fault injection
		//		temp = calculateIntersection(differ_LSB_2[i][columnsWith_Num[Num][i]], differ_LSB_2[j][columnsWith_Num[Num][j]]);
		//		for (int k = 0; k < 16; ++k) {           //The third fault injection
		//			temp1 = calculateIntersection(temp, differ_LSB_2[k][columnsWith_Num[Num][k]]);
		//			for (int l = 0; l < 16; ++l) {           //The fourth fault injection
		//				temp2 = calculateIntersection(temp1, differ_LSB_2[l][columnsWith_Num[Num][l]]);
		//				for (int m = 0; m < 16; ++m) {           //The fifth fault injection
		//					temp3 = calculateIntersection(temp2, differ_LSB_2[m][columnsWith_Num[Num][m]]);
		//					for (int n = 0; n < 16; ++n) {           //The sixth fault injection
		//						temp4 = calculateIntersection(temp3, differ_LSB_2[n][columnsWith_Num[Num][n]]);
		//						for (int o = 0; o < 16; ++o) {           //The seventh fault injection
		//							if (calculateIntersection(temp4, differ_LSB_2[o][columnsWith_Num[Num][o]]).size() == 1) {
		//								w++;
		//								X[i]++;
		//							}
		//						}
		//					}
		//				}
		//			}
		//		}
		//	}
		//	std::cout << X[i] << " ";
		//	std::cout << std::endl;
		//	std::cout << std::endl;
		//}
	//	std::cout << w << " ";
	//}

	//std::cout << "\nThe fault trails when the S-box input value is " << Num << " after 8 injections:\n"; 
	//for (int i = 1; i < 16; ++i) {               //First fault injection
	//	for (int j = 0; j < 16; ++j) {           //Second fault injection
	//		temp = calculateIntersection(differ_LSB_2[i][columnsWith_Num[Num][i]], differ_LSB_2[j][columnsWith_Num[Num][j]]);
	//		for (int k = 0; k < 16; ++k) {           //The third fault injection
	//			temp1 = calculateIntersection(temp, differ_LSB_2[k][columnsWith_Num[Num][k]]);
	//			for (int l = 0; l < 16; ++l) {           //The fourth fault injection
	//				temp2 = calculateIntersection(temp1, differ_LSB_2[l][columnsWith_Num[Num][l]]);
	//				for (int m = 0; m < 16; ++m) {           //The fifth fault injection
	//					temp3 = calculateIntersection(temp2, differ_LSB_2[m][columnsWith_Num[Num][m]]);
	//					for (int n = 0; n < 16; ++n) {           //The sixth fault injection
	//						temp4 = calculateIntersection(temp3, differ_LSB_2[n][columnsWith_Num[Num][n]]);
	//						for (int o = 0; o < 16; ++o) {           //The seventh fault injection
	//							temp5 = calculateIntersection(temp4, differ_LSB_2[o][columnsWith_Num[Num][o]]);
	//							for (int p = 0; p < 16; ++p) {           //The eighth fault injection
	//								if (calculateIntersection(temp5, differ_LSB_2[p][columnsWith_Num[Num][p]]).size() == 1) {
	//									w++;
	//									X[i]++;
	//								}
	//							}
	//						}
	//					}
	//				}
	//			}
	//		}
	//	}
	//	std::cout << X[i] << " ";
	//	std::cout << std::endl;
	//	std::cout << std::endl;
	//}
	//std::cout << w << " ";

	system("pause");
	return 0;
}