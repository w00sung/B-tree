#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "insertion.h"

#define DEGREE 4




int main()
{
	Node* root = createNode();
	root->N = 0;
	root->isLeaf = true;

	/* 1 번 */
	//insertTree(&root, 20);
	//deleteTree(&root, root, 20);
	//insertTree(&root, 30);
	//printf("30 : %d\n", root->Key[0]);

	/* 2번 */
	//insertTree(&root, 20);
	//insertTree(&root, 30);
	//insertTree(&root, 40);
	//deleteTree(&root, root, 40);
	//printf("20 : %d\n", root->Key[0]);
	//printf("30 : %d\n", root->Key[1]);
	//printf("X : %d\n", root->Key[2]);

	///* 3번 */
	//insertTree(&root, 20);
	//insertTree(&root, 30);
	//insertTree(&root, 40);
	//insertTree(&root, 50);
	//deleteTree(&root, root, 30);
	////printf("40 : %d\n", root->Key[0]);
	////printf("20 : %d\n", root->C[0]->Key[0]);
	////printf("50 : %d\n", root->C[1]->Key[0]);

	///* 4번 */
	//insertTree(&root, 10);
	//deleteTree(&root, root, 40);
	//printf("20 : %d\n", root->Key[0]);
	//printf("10 : %d\n", root->C[0]->Key[0]);
	//printf("50 : %d\n", root->C[1]->Key[0]);

	///* 5번 */
	//deleteTree(&root, root, 20);
	//printf("10 : %d\n", root->Key[0]);
	//printf("50 : %d\n", root->Key[1]);





	/* squid 작성 예제 */

	insertTree(&root, 10);
	insertTree(&root, 200);
	insertTree(&root, 300);
	insertTree(&root, 400);
	insertTree(&root, 500);
	insertTree(&root, 0);
	insertTree(&root, 450);
	//printf("450 : %d\n", root->C[2]->Key[0]);
	insertTree(&root, 600);
	//printf("600 : %d\n", (root->C[2]->Key[2]));
	insertTree(&root, 700);
	//printf("300 : %d\n", root->C[1]->Key[0]);
	//printf("400 : %d\n", root->Key[1]);
	//printf("450 : %d\n", root->C[2]->Key[0]);
	//printf("500 : %d\n", (root->Key[2]));
	//printf("600 : %d\n", (root->C[3]->Key[0]));
	//printf("700 : %d\n", (root->C[3]->Key[1]));
	insertTree(&root, 800);
	//printf("800 : %d\n", (root->C[1]->C[1]->Key[2]));
	insertTree(&root, 900);
	//printf("400 : %d\n", root->Key[0]);
	//printf("900 : %d\n", root->C[1]->C[2]->Key[1]);
	
	//deleteTree(&root, root, 400);
	//printf("500 : %d\n", root->Key[0]);
	//printf("700 : %d\n", root->C[1]->Key[0]);
	//printf("450 : %d\n", root->C[1]->C[0]->Key[0]);
	//printf("600 : %d\n", root->C[1]->C[0]->Key[1]);


	deleteTree(&root, root, 200);
	//printf("500 : %d\n", root->Key[0]);
	//printf("10 : %d\n", root->C[0]->Key[0]);
	//printf("400 : %d\n", root->C[0]->Key[1]);
	//printf("700 : %d\n", root->C[1]->Key[0]);
	//printf("0 : %d\n", root->C[0]->C[0]->Key[0]);
	//printf("450 : %d\n", root->C[0]->C[2]->Key[0]);
	//printf("600 : %d\n", root->C[1]->C[0]->Key[0]);
	//printf("800 : %d\n", root->C[1]->C[1]->Key[0]);

	deleteTree(&root, root, 0);
	//printf("400 : %d\n", root->C[0]->Key[0]);
	//printf("10 : %d\n", root->C[0]->C[0]->Key[0]);
	//printf("300 : %d\n", root->C[0]->C[0]->Key[1]);

	deleteTree(&root, root, 900);
	printf("400 : %d\n", root->Key[0]);
	printf("500 : %d\n", root->Key[1]);
	printf("700 : %d\n", root->Key[2]);
	printf("10 : %d\n", root->C[0]->Key[0]);
	printf("300 : %d\n", root->C[0]->Key[1]);
	printf("450 : %d\n", root->C[1]->Key[0]);
	printf("600 : %d\n", root->C[2]->Key[0]);
	printf("900 : %d\n", root->C[3]->Key[0]);




	return 0;
}