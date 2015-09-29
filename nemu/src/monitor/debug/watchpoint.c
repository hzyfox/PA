#include "monitor/watchpoint.h"
#include "monitor/expr.h"

#define NR_WP 32
static WP wp_list[NR_WP];
static WP *head, *free_;
void init_wp_list() {
	int i;
	for(i = 0; i < NR_WP; i ++) {
		wp_list[i].NO = i;
		wp_list[i].next = &wp_list[i + 1];
	}
	wp_list[NR_WP - 1].next = NULL;

	head = NULL;
	free_ = wp_list;
}
WP* get_head(){
	return head;
}

WP* new_wp()
{
    
    WP*temp;
    if(free_==NULL)
    {
        assert(0);
    }
    else if(free_==wp_list+NR_WP-1)
    {
        temp=free_;
        free_=NULL;
    }
    else
    {
        temp=free_;
        free_=free_->next;
    }
    temp->next=head;
    head=temp;
    return temp;
}

void free_wp(int num)
{
    WP*temp,*p;
    temp=head;
    if(head==wp_list+num)
    {
        p=head->next;
        head->next=free_;
        free_=head;
        head=p;

    }
    else
    {
        while(temp!=NULL)
        {
            p=temp;
            temp=temp->next;
            if(temp==wp_list+num)
                break;
        }
        if(temp==NULL){
            printf("NOT FOUND");
            assert(0);
        }
        p->next=temp->next;
        temp->next=free_;
        free_=temp;
    }
}

/* TODO: Implement the functionality of watchpoint */


