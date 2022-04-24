#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         lab3의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("[----------------- [Cho Daehyeon] [2016039075] -----------------]\n");
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {

	if(*h != NULL)		// 헤더노드 h가 NULL이 아닐 경우 freelist 함수를 이용해 메모리 해제
		freeList(*h);

	*h = (headNode*)malloc(sizeof(headNode));	// 헤더노드 h에 메모리 할당
	(*h)->first = NULL;
	return 1;
}

int freeList(headNode* h){

	listNode* p = h->first;		// 첫 번째 노드 p로 지정

	listNode* prev = NULL;		// 삭제할 노드 가리키는 포인터 생성
	while(p != NULL) {			// p가 NULL값이 될 때까지 한 칸씩 뒤로 옮기면서 차례대로 노드 삭제
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);					// 헤더노드 삭제
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}

int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));	// 노드 새로 생성
	node->key = key;		// 노드에 저장할 값 입력
	node->rlink = NULL;		// 양 옆 링크는 NULL로 초기화
	node->llink = NULL;

	if (h->first == NULL)	// 리스트가 비어있을 경우
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;		// 맨 마지막 노드로 이동
	while(n->rlink != NULL) {
		n = n->rlink;
	}
	n->rlink = node;		// 마지막 노드의 뒤에 새로 생성한 노드 연결
	node->llink = n;
	return 0;
}

int deleteLast(headNode* h) {

	if (h->first == NULL)		// 리스트가 비어있을 경우 오류 메시지 출력
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	if(n->rlink == NULL) {		// 리스트에 노드가 하나밖에 없을 때
		h->first = NULL;
		free(n);
		return 0;
	}

	while(n->rlink != NULL) {	// 맨 마지막 노드로 이동
		trail = n;
		n = n->rlink;
	}

	trail->rlink = NULL;	// 맨 마지막 노드 연결 끊기
	free(n);				// 노드 삭제

	return 0;
}

int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));	// 노드 생성
	node->key = key;
	node->rlink = node->llink = NULL;

	if(h->first == NULL)	// 리스트가 비어있을 경우
	{
		h->first = node;
		return 1;
	}

	node->rlink = h->first;	// 새로 생성한 노드의 오른쪽 링크와 기존의 맨 앞 노드 연결 (-> 방향)
	node->llink = NULL;

	listNode *p = h->first;
	p->llink = node;		// 기존의 맨 앞 노드의 왼쪽 링크와 새로 생성한 노드 연결 (<- 방향)
	h->first = node;

	return 0;
}

int deleteFirst(headNode* h) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");	// 리스트가 비어있을 경우 오류 메시지 출력
		return 0;
	}
	listNode* n = h->first;				// 헤더 노드를 앞에서 두번째 노드로 옮기기
	h->first = n->rlink;

	free(n);

	return 0;
}

int invertList(headNode* h) {

	if(h->first == NULL) {		// 리스트가 비어있을 경우 오류 메시지 출력
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){
		trail = middle;			// middle이 가리키는 노드를 trail도 가리키도록 변경(trail을 한칸 앞으로 옮김)
		middle = n;				// n이 가리키는 노드를 middle도 가리키도록 변경
		n = n->rlink;			// n을 한 칸 앞으로 옮기기
		middle->rlink = trail;	// middle 노드의 오른쪽 링크를 middle의 앞 노드를 가리키도록 변경
		middle->llink = n;		// middle 노드의 왼쪽 링크를 middle의 뒤 노드를 가리키도록 변경 
	}

	h->first = middle;			// 맨 뒷 노드를 헤더 노드로 변경

	return 0;
}
/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	if (h->first == NULL)		// 리스트가 비어있을 때
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;		

	while(n != NULL) {
		if(n->key >= key) {			// 입력받은 key와 비교
			if(n == h->first) {		// 입력받은 key가 맨 앞의 key보다 작거나 같을 때
				insertFirst(h, key);	// 맨 앞에 노드 삽입
			} else {
				node->rlink = n;		// 리스트 중간에 노드를 삽입할 때
				node->llink = n->llink;
				n->llink->rlink = node;
			}
			return 0;
		}

		n = n->rlink;
	}

	insertLast(h, key);		// 입력받은 key가 리스트의 모든 key보다 클 때
	return 0;
}

int deleteNode(headNode* h, int key) {

	if (h->first == NULL)	// 리스트가 비어있을 때 오류 메시지 출력
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first;

	while(n != NULL) {
		if(n->key == key) {
			if(n == h->first) { // 첫 번째 노드를 삭제할 때
				deleteFirst(h);
			} else if (n->rlink == NULL){ // 마지막 노드를 삭제할 때
				deleteLast(h);
			} else { // 중간 노드를 삭제할 때
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n);
			}
			return 1;
		}

		n = n->rlink;
	}

	printf("cannot find the node for key = %d\n", key);	// 삭제하려는 key가 없을 때 오류 메시지 출력
	return 1;
}


