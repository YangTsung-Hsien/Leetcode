#include <stdio.h>
#include <math.h>


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define HASH_SIZE 10000
typedef struct {
	int idx;
	struct element* next;
}element;

int findElement(int* nums, element* hashTable, int inputNum) 
{
    
    int hashValue = abs(inputNum % HASH_SIZE);
    
    if (hashTable[hashValue].idx == -1)
    {
        return -1;
    }
    else
    {
        if (nums[hashTable[hashValue].idx] == inputNum)
        {
            return hashTable[hashValue].idx;
        }
        else
        {
            element* nextElement = hashTable[hashValue].next;
            while(nextElement != NULL) 
            {
                if (nums[nextElement->idx] == inputNum)
                {
                    return nextElement->idx;
                }
            }
        }
    }
    
    return -1; 
}
void addElement(element* hashTable, int inputNum, int inputIdx)
{
    
    int hashValue = abs(inputNum % HASH_SIZE);
    if (hashTable[hashValue].idx == -1)
    {
        hashTable[hashValue].idx = inputIdx;
    }
    else
    {
        element* nextElement = hashTable[hashValue].next;
        element* newElement = calloc(1, sizeof(element));
        newElement->idx = inputIdx;
        
        while(nextElement != NULL)
        {
            nextElement = nextElement->next;
        }
        // nextElement = newElement;
        newElement->next = hashTable[hashValue].next;
        hashTable[hashValue].next = newElement;

    }
}
int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
    *returnSize = 2;
    int* output = (int*)calloc(*returnSize, sizeof(int));

    element hashTable[HASH_SIZE];
    memset(hashTable, 0, sizeof(element) * HASH_SIZE);
    for(int i = 0; i < HASH_SIZE; i++)
    {
        hashTable[i].idx = -1;
    }
    
    
    for (int i = 0; i < numsSize; i++)
    {
        int remain = target - nums[i];
        int remainIdx = findElement(nums, hashTable, remain);
        if (remainIdx != -1 && remainIdx != i)
        {
            output[0] = i;
            output[1] = remainIdx;
            return output;
            
        }

        if (findElement(nums, hashTable, nums[i]) == -1)
        {
            addElement(hashTable, nums[i], i);
        }
  
    }
    
    return output;
    
}



int main(void) {
  int nums[4] = {2,7,11,15};
  int returnSize = 2;
  int* result = twoSum(nums, 4, 9, &returnSize);
  printf("%d, %d", result[0], result[1]);
  return 0;
}