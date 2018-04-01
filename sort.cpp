
template <typename T>
void bubble_sort(vector<T>& v) {
    //相邻元素比较与交换，要么最小上浮，要么最大下浮，稳定
    int n = static_cast<int>(v.size());
    if (n <= 1) {
        return;
    }
    int temp; //额外空间 S(n) = O(1)
    //时间复杂度为（n -1 + n -2 + ... + 1 = n(n-1)/2）,即O(n) = n^2
    for (int j = 0; j < n; ++j) {
        //选择相邻元素比较交换
        for (int i = n - 1; i > j; --i) {
            if (v[i] < v[i -1]) {
                temp = v[i -1];
                v[i - 1] = v[i];
                v[i] = temp;
            }
        }
    }
}

template <typename T>
void select_sort(vector<T>& v) {
    //找到未序部分最小值，记录下标，非相邻元素交换，不稳定
    int n = static_cast<int>(v.size());
    if (n <= 1) {
        return;
    }
    int temp, index = 0 , min; //额外空间, 即S(n) = O(1)
    //时间复杂度为（ n - 1 + n - 2 + ... + 1） = n(n -1)/2, 即O(n) = n^2
    for (int i = 1; i < n; ++i) {
        min = v[i -1];
        //选择出最小元素
        for (int j = i; j < n; ++j) {
            if (v[j] < min) {
                min = v[j];
                index = j;
            }
        }
        //交换最小元素，明显减少了交换次数
        if (index != i -1) {
            temp = v[i -1];
            v[i -1] = v[index];
            v[index] = temp;
        }
    }
}

//直接插入排序
//二分插入排序
//shell排序

template <typename T>
void quick_sort(vector<T>& v, int left, int right) {
    //快速排序适用于数字分布均匀，针对有序复杂度达到最坏，即O(n^2),平均情况下为O(nlogn),
    //logn为递归次数, 不稳定排序， 应用了分治法
    int lp = left, rp = right;
    //思想来自于冒泡排序，选择同时小值上浮和大值下沉
    if (lp >= rp) {
        return; //不需要比较了，直接退出
    }
    T key = v[left]; //基准比较对象
    T temp;
    
    //注意while条件，不能写成lp <= rp,若包含lp = rp的话，最会卡在while循环出不来
    //即循环退出条件为lp = rp的时候
    while (lp < rp) {
        //必须从右边头部开始，找到小于基准元素的位置， 注意rp != lp
        while (rp > lp && v[rp] >= key) {
            --rp;
        }
        //后从左边头部开始，找到大于基准元素的位置, 注意rp != rp
        while (rp > lp && v[lp] <= key) {
            ++lp;
        }
        //然后交换lp和rp分别指向的元素, 此时分为两种情况，
        //即lp < rp 或者 lp = rp,交换元素都没有影响, 后者要退出循环
        temp = v[lp];
        v[lp] = v[rp];
        v[rp] = temp;
    }
    //交换基准元素和lp元素的位置，因为lp指向的元素始终比基准元素小，从而将所有元素切换为3个部分
    //因为在最后两个指针相遇的时候，要交换基准数到相遇的位置
    //一般选取第一个数作为基准数，那么就是在左边，所以最后相遇的数要和基准数交换，
    //那么相遇的数一定要比基准数小。所以rp指针先移动才能先找到比基准数小的数
    //若lp先动，就必然导致lp找到一个比基准的大的数字，最后交换的时候就可能发生问题，导致不是有序
    v[left] = v[lp];
    v[lp] = key;
    //快速排序基准元素左边元素
    quick_sort(v, left, lp -1);
    //快速排序基准元素右边元素
    quick_sort(v, lp + 1, right);
}

template<typename T>
void merge(vector<T>& v, int begin, int middle, int end) {
    //对两个有序数组进行合并, 即v[begin, begin+middle)与v[begin+middle, end)合并
    int pivot = begin + middle;
    int i = begin, j = pivot;
    
    vector<T> v1{}; //额外空间
    while (i < pivot && j < end) {
        if (v[i] <= v[j]) {
            v1.push_back(v[i]);
            ++i;
        } else {
            v1.push_back(v[j]);
            j++;
        }
    }
    
    for (int k = i; k < pivot; ++k) {
        v1.push_back(v[k]);
    }
    
    for (int k = j; k < end; ++k) {
        v1.push_back(v[k]);
    }
    for (auto e: v1) {
        v[begin] = e;
        begin += 1;
    }
}

template <typename T>
void merge_sort(vector<T>& v, int begin, int end) {
    //数组区间为[begin, end)
    if (begin >= end) {
        return; //数组没有元素
    }
    int size = end - begin;
    //一个元素时，即为有序数组，退出
    if (size == 1) {
        return;
    }
    int middle = static_cast<int>(size/2);
    merge_sort(v, begin, begin + middle);
    merge_sort(v, begin + middle, end);
    merge(v, begin, middle, end);
}

//最大堆化
template<typename T>
void max_heapify(vector<T>& v, int start, int end) {
    if (start >= end) {
        return;
    }
    int root = start;
    int temp, child;
    while(true) {
        child = 2 * root + 1;
        if (child <= end) {
            //选取最大孩子节点
            if (child + 1 <= end && v[child] < v[child + 1]) {
                child = child + 1;
            }
            //满足条件，就要交换
            if (v[child] >= v[root]) {
                temp = v[root];
                v[root] = v[child];
                v[child] = temp;
                root = child;//对子节点继续
            } else {
                //已经为最大二叉堆，退出
                return;
            }
        } else {
            return; //到了叶子节点了
        }
    }
}

template <typename T>
void head_sort(vector<T>& v) {
    //建立最大堆，从第一个非叶子节点开始
    int n = static_cast<int>(v.size());
    if (n <= 1) {
        return;
    }
    
    int start = static_cast<int>(n/2 - 1);
    
    while (start >= 0) {
        max_heapify(v, start, n - 1);
        --start;
    }
    
    //堆排序，取出堆顶元素，放置到末尾
    int end = n - 1, temp;
    while (end >= 0) {
        temp = v[0];
        v[0] = v[end];
        v[end] = temp;
        
        --end;
        max_heapify(v, 0, end);
        
        for_each(v.begin(), v.end(), [](int i){cout << i << "\t";});
        cout << endl;
    }
}
