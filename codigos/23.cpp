/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists){
        if(lists.empty() or lists.size() == 0) return nullptr;
        while(lists.size() > 1){
            vector<ListNode*> mergedLists;
            for(int i = 0; i < lists.size(); i += 2){
                ListNode* l1 = lists[i];
                ListNode* l2 = (i + 1 < lists.size()) ? lists[i + 1] : nullptr;
                mergedLists.push_back(mergeTwoLists(l1, l2));
            }
            lists = mergedLists;
        }
        return lists[0];
    }   
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2){
        if(l1 == nullptr) return l2;
        if(l2 == nullptr) return l1;
        if(l1->val <= l2->val){
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        } else{
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;            
        }
    }
};
