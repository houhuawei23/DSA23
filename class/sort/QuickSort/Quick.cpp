#include <iostream>
#include <random>

using namespace std;

void QuickSort(int *arr, int left, int right);
int Partition(int *arr, int left, int right);
void Shuffle(int *arr, int n);

void QuickSort(int *arr, int left, int right)
{
    if (left >= right)
        return;
    int p = Partition(arr, left, right);
    QuickSort(arr, left, p - 1);
    QuickSort(arr, p + 1, right);
}

int Partition(int *arr, int left, int right)
{
    int pivot = arr[left];
    int i = left + 1, j = right;
    while (i <= j)
    {
        while (i <= j && arr[i] <= pivot)
            i++;
        while (i <= j && arr[j] > pivot)
            j--;
        if (i < j)
            swap(arr[i], arr[j]);
    }
    swap(arr[left], arr[j]); // j is the final position of pivot
    return j;
}
/*
该代码实现了一个洗牌算法，将数组 arr 中的元素随机打乱。

具体实现中，需要使用随机数生成器生成随机数，根据 C++ 标准库的定义，random_device 类是一种产生随机数的设备，
mt19937 类是一个以 Mersenne Twister 算法为基础的随机数引擎（即生成伪随机数的一个算法），
uniform_int_distribution<> 类则是用于生成一个整型均匀分布的随机数分布器。

函数的参数 arr 指向要进行洗牌的数组，n 表示数组的大小。其中 rd() 会创建一个 random_device 实例，
它会以真正的物理设备为基础，生成随机数种子，然后传递给 mt19937 引擎实例 gen。接着，循环从数组的第一个元素开始，
每次选择一个随机位置 r 并用 swap 函数交换 arr[i] 和 arr[r]，以实现随机打乱数组元素的目的。
在每次循环中，需要调用 uniform_int_distribution 实例的 dis(gen) 方法以获得一个在 i 和 n-1 之间的随机整数。
*/
void Shuffle(int *arr, int n)
{
    random_device rd;
    mt19937 gen(rd());
    for (int i = 0; i < n; i++)
    {
        uniform_int_distribution<> dis(i, n - 1);
        int r = dis(gen);
        swap(arr[i], arr[r]);
    }
}
// test
int main()
{
    int arr[] = {2,3,7,6,2,3,5522,3662,154,875,33,452,21};
    int len = 13;
    cout<<"Before sort:"<<endl;
    for(int i = 0; i <len; i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    Shuffle(arr, len);
    QuickSort(arr, 0, len-1);
    printf("After sorted:\n");
    for(int i = 0; i < len; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}