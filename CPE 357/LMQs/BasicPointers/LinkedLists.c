// Remove the second node from the list, or if there are not two nodes, leave the list unchanged.
void RemoveSecond(Node *head) {
   Node *temp;
   
	if(head && head ->next)
	{
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
}



// Insert a new node as the second one on the list, if there is already a node, or 
// as the only node on the list, otherwise.
Node *AddSecond(Node *head, int data) {
   Node *temp;

    temp = malloc(sizeof(Node));
	temp->data = data;
	temp->next = NULL;

	if(head) {
	   temp->next = head->next;
	   head->next = temp;
	} else {
	   head = temp;
	}

	return head;

}

//swapping pairs
Node *SwapPairs(Node *head) {
    Node *cur = head, *next, *temp;

   
    head = cur->next;
	while(cur && cur->next)
	{
	   next = cur->next;
	   cur->next = next->next;
	   next->next = cur;
	   temp = cur;
	   cur = cur->next;

	   if(cur && cur->next)
		  temp->next = cur->next;
	}
	return head;

}




