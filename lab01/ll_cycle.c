#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    /* your code here */
    node *slow = head;
    node *fast = head;

    while(fast != NULL &&  fast != slow) {
        fast = fast->next;
        if(fast == NULL)
            return 0;
        fast = fast->next;
        slow = slow->next;
    }

    return fast == slow;
}