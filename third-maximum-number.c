int thirdMax(int* nums, int numsSize) {
    long long first=LLONG_MIN;
    long long second=LLONG_MIN;
    long long third=LLONG_MIN;

    

    for(int i=0;i<numsSize;i++){
        long long x=nums[i];

    if(x==first || x==second || x==third)  continue;

    if(x>first){
        third=second;
        second=first;
        first=x;
    }else if(x>second){
        third=second;
        second=x;
    }else if(x>third){
        third=x;
        }
    }
    return (third==LLONG_MIN)?(int)first:(int)third;
    
}
