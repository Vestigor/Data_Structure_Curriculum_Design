/***********************************************************
* File:     ComparisonOfSortingAlgorithms.cpp
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.cn
* Function: Comparison of Sorting Algorithms
* Encoding: UTF-8
* Date:     2024.11.25
* Update:   2024.11.25
***********************************************************/
#include <cassert>
#include <climits>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>

constexpr int min=0;
constexpr int max=std::numeric_limits<int>::max();

int compare_count;


/***********************************************************
* Function Name:   ClearBuffer
* Function:        清理输入缓冲区，重置输入状态
* Input Parameter: 无
* Returned Value:  无
***********************************************************/
void Clear()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<int>::max(),'\n');
}

template<typename T>
void Swap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

/***********************************************************
* Function Name:   Print
* Function:        打印数组内容
* Input Parameter: arr - 待打印的数组
*                  len - 数组的长度
*                  str - 打印前的提示字符串
* Returned Value:  无
***********************************************************/
#ifdef MY_DEBUG
template<typename  T>
void Print(const T arr[],const int len,const char* str)
{
    std::cout<<str<<"\n";
    for(int i=0;i<len;i++) {
        std::cout<<std::setw(12)<<arr[i];
        if((i+1)%10==0&&i+1!=len)
            std::cout<<"\n";
    }
    std::cout<<"\n\n";
}
#endif
/***********************************************************
* Function Name:   BubbleSort
* Function:        实现冒泡排序算法
* Input Parameter: arr - 待排序的数组
*                  len - 数组的长度
* Returned Value:  无
***********************************************************/
template<typename  T>
void BubbleSort(T arr[],const int len)
{
    for(int i=0;i<len-1;i++)
        for(int j=0;j<len-i-1;j++) {
            compare_count++;
            if (arr[j] > arr[j + 1]) {
                Swap(arr[j],arr[j+1]);
            }
        }
}

/***********************************************************
* Function Name:   SelectionSort
* Function:        实现选择排序算法
* Input Parameter: arr - 待排序的数组
*                  len - 数组的长度
* Returned Value:  无
***********************************************************/
template<typename T>
void SelectionSort(T arr[], const int len)
{
    for(int i=0;i<len-1;i++) {
        int minIndex = i;
        for(int j=i+1;j<len;j++) {
            compare_count++;
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        if(minIndex != i) {
            Swap(arr[minIndex],arr[i]);
        }
    }
}

/***********************************************************
* Function Name:   InsertionSort
* Function:        实现插入排序算法
* Input Parameter: arr - 待排序的数组
*                  len - 数组的长度
* Returned Value:  无
***********************************************************/
template<typename T>
void InsertionSort(T arr[], const int len)
{
    for(int i=1;i<len;i++) {
        T temp = arr[i];
        int j=i-1;
        while(j>=0&&arr[j]>temp) {
            compare_count++;
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = temp;
    }
}

/***********************************************************
* Function Name:   ShellSort
* Function:        实现希尔排序算法
* Input Parameter: arr - 待排序的数组
*                  len - 数组的长度
* Returned Value:  无
***********************************************************/
template<typename T>
void ShellSort(T arr[], const int len)
{
    for(int gap=len/2;gap>0;gap/=2) {
        for(int i=gap;i<len;i++) {
            T temp = arr[i];
            int j = i - gap;
            for(;j>=0;j-=gap) {
                compare_count++;
                if(arr[j]>temp) {
                    arr[j + gap] = arr[j];
                }
                else
                    break;
            }
            arr[j + gap] = temp;
        }
    }
}

/***********************************************************
* Function Name:   Partition
* Function:        实现快速排序的分区操作
* Input Parameter: arr - 待排序的数组
*                  low - 分区起始索引
*                  high - 分区结束索引
* Returned Value:  分区后的主元索引
***********************************************************/
template<typename T>
int Partition(T arr[], int low, int high)
{
    T pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        compare_count++;
        if (arr[j] < pivot) {
            Swap(arr[j],arr[++i]);
        }
    }
    Swap(arr[i + 1],arr[high]);
    return i + 1;
}

/***********************************************************
* Function Name:   QuickSort
* Function:        实现快速排序算法
* Input Parameter: arr - 待排序的数组
*                  len - 数组的长度
*                  low - 分区起始索引
*                  high - 分区结束索引
* Returned Value:  无
***********************************************************/
template<typename T>
void QuickSort(T arr[], const int len,int low,int high)
{
    if (low < high) {
        int pi = Partition(arr, low, high);
        QuickSort(arr,len, low, pi - 1);
        QuickSort(arr,len,pi + 1, high);
    }
}

/***********************************************************
* Function Name:   Heapify
* Function:        构建最大堆或维护堆性质
* Input Parameter: arr - 待处理数组
*                  len - 数组长度
*                  i - 当前处理的节点索引
* Returned Value:  无
***********************************************************/
template<typename T>
void Heapify(T arr[], const int len, int i)
{
    int largest = i, left = 2 * i + 1, right = 2 * i + 2;

    compare_count++;
    // 如果左子节点大于当前节点，更新最大值为左子节点
    if (left < len && arr[left] > arr[largest])
        largest = left;

    compare_count++;
    // 如果右子节点大于当前节点，更新最大值为右子节点
    if (right < len && arr[right] > arr[largest])
        largest = right;

    compare_count++;
    // 如果最大值不是当前节点，交换并继续递归
    if (largest != i) {

        Swap(arr[i],arr[largest]);
        // 递归地维护堆性质
        Heapify(arr, len,  largest);
    }
}

/***********************************************************
* Function Name:   HeapSort
* Function:        堆排序算法
* Input Parameter: arr - 待排序数组
*                  len - 数组长度
* Returned Value:  无
***********************************************************/
template<typename T>
void HeapSort(T arr[], const int len)
{
    // 构建最大堆，从最后一个非叶子节点开始调整
    for (int i = len / 2 - 1; i >= 0; i--)
        Heapify(arr, len,i);
    for (int i = len-1; i>0; i--) {
        Swap(arr[0], arr[i]);
        // 重新调整堆，保持堆性质
        Heapify(arr, i, 0);
    }

}

/***********************************************************
* Function Name:   Merge
* Function:        实现归并排序的合并操作
* Input Parameter: arr - 待排序的数组
*                  temp - 临时数组，用于合并
*                  left - 左边起始索引
*                  mid - 中间索引
*                  right - 右边结束索引
* Returned Value:  无
***********************************************************/
template<typename T>
void Merge(T arr[], int left, int mid,int right)
{
    // 将两个已排序的子数组合并为一个有序数组
    int len1 = mid - left + 1, len2 = right - mid, i = 0, j = 0, k = left;
    T *left_arr = new(std::nothrow) T[len1];
    assert(left_arr != nullptr);

    T *right_arr = new(std::nothrow) T[len2];
    assert(right_arr != nullptr);

    for (int i = 0; i < len1; i++) {
        left_arr[i] = arr[left + i];
    }
    for (int i = 0; i < len2; i++) {
        right_arr[i] = arr[mid + 1 + i];
    }
    while (i < len1 && j < len2) {
        compare_count++;
        if (left_arr[i] <= right_arr[j]) {
            arr[k++] = left_arr[i++];
        }
        else {
            arr[k++] = right_arr[j++];
        }
    }
    // 复制剩余的元素
    while (i < len1) {
        compare_count++;
        arr[k++] = left_arr[i++];
    }
    while (j < len2) {
        compare_count++;
        arr[k++] = right_arr[j++];
    }
    delete[] left_arr;
    delete[] right_arr;
}

/***********************************************************
* Function Name:   MergeSort
* Function:        实现归并排序算法
* Input Parameter: arr - 待排序的数组
*                  temp - 临时数组
*                  left - 左边起始索引
*                  right - 右边结束索引
* Returned Value:  无
***********************************************************/
template<typename T>
void MergeSort(T arr[], const int len,int left,int right)
{
    if(left<right) {
        int mid = left + (right - left) / 2;
        MergeSort(arr, len,left, mid);
        MergeSort(arr, len,mid + 1, right);
        Merge(arr, left, mid, right);
    }

}

/***********************************************************
* Function Name:   SortByDigit
* Function:        根据当前数字位对数组进行计数排序
*                  Sorts the array based on the current digit place
* Input Parameter: arr - 待排序数组
*                  len - 数组长度
*                  digit_place - 当前的数字位（如个位、十位）
* Returned Value:  无
***********************************************************/
template<typename T>
void SortByDigit(T arr[],const int len,const int digit_place)
{
    int frequency[10]={0};// 用于存储当前数字位的频率
    // 计算当前位数字的频率
    for(int i=0;i<len;i++)
        ++frequency[(arr[i] / digit_place) % 10];

    // 将频率转换为累积计数，用于确定排序后位置
    for(int i=1;i<10;i++)
        frequency[i]+=frequency[i-1];

    // 创建一个临时数组来存储排序后的结果
    T* output= new(std::nothrow) T[len];
    assert(output!=nullptr);

    // 倒序遍历数组，按照当前位数字进行排序
    for(int i=len-1;i>=0;i--) {
        output[frequency[(arr[i] / digit_place) % 10] - 1] = arr[i];
        --frequency[(arr[i] / digit_place) % 10];
    }
    // 将排序后的结果复制回原数组
    for(int i=0;i<len;i++)
        arr[i]=output[i];

    delete[] output;
}

/***********************************************************
* Function Name:   RadixSort
* Function:        基数排序主函数
*                  Performs radix sort on the array
* Input Parameter: arr - 待排序数组
*                  len - 数组长度
*                  count - 比较次数（引用，用于统计比较的总次数）
* Returned Value:  无
***********************************************************/
template<typename T>
void RadixSort(T arr[], const int len)
{
    // 找到数组中的最大元素，用于确定需要排序的位数
    T max_element=arr[0];
    for(int i = 0; i < len; i++) {
        max_element = max_element > arr[i] ? max_element : arr[i];
    }

    // 从个位开始对每一位数字进行排序
    for(int digit_place = 1; max_element/digit_place>0 ; digit_place*=10) {
        SortByDigit(arr, len,digit_place);
    }

}

/***********************************************************
* Function Name:   Select
* Function:        获取用户输入的算法选项
*                  Prompt the user to select an algorithm option
* Input Parameter: 无
* Returned Value:  用户选择的算法编号（1-9之间的整数）
***********************************************************/
int Select()
{
    double selection;
    while (true) {
        std::cout<<"\n请输入您选择的算法选项：";
        std::cin >> selection;
        // 检查输入是否合法
        if (std::cin.fail() || selection > 9 || selection <= 0 || selection != static_cast<int>(selection)) {
            std::cout << "输入非法，请重新输入！\n";
            Clear();// 清空输入缓冲区，处理 cin 错误状态
            continue;
        }
        Clear();// 清空缓冲区，防止多余字符干扰
        break;
    }
    // 返回合法的整数选项
    return static_cast<int>(selection);
}


/***********************************************************
* Function Name:   Evaluation
* Function:        根据用户选择的排序算法，对数组进行排序并分析算法性能
* Input Parameter: numbers - 原始数组
*                  N - 数组大小
*                  sort_type_name - 排序算法名称数组
* Returned Value:  用户是否继续进行排序（true 继续，false 退出）
***********************************************************/
bool Evaluation(const int numbers[],const int N,const char sort_type_name[8][15])
{

    int selection = Select();
    if (selection == 9)
        return false;

    compare_count=0;

    int* nums= new(std::nothrow) int[N];
    assert(nums != nullptr);
    for(int i=0;i<N;i++)
        nums[i]=numbers[i];

    // 定义计时变量
    clock_t start_time = clock();

    // 根据用户选择调用对应的排序算法
    if (selection == 1)
        BubbleSort(nums, N);
    else if (selection == 2)
        SelectionSort(nums, N);
    else if (selection == 3)
        InsertionSort(nums, N);
    else if (selection == 4)
        ShellSort(nums, N);
    else if (selection == 5)
        QuickSort(nums, N,0,N-1);
    else if (selection == 6)
        HeapSort(nums, N);
    else if (selection == 7)
        MergeSort(nums, N,0,N-1);
    else
        RadixSort(nums, N);
    clock_t end_time=clock();

    // 输出排序结果
    std::cout<<"排序算法: "<<sort_type_name[selection-1]<<"\n";
    std::cout<<"排序时间: "<<(end_time - start_time)/static_cast<double>(CLOCKS_PER_SEC) <<"s\n";
    std::cout<<"比较次数: " << compare_count << "\n";

    // 显示排序后的数组
#ifdef MY_DEBUG
    Print(nums, N, "排序后的数列为：");
#endif
    delete[] nums; // 释放动态分配的数组内存
    return true;
}

/***********************************************************
* Function Name:   ComparisonOfSortingAlgorithms
* Function:        显示界面，根据输入长度初始数组为数组赋随机值
* Input Parameter: 无
* Returned Value:  无
***********************************************************/
void ComparisonOfSortingAlgorithms()
{
    std::cout << "+-------------------------------------------+\n";
    std::cout << "|               排序算法比较                |\n";
    std::cout << "|     Comparison Of Sorting Algorithms      |\n";
    std::cout << "+-------------------------------------------+\n\n";
    double dN;// 用户输入的随机数个数 (double 用于初步验证合法性)
    while (true){
        std::cout << "请输入要产生随机数的个数：\n";
        std::cin>>dN;
        // 输入验证：判断是否为有效的整数
        if (std::cin.fail()  || dN<=0 || dN != static_cast<int>(dN)) {
            std::cout << "输入非法，请重新输入！\n";
            Clear();
            continue;
        }
        Clear();
        break;
    }
    int N = static_cast<int>(dN);// 转换为整数类型
    int* numbers=new(std::nothrow) int[N];// 动态分配数组
    assert(numbers!=nullptr);// 检查内存分配是否成功

    // 随机数生成
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    for(int i=0;i<N;i++)
        numbers[i]=dist(gen);// 为数组填充随机数

#ifdef MY_DEBUG
    Print(numbers,N,"生成的随机数列为：\n");
#endif
    std::cout << "+----------------------------+\n";
    std::cout << "|       1 --- 冒泡排序       |\n";
    std::cout << "|       2 --- 选择排序       |\n";
    std::cout << "|       3 --- 插入排序       |\n";
    std::cout << "|       4 --- 希尔排序       |\n";
    std::cout << "|       5 --- 快速排序       |\n";
    std::cout << "|       6 --- 堆 排 序       |\n";
    std::cout << "|       7 --- 归并排序       |\n";
    std::cout << "|       8 --- 基数排序       |\n";
    std::cout << "|       9 --- 退出程序       |\n";
    std::cout << "+----------------------------+\n";
    char sort_type_name[8][15] = {"冒泡排序", "选择排序", "插入排序", "希尔排序", "快速排序", "堆排序", "归并排序", "基数排序"};
    // 循环调用 Evaluation 函数，根据用户选择进行排序比较
    while(Evaluation(numbers,N,sort_type_name))
        ;

    delete[] numbers;
    std::cout<<"成功推出算法比较系统！\n";
}

/***********************************************************
* Function Name:   main
* Function:        程序入口
* Input Parameter: 无
* Returned Value:  0
***********************************************************/
int main()
{
    ComparisonOfSortingAlgorithms();

    return 0;
}
